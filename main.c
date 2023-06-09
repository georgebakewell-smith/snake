#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<time.h>

#define WIDTH 20
#define HEIGHT 10
#define SIZE 200

struct Point{
    int x;
    int y;
};

struct Snake{

    struct Point head;
    struct Point tail;
    struct Point *body;
    char direction;
    int length;
};

char screen[SIZE];
const int maxScore = SIZE - 2*WIDTH - 2*HEIGHT + 2;

void initScreen(struct Snake *snake);
void placeFood(struct Point *food, struct Snake *snake);
struct Snake *initSnake();
void drawScreen();
char getInput();
struct Snake *updateSnake(struct Snake *snake,char input, int *hasEaten);
int collisionDetection(struct Snake *snake);
int isWin(struct Snake *snake, struct Point *food);
void freeAll(struct Snake *snake, struct Point *food);
int main()
{
    int gameover = 0, hasEaten = 0, score = 0, timeInt = 1000;
    char input;
    struct Point *food = (struct Point *)malloc(sizeof(struct Point));

    struct Snake *snake = initSnake();

    initScreen(snake);

    placeFood(food,snake);

    while(gameover!=1){


        input = getInput();
        updateSnake(snake,input,&hasEaten);
        if(collisionDetection(snake)){
            printf("Final score: %d", score);
            Sleep(5000);    //Sleep to process the loss
            break;
        }
        drawScreen();
        if(isWin(snake,food)){
            hasEaten = 1;
            score++;
            timeInt = 500 - score*(500-10)/maxScore;
            if(score==maxScore){
                printf("Congratulations, you won\n");
                break;
            }
        }

        Sleep(timeInt);

    }

    freeAll(snake,food);
    return 0;
}

void freeAll(struct Snake *snake, struct Point *food){
    free(food);
    free(snake->body);
    free(snake);
}

void placeFood(struct Point *food, struct Snake *snake){
    srand(time(NULL));
    int freeSpace = maxScore - snake->length + 2, randPosition, i=0;   //Account for spaces taken up by snake and borders
    randPosition = rand()% freeSpace;

    while(i<SIZE){
        if(screen[i] != ' '){
            randPosition += 1;
        }
        if(i==randPosition){
            screen[i] = '#';
            food->x = i%WIDTH;
            food->y = i/WIDTH;
            break;
        }
        i++;
    }

}

void initScreen(struct Snake *snake){

    for(int i=0;i<SIZE;i++){
        if(i<WIDTH||i>SIZE-WIDTH-1){
            screen[i] = '=';
        }else if(i%WIDTH==0||i%WIDTH==WIDTH-1){
            screen[i] = '|';
        } else{
            screen[i] = ' ';
        }
    }
    screen[snake->head.y*WIDTH+snake->head.x] = '@';
    screen[snake->tail.y*WIDTH+snake->tail.x] = '@';

}

void drawScreen(){
    system("cls");
    for(int i=0;i<HEIGHT;i++){

        for(int j=0;j<WIDTH;j++){
            printf("%c",screen[i*WIDTH+j]);
        }
        printf("\n");
    }
}

struct Snake *initSnake(){
    struct Snake *snake = (struct Snake*)malloc(sizeof(struct Snake));


    snake->tail.x = floor(WIDTH/2)-1;
    snake->tail.y = floor(HEIGHT/2)-1;
    snake->head.x = floor(WIDTH/2);
    snake->head.y = floor(HEIGHT/2)-1;

    snake->direction = 'R';
    snake->length = 2;
    snake->body = (struct Point*)malloc((snake->length)*sizeof(struct Point));
    snake->body[0].x = snake->head.x;
    snake->body[0].y = snake->head.y;
    snake->body[1].x = snake->tail.x;
    snake->body[1].y = snake->tail.y;

    return snake;

}

char getInput(){
    char c;
    if(kbhit()){
        c = getch();
    }

    return c;
}

struct Snake *updateSnake(struct Snake *snake,char input, int *hasEaten){
    switch(input){
    case 'w':
        if(snake->direction=='L'||snake->direction=='R'){
            snake->direction = 'U';
        }
        break;
    case 'a':
        if(snake->direction=='U'||snake->direction=='D'){
            snake->direction = 'L';
        }
        break;
    case 's':
        if(snake->direction=='L'||snake->direction=='R'){
            snake->direction = 'D';
        }
        break;
    case 'd':
        if(snake->direction=='U'||snake->direction=='D'){
            snake->direction = 'R';
        }
        break;
    }

    switch(snake->direction){
    case 'U':
        snake->head.y = snake->head.y - 1;
        break;
    case 'L':
        snake->head.x = snake->head.x - 1;
        break;
    case 'D':
        snake->head.y = snake->head.y + 1;
        break;
    case 'R':
        snake->head.x = snake->head.x + 1;
        break;
    }

    if(*hasEaten==1){
        snake->length += 1;
        snake->body = realloc(snake->body,(snake->length)*sizeof(struct Point));

        *hasEaten = 0;

    }else{
        screen[snake->tail.y*WIDTH+snake->tail.x] = ' ';
        snake->tail.x = snake->body[snake->length-2].x;
        snake->tail.y = snake->body[snake->length-2].y;


    }

    for(int i=snake->length-2;i>0;i--){
        snake->body[i].x = snake->body[i-1].x;
        snake->body[i].y = snake->body[i-1].y;

    }
    snake->body[0].x = snake->head.x;
    snake->body[0].y = snake->head.y;
    snake->body[snake->length-1].x = snake->tail.x;
    snake->body[snake->length-1].y = snake->tail.y;

    screen[snake->head.y*WIDTH+snake->head.x] = '@';


    return snake;
}

int collisionDetection(struct Snake *snake){
    if(snake->head.x<1||snake->head.x>=WIDTH-1||snake->head.y<1||snake->head.y>=HEIGHT-1){
        printf("You hit the wall!\n");
        return 1;
    }
    for(int i=1;i<snake->length;i++){
        if(snake->head.x==snake->body[i].x && snake->head.y==snake->body[i].y){
            printf("You ate yourself!\n");
            return 1;
        }
    }

    return 0;
}

int isWin(struct Snake *snake, struct Point *food){
    if(snake->head.x==food->x&&snake->head.y==food->y){
        printf("Nice!\n");
        placeFood(food,snake);
        return 1;
    }

    return 0;
}

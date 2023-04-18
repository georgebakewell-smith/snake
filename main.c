#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<math.h>
#include<conio.h>
#include<time.h>

#define WIDTH 20
#define HEIGHT 20
#define SIZE 400

struct Point{
    int x;
    int y;
};

struct Snake{

    struct Point head;
    struct Point tail;
    struct Point *body[1];
    char direction;
    int length;
};

char screen[SIZE];

void initScreen(struct Snake *snake);
struct Snake *initSnake();
void drawScreen();
char getInput();
void updateSnake(struct Snake *snake,char input);
void collisionDetection();
void isWin();

int main()
{
    int gameover = 0;
    char input;
    struct Point *food;

    struct Snake *snake = initSnake();



    initScreen(snake);

    placeFood(food,snake);
    drawScreen();
    //printf("%d\n",food->x);

    //printf("%d\n%d\n%d\n%d\n%c\n",snake->tail.x,snake->tail.y,snake->head.x,snake->head.y,snake->direction);
    while(gameover!=1){
        input = getInput();

        updateSnake(snake,input);
        collisionDetection();
        isWin();
        drawScreen();
        printf("Direction: %c",snake->direction);

        Sleep(100);
    }

    //Maybe write function to free all memory correctly
    free(snake->body[0]);
    free(snake);
    return 0;
}

void placeFood(struct Point *food, struct Snake *snake){
    srand(time(NULL));
    int freeSpace = SIZE - snake->length, randPosition, i=0;
    randPosition = rand()% freeSpace;

    while(i<SIZE){
        if(screen[i] == '@'){
            randPosition += 1;
        }
        if(i==randPosition){
            screen[i] = '#';
            break;
        }
        i++;
    }

}

void initScreen(struct Snake *snake){

    for(int i=0;i<SIZE;i++){
        screen[i] = ' ';
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
    snake->head.y = floor(WIDTH/2)-1;
    snake->direction = 'R';
    snake->length = 2;
    snake->body[0] = (struct Point*)malloc((snake->length-1)*sizeof(struct Point));
    snake->body[0]->x = snake->head.x;
    snake->body[0]->y = snake->head.y;

    return snake;

}

char getInput(){
    char c;
    c = getch();

    return c;
}

void updateSnake(struct Snake *snake,char input){

    switch(input){
    case 'w':
        snake->direction = 'U';
        break;
    case 'a':
        snake->direction = 'L';
        break;
    case 's':
        snake->direction = 'D';
        break;
    case 'd':
        snake->direction = 'R';
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

    screen[snake->head.y*WIDTH+snake->head.x] = '@';
    screen[snake->tail.y*WIDTH+snake->tail.x] = ' ';
    snake ->tail.x = snake->body[0]->x;
    snake->tail.y = snake->body[0]->y;
    snake->body[0]->x = snake->head.x;
    snake->body[0]->y = snake->head.y;
}

void collisionDetection(){

}

void isWin(){

}

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<math.h>

#define WIDTH 10
#define HEIGHT 10
#define SIZE 100

struct Point{
    int x;
    int y;
};

struct Snake{

    struct Point head;
    struct Point tail;
    char direction;

};

char screen[SIZE];

void initScreen();
struct Snake *initSnake();
void drawScreen();
void getInput();
void updateSnake(struct Snake *snake);
void collisionDetection();
void isWin();

int main()
{
    int gameover = 0;
    struct Point *food;

    initScreen();
    struct Snake *snake = initSnake();
    updateSnake(snake);
    drawScreen();
    printf("%d\n%d\n%d\n%d\n%c\n",snake->tail.x,snake->tail.y,snake->head.x,snake->head.y,snake->direction);
    while(gameover==1){
        getInput();
        updateSnake(snake);
        collisionDetection();
        isWin();
        drawScreen();

        Sleep(1000);
    }

    free(snake);
    return 0;
}

void initScreen(){

    for(int i=0;i<SIZE;i++){
        screen[i] = ' ';
    }

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

    return snake;

}

void getInput(){

}

void updateSnake(struct Snake *snake){
    screen[snake->head.y*WIDTH+snake->head.x] = '@';
    screen[snake->tail.y*WIDTH+snake->tail.x] = '@';
}

void collisionDetection(){

}

void isWin(){

}

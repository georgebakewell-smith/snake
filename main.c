#include <stdio.h>
#include <stdlib.h>

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

};

char screen[SIZE];
int gameover = 0;

void initScreen();
void drawScreen();
void getInput();
void updateSnake();
void collisionDetection();
void isWin();

int main()
{
    struct Point *food;

    initScreen();
    drawScreen();
    while(gameover!=1){
        getInput();
        updateSnake();
        collisionDetection();
        isWin();
        drawScreen();


    }

    return 0;
}

void initScreen(){

    for(int i=0;i<SIZE;i++){
        screen[i] = 'a';
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

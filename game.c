#include <GL/glut.h>
#include "game.h"
#include <time.h>

int gridX,gridY;
short sDirection = RIGHT;
extern gameOver;
int food = 1;
int foodX,foodY;
int snake_length = 5;

extern score;

int posX[60] = {20,20,20,20,20},posY[60] = {20,19,18,17,16};

void initGrid(int x,int y){
    gridX = x;
    gridY = y;

}

void drawGrid(){

    for(int x = 0; x < gridX; x++){
        for(int y = 0; y < gridY; y++){
            unit(x,y);
        }

    }
}

void unit(int x, int y){

    if( x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1){
        glLineWidth(3.0);
        glColor3f(0.87,0.72,0.52);
        glBegin(GL_QUADS);

    }else{
        glLineWidth(1.0);
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
    }

        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1, y+1);
        glVertex2f(x,y+1);
    glEnd();

}

void drawSnake(){

    for(int i = snake_length -1 ; i > 0; i--){
        posX[i] = posX[i - 1];
        posY[i] = posY[i - 1];
    }
    if(sDirection == UP)
        posY[0]++;
    else if(sDirection == DOWN)
        posY[0]--;
    else if(sDirection == RIGHT)
        posX[0]++;
    else if(sDirection == LEFT)
        posX[0]--;

    for(int i = 0; i < snake_length; i++){

        if(i == 0){
            glColor3f(0.0,1.0,0.0);
        }else{

            glColor3f(0.6,0.2,1.0);
        }
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);
    }

    if(posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1)
        gameOver = 1;

    for(int j = 1; j < snake_length; j++){
        if(posX[0] == posX[j] && posY[0] == posY[j])
            gameOver = 1;
    }

    if(posX[0] == foodX && posY[0] == foodY){
        food = 1;
        score++;
        if(snake_length < MAX)
            snake_length++;
    }

}

void drawFood(){

    if(food)
        randomFoodGenerator();
    food = 0;
    glColor3f(1.0,0.0,0.0);
    glRectf(foodX,foodY, foodX + 1, foodY + 1);
}

void randomFoodGenerator(){
    int _maxX = gridX - 2;
    int _maxY = gridY - 2;
    int _min = 2;
    srand(time(NULL));
    foodX = _min + rand()%(_maxX - _min);
    foodY = _min + rand() % (_maxY - _min);
}

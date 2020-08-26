#include <GL/gl.h>
#include <GL/glut.h>
#include "game.h"

#define COLUMNS 40
#define ROWS 40
#define FPS 10

extern short sDirection;

void display_callback();
void reshape_callback(int,int);
void timer_callback();
void keyboard_callback(int);

void init(){
    glClearColor(1.0,1.0,1.0,1.0);
    initGrid(COLUMNS,ROWS);
}

int main(int argc, char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("SNAKE GAME");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0,timer_callback,0);
    glutSpecialFunc(keyboard_callback);
    init();
    glutMainLoop();
    return 0;

}


void display_callback(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawSnake();
    glutSwapBuffers();
}

void timer_callback(){
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer_callback,0);
}


void reshape_callback(int w, int h){
    glViewport(0.0,0.0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard_callback(int key){
    switch(key){
        case GLUT_KEY_UP:
            if(sDirection != DOWN)
                sDirection = UP;
            break;

        case GLUT_KEY_DOWN:
            if(sDirection != UP)
                sDirection = DOWN;
            break;

        case GLUT_KEY_RIGHT:
            if(sDirection != LEFT)
                sDirection = RIGHT;
            break;

        case GLUT_KEY_LEFT:
            if(sDirection != RIGHT)
                sDirection = LEFT;
    }
}

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

#include "tetris.h"

Tetris myTetris;
int width = 800;
int height = 800;
double fov = 45;
double aspect = 1;
double zNear = 1;
double zFar = 1000;
double lookX = 0;
double lookY = 0;
double lookZ = 30;
double lookTheta = 0;

void init();
void initLight();
void display();
void reshape(int, int);
void keyboard(unsigned char, int, int);
void special(int, int, int);
void timer(int);
void aitimer(int);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    init();
    glutMainLoop();
    return 0;
}

void initLight()
{
    GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat position[] = {100, 0, 0, 1};
    GLfloat matDiffuse[] = {0.6, 0.6, 0.6, 1.0};
    GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat matShininess[] = {50.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShininess); 
}

void init()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tetris");

    glClearColor(0.2, 0.2, 0.2, 1.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH);
    initLight();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(0, aitimer, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect, zNear, zFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(lookX, lookY, lookZ, 0, 0, 0, 0, 1, 0);
    glPushMatrix();
    glTranslatef(-(myTetris.getWidth()+myTetris.getOffset())/2,
            -myTetris.getHeight()/2, 0);
    myTetris.draw();
    glTranslatef(myTetris.getWidth() + 1,
            myTetris.getHeight() - 4, 0);
    myTetris.drawInfo();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    width = w;
    height = h;
    aspect = (double)w/h;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void special(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP:
        myTetris.rotate();
        break;
    case GLUT_KEY_DOWN:
        myTetris.goDown();
        break;
    case GLUT_KEY_LEFT:
        myTetris.goLeft();
        break;
    case GLUT_KEY_RIGHT:
        myTetris.goRight();
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    case 32:
        myTetris.togglePause();
        break;
    case 'r':
        if (myTetris.isStopped())
            myTetris.restart();
        break;
    case 'a':
        myTetris.toggleAI();
        break;
    default:
        break;
    }
}

void timer(int value)
{
    if (value) {
        myTetris.goDown();
    }
    glutTimerFunc(myTetris.getPeriod(), timer, 1);
    glutPostRedisplay();
}

void aitimer(int value)
{
    if (value && myTetris.useAI()) {
        myTetris.aiMove();
    }
    glutTimerFunc(myTetris.getPeriod()/10, aitimer, 1);
    glutPostRedisplay();
}

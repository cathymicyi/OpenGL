// For MinGW
//#include <windows.h>
//#include "GL/glut.h"
//for xcode
#include <stdlib.h>
#include <stdio.h>
//#include<iostream>
//#include <glm/glm.hpp>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include <math.h>

static int viewstate = 1;//1 is perspective, 2 is orth, 3 is first persopn
static float ratio = 600/480;
double dim =5.0;//dim for orth box
float viewpoint_x = 0.0;
float viewpoint_y = 0.0;
float viewpoint_z = -1.0;
float eye_x = -4.0;
float eye_y = 4.0;
float eye_z = 1.0;
int eyeindex = 1;//we have default 1 eyevalue;
int eyevalue;
float eyepos_x[10];
float eyepos_y[10];
float eyepos_z[10];



void build_sove()
{
    
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f( 1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f,  1.0f);
    
    // Bottom face (y = -1.0f)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    
    // Front face  (z = 1.0f)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);
    
    // Back face (z = -1.0f)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    
    // Left face (x = -1.0f)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    
    // Right face (x = 1.0f)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube
    
    
}

void drawCube(){
    
    //BUILD WALL
    glBegin(GL_QUADS);
    glColor3f(0.63, 0.32, 0.17);
    glVertex3f(0.2, 0.05, 0.0);
    glVertex3f(0.2, 0, 0);
    glVertex3f(0.3, 0, 0);
    glVertex3f(0.3, 0.05, 0.0);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.63, 0.32, 0.17);
    glVertex3f(0.2, 0.05, 0.05);
    glVertex3f(0.2, 0, 0.05);
    glVertex3f(0.3, 0, 0.05);
    glVertex3f(0.3, 0.05, 0.05);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(0.2, 0.05, 0.0);
    glVertex3f(0.2, 0, 0.0);
    glVertex3f(0.2, 0, 0.05);
    glVertex3f(0.2, 0.05, 0.05);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(0.3, 0.05, 0.05);
    glVertex3f(0.3, 0, 0.05);
    glVertex3f(0.3, 0, 0);
    glVertex3f(0.3, 0.05, 0.0);
    glEnd();
    //BULID ROOF
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.1);
    glVertex3f(0.193, 0.045, -0.005);
    glVertex3f(0.193, 0.075, 0.025);
    glVertex3f(0.307, 0.075, 0.025);
    glVertex3f(0.307, 0.045, -0.005);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.1);
    glVertex3f(0.193, 0.075, 0.025);
    glVertex3f(0.193, 0.045, 0.055);
    glVertex3f(0.307, 0.045, 0.055);
    glVertex3f(0.307, 0.075, 0.025);
    glEnd();
    //chimney
    glPushMatrix();
    glTranslated(0.25, 0.07, 0.01);
    glScaled(0.005, 0.03, 0.01);
    build_sove();
    glPopMatrix();

    // BUILD  FRONT roof
    glBegin(GL_TRIANGLES);
    glColor3f(0.5, 0.5, 1.5);
    glVertex3f(0.2, 0.05, 0.0);
    glVertex3f(0.2, 0.075, 0.025);
    glVertex3f(0.2, 0.05, 0.05);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glColor3f(0.5, 0.5, 1.5);
    glVertex3f(0.3, 0.05, 0.0);
    glVertex3f(0.3, 0.075, 0.025);
    glVertex3f(0.3, 0.05, 0.05);
    glEnd();

    //BUILD WINDOW
    glBegin(GL_QUADS);
    glColor3f(0.1, 0.1, 1.0);
    glVertex3f(0.199, 0.035, 0.015);
    glVertex3f(0.199, 0.0, 0.015);
    glVertex3f(0.199, 0.0, 0.03);
    glVertex3f(0.199, 0.035, 0.03);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(0.215, 0.035, -0.0001);
    glVertex3f(0.214, 0.013, -0.0001);
    glVertex3f(0.233, 0.013, -0.0001);
    glVertex3f(0.233, 0.035, -0.0001);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(0.265, 0.035, -0.0001);
    glVertex3f(0.265, 0.0, -0.0001);
    glVertex3f(0.283, 0.0, -0.0001);
    glVertex3f(0.283, 0.035, -0.0001);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.f, 1, 1.5);
    glVertex3f(0.215, 0.035, 0.0501);
    glVertex3f(0.215, 0.013, 0.0501);
    glVertex3f(0.233, 0.013, 0.0501);
    glVertex3f(0.233, 0.035, 0.0501);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.f, 1, 1.5);
    glVertex3f(0.265, 0.035, 0.0501);
    glVertex3f(0.265, 0.013, 0.0501);
    glVertex3f(0.283, 0.013, 0.0501);
    glVertex3f(0.283, 0.035, 0.0501);
    glEnd();

    

}


void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*
     SWITCH projecttion mode then render scene
     
     */
    if(viewstate==1)
    {
        gluPerspective(45, ratio, dim/4, dim*4);
        //std::cout<<"perspective"<<std::endl;
        printf("perspective mode.\n" );
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye_x, eye_y, eye_z, viewpoint_x, viewpoint_y, viewpoint_z, 0, 0.5, 0);
    }
    else if(viewstate==2)
    {
        glOrtho(-dim*ratio, dim*ratio, -dim, dim, -dim/4, dim*4);
       // std::cout<<"orth"<<std::endl;
        printf("orth mode.\n" );
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye_x, eye_y, eye_z, viewpoint_x, viewpoint_y, viewpoint_z, 0, 0.5, 0);
    }
    else if(viewstate ==0)
    {
      //  std::cout<<"first person mode"<<std::endl;
        printf("1st person mode.\n" );
        gluPerspective(45.0f, ratio, 0.1, 100.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye_x, eye_y, eye_z, viewpoint_x, viewpoint_y, viewpoint_z, 0.0, 1.0, 0.0);
        
        
        
    }
    for(int i = 0; i < 5; i++){
    glPushMatrix();
    glTranslated(i*2.5, -i-1, -i*3.2);
    glRotated(-90*i, 1, 0, 0);
    glScaled(8, 8, 8);
    drawCube();
    glPopMatrix();
    }

    
    glFlush();
    glutSwapBuffers();
}
void reshape(GLsizei w, GLsizei h)
{
    if (w == 0 || h == 0) return;
    
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

}

void mykey(unsigned char key, int x, int y){
    switch (key) {
        case 'Q':
            exit(0);
            break;
        case 'O':
            viewstate=2;
            break;
        case 'I'://first person
            viewstate = 0;
            /**here we set our view as default**/
            eye_x=-2.5;
            eye_y=-1.0;
            eye_z=2.0;
            viewpoint_x = 1.0;
            viewpoint_y = -1.0;
            viewpoint_z = -.5;
            break;
        case 'P':
            viewstate=1;
            break;
        case 'W'://change viewpoint y++
            viewpoint_y +=0.03;
            break;
        case 'S'://change viewpoint y--
            viewpoint_y -=0.03;
            break;
        case 'A'://change viewpoint x--
            viewpoint_x -=0.03;
            break;
        case 'D':
            viewpoint_x +=0.03;//viewpoint x++
            break;
        case 'Z':
            viewpoint_z +=0.03;//viewpoint z++
            break;
        case 'X':
            viewpoint_z -=0.03;//viewpoint z--
            break;
        case 'H'://switch position.
            if(eyeindex < eyevalue)
            {
                eye_x = eyepos_x[eyeindex];
                eye_y = eyepos_y[eyeindex];
                eye_z = eyepos_z[eyeindex];
                eyeindex++;
            }
            else{
                eyeindex = 1;//reset to first one
                viewpoint_x = 0.0;
                viewpoint_y = 0.0;
                viewpoint_z = -1.0;
                eye_x = -4.0;
                eye_y = 4.0;
                eye_z = 1.0;
            }
            break;
        default:
            break;
    }
    glutPostRedisplay();
}
void navigation(int key, int x, int y){//first person navigation, move the whole frustum.
    if(viewstate==0)
    {
       // glm::vec3 dir = viewpoint - eye;
        //glm::vec3 right =glm::vec3(1.0,0.0,0.0);
        float dir_x = viewpoint_x - eye_x;
        float dir_y = viewpoint_y - eye_y;
        float dir_z = viewpoint_z - eye_z;
       // float distance = sqrt( pow(dir_x, dir_x)+pow(dir_y, dir_y)+pow(dir_z, dir_z));

        
        if(key == GLUT_KEY_LEFT)
        {
            
            eye_x -= 0.1 ;
            viewpoint_x -= 0.1;
        }
        else if(key == GLUT_KEY_RIGHT)
        {
            
            eye_x += 0.1;
            viewpoint_x += 0.1;
        }
        else if(key == GLUT_KEY_UP)
        {
            eye_x -= dir_x*0.1;
            eye_z -= dir_z*0.1;
            eye_y -= dir_y*0.1;
        
        }
        else if(key == GLUT_KEY_DOWN)
        {
            eye_x += dir_x*0.1;
            eye_y += dir_y*0.1;
            eye_z += dir_z*0.1;
        }
        else if(key==GLUT_KEY_F1)
        {
            eye_z+=0.1;
            viewpoint_z+=0.1;
       
        }
        else if(key == GLUT_KEY_F2)
        {
            eye_z-=0.1;
            viewpoint_z-=0.1;
        }

    }
    glutPostRedisplay();
    

}

void Init(){
    
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}
void geteyePos()
{
    printf("how many eye pos u want to input:(max is 10, first one is default value) \n");
    scanf("%d", &eyevalue);
    if(eyevalue>10)
        eyevalue = 10;
    
    printf("input eyepos: with space beteen number(eg. 0.3 9.5 6.0)\n");
    for(int i = 1; i < eyevalue; i++ )
    {
        scanf("%f %f %f", &eyepos_x[i],&eyepos_y[i],&eyepos_z[i]);
    }
    printf("Start scene.....\n");

}

int main(int argc, char** argv)
{
    geteyePos();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(600, 480);
    glutInitWindowPosition(50, 100);
    glutCreateWindow("Assignment4");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(mykey);
    glutSpecialFunc(navigation);
    Init();
    glutMainLoop();
    return 0;
}

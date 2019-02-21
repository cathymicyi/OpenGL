#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static float ratio = 600/480;
double dim =5.0;//dim for orth box
float viewpoint_x = -1;
float viewpoint_y = -1.5;
float viewpoint_z = 0.5;
float eye_x = -2.5;
float eye_y = -1.0;
float eye_z = 3.0;
int lightmode = 0;
float no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
float mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
float mat_ambient_color[] = { 0.7, 0.4, 0.7, 1.0 };
float mat_diffuse[] = { 0.6, 0.5, 0.4, 1.0 };
float mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
float no_shininess[] = { 0.0 };
float low_shininess[] = { 5.0 };
float high_shininess[] = { 100.0 };
float mat_emission[] = {0.3, 0.2, 0.2, 0.0};
float lightpos[] = {0.2,2.0,3.0,0.0};
float rotate = 0;
int ambient   =  0;
int diffuse   = 100;
int specular  =  100;
void lightDebug(double r, int lats, int longs)
{

    glMaterialf(GL_FRONT,GL_SHININESS,5.0);
    glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);
    int i, j;
    for(i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);
        
        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);
        
        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);
            
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
    
}
void nomalizaiton(float *a)
{
    float len = sqrt(a[0]*a[0] + a[1]*a[1]+ a[2]*a[2]);
    
    for(int i = 0  ; i < 3;i++ )
        a[i] = a[i]/len;
    
}

float *crossproduct(float *a, float *b)
{
    float result[] = {a[1]*b[2]+a[2]*b[1], a[0]*b[2]+a[2]*b[0], a[0]*b[1] + a[1]*b[0]};
    nomalizaiton(result);
    return result;
}

float *countingNormal(float *x, float *y, float *z)
{
    float v[] = {y[0] - x[0], y[1]-x[1], y[2] - x[2]};
    float u[] = {z[0] - x[0], z[1]-x[1], z[2] - x[2]};
    
    float *result = crossproduct(u, v);
    //nomalization
    
    return result;
    
}
void build_sove()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    glBegin(GL_QUADS);
    glColor3f(1,0,0);
    glNormal3f(0.0f,1.0f,0.0f);//crossproduct find normal.
    glVertex3f( 1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f,  1.0f);
    
    // Bottom face (y = -1.0f)
    
    glColor3f(1,0,0);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    
    // Front face  (z = 1.0f)
    
    glColor3f(1,0,0);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);
    
    // Back face (z = -1.0f)
    
    glColor3f(1,0,0);
    glNormal3f(0, 0, -1);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    
    // Left face (x = -1.0f)
    
    glColor3f(1,0,0);
    glNormal3f(-1,0,0);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    
    // Right face (x = 1.0f)
    
    glColor3f(1,0,0);
    glNormal3f(1,0,0);
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube
    
    
}

void drawCube(){
    

    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);


    glColor3f(0.63, 0.32, 0.17);
    glBegin(GL_QUADS);
    //BWALL
   
    glNormal3f(0,0,-1);
    glVertex3f(0.2, 0.05, 0.0);
    glVertex3f(0.2, 0.0, 0.0);
    glVertex3f(0.3, 0.0 , 0.0);
    glVertex3f(0.3, 0.05, 0.0);
    glEnd();
    
   
    glColor3f(0.63, 0.32, 0.17);
    glBegin(GL_QUADS);

    glNormal3f(0,0,1);
    glVertex3f(0.2, 0.05, 0.05);
    glVertex3f(0.2, 0.0, 0.05);
    glVertex3f(0.3, 0.0, 0.05);
    glVertex3f(0.3, 0.05, 0.05);
    glEnd();
    //LWALL
    
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glVertex3f(0.2, 0.05, 0.0);
    glVertex3f(0.2, 0, 0.0);
    glVertex3f(0.2, 0, 0.05);
    glVertex3f(0.2, 0.05, 0.05);
    glEnd();
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glVertex3f(0.3, 0.05, 0.05);
    glVertex3f(0.3, 0, 0.05);
    glVertex3f(0.3, 0, 0);
    glVertex3f(0.3, 0.05, 0.0);
    glEnd();
    
    //BULID ROOF
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);

    glColor3f(0.2, 0.2, 0.1);
    glBegin(GL_QUADS);
 
    glNormal3f(0, -0.707, -0.707);
    glVertex3f(0.193, 0.045, -0.005);
    glVertex3f(0.193, 0.075, 0.025);
    glVertex3f(0.307, 0.075, 0.025);
    glVertex3f(0.307, 0.045, -0.005);
    glEnd();
    
    glBegin(GL_QUADS);

    glNormal3f(0, -0.707, 0.707);
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
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glColor3f(0.5, 0.5, 1.0);
    
    glBegin(GL_TRIANGLES);

    glNormal3f(-1,0,0);
    glVertex3f(0.2, 0.05, 0.0);
    glVertex3f(0.2, 0.075, 0.025);
    glVertex3f(0.2, 0.05, 0.05);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    
    glNormal3f(1,0,0);
    glVertex3f(0.3, 0.05, 0.0);
    glVertex3f(0.3, 0.075, 0.025);
    glVertex3f(0.3, 0.05, 0.05);
    glEnd();
    //=========DOOR
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glColor3f(0.4, 0.4, 0.6);
    glBegin(GL_QUADS);

   
    glNormal3f(-1,0,0);
    glVertex3f(0.199, 0.035, 0.015);
    glVertex3f(0.199, 0.0, 0.015);
    glVertex3f(0.199, 0.0, 0.03);
    glVertex3f(0.199, 0.035, 0.03);
    glEnd();
      //BUILD WINDOW
    

    //glColor3f(0.2, 0.1, 0.8);
    glBegin(GL_QUADS);

    glNormal3f(0,0,-1);
    glVertex3f(0.215, 0.035, -0.0001);
    glVertex3f(0.214, 0.013, -0.0001);
    glVertex3f(0.233, 0.013, -0.0001);
    glVertex3f(0.233, 0.035, -0.0001);
    glEnd();
    
    glBegin(GL_QUADS);

    glNormal3f(0,0,-1);
    glVertex3f(0.265, 0.035, -0.0001);
    glVertex3f(0.265, 0.013, -0.0001);
    glVertex3f(0.283, 0.013, -0.0001);
    glVertex3f(0.283, 0.035, -0.0001);
    glEnd();
    
    glBegin(GL_QUADS);

    glNormal3f(0, 0, 1);
    glVertex3f(0.215, 0.035, 0.0501);
    glVertex3f(0.215, 0.013, 0.0501);
    glVertex3f(0.233, 0.013, 0.0501);
    glVertex3f(0.233, 0.035, 0.0501);
    glEnd();
    
    glBegin(GL_QUADS);

    glNormal3f(0, 0, 1);
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
    
    gluPerspective(45, ratio, dim/4, dim*4);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye_x, eye_y, eye_z, viewpoint_x, viewpoint_y, viewpoint_z, 0, 0.5, 0);
    
    if(lightmode){
        float light_ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
        float light_diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
        float light_specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        float light_position[] = {lightpos[0],lightpos[1],lightpos[2], 0.0 };

    glEnable(GL_LIGHTING);
        glPushMatrix();
        glScaled(.1, .1, .1);
        glTranslated(light_position[0], light_position[1], light_position[2]);
        lightDebug(1,100,100);
        glPopMatrix();
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHT0); //enable the light after setting the properties
  }
    else
        glDisable(GL_LIGHTING);
    glPushMatrix();
    glRotated(rotate, 0, 1, 0);
    glTranslated(-2.5, -2, 0);
    glScaled(8, 8, 8);
    drawCube();
    glPopMatrix();
    
    
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
        case 'W'://[0,1,2]
            lightpos[1]+=0.3;
            break;
        case 'S':
            lightpos[1]-=0.3;
            break;
        case 'A':
            lightpos[0]+=0.3;
            break;
        case 'D':
            lightpos[0]-=0.3;
            break;
        case 'Z':
            lightpos[2]+=0.3;
            break;
        case 'X':
            lightpos[2]-=0.3;
            break;
        case 'H'://switch position.
            rotate +=5;
            break;
        case 'Y':
            rotate -=5;
            break;
        case 'L'://change lightmode:
            if(lightmode ==0)
                lightmode =1;
            else
                lightmode =0;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


void Init(){
    glClearColor(0.0, 0.1, 0.1, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 100);
    glutCreateWindow("Assignment4");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(mykey);
    
    Init();
    glutMainLoop();
    return 0;
}

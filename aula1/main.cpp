#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <ctime>


void changeSize(int w, int h)
{
    // prevent a divide by zero, when window is too short
    // (you can not make a window with zero width).
    if (h == 0)
        h = 1;
    // compute window's aspect ratio
    float ratio = w * 1.0f / h;

    // set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load the identity matrix
    glLoadIdentity();
    // set the perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);

    // et the viewport to be the entire window
    glViewport(0, 0, w, h);
}


void draw_torus(float innerRadius, float outterRadius){
    glutWireTorus(innerRadius, outterRadius, 10, 50);
}

float angle=0;

void rotationAnimation(int value){
    angle+=30;
    if (angle>360){
        angle=0;
    }
    glutTimerFunc(100, rotationAnimation, 0);
}


void painter(int weight){
    time_t now = time(nullptr);
    time_t mnow = weight * now * 1000;
    glColor3f(1-sin(mnow),1-cos(mnow),sin(mnow));
}


void renderScene(void)
{
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // set camera
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f);
    
    
    //rotationAnimation on all axis
    glRotatef(angle, 1, 1, 1);
    // put drawing instructions here
    painter(1);
    draw_torus(0.1,1);
    
    //rotationAnimation on the x axis only
    glRotatef(angle, 1, 0, 0);
    painter(2);
    draw_torus(0.1,0.5);
    
    // End of frame
    glutSwapBuffers();
}


void printInfo() {

    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));
}


int main(int argc, char** argv)
{
    // put GLUT init here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Aula1");
    // put callback registry here
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    
    // some OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    glutTimerFunc(100, rotationAnimation, 25);
    // enter GLUTs main cycle
    glutMainLoop();
    
    return 1;
}

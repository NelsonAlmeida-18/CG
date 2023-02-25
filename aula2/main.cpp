#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdio.h>
#include <unistd.h>

float currScale=1;
float pitchAngle=0;
float yawAngle=0;
float xTranslate=0;
float yTranslate=0;
float zTranslate=0;


void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();
    
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void drawAxis(){
    glBegin(GL_LINES);
        //draw x axis
        //set color to red
        glColor3f(1.0f,0.0f,0.0f);
        //get screenWidth && screenHeight
        float screenWidth = glutGet(GLUT_WINDOW_WIDTH);
        float screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
        glVertex3f(-screenWidth/2,0,0);
        glVertex3f(screenWidth/2,0,0);
        //draw y axis;
        glColor3f(0,1,0);
        glVertex3f(0,-screenWidth/2,0);
        glVertex3f(0,screenWidth/2,0);
        //draw z axis;
        glColor3f(0,0,1);
        glVertex3f(0,0,-screenHeight/2);
        glVertex3f(0,0,screenHeight/2);
    glEnd();
}


void pyramidDrawer(int gama){
    glBegin(GL_TRIANGLES);
    //base
    //triangulo1
    glColor3f(1,0,0);
    glVertex3f(-gama/2,0.0,-gama/2);
    glVertex3f(gama/2,0,-gama/2);
    glVertex3f(-gama/2,0,gama/2);

    //triangulo2
    glColor3f(1,0.8,0);
    glVertex3f(-gama/2,0,-gama/2);
    glVertex3f(gama/2,0,gama/2);
    glVertex3f(gama/2,0.0,-gama/2);
    
    //face1
    glColor3f(0.9,0.1,0.8);
    glVertex3f(-gama/2,0,gama/2);
    glVertex3f(gama/2,0,gama/2);
    glVertex3f(0,gama,0);
    //face2
    glColor3f(0.1,0.8,0.9);
    glVertex3f(gama/2,0.0,gama/2);
    glVertex3f(gama/2,0,-gama/2);
    glVertex3f(0,gama,0);
    //face3
    glColor3f(0.1,0.9,0.2);
    glVertex3f(gama/2,0,-gama/2);
    glVertex3f(-gama/2,0,-gama/2);
    glVertex3f(0,gama,0);
    //face4
    glColor3f(0.5,0.1,0.9);
    glVertex3f(-gama/2,0,-gama/2);
    glVertex3f(-gama/2,0,gama/2);
    glVertex3f(0,gama,0);
    
    
    glEnd();
    
}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);
    
// put axis drawing in here
    drawAxis();
    
// put the geometric transformations here
    glRotatef(yawAngle, 0, 1, 0);
    glRotatef(pitchAngle,1,0,0);
    glScalef(currScale,currScale,currScale);
    glTranslatef(xTranslate,yTranslate,zTranslate);

// put pyramid drawing instructions here
    pyramidDrawer(2);
    glLoadIdentity();
    glScalef(20,20,20);
    // End of frame
    glutSwapBuffers();
}

// write function to process keyboard events

void zoomIn(unsigned char key, int x, int y){
    //para saber qual o valor da key
    //zoom Out
    if (key=='-'){
        currScale-=0.2;
        glutPostRedisplay();
    }
    //zoom In
    if(key=='+'){
        currScale+=0.2;
        glutPostRedisplay();
    }
    //move pyramid right
    if(key=='d'){
        xTranslate+=0.1;
        glutPostRedisplay();
    }
    //move pyramid left
    if(key=='a'){
        xTranslate-=0.1;
        glutPostRedisplay();
    }
    //move pyramid forward
    if (key=='f'){
        zTranslate+=0.1;
        glutPostRedisplay();
    }
    //move pyramid backward
    if(key=='r'){
        zTranslate-=0.1;
        glutPostRedisplay();
    }
    if(key=='w'){
        yTranslate+=0.1;
        glutPostRedisplay();
    }
    if(key=='s'){
        yTranslate-=0.1;
        glutPostRedisplay();
    }
    
}

void yawRotation(int key_code, int x, int y){
    if (key_code==GLUT_KEY_RIGHT){
        yawAngle+=30;
        glutPostRedisplay();
    }
    if (key_code==GLUT_KEY_LEFT){
        yawAngle-=30;
        glutPostRedisplay();
    }
    if (key_code==GLUT_KEY_DOWN){
        pitchAngle-=30;
        glutPostRedisplay();
    }
    if (key_code==GLUT_KEY_UP){
        pitchAngle+=30;
        glutPostRedisplay();
    }
    //move pyramid up
    if (key_code==GLUT_ACTIVE_SHIFT){
        
    }
}

int initialMouseX=-1;
// 100% screen width = rotação de 360 graus

void spinRoutine(int x, int y){
    float windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    float operation =(x-initialMouseX)*360/windowWidth;
    yawAngle+=operation;
    glutPostRedisplay();
    initialMouseX=x;
}

void youSpinMyHead(int button, int state, int x, int y){
    
    initialMouseX=x;
    if (button==GLUT_LEFT_BUTTON){
        glutMotionFunc(spinRoutine);
    }
}


int main(int argc, char **argv) {

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("P02");
        
// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

// put here the registration of the keyboard callbacks
    glutKeyboardFunc(zoomIn);
    glutSpecialFunc(yawRotation);
    glutMouseFunc(youSpinMyHead);
    

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
// enter GLUT's main cycle
    glutMainLoop();
    
    return 1;
}

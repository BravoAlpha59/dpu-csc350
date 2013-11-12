//
// File: hw5.cc
//
// Author: 
//
// Description: Draws 2 spheres.  You must define 2 light sources for the 
// homework assignment
//

#include <GL/glut.h>
#include <stdlib.h> 
#include <math.h>
#include <iostream>
#include "drawSphere.h"

using namespace std;

// theta, phi, and dist are the eye position in 3d polar coordinates
static float theta=-30;       // eye position to z-axis
static float phi=30;          // eye position to x-z plane
static float dist=5.0;

// display options
bool displayLightSpheres;     // true=>display spheres at light sources

void init(void)
{
  // define light property parameters
  GLfloat lightAmbient[] = {0.0, 0.0, 0.5, 1.0};
  GLfloat lightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat lightSpecular[]= {1.0, 1.0, 1.0, 1.0};

  // define clear color to be black
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // set up ambient, diffuse, and specular components for the lights
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

  glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);

  // We'll use glColor to set the diffuse and ambient material properties
  glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable (GL_COLOR_MATERIAL);

  // enable light sources
  glEnable (GL_LIGHT0);
  glEnable (GL_LIGHT1);

  // enable other things
  glEnable (GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  glShadeModel (GL_SMOOTH);

  // initialize options
  displayLightSpheres = true;
}

void setCamera(void)
{
  // sets the camera position in the world

  // set the view transformation
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -dist);
  glRotatef(phi, 1.0, 0.0, 0.0);
  glRotatef(theta, 0.0, 1.0, 0.0);
}

void display(void)
{
  // define material reflectivity
  GLfloat matSpecular[]  = {1.0, 1.0, 1.0, 1.0};

  // Shininess coefficient
  // between 100 and 200 metallic
  // between 5 and 10 plastic
  GLfloat matShininess =   80.0;

  // define light source positions
  GLfloat light0Pos[] = {0.0, 2.0, 0.0, 1.0};
  GLfloat light1Pos[] = {2.0, 1.5, 1.5, 1.5};
  
  // define default material properties
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

  // clear frame buffer and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // position camera
  glLoadIdentity ();
  setCamera ();

  // enable lighting the axes and source spheres
  // this turns on shading calculations
  glEnable (GL_LIGHTING);

  // place light sources
  glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
  glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);

  // draw axes
  glBegin(GL_LINES);
    // x in red
    glColor3f(1.0,0.0,0.0);
    glVertex3i(0,0,0);
    glVertex3i(2,0,0);

    // y in green
    glColor3f (0.0, 1.0, 0.0);
    glVertex3i (0,0,0);
    glVertex3i (0,2,0);

    // z in blue
    glColor3f (0.0, 0.0, 1.0);
    glVertex3i (0,0,0);
    glVertex3i (0,0,2);
  glEnd();

  // draw small spheres at the light sources if selected
  // remember that this is going to behave relative to
  // attributes of the first object to be drawn (i.e. sphere one)
  if (displayLightSpheres)
    {
      glPushMatrix();
        glColor3f (1.0, 1.0, 1.0);
        glTranslatef (light0Pos[0],light0Pos[1],light0Pos[2]);
        glScalef (0.1, 0.1, 0.1);
        drawSphere(100,100);
      glPopMatrix();

      glPushMatrix();
        glColor3f (1.0, 1.0, 1.0);
        glTranslatef (light1Pos[0],light1Pos[1],light1Pos[2]);
        glScalef (0.05, 0.05, 0.05);
        drawSphere(100,100);
      glPopMatrix();
    }

  // draw sphere one at the origin of the world
  // size is 1.0
  glColor3f (0.5, 0.0, 0.5);
  drawSphere (200,200);
  
  // draw sphere two relative to one
  glPushMatrix();
    glTranslatef (1.5, 0.0, 0.0);
    glColor3f (0.0, 1.0, 0.0);
    glScalef (0.25, 0.25, 0.25);
    drawSphere (50,50);
  glPopMatrix();
  
  // display things  
  glutSwapBuffers();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.01, 20.0);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
  case '4': // left
    theta -= 5;
    glutPostRedisplay();
    break;
  case '6': //right
    theta += 5;
    glutPostRedisplay();
    break;
  case '2': //down
    phi += 5;
    // don't let elevation go past 90 or -90
    if (phi>90.0)
      phi = 90.0;
    else if (phi < -90.0)
      phi = -90.0;
    glutPostRedisplay();
    break;
  case '8': //up
    phi -= 5;
    // don't let elevation go past 90 or -90
    if (phi>90.0)
      phi = 90.0;
    else if (phi < -90.0)
      phi = -90.0;
    glutPostRedisplay();
    break;
  case '3': //pgDn (back up)
    dist += 0.5;
    glutPostRedisplay();
    break;
  case '9': //pgUp (move forward)
    dist -= 0.5;
    glutPostRedisplay();
    break;

  // toggle display of lighting spheres
  case 'L':
  case 'l':
    displayLightSpheres = !displayLightSpheres;
    glutPostRedisplay ();
    break;

  case 27: /* esc */
  case 'Q':
  case 'q':
    exit(0);
    break;
  }
}

void SpecialKeys(int key, int x, int y)
{
    // will be used to speed up/slow down rotation rates
    if (key == GLUT_KEY_LEFT)
    {
        theta -= 5;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        theta += 5;
    }
    if (key == GLUT_KEY_UP)
    {
        phi -= 5;
        // don't let elevation go past 90 or -90
        if (phi>90.0)
          phi = 90.0;
        else if (phi < -90.0)
          phi = -90.0;
    }
    if (key == GLUT_KEY_DOWN)
    {
        phi += 5;
        // don't let elevation go past 90 or -90
        if (phi>90.0)
          phi = 90.0;
        else if (phi < -90.0)
          phi = -90.0;
    }

    if (key == GLUT_KEY_PAGE_UP)
    {
        dist += 0.5;
    }
    if (key == GLUT_KEY_PAGE_DOWN)
    {
        dist -= 0.5;
    }
    // process other special keys here


    glutPostRedisplay();
}

int main(int argc, char** argv)
{
  // initialize glut, creat window, etc.
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Draw Sphere");
  init();

  // register callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(SpecialKeys);

  // do everything!
  glutMainLoop();
}

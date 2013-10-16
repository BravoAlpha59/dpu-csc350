//
//	Bob Arrington
//	CSC350A - Computer Graphics
//	Doug Harms, Professor
//	October 10, 2013
//
//	Homework #1
//	Introduction to using some primitive openGL functions
//  to display, animate and alter the view of objects
//
// File: myGraphics.cc
//
//
#include <GL/glut.h>
#include <stdlib.h> 
#include <math.h>
#include <iostream>

using namespace std;

// global state variables
float length;
float adjustment;
float yPos;
bool animate;
GLdouble eyeX;
GLdouble eyeY;
GLdouble eyeZ;

void init(void)
{
  // define clear color to be black
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // shade polygons as flat surfaces
  glShadeModel(GL_FLAT);

  // do hidden surface removal
  glEnable (GL_DEPTH_TEST);

 // initialize global state
  eyeX = 3.0;
  eyeY = 2.0;
  eyeZ = 3.0;
  length = 2.0;
  adjustment = 0.1;
  yPos = 0.0;
  animate = false;
}

void display(void)
{
  // clear frame buffer and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // set viewpoint
  glLoadIdentity();
  gluLookAt (eyeX, eyeY, eyeZ,     /* eye */
	     0.0, 0.0, 0.0,     /* center */
	     0.0, 1.0, 0.0);    /* up */

  // draw things in the world

  // let's draw the axes first
  glBegin(GL_LINES);
	  // x in red
	  glColor3f(1.0,0.0,0.0);
	  glVertex3f(0.0,0.0,0.0);
	  glVertex3f(2.0,0.0,0.0);

	  // y in green
	  glColor3f (0.0, 1.0, 0.0);
	  glVertex3f(0.0,0.0,0.0);
	  glVertex3f (0.0,2.0,0.0);

	  // z in blue
	  glColor3f (0.0, 0.0, 1.0);
	  glVertex3f(0.0,0.0,0.0);
	  glVertex3f (0.0,0.0,2.0);
  glEnd();

  // now let's draw a purple square parallel with the zx plane that intersects
  // the y axis at y=yPos
  glColor3f (1.0, 0.0, 1.0);
  glBegin (GL_POLYGON);
	  glVertex3f (-length/2.0, yPos, -length/2.0);
	  glVertex3f (-length/2.0, yPos, length/2.0);
	  glVertex3f (length/2.0, yPos, length/2.0);
	  glVertex3f (length/2.0, yPos, -length/2.0);
  glEnd ();

  glTranslatef(0.0f,1.0f,-2.0f);//move forward 2 units

  glColor3f(0.0f,0.0f,1.0f); //blue color

  glBegin(GL_LINE_LOOP);//start drawing a line loop
    glVertex3f(-1.0f,0.0f,0.0f);//left of window
    glVertex3f(0.0f,-1.0f,0.0f);//bottom of window
    glVertex3f(1.0f,0.0f,0.0f);//right of window
    glVertex3f(0.0f,1.0f,0.0f);//top of window
  glEnd();//end drawing of line loop


 // glTranslatef(2.0f,0.0f,2.0f);//move forward 4 units
  glTranslatef (0.0f, -1.5f, 4.0f);

  glColor3f(1.0f,1.0f,0.0f); //yellow color

  glBegin(GL_LINE_STRIP);
    glVertex3f(0.0f, 0.0f, 0.0f);  // V0
    glVertex3f(1.0f, 1.5f, 0.0f);  // V1
    glVertex3f(0.5f, 2.5f, 0.0f);  // V2
    glVertex3f(-1.0f, 1.0f, 0.0f);  // V3
  glEnd();

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

void timer(int val)
{
  if (animate)
    {
      // register callback to executer again in .1 seconds
      glutTimerFunc (100,timer,0);

      // adjust square length
      length += adjustment;

      if (length > 1.5)
	{
	  length = 1.5;
	  adjustment = -0.1;
	}
      if (length < 0)
	{
	  length = 0;
	  adjustment = 0.1;
	}

      // redraw everything
      glutPostRedisplay ();
    }
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
	  case 27: /* esc */
	  case 'Q':
	  case 'q':
		exit(0);
		break;

	  case '+': // increase length
		yPos+= 0.25;
		glutPostRedisplay();
		break;

	  case '-': // decrease length
		yPos -= 0.25;
		glutPostRedisplay();
		break;

	  case '4': // decrease eyeX
		eyeX -= 0.25;
	    gluLookAt (eyeX, eyeY, eyeZ,     /* eye */
		  	       0.0, 0.0, 0.0,     /* center */
			       0.0, 1.0, 0.0);    /* up */
		glutPostRedisplay();
		break;

	  case '6': // increase eyeX
		eyeX += 0.25;
	    gluLookAt (eyeX, eyeY, eyeZ,     /* eye */
		  	       0.0, 0.0, 0.0,     /* center */
			       0.0, 1.0, 0.0);    /* up */
		glutPostRedisplay();
		break;

	  case '2': // decrease eyeY
		eyeY -= 0.25;
	    gluLookAt (eyeX, eyeY, eyeZ,     /* eye */
		  	       0.0, 0.0, 0.0,     /* center */
			       0.0, 1.0, 0.0);    /* up */
		glutPostRedisplay();
		break;

	  case '8': // increase eyeY
		eyeY += 0.25;
	    gluLookAt (eyeX, eyeY, eyeZ,     /* eye */
		  	       0.0, 0.0, 0.0,     /* center */
			       0.0, 1.0, 0.0);    /* up */
		glutPostRedisplay();
		break;

	  case '3': // decrease eyeZ
		eyeZ -= 0.25;
	    gluLookAt (eyeX, eyeY, eyeZ,     /* eye */
		  	       0.0, 0.0, 0.0,     /* center */
			       0.0, 1.0, 0.0);    /* up */
		glutPostRedisplay();
		break;

	  case '9': // increase eyeZ
		eyeZ += 0.25;
	    gluLookAt (eyeX, eyeY, eyeZ,     /* eye */
		  	       0.0, 0.0, 0.0,     /* center */
			       0.0, 1.0, 0.0);    /* up */
		glutPostRedisplay();
		break;

	  case 'A':
	  case 'a':
		// turn animate on/off
		animate = !animate;

		// if we just turned it on, then set the timer to go off in .1 seconds
		if (animate)
		  glutTimerFunc (100,timer,0);
		break;

  }
}

int main(int argc, char** argv)
{
  // initialize glut, create window, etc.
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Homework #1");

  // initialize program data structures
  init();

  // register callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);

  // do everything!
  glutMainLoop();

  return 0;

}


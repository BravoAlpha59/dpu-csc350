//
//      File:     hw3.cc
//      Author:   Bob Arrington
//      Course:   CSC350A - Computer Graphics
//      Prof. :   D. Harms
//      Due Date: October 3, 2013
//
//      Homework #2
//      Create a small solar system which utilizes the
//      openGL 4 x 4 matrices of model view projections
//
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h> 
#include <math.h>
#include <iostream>

using namespace std;

// define global state variables

struct rotateInfo {
	float rotate;
	float X;
	float Y;
	float Z;
};

struct revolveInfo {
        float revolve;
        float X;
        float Y;
        float Z;
};

struct scaleInfo {
	float X;
	float Y;
	float Z;
};

struct translateInfo {
	float X;
	float Y;
	float Z;
};

struct colorInfo {
	float RED;
	float GREEN;
	float BLUE;
};

struct planetInfo {
  scaleInfo scale;       	// scale/size of object X,Y,Z
  translateInfo translate;      // translate distance
  rotateInfo rotate;            // rotate on axis (Day)
  revolveInfo revolve;          // revolve in orbit (Year)
  colorInfo color;		// RGB color
  float deltaX,deltaY;   	// velocity of the object
  float deltaPsi;        	// angular velocity
};

planetInfo sun;
planetInfo earth;
planetInfo earthMoon;
planetInfo P2;
planetInfo P2Moon[2];
planetInfo P3;
planetInfo P3Moon[3];

// theta, phi, and dist are the eye position in 3d polar coordinates
float theta=-30;       // eye position to z-axis
float phi=30;        // eye position to x-z plane
float dist=5.0;

bool animate;

static int DeltaSpeed = 1.0;

// These variables control the animation's state and speed.
static int EarthDay = 0;
static int EarthYear = 0;
static int Increment = 1;

// These variables control the animation's state and speed.
static int P2Day = 0;
static int P2Year = 100;
static int P2Increment = 2;

// These variables control the animation's state and speed.
static int P3Day = 0;
static int P3Year = 280;
static int P3Increment = 1;

// set the camera in the world at spherical coordinate (dist, theta, phi)
void setCamera(void)
{
  // set the view transformation
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -dist);
  glRotatef(phi, 1.0, 0.0, 0.0);
  glRotatef(theta, 0.0, 1.0, 0.0);
}

void init(void)
{
  // define clear color to be black
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // shade polygons as flat surfaces
  glShadeModel(GL_FLAT);

  // do depth testing
  glEnable (GL_DEPTH_TEST);

  // do other initialization things here

  // SUN Attributes (center of world)
  // scale down by half
  sun.scale.X=0.5f;
  sun.scale.Y=0.5f;
  sun.scale.Z=0.5f;
  // color yellow
  sun.color.RED=1.0f;
  sun.color.GREEN=1.0f;
  sun.color.BLUE=0.0f;

  // EARTH Attributes (relative to SUN)
  // scale down
  earth.scale.X=0.25f;
  earth.scale.Y=0.25f;
  earth.scale.Z=0.25f;
  // color blue
  earth.color.RED=0.0f;
  earth.color.GREEN=0.0f;
  earth.color.BLUE=1.0f;
  // translate distance from the sun
  earth.translate.X=2.0f;
  earth.translate.Y=0.0f;
  earth.translate.Z=0.0f;
  // rotate from sun orientation
  earth.rotate.rotate=30.0f;
  earth.rotate.X=0.0f;
  earth.rotate.Y=1.0f;
  earth.rotate.Z=0.0f;

  // Earth's MOON Attributes
  // scale down
  earthMoon.scale.X=0.5f;
  earthMoon.scale.Y=0.5f;
  earthMoon.scale.Z=0.5f;
  // color white
  earthMoon.color.RED=1.0f;
  earthMoon.color.GREEN=1.0f;
  earthMoon.color.BLUE=1.0f;
  // translate distance from the earth
  earthMoon.translate.X=2.25f;
  earthMoon.translate.Y=0.0f;
  earthMoon.translate.Z=0.0f;
  // rotate from earth orientation
  earthMoon.rotate.rotate=30.0f;
  earthMoon.rotate.X=0.0f;
  earthMoon.rotate.Y=1.0f;
  earthMoon.rotate.Z=0.0f;

  // Planet 2 Attributes (relative to SUN)
  // scale down
  P2.scale.X=0.5f;
  P2.scale.Y=0.5f;
  P2.scale.Z=0.5f;
  // color red
  P2.color.RED=1.0f;
  P2.color.GREEN=0.0f;
  P2.color.BLUE=0.0f;
  // translate distance from the sun
  P2.translate.X=4.0f;
  P2.translate.Y=0.0f;
  P2.translate.Z=0.0f;
  // rotate from sun orientation
  P2.rotate.rotate=150.0f;
  P2.rotate.X=0.0f;
  P2.rotate.Y=1.0f;
  P2.rotate.Z=0.0f;

  // Planet 2's MOON Attributes
  // scale down by three quarter
  P2Moon[0].scale.X=0.25f;
  P2Moon[0].scale.Y=0.25f;
  P2Moon[0].scale.Z=0.25f;
  // color green
  P2Moon[0].color.RED=0.0f;
  P2Moon[0].color.GREEN=1.0f;
  P2Moon[0].color.BLUE=0.0f;
  // translate distance from the P2
  P2Moon[0].translate.X=1.75f;
  P2Moon[0].translate.Y=0.0f;
  P2Moon[0].translate.Z=0.0f;
  // rotate from P2 orientation
  P2Moon[0].rotate.rotate=30.0f;
  P2Moon[0].rotate.X=0.0f;
  P2Moon[0].rotate.Y=1.0f;
  P2Moon[0].rotate.Z=0.0f;

  // Planet 2's MOON Attributes
  // scale down by three quarter
  P2Moon[1].scale.X=0.35f;
  P2Moon[1].scale.Y=0.35f;
  P2Moon[1].scale.Z=0.35f;
  // color green
  P2Moon[1].color.RED=0.5f;
  P2Moon[1].color.GREEN=0.0f;
  P2Moon[1].color.BLUE=0.5f;
  // translate distance from the P2
  P2Moon[1].translate.X=2.50f;
  P2Moon[1].translate.Y=0.5f;
  P2Moon[1].translate.Z=0.0f;
  // rotate from P2 orientation
  P2Moon[1].rotate.rotate=100.0f;
  P2Moon[1].rotate.X=0.0f;
  P2Moon[1].rotate.Y=1.0f;
  P2Moon[1].rotate.Z=0.0f;

  // Planet 3 Attributes (relative to SUN)
  // scale down
  P3.scale.X=0.25f;
  P3.scale.Y=0.25f;
  P3.scale.Z=0.25f;
  // color red
  P3.color.RED=0.0f;
  P3.color.GREEN=1.0f;
  P3.color.BLUE=0.0f;
  // translate distance from the sun
  P3.translate.X=6.5f;
  P3.translate.Y=0.0f;
  P3.translate.Z=0.0f;
  // rotate from sun orientation
  P3.rotate.rotate=300.0f;
  P3.rotate.X=0.0f;
  P3.rotate.Y=1.0f;
  P3.rotate.Z=0.0f;

  // Planet 2's MOON Attributes
  // scale down by three quarter
  P3Moon[0].scale.X=0.25f;
  P3Moon[0].scale.Y=0.25f;
  P3Moon[0].scale.Z=0.25f;
  // color green
  P3Moon[0].color.RED=1.0f;
  P3Moon[0].color.GREEN=0.0f;
  P3Moon[0].color.BLUE=0.0f;
  // translate distance from the P2
  P3Moon[0].translate.X=1.75f;
  P3Moon[0].translate.Y=0.0f;
  P3Moon[0].translate.Z=0.0f;
  // rotate from P2 orientation
  P3Moon[0].rotate.rotate=30.0f;
  P3Moon[0].rotate.X=0.0f;
  P3Moon[0].rotate.Y=1.0f;
  P3Moon[0].rotate.Z=0.0f;

  // Planet 3's MOON Attributes
  // scale down by three quarter
  P3Moon[1].scale.X=0.35f;
  P3Moon[1].scale.Y=0.35f;
  P3Moon[1].scale.Z=0.35f;
  // color green
  P3Moon[1].color.RED=0.5f;
  P3Moon[1].color.GREEN=0.0f;
  P3Moon[1].color.BLUE=0.5f;
  // translate distance from the P2
  P3Moon[1].translate.X=2.50f;
  P3Moon[1].translate.Y=0.5f;
  P3Moon[1].translate.Z=0.0f;
  // rotate from P2 orientation
  P3Moon[1].rotate.rotate=100.0f;
  P3Moon[1].rotate.X=0.0f;
  P3Moon[1].rotate.Y=1.0f;
  P3Moon[1].rotate.Z=0.0f;
}

// draw a radius 1 wire sphere centered around the origin.  The longitude
// lines (i.e., north and south poles) will meet on the y-axis.
void drawSphere (bool planet)
{
  glPushMatrix ();
  glRotatef (90.0, 1.0, 0.0, 0.0);
  glutWireSphere (1.0, 20, 20);
  glPopMatrix ();
  glBegin( GL_LINES );
    glVertex3f( 0.0, 1.5, 0.0 );
    glVertex3f( 0.0, -1.5, 0.0 );
    // if this is not the sun or a moon, draw a flag
    // at the top of the 'north' axis
    if (planet)
      {
        glVertex3f( 0.0, 1.5, 0.0 );
        glVertex3f( 0.25, 1.5, 0.0 );
      }
  glEnd();
}

void drawAxes()
{
  // X , Y, Z axes at the center of the current frame
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

}

void drawSun()
{
  bool planet = false;
  // set the scale of the next object to be displayed reduced by half
  glScalef(sun.scale.X, sun.scale.Y, sun.scale.Z);
  // set the color of the next object to be displayed to yellow
  glColor3f(sun.color.RED,sun.color.GREEN,sun.color.BLUE);
  // draw the Sun in center of the universe (world)
  drawSphere(planet);
}

void drawEarth()
{
  bool planet = true;
  // rotate from sun orientation
  glRotatef(EarthYear,earth.rotate.X, earth.rotate.Y, earth.rotate.Z);
  // translate the earth a distance from sun
  glTranslatef(earth.translate.X, earth.translate.Y, earth.translate.Z);
  // rotate the earth on its axis.
  glRotatef( EarthDay, earth.rotate.X, earth.rotate.Y, earth.rotate.Z);
  // set the scale of the next object to be displayed reduced by half
  glScalef(earth.scale.X, earth.scale.Y, earth.scale.Z);
  // set the color of the next object to be displayed to yellow
  glColor3f(earth.color.RED,earth.color.GREEN,earth.color.BLUE);
  // draw the Earth in translated and rotated relative to the sun
  drawSphere(planet);
}

void drawEarthMoon()
{
  bool planet = false;
  // rotate from earth orientation
  glRotatef(earthMoon.rotate.rotate,earthMoon.rotate.X, earthMoon.rotate.Y, earthMoon.rotate.Z);
  // translate the moon a distance from earth
  glTranslatef(earthMoon.translate.X, earthMoon.translate.Y, earthMoon.translate.Z);
  // set the scale of the next object to be displayed reduced by half
  glScalef(earthMoon.scale.X, earthMoon.scale.Y, earthMoon.scale.Z);
  // set the color of the next object to be displayed to white
  glColor3f(earthMoon.color.RED,earthMoon.color.GREEN,earthMoon.color.BLUE);
  // draw the Moon in translated and rotated relative to the Earth
  drawSphere(planet);
}

void drawP2()
{
  bool planet = true;
  // rotate P2 on its axis.
  //		Use JupiterHourOfDay to determine its rotation.
  glRotatef( P2Year, P2.rotate.X, P2.rotate.Y, P2.rotate.Z );
  // translate the earth a distance from sun
  glTranslatef(P2.translate.X, P2.translate.Y, P2.translate.Z);
  // rotate from sun orientation
  glRotatef(P2Day,P2.rotate.X, P2.rotate.Y, P2.rotate.Z);
  // set the scale of the next object to be displayed reduced by half
  glScalef(P2.scale.X, P2.scale.Y, P2.scale.Z);
  // set the color of the next object to be displayed to yellow
  glColor3f(P2.color.RED,P2.color.GREEN,P2.color.BLUE);
  // draw the Earth in translated and rotated relative to the sun
  drawSphere(planet);
}

void drawP2Moon(int m)
{
  bool planet = false;
  // rotate from planet orientation
  glRotatef(P2Moon[m].rotate.rotate,P2Moon[m].rotate.X, P2Moon[m].rotate.Y, P2Moon[m].rotate.Z);
  // translate the moon a distance from planet
  glTranslatef(P2Moon[m].translate.X, P2Moon[m].translate.Y, P2Moon[m].translate.Z);
  // set the scale of the next object to be displayed reduced by half
  glScalef(P2Moon[m].scale.X, P2Moon[m].scale.Y, P2Moon[m].scale.Z);
  // set the color of the next object to be displayed to white
  glColor3f(P2Moon[m].color.RED,P2Moon[m].color.GREEN,P2Moon[m].color.BLUE);
  // draw the Moon in translated and rotated relative to the planet
  drawSphere(planet);
}

void drawP3()
{
  bool planet = true;
  // rotate P3 on its axis.
  //            Use JupiterHourOfDay to determine its rotation.
  glRotatef( P3Year, P3.rotate.X, P3.rotate.Y, P3.rotate.Z );
  // translate the earth a distance from sun
  glTranslatef(P3.translate.X, P3.translate.Y, P3.translate.Z);
  // rotate from sun orientation
  glRotatef(P3Day,P3.rotate.X, P3.rotate.Y, P3.rotate.Z);
  // set the scale of the next object to be displayed reduced by half
  glScalef(P3.scale.X, P3.scale.Y, P3.scale.Z);
  // set the color of the next object to be displayed to yellow
  glColor3f(P3.color.RED,P3.color.GREEN,P3.color.BLUE);
  // draw the Earth in translated and rotated relative to the sun
  drawSphere(planet);
}

void drawP3Moon(int m)
{
  bool planet = false;
  // rotate from planet orientation
  glRotatef(P3Moon[m].rotate.rotate,P3Moon[m].rotate.X, P3Moon[m].rotate.Y, P3Moon[m].rotate.Z);
  // translate the moon a distance from planet
  glTranslatef(P3Moon[m].translate.X, P3Moon[m].translate.Y, P3Moon[m].translate.Z);
  // set the scale of the next object to be displayed reduced by half
  glScalef(P3Moon[m].scale.X, P3Moon[m].scale.Y, P3Moon[m].scale.Z);
  // set the color of the next object to be displayed to white
  glColor3f(P3Moon[m].color.RED,P3Moon[m].color.GREEN,P3Moon[m].color.BLUE);
  // draw the Moon in translated and rotated relative to the planet
  drawSphere(planet);
}

void display(void)
{
  // clear frame buffer and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  setCamera();

  // draw axes
  drawAxes();

  // draw sun
  drawSun();

  glPushMatrix();

  // draw earth
  drawEarth();

  // draw earth moon
  drawEarthMoon();

  glPopMatrix();

  glPushMatrix();

  // draw P2
  drawP2();

  glPushMatrix();

  // draw P2 moon
  drawP2Moon(0);

  glPopMatrix();

  // draw P2 moon
  drawP2Moon(1);

  glPopMatrix();

  // draw P3
  drawP3();

  glPushMatrix();

  // draw P3 moon
  drawP3Moon(0);

  glPopMatrix();

  // draw P3 moon
  drawP3Moon(1);

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

void timer(int val)
{
  // nothing to do if animation stopped
  if (!animate)
    return;

  // Update the Earth animation state
  EarthDay = (EarthDay + Increment)   + DeltaSpeed % 360;
  EarthYear = (EarthYear + Increment)  + DeltaSpeed % 360;

  // Update the Planet 2 animation state
  P2Day = (P2Day + P2Increment)  + DeltaSpeed % 360;
  P2Year = (P2Year + P2Increment)  + DeltaSpeed % 360;

  // Update the Planet 3 animation state
  P3Day = (P3Day + P3Increment)  + DeltaSpeed % 360;
  P3Year = (P3Year + P3Increment)  + DeltaSpeed % 360;

  //	Use DayOfYear to control its rotation around the earth
  earthMoon.rotate.rotate= 360.0*EarthDay/365.0;

  //	Use DayOfYear to control its rotation around the planet
//  P2Moon[0].rotate.rotate= 360.0*0.45*P2Day/365.0;
  P2Moon[0].rotate.rotate= 360.0*2*P2Day/365.0;;
  //	Use DayOfYear to control its rotation around the planet
//  P2Moon[1].rotate.rotate= 360.0*0.25*P2Day/365.0;
  P2Moon[1].rotate.rotate= 360.0*P2Day/365.0;;

  //    Use DayOfYear to control its rotation around the planet
  P3Moon[0].rotate.rotate= 360.0*P3Day/200.0;
  //    Use DayOfYear to control its rotation around the planet
  P3Moon[1].rotate.rotate= 360.0*2.0*P3Day/200.0;
  //    Use DayOfYear to control its rotation around the planet
  P3Moon[2].rotate.rotate= 360.0*0.5*P3Day/200.0;

  // register timer to tick in 1/25th second
  glutTimerFunc (40,timer,0);

  // we need to redraw it now
  glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
    
  // keys to change the camera position
  case '4': // left
    theta += 5;
    glutPostRedisplay();
    break;
  case '6': //right
    theta -= 5;
    glutPostRedisplay();
    break;
  case '2': //down
    phi -= 5;
    if( phi < -90.0 )
      phi = -90;
    glutPostRedisplay();
    break;
  case '8': //up
    phi += 5;
    if( phi > 90.0 )
      phi = 90.0;
    glutPostRedisplay();
    break;
  case '3': //move away
    dist += 0.5;
    glutPostRedisplay();
    break;
  case '9': //move closer
    dist -= 0.5;
    glutPostRedisplay();
    break;

  // also the direction keys perform this
  // same functionality
  case '+': // increase animation speed
    DeltaSpeed += 1;
    glutPostRedisplay();
    break;
  case '-': // decrease animation speed
    DeltaSpeed -= 1;
    glutPostRedisplay();
    break;



  case 'A': // toggle animation
  case 'a':
    animate = !animate;
    // register callback if we just turned animation on
    if (animate)
      glutTimerFunc (40,timer,0);
    break;


  case 27: /* esc */
  case 'Q':
  case 'q':
    exit(0);
    break;
    

    // process other keys here

   }
}

void SpecialKeys(int key, int x, int y)
{
    // will be used to speed up/slow down rotation rates
    if (key == GLUT_KEY_LEFT)
    {
        DeltaSpeed -= 1;
    }

    if (key == GLUT_KEY_RIGHT)
    {
        DeltaSpeed += 1;
    }

    // process other special keys here


    glutPostRedisplay();
}


int main(int argc, char** argv)
{
  // initialize glut, create window, etc.
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1000,1000);
  glutInitWindowPosition(100,100);
  glutCreateWindow("My Animated Universe");

  // initialize program data structures
  init();

  // register callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(SpecialKeys);

  // do everything!
  glutMainLoop();

  return 0;

}

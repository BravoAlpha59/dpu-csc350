//
// File: drawSphere.h
// Author: Douglas Harms
//
// Description: defines a function to draw a sphere
//
#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

//#define BA_DEBUG

#ifdef BA_DEBUG
#define Debug(x) cout << x
#else
#define Debug(x)
#endif

void drawSphere(int numSlices, int numStacks)
{
  // draws a unit sphere with the origin at the center.  The "top" of the
  // sphere will be on the y-axis.  Normals will be defined appropriately.
  GLdouble deltaTheta = (2.0 * M_PI) / numSlices; // radians
  GLdouble deltaY = 2.0 / numStacks;
  // stack offset
  GLdouble * y = new GLdouble[numStacks + 1];
  // slice offset
  GLdouble * r = new GLdouble[numStacks + 1];
  // quad vertices
  GLdouble * leftX = new GLdouble[numStacks + 1];
  GLdouble * leftZ = new GLdouble[numStacks + 1];
  GLdouble * rightX = new GLdouble[numStacks + 1];
  GLdouble * rightZ = new GLdouble[numStacks + 1];

  // top of sphere on Y is at 1.0
  y[0] = 1.0;
  // bottom of sphere on Y is at -1.0
  y[numStacks] = -1.0;
  // origin on X is 0.0
  r[0] = 0.0;
  // last position on X is 0.0
  r[numStacks] = 0.0;

  leftX[0] = r[0];
  leftZ[0] = 0.0;

  Debug("Stacks:" << numStacks << " Slices:" << numSlices << endl); Debug("deltaTheta:" << deltaTheta << " radians " << deltaTheta * (180 / M_PI) << " degrees" << endl); Debug("deltaY:" << deltaY << endl); Debug("----------" << endl);

  Debug("0" << ": y=" << y[0] << " r=" << r[0] << endl);

  int i, j;
  for (i = 0; i <= numStacks; i++)
    {
      // calculate Y position of each stack
      y[i] = 1 - (i * deltaY);
      // sqrt of ( radius (1) - Y^2 )
      r[i] = sqrt(1.0 - pow(y[i], 2));
      // initialize leftX = r
      leftX[i] = r[i];
      // initialize leftZ = 0.0
      leftZ[i] = 0.0;

      Debug(i << ": y=" << y[i] << " r=" << r[i] << endl);
    }

  Debug(numStacks << ": y=" << y[numStacks] << " r=" << r[numStacks] << endl); Debug("++++++++++" << endl);

  GLdouble theta = deltaTheta;

  for (j = 0; j <= numSlices; j++)
    {

      glBegin(GL_QUADS);

      // remember to compose quads counter-clockwise because of the
      // affect on lighting and shading
      // leftX, leftX+1, rightX+1, rightX

      // close the top whose Quad origin of course is 0 stack/slice
      // and Y at the top of sphere is 1
      //-TL
      glNormal3d(0, 1, 0);
      glVertex3d(0, 1, 0);
      //-BL
      glNormal3d(leftX[1], y[1], leftZ[1]);
      glVertex3d(leftX[1], y[1], leftZ[1]);
      //-BR
      glNormal3d(r[1] * cos(theta), y[1], -r[1] * sin(theta));
      glVertex3d(r[1] * cos(theta), y[1], -r[1] * sin(theta));
      //-TR
      glNormal3d(0, 1, 0);
      glVertex3d(0, 1, 0);

      // fill out the stacks
      for (i = 1; i < numStacks; i++)
        {
          Debug("stack: " << i << " theta: " << theta << endl);

          // calculate the X point of Right vertices
          rightX[i] = r[i] * cos(theta);
          rightX[i + 1] = r[i + 1] * cos(theta);

          // calculate the Z point of Right vertices
          rightZ[i] = -r[i] * sin(theta);
          rightZ[i + 1] = -r[i + 1] * sin(theta);

          // top-left
          Debug("TL->" << "leftX: " << leftX[i] << "  y: " << y[i] << "  leftZ: " << leftZ[i] << endl);
          glNormal3d(leftX[i], y[i], leftZ[i]);
          glVertex3d(leftX[i], y[i], leftZ[i]);

          // bottom-left
          Debug("BL->" << "  leftX: " << leftX[i+1] << "  y: " << y[i+1] << "  leftZ: " << leftZ[i+1] << endl);
          glNormal3d(leftX[i + 1], y[i + 1], leftZ[i + 1]);
          glVertex3d(leftX[i + 1], y[i + 1], leftZ[i + 1]);

          // bottom-right
          Debug("BR->" << "rightX: " << rightX[i+1] << "  y: " << y[i+1] << "  rightZ: " << rightZ[i+1] << endl);
          glNormal3d(rightX[i + 1], y[i + 1], rightZ[i + 1]);
          glVertex3d(rightX[i + 1], y[i + 1], rightZ[i + 1]);

          // top-right
          Debug("TR->" << "rightX: " << rightX[i] << "  y: " << y[i] << "  rightZ: " << rightZ[i] << endl);
          glNormal3d(rightX[i], y[i], rightZ[i]);
          glVertex3d(rightX[i], y[i], rightZ[i]);

          leftX[i] = rightX[i];
          leftZ[i] = rightZ[i];

          theta += deltaTheta;

          Debug("xxxxxxxxxx" << endl);
        }

      // close the bottom of the slice
      //-TL
      glNormal3d(leftX[numStacks], y[numStacks], leftZ[numStacks]);
      glVertex3d(leftX[numStacks], y[numStacks], leftZ[numStacks]);
      //-BL
      glNormal3d(0, -1, 0);
      glVertex3d(0, -1, 0);
      //-BR
      glNormal3d(0, -1, 0);
      glVertex3d(0, -1, 0);
      //-TR
      glNormal3d(rightX[numStacks], y[numStacks], rightZ[numStacks]);
      glVertex3d(rightX[numStacks], y[numStacks], rightZ[numStacks]);

      glEnd();

    }

  delete[] y;
  delete[] r;
  delete[] leftX;
  delete[] leftZ;
  delete[] rightX;
  delete[] rightZ;
}

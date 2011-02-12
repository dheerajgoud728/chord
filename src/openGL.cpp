#include "funcs.h"
#include <math.h>
#include <memory.h>

float _posx=2,_posy=2,_posz=2;
int _anglex=0,_angley=0,_angleo=0;

static double _left   = 0.0;
static double _right  = 0.0;
static double _bottom = 0.0;
static double _top    = 0.0;
static double _zNear  = -10.0;
static double _zFar   = 10.0;

static int  _mouseX      = 0;
static int  _mouseY      = 0;
static bool _mouseLeft   = false;
static bool _mouseMiddle = false;
static bool _mouseRight  = false;
static bool _scrollup  = false;
static bool _scrolldown  = false;

static double _dragPosX  = 0.0;
static double _dragPosY  = 0.0;
static double _dragPosZ  = 0.0;

float rad=3.0;

static double _matrix[16];
static double _matrixInverse[16];

float cameraPos[3]={0,0,1};

void renderBitmapCharacher(float x,float y,float z,char *string)
{

  char *c;
  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter((void *)font, *c);
  }
}
const float DEG2RAD = 3.14159/180;
void display(void)
{
   int u, v, i;
   hermit_to_bezier();
   GLfloat points[4][3],pt[3],pt1[4][3];
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPushMatrix ();

   /*glRotatef(asin(cameraPos[0])/DEG2RAD,1.0,0.0,0.0);
   glRotatef(asin(cameraPos[1])/DEG2RAD,0.0,1.0,0.0);
   glRotatef(asin(cameraPos[2])/DEG2RAD,0.0,0.0,1.0);*/
   //glTranslatef(cameraPos[0],cameraPos[1],cameraPos[2]);
    glRotatef(-_anglex,1.0,0.0,0.0);
    glRotatef(-_angley,0.0,1.0,0.0);
   //display point position
   char* str = new char[100];
   //sprintf(str, "(%.1f, %.1f, %.1f)", posx,posy,posz);
   //renderBitmapCharacher(posx,posy,posz,str);
   sprintf(str, "(%.1f, %.1f, %.1f)", cameraPos[0],cameraPos[1],cameraPos[2]);
   renderBitmapCharacher(cameraPos[0],cameraPos[1],cameraPos[2],str);
   delete str;
   //test
    glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(0.0,1.0,1.0);
	glVertex3f(cameraPos[0],cameraPos[1],cameraPos[2]);
	glEnd();
    glBegin(GL_LINES);
    glColor3f(0.7,0.5,0.7);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(2*cameraPos[0],2*cameraPos[1],2*cameraPos[2]);
    glEnd();
   //end of display
    //point
    /*glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(0.0,1.0,1.0);
	glVertex3f(posx,posy,posz);
	glEnd();*/
    //x-y-z axis
    //z-axis
    glBegin(GL_LINES);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.0,-30.0);
    glVertex3f(0.0,0.0,30.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0,0.0,0.5);
    glVertex3f(0.0,0.0,posz);
    glVertex3f(posx,posy,posz);
    glEnd();
    //y-axis
    glBegin(GL_LINES);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0,-30.0,0.0);
    glVertex3f(0.0,30.0,0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0,0.5,0.0);
    glVertex3f(0.0,posy,0.0);
    glVertex3f(posx,posy,posz);
    glEnd();
    //x-axis
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-30.0,0.0,0.0);
    glVertex3f(30.0,0.0,0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.5,0.0,0.0);
    glVertex3f(posx,0.0,0.0);
    glVertex3f(posx,posy,posz);
    glEnd();
    //end of axis
    //plotting bezier points
    glColor3f(0,0,0);
    glutWireSphere(1,20,20);
    glutSolidSphere(20,20,20);
    glColor3f(0.5,1.0,1.0);
    for(int i=0;i<15;i++)
    {
        glBegin(GL_LINES);
        glVertex3f(ctrlpoints[i/4][i%4][0],ctrlpoints[i/4][i%4][1],ctrlpoints[i/4][i%4][2]);
        glVertex3f(ctrlpoints[(i+1)/4][(i+1)%4][0],ctrlpoints[(i+1)/4][(i+1)%4][1],ctrlpoints[(i+1)/4][(i+1)%4][2]);
        glEnd();
    }
    glBegin(GL_LINES);
    glVertex3f(ctrlpoints[3][3][0],ctrlpoints[3][3][1],ctrlpoints[3][3][2]);
    glVertex3f(ctrlpoints[0][0][0],ctrlpoints[0][0][1],ctrlpoints[0][0][2]);
    glEnd();
    //end of plot
	glColor3f(0.0, 0.0, 0.0);
   for (u = 0; u <= 8; u++) {
       glBegin(GL_LINE_STRIP);
       for (v = 0; v <= 30; v++) {

           for(i=0;i<4;i++)
           {
                decast_algo((GLfloat)v/30.0,ctrlpoints[i],points[i]);
           }
           decast_algo((GLfloat)u/8.0,points,pt);
            glVertex3fv(pt);
        }
         glEnd();
        glBegin(GL_LINE_STRIP);
       for (v = 0; v <= 30; v++) {

         for(i=0;i<4;i++)
           {
                convert(ctrlpoints,pt1,i);
                decast_algo((GLfloat)v/30.0,pt1,points[i]);
           }
            decast_algo((GLfloat)u/8.0,points,pt);
            glVertex3fv(pt);
        }
         glEnd();
   }
   glPopMatrix ();
   glFlush();
}

void init(void)
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
           0, 1, 12, 4, &ctrlpoints[0][0][0]);
   glEnable(GL_MAP2_VERTEX_3);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-4.0, 4.0, -4.0*(GLfloat)h/(GLfloat)w,
              4.0*(GLfloat)h/(GLfloat)w, -4.0, 4.0);
   else
      glOrtho(-4.0*(GLfloat)w/(GLfloat)h,
              4.0*(GLfloat)w/(GLfloat)h, -4.0, 4.0, -4.0, 4.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void change_bpts()
{
    hermitPoints[ppos/4][ppos%4][0] =posx;
    hermitPoints[ppos/4][ppos%4][1] =posy;
    hermitPoints[ppos/4][ppos%4][2] =posz;
    if(ppos == 15)
    {
        ppos=0;
    }
    else
        ppos++;
    display();
    dump();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   	  case 'w':
   	  	posy+=0.1;
   	  	display();
   	  	break;
   	  case 's':
   	  	posy-=0.1;
   	  	display();
   	  	break;
   	  case 'a':
   	  	posx-=0.1;
   	  	display();
   	  	break;
   	  case 'd':
   	  	posx+=0.1;
   	  	display();
   	  	break;
   	  case 'q':
   	  	posz-=0.1;
   	  	display();
   	  	break;
   	  case 'e':
   	  	posz+=0.1;
   	  	display();
   	  	break;
      case '0':
        print_pos();
        break;
      case 27:
         exit(0);
         break;
      case ' ':
        change_bpts();
        break;
      case '+':
         rot=rot+1.0f;
         glutPostRedisplay();
        break;
      case '-':
         rot=rot-1.0f;
         glutPostRedisplay();
        break;
   }
}

void Mouse(int button, int state, int x, int y)
{
    _mouseX = x;
    _mouseY = y;

    if (state==GLUT_UP)
        switch (button)
        {
            case GLUT_LEFT_BUTTON:   _mouseLeft   = false; break;
            case GLUT_MIDDLE_BUTTON: _mouseMiddle = false; break;
            case GLUT_RIGHT_BUTTON:  _mouseRight  = false; break;
            case 3: _scrollup = false;break;
            case 4: _scrolldown = false;break;
        }
    else
        switch (button)
        {
            case GLUT_LEFT_BUTTON:   _mouseLeft   = true; break;
            case GLUT_MIDDLE_BUTTON: _mouseMiddle = true; break;
            case GLUT_RIGHT_BUTTON:  _mouseRight  = true; break;
            case 3: _scrollup = true;break;
            case 4: _scrolldown = true;break;
        }
    if(_mouseMiddle)
    {
        _angley=0;
        _anglex=0;
    }
	if (_scrollup)
	{
        double s = 1.25;
        rad*=s;
        /*cameraPos[0]*=s;
        cameraPos[1]*=s;
        cameraPos[2]*=s;*/
        glScalef(s,s,s);
	}
	else if(_scrolldown)
	{
        double s = 0.80;
        rad*=s;
        /*cameraPos[0]*=s;
        cameraPos[1]*=s;
        cameraPos[2]*=s;*/
        glScalef(s,s,s);
	}
    glutPostRedisplay();
}

void Motion(int x, int y)
{
    bool changed = false;

    const int dx = x - _mouseX;
    const int dy = y - _mouseY;

    if (dx==0 && dy==0)
        return;

    if (_mouseRight)
    {
        cameraPos[0]=cameraPos[0]*cos(dx*DEG2RAD)-cameraPos[1]*sin(dx*DEG2RAD)*sin(dy*DEG2RAD)-cameraPos[2]*cos(dx*DEG2RAD)*sin(dy*DEG2RAD);
        cameraPos[1]=cameraPos[1]*cos(dx*DEG2RAD)-cameraPos[2]*sin(dx*DEG2RAD);
        cameraPos[2]=cameraPos[0]*sin(dy*DEG2RAD)-cameraPos[1]*sin(dx*DEG2RAD)*cos(dy*DEG2RAD)-cameraPos[2]*cos(dx*DEG2RAD)*cos(dy*DEG2RAD);
        _angley-=dx;
        _anglex-=dy;
        _anglex=_anglex%360;
        _angley=_angley%360;
        //float rad=sqrt(cameraPos[0]*cameraPos[0]+cameraPos[1]*cameraPos[1]+cameraPos[2]*cameraPos[2]);

        changed = true;
    }
    _mouseX = x;
    _mouseY = y;

    if (changed)
        glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);

    //zprInit();
    //zprSelectionFunc(display);     /* Selection mode draw function */
    //zprPickFunc(pick);

    /*glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);*/
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
/*
 *Used mouse functions from zpr.cpp
 */

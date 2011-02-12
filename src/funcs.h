#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

float posx=0,posy=0,posz=0;

int ppos=0;
int font=(int)GLUT_BITMAP_8_BY_13;

struct cubicPoints{
    GLfloat points[3];
};

GLfloat hermitPoints[4][4][3];

GLfloat ctrlpoints[4][4][3];

GLfloat rot=0.0;

void hermit_to_bezier()
{
    for(int i=0; i<4;  i++)
    {
        for(int j=0;j<3;j++)//P0
            ctrlpoints[i][0][j] = hermitPoints[i][0][j];
        for(int j=0;j<3;j++)//P1
            ctrlpoints[i][1][j] = hermitPoints[i][0][j] + (hermitPoints[i][1][j])/3;
        for(int j=0;j<3;j++)//P'0
            ctrlpoints[i][2][j] = hermitPoints[i][2][j] - (hermitPoints[i][3][j])/3;
        for(int j=0;j<3;j++)//P'1
            ctrlpoints[i][3][j] = hermitPoints[i][2][j];
    }
}

void ratio(GLfloat pt1[], GLfloat pt2[], GLfloat npt[], GLfloat r )
{
    npt[0] = (1-r)*pt1[0] + (r)*pt2[0];
    npt[1] = (1-r)*pt1[1] + (r)*pt2[1];
    npt[2] = (1-r)*pt1[2] + (r)*pt2[2];
}

void decast_algo(GLfloat u, GLfloat point[][3], GLfloat pnt[])
{
	GLfloat temp1[3],temp2[3],temp3[3],temp4[3],temp5[3];
    ratio(point[0],point[1],temp1,u);
    ratio(point[1],point[2],temp2,u);
    ratio(point[2],point[3],temp3,u);
    ratio(temp1,temp2,temp4,u);
    ratio(temp2,temp3,temp5,u);
    ratio(temp4,temp5,pnt,u);
}

void convert(GLfloat points[][4][3],GLfloat pts[][3],int j)
{
      for(int k=0;k<3;k++)
      {
          pts[0][k]=points[0][j][k];
          pts[1][k]=points[1][j][k];
          pts[2][k]=points[2][j][k];
          pts[3][k]=points[3][j][k];
      }
}

void print_pos()
{
    cout<<ppos<<" ("<<posx<<", "<<posy<<", "<<posz<<")"<<endl;
}

void dump()
{
    ofstream f;
    f.open("cpoints.txt");
    for(int i=0;i<15;i++)
    {
        f<<ctrlpoints[i/4][i%4][0]<<" "<<ctrlpoints[i/4][i%4][1]<<" "<<ctrlpoints[i/4][i%4][2]<<" "<<endl;
        cout<<ctrlpoints[i/4][i%4][0]<<" "<<ctrlpoints[i/4][i%4][1]<<" "<<ctrlpoints[i/4][i%4][2]<<" "<<endl;
    }
    f.close();
}

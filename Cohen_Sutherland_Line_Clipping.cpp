#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<iostream>

void display();
using namespace std;
float xMin=-100;
float yMin=-100;
float xMax=100;
float yMax=100;
float xDif1,yDif1,xDif2,yDif2;


void init(void)
{

    glClearColor(0.0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300,300,-300,300);

}

int code(float x,float y)
{
    int c=0;
    if(y>yMax)c=8;
    if(y<yMin)c=4;
    if(x>xMax)c=c|2;
    if(x<xMin)c=c|1;
    return c;
}

void cohen_Line(float x1,float y1,float x2,float y2)
{
    int c1=code(x1,y1);
    int c2=code(x2,y2);
    float m=(y2-y1)/(x2-x1);
    while((c1|c2)>0)
    {
        if((c1 & c2)>0)
        {
           exit(0);
        }

    float xi=x1;float yi=y1;
    int c=c1;
    if(c==0)
    {
         c=c2;
         xi=x2;
         yi=y2;
    }
    float x,y;
    if((c & 8)>0)
    {
       y=yMax;
       x=xi+ 1.0/m*(yMax-yi);
    }
    else
      if((c & 4)>0)
      {
          y=yMin;
          x=xi+1.0/m*(yMin-yi);
      }
      else
       if((c & 2)>0)
       {
           x=xMax;
           y=yi+m*(xMax-xi);
       }
       else
       if((c & 1)>0)
       {
           x=xMin;
           y=yi+m*(xMin-xi);
       }

       if(c==c1)
       {
           xDif1=x;
           yDif1=y;
           c1=code(xDif1,yDif1);
       }

       if(c==c2)
       {
           xDif2=x;
           yDif2=y;
           c2=code(xDif2,yDif2);
       }
}

 display();

}

void mykey(unsigned char key,int x,int y)
{
    if(key=='c')
    {  cout<<"Line is Clipped";
        cohen_Line(xDif1,yDif1,xDif2,yDif2);
        glFlush();
    }
}
void display()
{

   glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);

   glBegin(GL_LINE_LOOP);
   glVertex2i(xMin,yMin);
   glVertex2i(xMin,yMax);
   glVertex2i(xMax,yMax);
   glVertex2i(xMax,yMin);
   glEnd();
   glColor3f(1.0,0.0,0.0);
   glBegin(GL_LINES);
   glVertex2i(xDif1,yDif1);
   glVertex2i(xDif2,yDif2);
   glEnd();
   glFlush();


}


int main(int argc,char** argv)
{
    printf("Enter co-ordinates of the start and end points of line:");
    cin>>xDif1>>yDif1>>xDif2>>yDif2;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Cohen-Sutherland-Line-Clipping Algorithm");
    glutDisplayFunc(display);
    glutKeyboardFunc(mykey);
    init();
    glutMainLoop();
    return 0;
}

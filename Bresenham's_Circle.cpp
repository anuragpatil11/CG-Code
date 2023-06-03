#include<GL/glut.h>
#include<math.h>
#include <stdio.h>

int r;
int windowHeight=800;
int windowWeidth=800;

void drawpoint(int x,int y){

  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}

void Bresenhems(int Cx,int Cy,int r){

//int pk;
int x=0;
int y=r;
int pk=3-(2*r);

while(x<=y){
  drawpoint(x+Cx,y+Cy);
  drawpoint(y+Cx,x+Cy);
  drawpoint(-x+Cx,y+Cy);
  drawpoint(-y+Cx,x+Cy);
  drawpoint(-x+Cx,-y+Cy);
  drawpoint(-y+Cx,-x+Cy);
  drawpoint(x+Cx,-y+Cy);
  drawpoint(y+Cx,-x+Cy);
  
  if(pk<0){
    pk=pk+4*x+6;
  }
  else{
    pk=pk+4*(x-y)+10;
    y--;
  }
  x++;
}

}

void drawCordinateAxes(){

  glColor3f(1.0,1.0,1.0);
  glBegin(GL_LINES);
  glVertex2i(0,-windowHeight/2);
  glVertex2i(0,windowHeight/2);
  glEnd();
  
  glBegin(GL_LINES);
  glVertex2i(-windowWeidth/2,0);
  glVertex2i(windowWeidth/2,0);
  glEnd();
  
  glFlush();
}

void init(){

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glClearColor(0.0,0.0,0.0,0.0);
  //glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-windowHeight/2,windowHeight/2,-windowWeidth/2,windowWeidth/2);
}

void myDisplay(){

  glClear(GL_COLOR_BUFFER_BIT);
  drawCordinateAxes();
  glColor3f(0.0,0.0,1.0);
  glFlush();

}

void Mymouse(int button,int state,int x,int y){

  if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
  int Cx=x-windowWeidth/2;
  int Cy=windowHeight/2-y;
  //int r=200;
  Bresenhems( Cx,Cy, r);
  glFlush();
  }

}
int main(int argc,char** argv){
printf("Radius: \n");
scanf("%d",&r);
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(0,0);
glutInitWindowSize(windowHeight,windowWeidth);
glutCreateWindow("cgp2");

init();
glutDisplayFunc(myDisplay);
glutMouseFunc(Mymouse);

glutMainLoop();

return 0;

}

#include <GL/glut.h>
#include <math.h>
#include <cstdio>

int line_type,xa,ya,xb,yb;
int Round(float a){
  return (int)(a+0.5);
}

void dda(int xa,int xb,int ya,int yb,int line_type){
int steps,dx,dy;
dx=xb-xa;
dy=yb-ya;
if(abs(dx)>abs(dy)){
  steps=abs(dx);
}
else{
  steps=abs(dy);
}

float xinc,yinc,x,y;
xinc=dx/(float)(steps);
yinc=dy/(float)(steps);

x=xa;
y=ya;

glBegin(GL_POINTS);
glVertex2d(Round(x),Round(y));
for(int k=0;k<steps;k++){
if(line_type==1){
  x=x+xinc;
  y=y+yinc;
  glVertex2d(Round(x),Round(y));
  }
  else if(line_type==2){
  if(k%4!=0){
  glVertex2d(Round(x),Round(y));
  }
  x=x+xinc;
  y=y+yinc;
  }
  else if(line_type==3){
  if(k%4==0){
  glVertex2d(Round(x),Round(y));
  }
  x=x+xinc;
  y=y+yinc;
  }
  else if(line_type==4){
  glPointSize(6.0);
  x=x+xinc;
  y=y+yinc;
  glVertex2d(Round(x),Round(y));
  }
}
glEnd();
glFlush();
}

// it is for initialization of window's background color and window's coordinate
void init(){

  glClearColor(1.0,1.0,1.0,0.0);
  gluOrtho2D(0,800,0,800);

}

// it is for object drawn on the window
void draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,0.0,0.0);
  dda(0,800,400,400,1);
  dda(400,400,0,800,1);
  
}

void Mymouse(int button,int state,int x,int y){
 y=800-y;
  if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
  xa=x;
  ya=y;
  }
  if(button==GLUT_LEFT_BUTTON && state==GLUT_UP){
    xb=x;
    yb=y;
    glColor3f(0.0,0.0,1.0);
    dda(xa,xb,ya,yb,line_type);
  }

}
int main(int argc, char** argv){
printf("1.simple\n 2.dashed \n 3.dooted\n 4.Solid");
scanf("%d",&line_type);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(800,800);
  glutCreateWindow("dda_line");
  
  init();
  glutDisplayFunc(draw);
  glutMouseFunc(Mymouse);
  glutMainLoop();
  return 0;

}

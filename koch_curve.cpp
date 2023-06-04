#include<GL/glut.h>
#include<math.h>

# define RADIAN ( M_PI / 180 ) 

int windowHeight=800;
int windowWeidth=800;
int iteration=3;
int xa,ya,xb,yb;

bool mousePressedBefore=false;

void drawLine(int x1,int y1,int x2,int y2){
    glBegin(GL_LINES);
    glVertex2i(x1,y1);
    glVertex2i(x2,y2);
    glEnd();
}

void koch(double x1,double y1,double x2,double y2 ,int n){
    double x3 = (x2 + 2*x1) / 3.0;
    double y3 = (y2 + 2*y1) / 3.0;
    
    double x4 = (2*x2 + x1) / 3.0;
    double y4 = (2*y2 + y1) / 3.0;
    
    double xh = x4 + ((x3-x4)* cos(60 * RADIAN)) + ((y3-y4) * sin(60 * RADIAN));
    double yh = y4 - ((x3-x4)* sin(60*RADIAN)) + ((y3-y4) * cos(60*RADIAN));
    
    if(n<=1){
      drawLine(x1,y1,x3,y3);
      drawLine(x3,y3,xh,yh);
      drawLine(xh,yh,x4,y4);
      drawLine(x4,y4,x2,y2);
      return;
    }
    
      koch(x1,y1,x3,y3,n-1);
      koch(x3,y3,xh,yh,n-1);
      koch(xh,yh,x4,y4,n-1);
      koch(x4,y4,x2,y2,n-1);

}

void init(){
    glClearColor(0.0,0.0,0.0,0.0);
    //glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,windowHeight,0,windowWeidth);
}

void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    glFlush();
}

void myMouse(int button, int state ,int x,int y){
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
    if(mousePressedBefore==false){
    xa=x;
    ya=windowHeight-y;
    mousePressedBefore=true;
    }
    }
    else{
    xb=x;
    yb=windowHeight-y;
    koch(xa,ya,xb,yb,iteration);
    mousePressedBefore=false;
    }
    glFlush();

}
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(windowHeight,windowWeidth);
    glutCreateWindow("koch");
    
    init();
    glutDisplayFunc(myDisplay); 
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}

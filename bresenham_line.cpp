
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int windowWidth = 800;
int windowHeight = 800;
int lineType = 1;  // 1: Simple Line, 2: Dotted Line, 3: Dashed Line, 4: Solid Line
int xa, ya, xb, yb;

void drawCoordinateAxes() {
    glBegin(GL_LINES);
    glVertex2i(0, windowHeight / 2);
    glVertex2i(0, -windowHeight / 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(windowWidth / 2, 0);
    glVertex2i(-windowWidth / 2, 0);
    glEnd();

    glFlush();
}

void Init() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-windowWidth / 2, windowWidth / 2, -windowHeight / 2, windowHeight / 2);
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    drawCoordinateAxes();
    glFlush();
}

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void drawSimpleLine() {
    int dx = abs(xb - xa);
    int dy = abs(yb - ya);
    int x = xa;
    int y = ya;
    int xStep = (xa < xb) ? 1 : -1;
    int yStep = (ya < yb) ? 1 : -1;

    int p = 2 * dy - dx;

    while (x != xb) {
        setPixel(x, y);

        if (p >= 0) {
            y += yStep;
            p -= 2 * dx;
        }

        x += xStep;
        p += 2 * dy;
    }

    setPixel(xb, yb);
}

void drawDottedLine() {
   int dx = abs(xb - xa);
    int dy = abs(yb - ya);
    int x = xa;
    int y = ya;
    int xStep = (xa < xb) ? 1 : -1;
    int yStep = (ya < yb) ? 1 : -1;

    int p = 2 * dy - dx;
    int count = 0;

    while (x != xb) {
        if (count % 4 == 0) {
            setPixel(x, y);
        }

        if (p >= 0) {
            y += yStep;
            p -= 2 * dx;
        }

        x += xStep;
        p += 2 * dy;
        count++;
    }

    setPixel(xb, yb);
}

void drawDashedLine() {
   int dx = abs(xb - xa);
    int dy = abs(yb - ya);
    int x = xa;
    int y = ya;
    int xStep = (xa < xb) ? 1 : -1;
    int yStep = (ya < yb) ? 1 : -1;

    int p = 2 * dy - dx;
    int count = 0;

    while (x != xb) {
        if (count % 4 != 0) {
            setPixel(x, y);
        }

        if (p >= 0) {
            y += yStep;
            p -= 2 * dx;
        }

        x += xStep;
        p += 2 * dy;
        count++;
    }

   setPixel(xb, yb);
}

void drawSolidLine() {
    int dx = abs(xb - xa);
    int dy = abs(yb - ya);
    int x = xa;
    int y = ya;
    int xStep = (xa < xb) ? 1 : -1;
    int yStep = (ya < yb) ? 1 : -1;

    int p = 2 * dy - dx;

    while (x != xb) {
        glPointSize(3.0);
        setPixel(x, y);

        if (p >= 0) {
            y += yStep;
            p -= 2 * dx;
        }

        x += xStep;
        p += 2 * dy;
    }

    setPixel(xb, yb);
}

void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        xa = x - windowWidth / 2;
        ya = windowHeight / 2 - y;
    } //else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        else{
        xb = x - windowWidth / 2;
        yb = windowHeight / 2 - y;

        glColor3f(0.0, 0.0, 1.0);

        switch (lineType) {
            case 1:
                drawSimpleLine();
                break;
            case 2:
                drawDottedLine();
                break;
            case 3:
                drawDashedLine();
                break;
            case 4:
                drawSolidLine();
                break;
        }
        glFlush();
    }
}

void myKeyboard(unsigned char key, int x, int y) {
    if (key == '1') {
        lineType = 1;  // Simple Line
    } else if (key == '2') {
        lineType = 2;  // Dotted Line
    } else if (key == '3') {
        lineType = 3;  // Dashed Line
    } else if (key == '4') {
        lineType = 4;  // Solid Line
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Bresenham's Line Drawing Algorithm");

    Init();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();

    return 0;
}


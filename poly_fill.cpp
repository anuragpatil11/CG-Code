#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;

int windowWidth = 800;
int windowHeight = 800;
vector<pair<int, int>> vertices;
int fillType = 0; // 0: No fill, 1: Flood Fill, 2: Boundary Fill
int fillColor[3] = { 1, 1, 0 }; // Yellow color (RGB)

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
    glColor3f(1.0, 0.0, 0.0);
    drawCoordinateAxes();

    if (fillType == 1) {
        // Flood Fill
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
        for (int i = 0; i < vertices.size(); i++) {
            glVertex2i(vertices[i].first, vertices[i].second);
        }
        glEnd();
    } else if (fillType == 2) {
        // Boundary Fill
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
        for (int i = 0; i < vertices.size(); i++) {
            glVertex2i(vertices[i].first, vertices[i].second);
        }
        glEnd();
    }

    glFlush();
}

void floodFill(int x, int y) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    if (glGetError() == GL_NO_ERROR) {
        glColor3ub(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        floodFill(x + 1, y);
        floodFill(x - 1, y);
        floodFill(x, y + 1);
        floodFill(x, y - 1);
    }
}

void boundaryFill(int x, int y, int boundaryColor[3]) {
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    if (pixel[0] != boundaryColor[0] || pixel[1] != boundaryColor[1] || pixel[2] != boundaryColor[2]) {
        glColor3ub(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        boundaryFill(x + 1, y, boundaryColor);
        boundaryFill(x - 1, y, boundaryColor);
        boundaryFill(x, y + 1, boundaryColor);
        boundaryFill(x, y - 1, boundaryColor);
    }
}

void myMouse(int button, int action, int xMouse, int yMouse) {
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
        int x = xMouse - windowWidth / 2;
        int y = windowHeight / 2 - yMouse;
        vertices.push_back(make_pair(x, y));

        if (fillType == 1) {
            // Flood Fill
            glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(1.0, 1.0, 1.0);
            drawCoordinateAxes();

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glBegin(GL_POLYGON);
            for (int i = 0; i < vertices.size(); i++) {
                glVertex2i(vertices[i].first, vertices[i].second);
            }
            glEnd();

            glFlush();
        } else if (fillType == 2) {
            // Boundary Fill
            glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(1.0, 1.0, 1.0);
            drawCoordinateAxes();

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glBegin(GL_POLYGON);
            for (int i = 0; i < vertices.size(); i++) {
                glVertex2i(vertices[i].first, vertices[i].second);
            }
            glEnd();

            glFlush();
        }
    }
}

void processMenuEvents(int option) {
    switch (option) {
        case 0:
            fillType = 0; // No fill
            break;
        case 1:
            fillType = 1; // Flood Fill
            break;
        case 2:
            fillType = 2; // Boundary Fill
            break;
    }

    glutPostRedisplay();
}

void createGLUTMenus() {
    int menu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("No Fill", 0);
    glutAddMenuEntry("Flood Fill", 1);
    glutAddMenuEntry("Boundary Fill", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
//inilizeColor();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Polygon Filling");

    Init();
    createGLUTMenus();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();

    return 0;
}

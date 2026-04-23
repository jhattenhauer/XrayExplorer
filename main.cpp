#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include "visualSpace/cloud.cpp"
#include "visualSpace/perspective.cpp"

perspective ViewingAngle;
pointCloud PointCloudModel;

void initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.33, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void generateData() {
// Generate 200 points in the positive 3D space (0 → +2)
    for (int i = 0; i < 10000; i++) {
        Point p;
        p.x = (rand() % 100) / 5.0f; // 0.0 → 2.0
        p.y = (rand() % 100) / 5.0f; // 0.0 → 2.0
        p.z = (rand() % 100) / 5.0f; // 0.0 → 2.0

        p.r = 0.3f + static_cast<float>(rand()) / RAND_MAX * 0.7f;
        p.g = 0.3f + static_cast<float>(rand()) / RAND_MAX * 0.7f;
        p.b = 0.3f + static_cast<float>(rand()) / RAND_MAX * 0.7f;
        PointCloudModel.points.push_back(p);
    }
}

void drawAxes(float length) {
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(length, 0, 0); // X
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, length, 0); // Y
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, length); // Z
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, ViewingAngle.zoom);
    glRotatef(ViewingAngle.angleX, 1.0, 0.0, 0.0);
    glRotatef(ViewingAngle.angleY, 0.0, 1.0, 0.0);

    drawAxes(10.0f);

    glPointSize(6.0f);
    glBegin(GL_POINTS);
    for (auto &p : PointCloudModel.points) {
        glColor3f(p.r, p.g, p.b);
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    glutSwapBuffers();
}

void keyboardInput(unsigned char key, int, int) {
    switch (key) {
        case 'w': ViewingAngle.angleX -= 5.0f; break;
        case 's': ViewingAngle.angleX += 5.0f; break;
        case 'a': ViewingAngle.angleY -= 5.0f; break;
        case 'd': ViewingAngle.angleY += 5.0f; break;
        case '+': ViewingAngle.zoom += 0.5f; break;
        case '-': ViewingAngle.zoom -= 0.5f; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("3D Imager");
    initOpenGL();

    generateData();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardInput);

    glutMainLoop();
    return 0;
}
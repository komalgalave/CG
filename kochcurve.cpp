#include <GL/glut.h>
#include <math.h>

// Recursive function to draw the Koch curve
void drawKoch(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        return;
    }

    float dx = (x2 - x1) / 3.0f;
    float dy = (y2 - y1) / 3.0f;

    float xA = x1 + dx;
    float yA = y1 + dy;
    float xB = x1 + 2 * dx;
    float yB = y1 + 2 * dy;

    // Coordinates of the peak of the equilateral triangle
    float px = xA + (dx * cos(M_PI / 3.0f)) - (dy * sin(M_PI / 3.0f));
    float py = yA + (dx * sin(M_PI / 3.0f)) + (dy * cos(M_PI / 3.0f));

    // Recursive subdivision
    drawKoch(x1, y1, xA, yA, depth - 1);
    drawKoch(xA, yA, px, py, depth - 1);
    drawKoch(px, py, xB, yB, depth - 1);
    drawKoch(xB, yB, x2, y2, depth - 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.7f, 1.0f); // Koch line color
    glBegin(GL_LINES);
    drawKoch(-0.8f, 0.0f, 0.8f, 0.0f, 4);
    glEnd();
    glFlush();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Background color: black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1); // 2D orthographic projection
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Koch Curve");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

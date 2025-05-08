#include <GL/glut.h>
#include <cmath>

// Ball position and velocity
float x = -0.5f, y = 0.0f;
float vx = 0.001f, vy = 0.02f;
const float gravity = -0.0005f;
const float radius = 0.05f;

void drawBall(float x, float y) {
    int segments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.2f, 0.2f); // Red color
    glVertex2f(x, y);
    for (int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * M_PI / segments;
        glVertex2f(x + cosf(angle) * radius, y + sinf(angle) * radius);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBall(x, y);
    glutSwapBuffers();
}

void update(int value) {
    // Apply gravity and update position
    vy += gravity;
    y += vy;
    x += vx;

    // Bounce off bottom wall
    if (y - radius <= -1.0f) {
        y = -1.0f + radius;
        vy = -vy;
    }

    // Bounce off side walls
    if (x + radius >= 1.0f) {
        x = 1.0f - radius;
        vx = -vx;
    }
    if (x - radius <= -1.0f) {
        x = -1.0f + radius;
        vx = -vx;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // 2D view
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Continuous Bouncing Ball");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}

#include <iostream>
#include <GL/glut.h>
using namespace std;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set background color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);  // Set the orthogonal view
}

void bound_it(int x, int y, float* fillColor, float* bc) {
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color); // Read the pixel color

    // Check if pixel is neither boundary nor filled
    if ((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2]) &&
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {
        
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);  // Set the fill color
        glBegin(GL_POINTS);
        glVertex2i(x, y);  // Fill the pixel
        glEnd();

        // Perform the fill in all 8 directions
        bound_it(x + 1, y, fillColor, bc);
        bound_it(x - 1, y, fillColor, bc);
        bound_it(x, y + 1, fillColor, bc);
        bound_it(x, y - 1, fillColor, bc);
        bound_it(x + 1, y + 1, fillColor, bc);
        bound_it(x - 1, y - 1, fillColor, bc);
        bound_it(x - 1, y + 1, fillColor, bc);
        bound_it(x + 1, y - 1, fillColor, bc);
    }
}

void mouse(int btn, int state, int x, int y) {
    y = 480 - y;  // Invert y-coordinate because OpenGL origin is at the bottom-left
    if (btn == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            float boundaryColor[] = {1.0, 0.0, 0.0};  // Red boundary color
            float fillColor[] = {0.0, 0.0, 1.0};  // Blue fill color
            bound_it(x, y, fillColor, boundaryColor);  // Start the filling process
        }
    }
}

void world() {
    glLineWidth(3);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    glColor3f(1.0, 0.0, 0.0);  // Set color for the triangle
    glBegin(GL_LINE_LOOP);  // Draw a triangle
    glVertex2i(150, 100);
    glVertex2i(300, 300);
    glVertex2i(450, 100);
    glEnd();
    glFlush();  // Ensure that drawing is done
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Boundary Fill Algorithm");

    glutDisplayFunc(world);   // Set the display function
    glutMouseFunc(mouse);     // Set the mouse function
    init();                   // Initialize OpenGL settings

    glutMainLoop();           // Start the main loop
    return 0;
}


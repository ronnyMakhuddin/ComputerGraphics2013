/**
 * MTAT.03.015 Computer Graphics.
 * Lecture 5 visualization app.
 *
 * Copyright 2013, Konstantin Tretyakov
 */

#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
using namespace std;

#include "glu_invert_matrix.h"

float ASPECT_RATIO = 1.0; // Ew, don't ask why it's here before #include "scenes.h"
float DOF_Y = 45;
#include "scenes.h"

// Define some constants we shall need later
#define GLUT_KEY_ESCAPE 27  // The keycode for the escape key.
#define GLUT_KEY_ENTER 13   // The keycode for "enter" key.
#define GLUT_KEY_BACKSPACE 0x08

// --------------- Forward declarations ------------- //
int main(int argc, char* argv[]);
void keyboard(unsigned char key, int x, int y);
void display();
void idle();

SceneSet scenes;

// ----------------------------------------------- //
int main(int argc, char* argv[]) {
    // Initialize GLUT
    glutInit(&argc, argv);
    // Request a double-buffered, RGB display mode.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // Specify size and position of a window and create it
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Visualization");
    glutFullScreen();
    ASPECT_RATIO = (float)glutGet(GLUT_SCREEN_WIDTH)/glutGet(GLUT_SCREEN_HEIGHT);

    // Register handlers
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    // Lighting and depth testing for non-wireframe scene
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LINE_SMOOTH);   // Line antialiasing
    glEnable(GL_POLYGON_SMOOTH);// Polygon antialiasing
    glEnable(GL_BLEND);         // Antialiasing works only with blending enabled
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(1.5);

    scenes.push(new FirstScene());
    scenes.push(new SecondScene());
    scenes.push(new ThirdScene());
    scenes.push(new FourthScene());
    scenes.push(new FifthScene());
    scenes.push(new SixthScene(false, false, false, false));
    scenes.push(new SixthScene(true, false, false, false));
    scenes.push(new SixthScene(true, true, false, false));
    scenes.push(new SixthScene(true, true, true, true));
    scenes.current()->start();

    // Run the event loop
    glutMainLoop();

    for (int i = 0; i < scenes.size(); i++) delete scenes[i];
    return 0;
}

// ----------------------------------------------- //
void keyboard(unsigned char key, int x, int y) {
    if (key == GLUT_KEY_ESCAPE)
        glutLeaveMainLoop();
    else if (key == GLUT_KEY_ENTER || key == ' ')
        scenes.next();
    else if (key == GLUT_KEY_BACKSPACE)
        scenes.prev();
    else scenes.current()->start();

}

// ----------------------------------------------- //
void display() {
    scenes.current()->draw();
    glutSwapBuffers();
}

// ----------------------------------------------- //
void idle() {
    scenes.current()->idle();
}

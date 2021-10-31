 /*
  *  cube.c
  *  This program demonstrates a single modeling transformation,
  *  glScalef() and a single viewing transformation, gluLookAt().
  *  A wireframe cube is rendered.
  */
#include <GL/glut.h>
#include <stdlib.h>

float z = 5, x = 0;
bool fullscreen = false;
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();             /* clear the matrix */
            /* viewing transformation  */ //(相機位置, 看的方向, up-vector)
    gluLookAt(x, 0.0, z, x, 0.0, z-1.0, 0.0, 1.0, 0.0);
    glScalef(1.0, 2.0, 1.0);      /* modeling transformation */
    glutWireCube(1.0);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w,
            1.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
    else
        glOrtho(-1.0 * (GLfloat)w / (GLfloat)h,
            1.0 * (GLfloat)w / (GLfloat)h, -1.0, 1.0, -1.0, 1.0);
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int mouse_x, int y)
{
    switch (key) {
    case 'w':
        z--;
        glutPostRedisplay();
        break;
    case 's':
        z++;
        glutPostRedisplay();
        break;
    case 'a':
        x--;
        glutPostRedisplay();
        break;
    case 'd':
        x++;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    }


}
void specialKey(GLint key, GLint x, GLint y)
{
    if (key == GLUT_KEY_F11)
    {
        fullscreen = !fullscreen;

        if (fullscreen)
            glutFullScreen(); //全螢幕
        else
        {
            glutReshapeWindow(500, 500);
            glutPositionWindow(100, 100);
        }
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutMainLoop();
    return 0;
}


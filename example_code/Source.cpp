#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

static float robot_pos_x = 0;
static float robot_pos_y = 0;
static float robot_pos_z = 5;

static float cam_pos_x = 0;
static float cam_pos_z = 5;

static int body_angle = 0;
static int head_angle = 0;

static int body_axis_z = 1;
static int body_axis_y = 0;

static bool head_rotate = false;
static bool jump = false;
static bool up = true;

GLdouble wx= robot_pos_x, wy=0, wz= robot_pos_z -1;  /*  returned world x, y, z coords  */


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex3f(x1, y1,0);
    glVertex3f(x2, y2,0);
    glVertex3f(x3, y3,0);
    glEnd();
    glPopMatrix();
}

void drawTree() {
    glPushMatrix();
    glScaled(2, 2, 0);
    glColor3f(0.54296875, 0.26953125, 0.07421875);
    drawTriangle(0, 0.7, -0.3, -1.2, 0.3, -1.2);
    drawTriangle(0.4, 0.4, -0.1, -0.5, 0.1, -0.5);
    drawTriangle(-0.4, 0.4, -0.1, -0.5, 0.1, -0.5);

    glColor3f(0.49609375, 1, 0);
    glRectd(-1, -0.3, 1, 1.2);

    glPopMatrix();

}

void drawBackground() {

    glPushMatrix();
    glTranslated(10, 0, -8);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2, 0, 5);
    drawTree();
    glPopMatrix();
}

void drawRobot() {
    glPushMatrix();

    glTranslated((float)robot_pos_x, robot_pos_y,(double)robot_pos_z);

    //head
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    GLdouble eqn[4] = { 0.0, 1.0, 0.0, 0.0 };
    /*    clip  y < 0          */
    glClipPlane(GL_CLIP_PLANE0, eqn);
    glEnable(GL_CLIP_PLANE0);
    glTranslated(0, 0.2, 0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glRotated(head_angle, 0, 0, 1);

    glutWireSphere(0.8, 20, 16);
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();

    //body
    glPushMatrix();
    glTranslated(0, -1.5, 0);
    glRotatef(90, 0, body_axis_y, body_axis_z);
    glRotatef(body_angle, 0, 0, 1);
    glutWireSphere(1.5, 20, 10);
    glPopMatrix();

    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    gluLookAt((float)cam_pos_x+robot_pos_x, 0.0, (double)cam_pos_z+10+robot_pos_z, wx, wy, wz, 0.0, 1.0, 0.0);

    drawBackground();
    drawRobot();

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    

}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
        body_angle = (body_angle + 5) % 360;
        body_axis_z = 0;
        body_axis_y = 1;
        --robot_pos_z;
        glutPostRedisplay();
        break;
    case 's':
        body_angle = (body_angle - 5) % 360;
        body_axis_z = 0;
        body_axis_y = 1;
        ++robot_pos_z;
        glutPostRedisplay();
        break;
    case 'a':
        body_angle = (body_angle + 5) % 360;
        body_axis_z = 1;
        body_axis_y = 0;
        --robot_pos_x;
        glutPostRedisplay();
        break;
    case 'd':
        body_angle = (body_angle - 5) % 360;
        body_axis_z = 1;
        body_axis_y = 0;
        ++robot_pos_x;
        glutPostRedisplay();
        break;

    case 32: //space
        jump = true;
        break;
        
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}


void idle() {
    if (head_rotate) {
        head_angle = (head_angle + 5) % 360;
        glutPostRedisplay();
    }

    if (jump) {
        if (up) {
            robot_pos_y+=0.01;
        }
        else {
            robot_pos_y -= 0.01;
        }

        if (robot_pos_y > 5) up = false;
        if (robot_pos_y < 0) {
            robot_pos_y = 0;
            jump = false;
            up = true;
        }
        glutPostRedisplay();
    }


}

void mouse(int button, int state, int x, int y)
{


    switch (button) {
    case GLUT_MIDDLE_BUTTON:
        if (state == GLUT_DOWN) head_rotate = !head_rotate;
        break;
            

    default:
        break;
    }
}
void motion(int x, int y) {
    GLint viewport[4];
    GLdouble mvmatrix[16], projmatrix[16];
    GLint realy;  /*  OpenGL y coordinate position  */

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
    /*  note viewport[3] is height of window in pixels  */
    realy = viewport[3] - (GLint)y - 1;
    //printf("Coordinates at cursor are (%4d, %4d)\n", x, realy);

    gluUnProject((GLdouble)x, (GLdouble)realy, 1.0,
        mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
    //printf("World coords at z=1.0 are (%f, %f, %f)\n",
        //wx, wy, wz);

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}

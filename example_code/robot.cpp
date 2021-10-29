 /*
  * robot.c
  * This program shows how to composite modeling transformations
  * to draw translated and rotated hierarchical models.
  * Interaction:  pressing the s and e keys (shoulder and elbow)
  * alters the rotation of the robot arm.
  * 記住矩陣乘的順序是由下往上看
  */
#include <GL/glut.h>
#include <stdlib.h>

static int shoulder = 0, elbow = 0;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
        glTranslatef(-1.0, 0.0, 0.0);////旋轉完將方塊左移1(移回去)
        glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);//旋轉
        glTranslatef(1.0, 0.0, 0.0);//將方塊右移1(左邊移到中心點)
        glPushMatrix();
            glScalef(2.0, 0.4, 1.0); //x放大兩倍
            glutWireCube(1.0);
        glPopMatrix();//返回到已旋轉的矩陣

        glTranslatef(1.0, 0.0, 0.0);//旋轉完再右移1
        glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);//旋轉
        glTranslatef(1.0, 0.0, 0.0);//將方塊右移1(方塊左邊移到旋轉中心點)
        glPushMatrix();
            glScalef(2.0, 0.4, 1.0);
            glutWireCube(1.0);
        glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION); //將當前矩陣指定為投影矩陣，之後可調用glFrustum()或gluPerspective()
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW); //對模型視景矩陣操作
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 's':
        shoulder = (shoulder + 5) % 360;
        glutPostRedisplay();
        break;
    case 'S':
        shoulder = (shoulder - 5) % 360;
        glutPostRedisplay();
        break;
    case 'e':
        elbow = (elbow + 5) % 360;
        glutPostRedisplay();
        break;
    case 'E':
        elbow = (elbow - 5) % 360;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}


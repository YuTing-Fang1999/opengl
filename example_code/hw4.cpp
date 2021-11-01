/***************************
4107056005 方郁婷 第IV次作業11/10
***************************/

//include glew and freeglut libs/dlls
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream> 

using namespace std;

static int shoulderz = 325, shouldery = -160, shoulderx = 0;
static int elbowz = 330, elbowy = -305, elbowx = 0;

static float year = 0, day = 0;

void solarDisplay(void)
{
    year = year + (float)360 / 365 / 30; //一天轉的角度分為30次轉
    if (year > 360) year = 0;
    day = day + (float)360 / 30; //一天轉的角度分為30次轉
    if (day > 360) day = 0;
    glutPostRedisplay();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glutIdleFunc(solarDisplay);

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    //開始畫機械手臂
    glPushMatrix();
    //glTranslatef(-5.0, -5.0, 0.0);

    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulderz, 0.0, 0.0, 1.0);//旋轉
    glRotatef((GLfloat)shouldery, 0.0, 1.0, 0.0);//旋轉
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2, 1.0, 1.0); //x放大兩倍
    glColor3f(0.0, 1.0, 0.0);
    glutSolidCube(1.0);
    glColor3f(1.0, 0.0, 0.0);
    glutWireCube(1.0);
    glPopMatrix();//返回到已旋轉的矩陣

    glTranslatef(1.0, 0.0, 0.0);//旋轉完再右移1
    glRotatef((GLfloat)elbowz, 0.0, 0.0, 1.0);//旋轉
    glRotatef((GLfloat)elbowy, 0.0, 1.0, 0.0);//旋轉
    glTranslatef(1.0, 0.0, 0.0);//將方塊右移1(方塊左邊移到旋轉中心點)
    glPushMatrix();
    glScalef(2.0, 1.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    //目前是小臂方塊，開始畫第一根手指
    glPushMatrix(); 
    glTranslatef(1.0, 0.5, 0.3);
    glRotatef(45, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);

    glPushMatrix();
    glScalef(1.0, 0.3, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(0.5, 0, 0);
    glRotatef(-45, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);

    glPushMatrix();
    glScalef(1.0, 0.3, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();
    //目前是小臂方塊，開始畫第二根手指
    glPushMatrix(); 
    glTranslatef(1.0, 0.5, 0.0);
    glRotatef(45, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);

    glPushMatrix();
    glScalef(1.0, 0.3, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(0.5, 0, 0);
    glRotatef(-45, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);

    glPushMatrix();
    glScalef(1.0, 0.3, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();
    //目前是小臂方塊，開始畫第三根手指
    glPushMatrix(); 
    glTranslatef(1.0, 0.5, -0.3);
    glRotatef(45, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);

    glPushMatrix();
    glScalef(1.0, 0.3, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(0.5, 0, 0);
    glRotatef(-45, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);

    glPushMatrix();
    glScalef(1.0, 0.3, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();
    //目前是小臂方塊，開始畫第四根手指
    glPushMatrix(); 
        glTranslatef(1.0, -0.5, 0);
        glRotatef(-45, 0.0, 0.0, 1.0);
        glTranslatef(0.5, 0.0, 0.0);

        glPushMatrix();
        glScalef(1.0, 0.3, 0.3);
        glutWireCube(1.0);
        glPopMatrix();

        glTranslatef(0.5, 0, 0);
        glRotatef(45, 0.0, 0.0, 1.0);
        glTranslatef(0.5, 0.0, 0.0);

        glPushMatrix();
        glScalef(1.0, 0.3, 0.3);
        glutWireCube(1.0);
        glPopMatrix();

    glPopMatrix(); 
    //太陽系
    glTranslatef(4, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(1.0, 20, 16);   /* draw sun */
    glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
    glTranslatef(2, 0.0, 0.0);
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glutWireSphere(0.2, 10, 8);    /* draw smaller planet */

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION); //將當前矩陣指定為投影矩陣，之後可調用glFrustum()或gluPerspective()
    glLoadIdentity();
    gluPerspective(80.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW); //對模型視景矩陣操作
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'u':
            shoulderz = (shoulderz + 5) % 360;
            glutPostRedisplay();
            break;
        case 'j':
            shouldery = (shouldery - 5) % 360;
            glutPostRedisplay();
            break;
        case 'i':
            elbowz = (elbowz + 5) % 360;
            glutPostRedisplay();
            break;
        case 'k':
            elbowy = (elbowy - 5) % 360;
            glutPostRedisplay();
            break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }

    printf("%d, %d, %d, %d\n", shoulderz, shouldery, elbowz, elbowy);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

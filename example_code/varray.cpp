 /*
  *  varray.c
  *  This program demonstrates vertex arrays.
  */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef GL_VERSION_1_1
#define POINTER 1
#define INTERLEAVED 2

#define DRAWARRAY 1
#define ARRAYELEMENT  2
#define DRAWELEMENTS 3

int setupMethod = POINTER;
int derefMethod = DRAWARRAY;

void setupPointers(void)
{
    static GLint vertices[] = { 25, 25, //(x, y)
                        100, 325,
                        175, 25,
                        175, 325,
                        250, 25,
                        325, 325 };
    static GLfloat colors[] = { 1.0, 0.2, 0.2, //(R, G, B)
                        0.2, 0.2, 1.0,
                        0.8, 1.0, 0.2,
                        0.75, 0.75, 0.75,
                        0.35, 0.35, 0.35,
                        0.5, 0.5, 0.5 };

    glEnableClientState(GL_VERTEX_ARRAY); //要記得enable才能使用array
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_INT, 8, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    // (size, type, stride, *pointer)
    // size 指定了每個element所需的個數
    // stride 指定了從這個element移動到下個element所需要的byte
    // If you pass a zero as stride, it means they are tightly packed. 
    // 在glVertexPointer中我們是用INT，一個INT是4個byte
    // vertices is x1,y1,x2,y2,.. and so on
    // 代表指向下一個element要移動 2 * 4 個byte
    // 所以寫0和寫8是同等意思
    // 為什麼要這麼做?
    // 因為我們的array可以塞其他東西(向量、顏色等等) 
    // ex: {x1,y1,nx1,ny1,r1,g1,b1,a1, x2,y2,nx2,ny2,r2,g2,b2,a2}
    // 這時移動到下個element可就不只vertex的個數了(2)，而是 8 * 4 個byte
    // 在某些情況下，在單一陣列中儲存頂點和屬性，會比使用不同的陣列更有效率 (請參閱 glInterleavedArrays) 。
}

void setupInterleave(void)
{
    static GLfloat intertwined[] =
    { 1.0, 0.2, 1.0, 100.0, 100.0, 0.0, //(R, G, B, x, ,y, z)
     1.0, 0.2, 0.2, 0.0, 200.0, 0.0,
     1.0, 1.0, 0.2, 100.0, 300.0, 0.0,
     0.2, 1.0, 0.2, 200.0, 300.0, 0.0,
     0.2, 1.0, 1.0, 300.0, 200.0, 0.0,
     0.2, 0.2, 1.0, 200.0, 100.0, 0.0 };

    glInterleavedArrays(GL_C3F_V3F, 0, intertwined);
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH); //默認為GL_SMOOTH(自行計算過度色)，GL_FLAT不會有過度色(混色)
    setupPointers();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (derefMethod == DRAWARRAY)
        glDrawArrays(GL_TRIANGLES, 0, 6); //從第0個開始畫之後6個點
    else if (derefMethod == ARRAYELEMENT) {
        glBegin(GL_TRIANGLES);
        glArrayElement(2);
        glArrayElement(3);
        glArrayElement(5);
        glEnd();
    }
    else if (derefMethod == DRAWELEMENTS) {
        GLuint indices[5] = { 0, 1, 3, 4, 5 };

        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, indices); //畫前4個點
    }
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // (目前左下角位置(相對坐標系), 視窗寬高)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);// (左下角座標, 右上角座標)
}

void mouse(int button, int state, int x, int y)
{
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            if (setupMethod == POINTER) {
                setupMethod = INTERLEAVED;
                setupInterleave();
            }
            else if (setupMethod == INTERLEAVED) {
                setupMethod = POINTER;
                setupPointers();
            }
            glutPostRedisplay();
        }
        break;
    case GLUT_MIDDLE_BUTTON:
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN) {
            if (derefMethod == DRAWARRAY)
                derefMethod = ARRAYELEMENT;
            else if (derefMethod == ARRAYELEMENT)
                derefMethod = DRAWELEMENTS;
            else if (derefMethod == DRAWELEMENTS)
                derefMethod = DRAWARRAY;
            glutPostRedisplay();
        }
        break;
    default:
        break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27: //esc
        exit(0);
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(350, 350);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
#else
int main(int argc, char** argv)
{
    fprintf(stderr, "This program demonstrates a feature which is not in OpenGL Version 1.0.\n");
    fprintf(stderr, "If your implementation of OpenGL Version 1.0 has the right extensions,\n");
    fprintf(stderr, "you may be able to modify this program to make it run.\n");
    return 0;
}
#endif

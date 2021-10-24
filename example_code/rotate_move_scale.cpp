#include<GL/glut.h>
#include <windows.h>

static GLfloat spin = 0.0;				//旋轉量
static GLfloat move = 0.0;				//平移量
static GLfloat size = 1.0;				//縮放量

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);		//指定清除顏色（黑色），即背景顏色
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);		//清除所有的畫素
	glPushMatrix();
	glTranslatef(move, 0, 0);				//移動，引數含義(x軸位移,y軸位移,z軸位移)
	glRotatef(spin, 0, 0, 1);				//旋轉，引數含義(旋轉量,x軸,y軸,z軸)
	glScalef(size, size, 1);				//縮放，引數含義(x軸倍數,y軸倍數,z軸倍數)
	glColor3f(0.0, 1.0, 0.0);				//繪製顏色RGB
	glRectf(-25.0, -25.0, 25.0, 25.0);		//繪製矩形
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
}

void spinAndSizeDisplay()
{
	spin > 360 ? spin -= 360 : spin += 2;
	size > 2 ? size -= 2 : size += 0.003;
	glutPostRedisplay();				//標記當前視窗需要重繪，否則不會旋轉
	Sleep(10);
}

void moveDisplay()
{
	move = move > 20 ? move -= 20 : move += 1;
	glutPostRedisplay();				//標記當前視窗需要重繪，否則不會旋轉
	Sleep(10);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);							//初始化GLUT並處理命令列引數
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);		//指定模式：雙快取；RGB模式
	glutInitWindowSize(250, 250);					//指定視窗大小（畫素）
	glutInitWindowPosition(300, 200);				//指定視窗左上角在螢幕上的位置
	glutCreateWindow(argv[0]);						//使用OpenGL場景建立一個視窗，引數為視窗名稱
	init();											//呼叫初始化函式
	glutDisplayFunc(display);						//顯示
	glutReshapeFunc(reshape);						//重繪
	glutIdleFunc(spinAndSizeDisplay);				//旋轉&縮放
	//glutIdleFunc(moveDisplay);						//移動(與上邊函式只能有一個有效)
	glutMainLoop();									//進入主迴圈並處理事件，此時建立的所有視窗都會顯示出來，被渲染到這些視窗中的內容也將顯示出來，程式開始處理事件，註冊的顯示回撥函式被觸發
	return 0;										//ANSI C要求函式main()返回一個int值
}

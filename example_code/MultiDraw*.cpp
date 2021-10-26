/***************************
4107056005 方郁婷 第三次作業10/27
***************************/

//include glew and freeglut libs/dlls
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream> 

using namespace std;

void setupVertexAndColor() {
	static GLint logoG_interleaved[] = {
		778, 274,	0,1,0,
		791, 203,	0,1,0,
		878, 177,	0,1,0,
		850, 265,	0,1,0,

		788, 212,	0,1,0,
		767, 141,	0,1,0,
		843, 159,	0,1,0,
		882, 250,	0,1,0,

		841, 159,	0,1,0,
		917, 139,	0,1,0,
		891, 219,	0,1,0,
		819, 237,	0,1,0,

		895, 214,	0,1,0,
		906, 274,	0,1,0,
		846, 264,	0,1,0,
		806, 177,	0,1,0,
	};

}

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnableClientState(GL_VERTEX_ARRAY); //要記得enable才能使用array
	glEnableClientState(GL_COLOR_ARRAY); //要記得enable才能使用array
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,  w, 0, h); //將normalize投影在哪些範圍的座標
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	static GLfloat logoG_interleaved[] = {
				0,1,0,		778, 274,0,
				0,1,0,		791, 203,0,
				0,1,0,		878, 177,0,
				0,1,0,		850, 265,0,

				0,1,0,		788, 212,0,
				0,1,0,		767, 141,0,
				0,1,0,		843, 159,0,
				0,1,0,		882, 250,0,

				0,1,0,		841, 159,0,
				0,1,0,		917, 139,0,
				0,1,0,		891, 219,0,
				0,1,0,		819, 237,0,

				0,1,0,		895, 214,0,
				0,1,0,		906, 274,0,
				0,1,0,		846, 264,0,
				0,1,0,		806, 177,0
	};
	glInterleavedArrays(GL_C3F_V3F, 0, logoG_interleaved);

	//glMultiDrawArrays
	//static GLint logo_first_g[] = { 0, 4, 8, 12 };
	//static GLint logo_count_g[] = { 4, 4, 4, 4 };
	//glMultiDrawArrays(GL_POLYGON, logo_first_g, logo_count_g, 4);

	//glMultiDrawElements
	static GLint logo_count_g[] = { 4, 4 };
	static GLint logo_g1[] = { 0, 1, 2, 3 };
	static GLint logo_g2[] = { 4, 5, 6, 7 };
	static GLvoid* logo_g_indices[] = { logo_g1, logo_g2 };
	glMultiDrawElements(GL_QUADS, logo_count_g, GL_UNSIGNED_INT, logo_g_indices, 2);

	glPopMatrix();


	glutSwapBuffers();
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(955, 600);
	glutCreateWindow("nchu logo");

	init();

	// Bind the two functions (above) to respond when necessary
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	// Very important!  This initializes the entry points in the OpenGL driver so we can 
	// call all the functions in the API.
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}


	glutMainLoop();
	return 0;
}

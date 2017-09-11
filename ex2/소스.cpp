#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <math.h>
#include <time.h>

#define POINTS 100

GLfloat pos[POINTS][2];
GLfloat Width = 600.0;
GLfloat Height = 600.0;
GLint n = 0;

void RenderScene(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glPointSize(10.0f);
	glEnableClientState(GL_VERTEX_ARRAY);// enable array

	for (i = 0; i < 3; i++)
	{
		glBegin(GL_POINTS);
		glVertex2f(pos[i][0], pos[i][1]);
	}
	//
	if (i>2 && (pos[2][0] != 0))
	{
		glBegin(GL_TRIANGLES);
		glVertex2f(pos[0][0], pos[0][1]);
		glVertex2f(pos[1][0], pos[1][1]);
		glVertex2f(pos[2][0], pos[2][1]);
	}
	//
	glEnd();
	glFlush();
}

void mousebutton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			pos[n][0] = x / Width;
			pos[n][1] = (Height - y) / Height;
			if (n > 2)
			{
				pos[n % 3][0] = pos[n][0];
				pos[n % 3][1] = pos[n][1];
			}
			//if (n < 3)
			//{
			n++;
			//}
			/*
			if (n > 2)
			{
			pos[n - 3][0] = pos[n][0];
			pos[n - 3][1] = pos[n][1];
			//	n = 0;
			}*/
			RenderScene();
		}
		/*
		if (state == GLUT_UP)
		{
		if (n > 3)
		{
		pos[(n-1) % 3][0] = pos[n-1][0];
		pos[(n-1) % 3][1] = pos[n-1][1];
		pos[n - 1][0] = NULL;
		pos[n - 1][1] = NULL;
		RenderScene();
		}
		}
		*/
	}
}

void ChangeSize(int w, int h)
{
	GLfloat asepectRatio;

	Width = w;
	Height = h;

	if (Height == 0)
		Height = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*
	if (w <= h)
	gluOrtho2D(-2.0, 2.0, -2.0*(float)w, 2.0*(float)h/(float)w);
	else
	gluOrtho2D(-2.0*(float)w/(float)h, 2.0*(float)w/(float)h, -2.0, 2.0);
	*/
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}
void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("ex2");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(mousebutton);

	glutMainLoop();
}
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

static bool mouseLeftDown;
static float point[2][2];
void mouseButton(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void timer(int value);
void timer2(int value);
void rotate();
int a, b, c;
bool rot = true;
static float theta;
int r;

void menu(int item)
{
	keyboard((unsigned char)item, 0, 0);
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q' | 'Q':
		exit(0); break;
	case VK_ESCAPE:
		exit(0); break;
	case 1:
		exit(0); break;
	case 2:
		exit(0); break;
	case 'R' | 'r':
		rotate(); break;
	default:
		break;
	}
}
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	float cos_th = cos(theta * 3.14159 / 180.0);
	float sin_th = sin(theta * 3.14159 / 180.0);

	glColor3f(a, b, c);
	glBegin(GL_POLYGON);
	{
		glVertex2f(cos_th, sin_th);
		glVertex2f(-sin_th, cos_th);
		glVertex2f(-cos_th, -sin_th);
		glVertex2f(sin_th, -cos_th);
	}
	glEnd();
	glutSwapBuffers();
}

void init(void)
{
	mouseLeftDown = false;

	point[0][0] = 0;
	point[0][1] = 0;
	point[1][0] = 0;
	point[1][1] = 0;

	theta = 0;
}

void SetupRc(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void ChangeSize(int w, int h)
{
	GLfloat aspectRatio;

	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
	{
		gluOrtho2D(-2.0, 2.0, -2.0*(float)h / (float)w, 2.0*(float)h / (float)w);
	}
	else
	{
		gluOrtho2D(-2.0*(float)w / (float)h, 2.0*(float)w / (float)h, -2.0, 2.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("ex1");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutTimerFunc(1000 / 30, timer, 1); //timer ½ÇÇà
	glutKeyboardFunc(keyboard);

	glutCreateMenu(menu);
	glutAddMenuEntry("1", 1);
	glutAddMenuEntry("2", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	SetupRc();
	srand(time(NULL));
	glutMainLoop();
}

void mouseButton(int button, int state, int x, int y)
{
	int r;
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			if (!mouseLeftDown)
			{
			}
			r = rand() % 3;
			if (r == 0)
			{
				if (a == 0)
					a = 1;
				else
					a = 0;
				glutPostRedisplay();
			}
			else if (r == 1)
			{
				if (b == 0)
					b = 1;
				else
					b = 0;
				glutPostRedisplay();
			}
			else
			{
				if (c == 0)
					c = 1;
				else
					c = 0;
				glutPostRedisplay();
			}
		}
		else if (state == GLUT_UP)
		{
			if (mouseLeftDown)
				mouseLeftDown = false;
		}
	}
}

void mouseMotion(int x, int y)
{
	if (mouseLeftDown)
	{
		double viewport[4];
		glGetDoublev(GL_VIEWPORT, viewport);

		point[1][0] = x / (float)viewport[2] * 500;
		point[1][1] = (viewport[3] - y) / (float)viewport[3] * 500;
	}
	glutPostRedisplay();
}

void timer(int value)
{
	if (rot)
	{
		theta += 2.0;
		if (theta >= 360.0)
			theta -= 360.0;
	}
	else
	{
		theta -= 2.0;
		if (theta <= 360.0)
			theta += 360.0;
	}
	glutTimerFunc(1000 / 30, timer, 1);
	glutPostRedisplay();
}

void rotate()
{
	if (rot)
		rot = false;
	else
		rot = true;
}
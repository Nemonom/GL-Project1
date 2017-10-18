#pragma once
#include <GL/glut.h>    
#include <Windows.h>
#include "gl_object.h"
using namespace std;

#define width 800
#define height 600

#define PI 3.141592
#define RADIAN(X) (PI / 180) * X

///////////////////////////�ݹ��Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int v);
GLvoid Keyboard(unsigned char key, int x, int y);//Ű����
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);


 /////////////�Լ�
bool isthattrue();
void cut();
void draw_line();

////////////����
gl_object bottle;
gl_object water;
gl_object parent;
gl_object child;

vector2 parent[4];
vector2 line[2];

bool cut_success = false; // �ڸ�
bool in_success = false; // ��

int collision = 0;
float mouse_dot[2][2] = { 0 };

void main(int argc, char *argv[]) {

	srand(time(NULL));

	parent.set_r(rand() % 15 + 20, rand() % 15 + 20);
	parent.init(4, 1, 0, 200);
	bottle.set_r(100, 50);
	bottle.init(4, 1, 0, -200);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // ���÷��� ��� ����
	glutInitWindowPosition(100, 100);    // �������� ��ġ���� 
	glutInitWindowSize(width, height);    // �������� ũ�� ����
	glutCreateWindow("project1");    // ������ ���� (������ �̸�)  
	glutDisplayFunc(drawScene);    // ��� �Լ��� ����
	glutTimerFunc(50, TimerFunction, 1); // Ÿ�̸� �Լ� ����
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse); glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);//Ű����
	glutMainLoop();
}

GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // ������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	bottle.move();
	parent.move();

	bottle.draw(1);
	parent.draw(0);

	if (collision == 1)
		draw_line();


	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1, 1);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'p':
		parent.set_r(rand() % 20 + 20, rand() % 20 + 20);
		parent.init(4, 1, 0, 200);
		bottle.init(4, 1, 0, -200);
		cut_success = false;
		in_success = false;
		break;

	case 'q':
		PostQuitMessage(0);
		break;
	}
}

void Motion(int x, int y)
{
	if (collision == 1)
	{
		mouse_dot[collision][0] = x - width/2;
		mouse_dot[collision][1] = -(y - height/2);
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && collision == 0)
	{
		mouse_dot[collision][0] = x - width/2;
		mouse_dot[collision][1] = -(y - height/2);
		mouse_dot[collision+1][0] = x - width / 2;
		mouse_dot[collision+1][1] = -(y - height / 2);
		collision++;
	}


	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		mouse_dot[collision][0] = x - width/2;
		mouse_dot[collision][1] = -(y - height/2);
		collision = 0;;
	}
}

void TimerFunction(int value) {
	glutPostRedisplay();   // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ���� 
}

void draw_line()
{
	glBegin(GL_LINES);
	for (int i = 0; i < 2; ++i)
	{
		glColor4f(0.8 - 0.2 * i, 0.4f + i * 0.2, 0.8f + i * 0.2, 1.0f);//����
		glVertex2f(mouse_dot[i][0], mouse_dot[i][1]);
	}
	glEnd();
}

void rotate()
{
	
}

bool isthattrue()
{




	return true;
}

void cut()
{

}
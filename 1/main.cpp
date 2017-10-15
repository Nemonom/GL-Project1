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

 /////////////�Լ�


////////////����
gl_object bottle;
gl_object parent;
gl_object child[2];

bool cut_success = false; // �ڸ�
bool in_success = false; // ��

void main(int argc, char *argv[]) {

	srand(time(NULL));

	parent.set_r(rand() % 15 + 20);
	parent.init(4, 1, 0, 200);
	bottle.set_r(60);
	bottle.init(4, 1, 0, -200);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // ���÷��� ��� ����
	glutInitWindowPosition(100, 100);    // �������� ��ġ���� 
	glutInitWindowSize(width, height);    // �������� ũ�� ����
	glutCreateWindow("project1");    // ������ ���� (������ �̸�)  
	glutDisplayFunc(drawScene);    // ��� �Լ��� ����
	glutTimerFunc(50, TimerFunction, 1); // Ÿ�̸� �Լ� ����
	glutReshapeFunc(Reshape);
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
		parent.set_r(rand() % 20 + 20);
		parent.init(4, 1, 0, 200);
		bottle.init(4, 1, 0, -200);
		success = false;
		break;

	case 'q':
		PostQuitMessage(0);
		break;
	}
}

void TimerFunction(int value) {
	glutPostRedisplay();   // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ���� 
}

void rotate()
{
	
}

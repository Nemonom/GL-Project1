#pragma once
#include <GL/glut.h>    
#include <Windows.h>
#include "gl_object.h"
#include "vector2.h"

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

//vector2 v_parent[4];
//vector2 line[2];

POINT p_parent[4];
POINT p_line[2];

//vector2 p1, p2, p3, p4;
POINT a1, a2, a3, a4; // ����� ����Ʈ

bool cut_success = false; // �ڸ�
bool in_success = false; // ��

int collision = 0;
float mouse_dot[2][2] = { 0 };

int collision_case = 0; // ��� �ε���?



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


	//	///////////���Ϳ�
	//	line[0].put_x(mouse_dot[0][0]);
	//	line[0].put_y(mouse_dot[0][1]);		
	//	line[1].put_x(mouse_dot[1][0]);
	//	line[1].put_y(mouse_dot[1][1]);



		//////////////����Ʈ��
		p_line[0].x = mouse_dot[0][0];
		p_line[0].y = mouse_dot[0][1];
		p_line[1].x = mouse_dot[1][0];
		p_line[1].y = mouse_dot[1][1];

		isthattrue();

		collision = 0;

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
	for (int i = 0; i < 4; ++i)
	{
		//////////���Ϳ�
	//	v_parent[i].put_x(parent.get_dot_x(i));
	//	v_parent[i].put_y(parent.get_dot_y(i));

		//////////����Ʈ��
		p_parent[i].x = parent.get_dot_x(i);
		p_parent[i].y = parent.get_dot_y(i);
	}	

	///////////����Ʈ
	GetIntersectPoint(p_parent[0], p_parent[1], p_line[0], p_line[1], &a1);
	GetIntersectPoint(p_parent[2], p_parent[3], p_line[0], p_line[1], &a2);
	GetIntersectPoint(p_parent[0], p_parent[3], p_line[0], p_line[1], &a3);
	GetIntersectPoint(p_parent[1], p_parent[2], p_line[0], p_line[1], &a4);


	/////////////����
	//segmentIntersection(v_parent[0], v_parent[1], line[0], line[1], p1);
	//segmentIntersection(v_parent[2], v_parent[3], line[0], line[1], p2);
	//segmentIntersection(v_parent[0], v_parent[3], line[0], line[1], p3);
	//segmentIntersection(v_parent[1], v_parent[2], line[0], line[1], p4);
	

	return false;
}

void cut()
{

}
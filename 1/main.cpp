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

///////////////////////////콜백함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int v);
GLvoid Keyboard(unsigned char key, int x, int y);//키보드
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);


 /////////////함수
bool isthattrue();
void cut();
void draw_line();
void follow(gl_object* p);
void water_cut(gl_object* p);

////////////변수
gl_object bottle;
gl_object water;
gl_object parent;
gl_object child;

//vector2 v_parent[4];
//vector2 line[2];

POINT p_parent[4];
POINT p_line[2];
POINT p_fall[4];
POINT p_water[2];
//vector2 p1, p2, p3, p4;
POINT a1, a2; // 저장용 포인트
POINT b1, b2;
bool cut_success = false; // 자름
bool in_success = false; // 들어감

int collision = 0;
float mouse_dot[2][2] = { 0 };

int cut_case = 0; // 어떻게 부딪힘?



void main(int argc, char *argv[]) {

	srand(time(NULL));

	parent.set_r(rand() % 15 + 20, rand() % 10 + 50);
	parent.init(4, 1, 0, 200);
	child.set_r(0, 0);
	child.init(4, 1, 0, 200);
	bottle.set_r(100, 50);
	bottle.init(4, 1, 0, -200);
	water.set_r(100, 25);
	water.init(4, 1, 0, -225);
	water.set_spd(bottle.get_spd());
	water.set_status(5);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);    // 윈도우의 위치지정 
	glutInitWindowSize(width, height);    // 윈도우의 크기 지정
	glutCreateWindow("project1");    // 윈도우 생성 (윈도우 이름)  
	glutDisplayFunc(drawScene);    // 출력 함수의 지정
	glutTimerFunc(50, TimerFunction, 1); // 타이머 함수 설정
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse); glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);//키보드
	glutMainLoop();
}

GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // 바탕색
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (child.get_stsatus() == 2 || child.get_stsatus() == 6)
		follow(&child);
	else if (parent.get_stsatus() == 2 || parent.get_stsatus() == 6)
		follow(&parent);

	bottle.move();
	water.move();
	parent.move();
	child.move();

	bottle.draw(1);
	water.draw(0);
	parent.draw(0);
	child.draw(0);

	if (child.get_stsatus() == 4 || child.get_stsatus() == 6)
		water_cut(&child);
	if (parent.get_stsatus() == 4 || parent.get_stsatus() == 6)
		water_cut(&parent);

	if (collision == 1)
		draw_line();

	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1, 1);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'a':
		break;
	case'p':
	case'P':
		parent.set_r(rand() % 20 + 20, rand() % 10 + 50);
		parent.init(4, 1, 0, 200);
		child.set_r(0, 0);
		child.init(4, 1, 0, 200);

		bottle.init(4, 1, 0, -200);
		water.init(4, 1, 0, -235);
		water.set_spd(bottle.get_spd());
		water.set_status(5);

		cut_success = false;
		in_success = false;
		break;

	case 'q':
	case 'Q':
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
	if (!cut_success)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && collision == 0)
		{
			mouse_dot[collision][0] = x - width / 2;
			mouse_dot[collision][1] = -(y - height / 2);
			mouse_dot[collision + 1][0] = x - width / 2;
			mouse_dot[collision + 1][1] = -(y - height / 2);
			collision++;
		}


		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			mouse_dot[collision][0] = x - width / 2;
			mouse_dot[collision][1] = -(y - height / 2);


			//	///////////벡터용
			//	line[0].put_x(mouse_dot[0][0]);
			//	line[0].put_y(mouse_dot[0][1]);		
			//	line[1].put_x(mouse_dot[1][0]);
			//	line[1].put_y(mouse_dot[1][1]);



				//////////////포인트용
			p_line[0].x = mouse_dot[0][0];
			p_line[0].y = mouse_dot[0][1];
			p_line[1].x = mouse_dot[1][0];
			p_line[1].y = mouse_dot[1][1];

			isthattrue();

			collision = 0;

			if (parent.operator>(child))
			{
				child.set_status(2);
				parent.set_status(3);
			}
			else
			{
				child.set_status(3);
				parent.set_status(2);
			}

		}
	} // 안잘렸으면 선 그려
}

void TimerFunction(int value) {
	glutPostRedisplay();   // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정 
}

void draw_line()
{
	glBegin(GL_LINES);
	for (int i = 0; i < 2; ++i)
	{
		glColor4f(0.8 - 0.2 * i, 0.4f + i * 0.2, 0.8f + i * 0.2, 1.0f);//점색
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
		//////////벡터용
	//	v_parent[i].put_x(parent.get_dot_x(i));
	//	v_parent[i].put_y(parent.get_dot_y(i));

		//////////포인트용
		p_parent[i].x = parent.get_dot_x(i);
		p_parent[i].y = parent.get_dot_y(i);
	}	

	///////////포인트
	GetIntersectPoint(p_parent[0], p_parent[1], p_line[0], p_line[1], &a1);
	GetIntersectPoint(p_parent[2], p_parent[3], p_line[0], p_line[1], &a2);

	if (a1.x == p_parent[1].x && a2.x == p_parent[2].x)
	{
		cut_case = 1;
		cut();
		return true;
	}

	GetIntersectPoint(p_parent[0], p_parent[3], p_line[0], p_line[1], &a1);
	GetIntersectPoint(p_parent[1], p_parent[2], p_line[0], p_line[1], &a2);

	if (a1.y == p_parent[0].y && a2.y == p_parent[1].y)
	{
		cut_case = 2;
		cut();
		return true;
	}

	GetIntersectPoint(p_parent[0], p_parent[1], p_line[0], p_line[1], &a1);
	GetIntersectPoint(p_parent[1], p_parent[2], p_line[0], p_line[1], &a2);

	if (a1.x == p_parent[0].x && a2.y == p_parent[1].y)
	{
		cut_case = 3;
		cut();
		return true;
	}


	GetIntersectPoint(p_parent[0], p_parent[3], p_line[0], p_line[1], &a1);
	GetIntersectPoint(p_parent[0], p_parent[1], p_line[0], p_line[1], &a2);

	if (a1.y == p_parent[0].y && a2.x == p_parent[0].x)
	{
		cut_case = 4;
		cut();
		return true;
	}


	GetIntersectPoint(p_parent[0], p_parent[3], p_line[0], p_line[1], &a1);
	GetIntersectPoint(p_parent[2], p_parent[3], p_line[0], p_line[1], &a2);

	if (a1.y == p_parent[0].y && a2.x == p_parent[2].x)
	{
		cut_case = 5;
		cut();
		return true;
	}


	GetIntersectPoint(p_parent[2], p_parent[3], p_line[0], p_line[1], &a1);
	GetIntersectPoint(p_parent[1], p_parent[2], p_line[0], p_line[1], &a2);

	if (a1.x == p_parent[2].x && a2.y == p_parent[2].y)
	{
		cut_case = 6;
		cut();
		return true;
	}
	/////////////벡터
	//segmentIntersection(v_parent[0], v_parent[1], line[0], line[1], p1);
	//segmentIntersection(v_parent[2], v_parent[3], line[0], line[1], p2);
	//segmentIntersection(v_parent[0], v_parent[3], line[0], line[1], p3);
	//segmentIntersection(v_parent[1], v_parent[2], line[0], line[1], p4);
	

	return false;
}

void cut()
{
	switch (cut_case)
	{
	case 1:
		child.set_dot(a1.x, a1.y, 0);
		child.set_dot(p_parent[1].x, p_parent[1].y, 1);
		child.set_dot(p_parent[2].x, p_parent[2].y, 2);
		child.set_dot(a2.x, a2.y, 3);

		parent.set_dot(a1.x, a1.y, 1);
		parent.set_dot(a2.x, a2.y, 2);
		break;

	case 2:
		child.set_dot(a1.x, a1.y, 0);
		child.set_dot(a2.x, a2.y, 1);
		child.set_dot(p_parent[2].x, p_parent[2].y, 2);
		child.set_dot(p_parent[3].x, p_parent[3].y, 3);

		parent.set_dot(a1.x, a1.y, 3);
		parent.set_dot(a2.x, a2.y, 2);
		break;

	case 3:
		child.set_dot(a1.x, a1.y, 0);
		child.set_dot(p_parent[1].x, p_parent[1].y, 1);
		child.set_dot(a2.x, a2.y, 2);
		child.set_polygon(3);

		parent.set_dot(p_parent[0].x, p_parent[0].y, 0);
		parent.set_dot(a1.x, a1.y, 1);
		parent.set_dot(a2.x, a2.y, 2);
		parent.set_dot(p_parent[2].x, p_parent[2].y, 3);
		parent.set_dot(p_parent[3].x, p_parent[3].y, 4);
		parent.set_polygon(5);
		break;
	case 4:
		child.set_dot(a1.x, a1.y, 0);
		child.set_dot(p_parent[0].x, p_parent[0].y , 1);
		child.set_dot(a2.x, a2.y, 2);
		child.set_polygon(3);

		parent.set_dot(a1.x, a1.y, 0);
		parent.set_dot(a2.x, a2.y, 1);
		parent.set_dot(p_parent[1].x, p_parent[1].y, 2);
		parent.set_dot(p_parent[2].x, p_parent[2].y, 3);
		parent.set_dot(p_parent[3].x, p_parent[3].y, 4);
		parent.set_polygon(5);
		break;

	case 5:
		child.set_dot(p_parent[3].x, p_parent[3].y, 0);
		child.set_dot(a1.x, a1.y, 1);
		child.set_dot(a2.x, a2.y, 2);
		child.set_polygon(3);

		parent.set_dot(a1.x, a1.y, 4);
		parent.set_dot(a2.x, a2.y, 3);		
		parent.set_polygon(5);
		break;

	case 6:
		child.set_dot(a1.x, a1.y, 0);
		child.set_dot(a2.x, a2.y, 1);
		child.set_dot(p_parent[2].x, p_parent[2].y, 2);
		child.set_polygon(3);

		parent.set_dot(a1.x, a1.y, 3);
		parent.set_dot(a2.x, a2.y, 2);
		parent.set_dot(p_parent[3].x, p_parent[3].y, 4);
		parent.set_polygon(5);
		break;
	}

	cut_success = true;
}

void follow(gl_object* p)
{
	//같이움직이기
	if (p->get_dot_x(0) >= bottle.get_dot_x(0)
		&& p->get_dot_x(0) <= bottle.get_dot_x(2)
		&& p->get_dot_x(1) >= bottle.get_dot_x(0)
		&& p->get_dot_x(1) <= bottle.get_dot_x(2)
		&& p->get_dot_x(2) >= bottle.get_dot_x(0)
		&& p->get_dot_x(2) <= bottle.get_dot_x(2)
		&& p->get_dot_y(2) <= bottle.get_dot_y(0) + 10
		&& p->get_dot_y(2) >= bottle.get_dot_y(0) - 10  
		&& p->get_stsatus() == 2)
	{
		p->set_status(6);
	}

	if (p->get_stsatus() == 6)
	{
		if(bottle.get_turn())
		{ 
			for (int i = 0; i < p->get_polygon(); ++i)
			{
				p->set_dot_x(i, p->get_dot_x(i) - bottle.get_spd());
			}
		}
		else
		{
			for (int i = 0; i < p->get_polygon(); ++i)
			{
				p->set_dot_x(i, p->get_dot_x(i) + bottle.get_spd());
			}
		}

		if ((p->get_dot_y(1) <= bottle.get_dot_y(2) + 15
			&& p->get_dot_y(1) >= bottle.get_dot_y(2) - 15)
			|| (p->get_dot_y(2) <= bottle.get_dot_y(2) + 15
				&& p->get_dot_y(2) >= bottle.get_dot_y(2) - 15)
			)
		{
			bottle.set_status(4);
			water.set_status(4);
			p->set_status(4);
		}

	}
	
}

void water_cut(gl_object* p)
{
	p_water[0].x = water.get_dot_x(0);
	p_water[0].y = water.get_dot_y(0);
	p_water[1].x = water.get_dot_x(3);
	p_water[1].y = water.get_dot_y(3);

	for (int i = 0; i < p->get_polygon(); ++i)
	{
		p_fall[i].x = p->get_dot_x(i);
		p_fall[i].y = p->get_dot_y(i);
	}

	if (p->get_polygon() == 4)
	{
		GetIntersectPoint(p_fall[0], p_fall[1], p_water[0], p_water[1], &b1);
		GetIntersectPoint(p_fall[2], p_fall[3], p_water[0], p_water[1], &b2);
	}
	else if(cut_case == 3 || cut_case == 6)
	{
		GetIntersectPoint(p_fall[0], p_fall[1], p_water[0], p_water[1], &b1);
		GetIntersectPoint(p_fall[0], p_fall[2], p_water[0], p_water[1], &b2);
	}
	else if (cut_case == 4 || cut_case == 5)
	{
		GetIntersectPoint(p_fall[2], p_fall[0], p_water[0], p_water[1], &b1);
		GetIntersectPoint(p_fall[2], p_fall[1], p_water[0], p_water[1], &b2);
	}

	if (b1.y == p_water[1].y && b2.y == p_water[1].y)
	{
		glBegin(GL_LINE_LOOP);
		glColor4f(0, 0, 0, 1.0f);//점색
		glVertex2f(b1.x, b1.y);
		for (int i = 0; i < p->get_polygon(); ++i)
		{
			if (p->get_dot_y(i) <= b1.y)
			{
				glVertex2f(p->get_dot_x(i), p->get_dot_y(i));
			}
		}
		glVertex2f(b2.x, b2.y);
		glEnd();
	}
	else if(p->get_dot_y(0) <= water.get_dot_y(0)
		&& p->get_dot_y(p->get_polygon()-1) <= water.get_dot_y(0))
	{
		glBegin(GL_LINE_LOOP);
		glColor4f(0, 0, 0, 1.0f);//점색
		for (int i = 0; i < p->get_polygon(); ++i)
		{
			glVertex2f(p->get_dot_x(i), p->get_dot_y(i));	
		}
		glEnd();
	}

	// 클리핑
}
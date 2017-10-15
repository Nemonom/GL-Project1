#pragma once
#include <GL/glut.h>    
#include <Windows.h>
#include "gl_object.h"
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

 /////////////함수


////////////변수
gl_object bottle;
gl_object parent;
gl_object child[2];

bool cut_success = false; // 자름
bool in_success = false; // 들어감

void main(int argc, char *argv[]) {

	srand(time(NULL));

	parent.set_r(rand() % 15 + 20);
	parent.init(4, 1, 0, 200);
	bottle.set_r(60);
	bottle.init(4, 1, 0, -200);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);    // 윈도우의 위치지정 
	glutInitWindowSize(width, height);    // 윈도우의 크기 지정
	glutCreateWindow("project1");    // 윈도우 생성 (윈도우 이름)  
	glutDisplayFunc(drawScene);    // 출력 함수의 지정
	glutTimerFunc(50, TimerFunction, 1); // 타이머 함수 설정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);//키보드
	glutMainLoop();
}

GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // 바탕색
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	bottle.move();
	parent.move();

	bottle.draw(1);
	parent.draw(0);

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
	glutPostRedisplay();   // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정 
}

void rotate()
{
	
}

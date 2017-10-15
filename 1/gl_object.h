#pragma once
#include <GL/glut.h>    
#include <iostream>
#include <time.h>
#include <math.h>

class gl_object
{
public:
	gl_object();
	~gl_object();

	int polygon = 0;
	float dot[5][2] = { 0 };

	int r = 0;
	float m_x = 0, m_y = 0; // 무게중심
	float move_x = 0, move_y = 0; // 움직인 정도
	float spd = 0;
	int status = 0;
	bool turn = false;

public:
	void init(int p, int s, float x, float y);
	void set_r(float f) { r = f; }
	void draw(int i);
	void rotate();
	void move();
	void set();

	float get_x() { return m_x; }
	float get_y() { return m_y; }
	int get_stsatus() { return status; }
	
	// 크기 비교
	bool operator>(const gl_object &p) const;

};


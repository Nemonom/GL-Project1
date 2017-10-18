#pragma once
#include <GL/glut.h>    
#include <iostream>
#include <time.h>
#include <math.h>
#include <cmath>

using namespace std;

class gl_object
{
public:
	gl_object();
	~gl_object();

	int polygon = 0;
	float dot[5][2] = { 0 };

	float x_r = 0, y_r = 0;
	float m_x = 0, m_y = 0; // 무게중심
	float move_x = 0, move_y = 0; // 움직인 정도
	float spd = 0;
	int status = 0;
	bool turn = false;

public:
	void init(int p, int s, float x, float y);
	void set_r(float xr, float yr) { x_r = xr; y_r = yr; }
	void draw(int i);
	void move();
	void set_polygon(int p) { polygon = p; }
	void set_dot_x(int i, float x) { dot[i][0] = x; }
	void set_dot_y(int i, float y) { dot[i][0] = y; }
	//void set_dot(const POINT& p, int i)
	//{ 
	//	dot[i][0] = p.x, dot[i][1] = p.y; 
	//}
	void set_dot(float x, float y, int i)
	{
		dot[i][0] = x, dot[i][1] = y;
	}
	void set_status(int s) { status = s; }
	
	float get_dot_x(int i) { return dot[i][0]; }
	float get_dot_y(int i) { return dot[i][1]; }
	float get_x() { return m_x; }
	float get_y() { return m_y; }
	int get_stsatus() { return status; }
	
	// 크기 비교
	bool operator>(const gl_object &p) const;

};

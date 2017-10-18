#pragma once
#include <GL/glut.h>    
#include <iostream>
#include <time.h>
#include <math.h>

#define EPSILON 0.0001

struct vector2 {
	double x, y;
	//생성자
	vector2(double _x, double _y) {
		x = _x, y = _y;
	}
	//외적
	double cross(const vector2& other) const {
		return x*other.y - y*other.x;
	}

	/* 연산자 오버로딩을 통해 실제 벡터의 연산을 구현합니다. */

	//벡터의 실수배
	vector2 operator * (double r) const {
		return vector2(x*r, y*r);
	}
	//벡터의 덧셈
	vector2 operator + (vector2 other) const {
		return vector2(x + other.x, y + other.y);
	}
	//벡터의 뺄셈
	vector2 operator - (vector2 other) const {
		return vector2(x - other.x, y - other.y);
	}
	//두 벡터의 비교
	bool operator == (vector2 other) const {
		return x == other.x && y == other.y;
	}
	bool operator < (vector2 other) const {
		return x < other.x && y < other.y;
	}
};

bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
	double det = (b - a).cross(d - c);
	//두선이 평행인 경우
	if (fabs(det) < EPSILON) return false;
	x = a + (b - a)*((c - a).cross(d - c) / det);
	return true;
}

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
	void rotate();
	void move();
	void set();

	float get_x() { return m_x; }
	float get_y() { return m_y; }
	int get_stsatus() { return status; }
	
	// 크기 비교
	bool operator>(const gl_object &p) const;

};


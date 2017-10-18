#pragma once
#include <GL/glut.h>    
#include <iostream>
#include <time.h>
#include <math.h>

#define EPSILON 0.0001

struct vector2 {
	double x, y;
	//������
	vector2(double _x, double _y) {
		x = _x, y = _y;
	}
	//����
	double cross(const vector2& other) const {
		return x*other.y - y*other.x;
	}

	/* ������ �����ε��� ���� ���� ������ ������ �����մϴ�. */

	//������ �Ǽ���
	vector2 operator * (double r) const {
		return vector2(x*r, y*r);
	}
	//������ ����
	vector2 operator + (vector2 other) const {
		return vector2(x + other.x, y + other.y);
	}
	//������ ����
	vector2 operator - (vector2 other) const {
		return vector2(x - other.x, y - other.y);
	}
	//�� ������ ��
	bool operator == (vector2 other) const {
		return x == other.x && y == other.y;
	}
	bool operator < (vector2 other) const {
		return x < other.x && y < other.y;
	}
};

bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
	double det = (b - a).cross(d - c);
	//�μ��� ������ ���
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
	float m_x = 0, m_y = 0; // �����߽�
	float move_x = 0, move_y = 0; // ������ ����
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
	
	// ũ�� ��
	bool operator>(const gl_object &p) const;

};


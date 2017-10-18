#pragma once
#include <iostream>
#include <cmath>
using namespace std; 
#define EPSILON 0.0001
/* ���� ���͸� ǥ���ϴ� ����ü�� �����մϴ�. */ 
struct vector2
{ double x, y; 
//������ 
vector2(){} 
vector2(double _x, double _y){ x = _x, y = _y; }
void put_x(float p_x) { x = p_x; }
void put_y(float p_y) { y = p_y; }
//����
double cross(const vector2& other) const{ return x*other.y-y*other.x; } 
/* ������ �����ε��� ���� ���� ������ ������ �����մϴ�. */ 
//������ �Ǽ���
vector2 operator * (double r) const{ return vector2(x*r, y*r); }
//������ ���� 
vector2 operator + (vector2 other) const{ return vector2(x + other.x, y + other.y); } 
//������ ���� 
vector2 operator - (vector2 other) const{ return vector2(x - other.x, y - other.y); }
//�� ������ �� 
bool operator == (vector2 other) const{ return x == other.x && y == other.y; } 
bool operator < (vector2 other) const{ return x < other.x && y < other.y; } }; 
/* - �� a, b�� ������ ������ �� c, d�� ������ ������ ������ x�� ��ȯ�Ѵ�. 
- �� ������ �����̸�(��ġ�� ��� ����) ������, �ƴϸ� ���� ��ȯ�Ѵ�. */ 
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x)
{
	double det = (b - a).cross(d - c);
	//�μ��� ������ ���
	if (fabs(det) < EPSILON) return false;
	x = a + (b - a)*((c - a).cross(d - c) / det); return true;
}
//�������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�. 
double ccw(vector2 a, vector2 b){ return a.cross(b); } 
//�� p�� �������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�. 
double ccw(vector2 p, vector2 a, vector2 b){ return ccw(a-p, b-p); } 
//�� a, b�� �� c, d�� ������ �� ���� �� �� �̵��� �� ������ ��ġ���� Ȯ���Ѵ�.
bool paralleSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p)
{ if(b < a) swap(a,b); if(d < c) swap(c,d); 
//�� �������� ���ų� �� ������ ��ġ�� �ʴ� ��츦 �켱 �ɷ�����. ������ 1�� ������ ����̴�. 
if(ccw(a, b, c) != 0 || b < c || d < a) return false;
//�� ������ Ȯ���� ��ģ�ٸ� ������ �ϳ��� ã�´�. 
if(a<c) p = c; else p = a; return true; } 
/* - p�� �� �� a, b�� ���θ鼭 �� ���� x, y�࿡ ������ �ּһ簢�� ���ο� �ִ��� Ȯ���Ѵ�. 
- a, b, p�� ������ �� �ִٰ� �����Ѵ�. */ 
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b)
{ if(b < a) swap(a, b); return p == a || p == b || (a <p && p < b); } 
/* - �� �� a, b�� ������ ���а� �� �� c, b�� ������ ������ p�� ��ȯ�Ѵ�. 
- ������ �������� ��� �ƹ����̳� ��ȯ�Ѵ�. */
bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p)
{ //�� ������ ������ ��츦 �켱 ���ܷ� ó���Ѵ�. 
	if (!lineIntersection(a, b, c, d, p))
		return paralleSegments(a, b, c, d, p);
	//p�� �� ���п� ���ԵǾ� �ִ� ��쿡�� ���� ��ȯ�Ѵ�. 
	return inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);
}


void lineOnPoint(const vector2 & lineS, const vector2 & lineE, const vector2 & Point)
{
	vector2 tmp1 = Point - lineS;
	vector2 tmp2 = Point - lineE;

	//return tmp1.inner(tmp2) < 0;
}




bool GetIntersectPoint(const POINT& AP1, const POINT& AP2, const POINT& BP1, const POINT& BP2, POINT* IP)
{
	double t;
	double s;
	double under = (BP2.y - BP1.y)*(AP2.x - AP1.x) - (BP2.x - BP1.x)*(AP2.y - AP1.y);
	if (under == 0) return false;

	double _t = (BP2.x - BP1.x)*(AP1.y - BP1.y) - (BP2.y - BP1.y)*(AP1.x - BP1.x);
	double _s = (AP2.x - AP1.x)*(AP1.y - BP1.y) - (AP2.y - AP1.y)*(AP1.x - BP1.x);

	t = _t / under;
	s = _s / under;

	if (t<0.0 || t>1.0 || s<0.0 || s>1.0) return false;
	if (_t == 0 && _s == 0) return false;

	IP->x = AP1.x + t * (double)(AP2.x - AP1.x);
	IP->y = AP1.y + t * (double)(AP2.y - AP1.y);
	return true;
}
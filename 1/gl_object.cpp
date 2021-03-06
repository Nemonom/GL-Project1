#include "gl_object.h"


gl_object::gl_object()
{
	srand(time(NULL));
}

gl_object::~gl_object()
{
}

void gl_object::init(int p, int s, float x, float y)
{

	polygon = p;
	spd = rand() % 4 + 5;
	status = s;
	m_x = x; m_y = y;
	move_x = 0; move_y = 0;

	turn = false;

	dot[0][0] = m_x - x_r;
	dot[0][1] = m_y + y_r;

	dot[1][0] = m_x - x_r;
	dot[1][1] = m_y - y_r;

	dot[2][0] = m_x + x_r;
	dot[2][1] = m_y - y_r;

	dot[3][0] = m_x + x_r;
	dot[3][1] = m_y + y_r;

	dot[4][0] = dot[3][0];
	dot[4][1] = dot[3][1];
}

void gl_object::draw(int i)
{
	if (i == 0)
	{
		if (status == 5)
		{
			glBegin(GL_POLYGON);
			for (int i = 0; i < polygon; ++i)
			{
				glColor4f(0.9 - 0.1 * i, 0.6 + 0.1 * i, 0.7 + 0.1 * i, 1.0f);//점색
				glVertex2f(dot[i][0], dot[i][1]);
			}
			glEnd();
		}
		else if (status == 2)
		{
			glBegin(GL_POLYGON);
			for (int i = 0; i < polygon; ++i)
			{
				glColor4f(0.4 + 0.1 * i, 0.8 - 0.1 * i, 1.0 - 0.1 * i, 1.0f);//점색
				glVertex2f(dot[i][0], dot[i][1]);
			}
			glEnd();

			glBegin(GL_LINE_LOOP);
			for (int i = 0; i < polygon; ++i)
			{
				glColor4f(1, 0.3, 0.3, 1.0f);//점색
				glVertex2f(dot[i][0], dot[i][1]);
			}
			glEnd();
		}
		else if (status == 6 || status == 4)
		{
			glBegin(GL_POLYGON);
			for (int i = 0; i < polygon; ++i)
			{
				glColor4f(0.4 + 0.1 * i, 0.8 - 0.1 * i, 1.0 - 0.1 * i, 1.0f);//점색
				glVertex2f(dot[i][0], dot[i][1]);
			}
			glEnd();

			glBegin(GL_LINE_LOOP);			
			for (int i = 0; i < polygon; ++i)
			{
				glColor4f(1, 0.3, 0.3, 1.0f);//점색
				glVertex2f(dot[i][0], dot[i][1]);
			}
			glEnd();
		}

		else {
			glBegin(GL_POLYGON);
			for (int i = 0; i < polygon; ++i)
			{
				glColor4f(0.4 + 0.1 * i, 0.8 - 0.1 * i, 1.0 - 0.1 * i, 1.0f);//점색
				glVertex2f(dot[i][0], dot[i][1]);
			}
			glEnd();
		}

	}

	if (i == 1)
	{
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < polygon; ++i)
		{
			glColor4f(0.6 - 0.1 * i, 0.4 + 0.1 * i, 0.5 + 0.1 * i, 1.0f);//점색
			glVertex2f(dot[i][0], dot[i][1]);
		}
		glEnd();
	}
}

void gl_object::move()
{
	if (status == 1) // 가로
	{
		if (!turn)
		{
			for (int i = 0; i < polygon; ++i)
			{
				dot[i][0] += spd;;
			}
			if (dot[3][0] > 350)
				turn = true;
		}
		else if (turn)
		{
			for (int i = 0; i < polygon; ++i)
			{
				dot[i][0] -= spd;;
			}
			if (dot[0][0] < -350)
				turn = false;
		}

	}
	else if (status == 2 || status == 6) // 세로
	{
		for (int i = 0; i < polygon; ++i)
		{
			dot[i][1] -= 15;
		}
	}
	else if (status == 3)
	{
		if (!turn)
		{
			for (int i = 0; i < polygon; ++i)
			{
				dot[i][0] += spd;;
			}
		}
		else if (turn)
		{
			for (int i = 0; i < polygon; ++i)
			{
				dot[i][0] -= spd;;
			}
		}
	}
	else if (status == 4) // 멈춰
	{

	}
	else if (status == 5) // 물
	{
		if (!turn)
		{
			for (int i = 0; i < polygon; ++i)
			{
				dot[i][0] += spd;;
			}
			if (dot[3][0] > 350)
				turn = true;

			dot[0][1]++;
			dot[3][1]++;
		}
		else if (turn)
		{
			for (int i = 0; i < polygon; ++i)
			{
				dot[i][0] -= spd;;
			}
			if (dot[0][0] < -350)
				turn = false;
			dot[0][1]--;
			dot[3][1]--;
		}
	}

}

bool gl_object::operator>(const gl_object &p) const
{
	if (polygon > p.polygon) return true;
	else if (polygon < p.polygon) return false;
	else // 둘 다 사각형
	{
		if (dot[2][0] == dot[3][0])
		{
			float h1 = dot[0][1] - dot[1][1];
			float h2 = dot[3][1] - dot[2][1];

			float ch1 = p.dot[0][1] - p.dot[1][1];
			float ch2 = p.dot[3][1] - p.dot[2][1];

			if (h1 + h1 >= ch1 + ch2)
				return true;
			else
				return false;
		}

		if (dot[1][1] == dot[2][1])
		{
			float w1 = dot[3][0] - dot[0][0];
			float w2 = dot[2][0] - dot[1][0];

			float cw1 = p.dot[3][0] - p.dot[0][0];
			float cw2 = p.dot[2][0] - p.dot[1][0];

			if (w1 + w1 > cw1 + cw2)
				return true;
			else
				return false;
		}
	}
}


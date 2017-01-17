#include <stdlib.h>
#include <stdio.h>
#include <gl/freeglut.h>


GLint Width = 500, Height = 500;
int k0 = 5;
int k1 = 2;
int koeffX = 0;
int koeffY = 0;
int scale = 20;
float vect[2] = { 0.25, -1 };

struct point {
	float x;
	float y;
	int k;
	
	point() {};
	point(float x, float y) { this->x = x; this->y = y; }
};
struct triangle {
	point first;
	point second;
	point third;
	triangle() {};
	void set(point a, point b, point c) { first = a; second = b; third = c; }
};

struct quadd {
	point first;
	point second;
	point third;
	point fourth;
	quadd() {};
	void set(point a, point b, point c, point d) { first = a; second = b; third = c; fourth = d; }
};


void Display(void)
{
	glClearColor(1, 0, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT); //для очищення буферів кольору і глибини.

	triangle *figures0 = new triangle[k0];
	figures0[0].set(point::point(-1, 2), point::point(-1, -2), point::point(3, -2));
	figures0[1].set(point::point(-1, -2), point::point(3, -2), point::point(3, -6));
	figures0[2].set(point::point(-1,-6), point::point(1, -4), point::point(3, -6));
	figures0[3].set(point::point(-1, -6), point::point(-1, -4), point::point(1, -4));
	figures0[4].set(point::point(-2, -2), point::point(-1, -1), point::point(-1, -3));

	quadd *figures1 = new quadd[k1];
	figures1[0].set(point::point(-1, 4), point::point(0.5, 5.5), point::point(3.5, 5.5), point::point(2, 4));
	figures1[1].set(point::point(-3, 2), point::point(-3, 4), point::point(-1, 4), point::point(-1, 2));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3ub(0, 100, 255);
	for (int i = 0; i < k0; i++) {
		glBegin(GL_TRIANGLES);
		glVertex2f(figures0[i].first.x * scale + koeffX, figures0[i].first.y * scale + koeffY);
		glVertex2f(figures0[i].second.x * scale + koeffX, figures0[i].second.y * scale + koeffY);
		glVertex2f(figures0[i].third.x * scale + koeffX, figures0[i].third.y * scale + koeffY);
		glEnd();
	}
	for (int i = 0; i < k1; i++) {
		glBegin(GL_QUADS);
		glVertex2f(figures1[i].first.x * scale + koeffX, figures1[i].first.y * scale + koeffY);
		glVertex2f(figures1[i].second.x * scale + koeffX, figures1[i].second.y * scale + koeffY);
		glVertex2f(figures1[i].third.x * scale + koeffX, figures1[i].third.y * scale + koeffY);
		glVertex2f(figures1[i].fourth.x * scale + koeffX, figures1[i].fourth.y * scale + koeffY);
		glEnd();
	}
	glFinish();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3ub(0, 0, 0);
	for (int i = 0; i < k0; i++) {
		glBegin(GL_TRIANGLES);
		glVertex2f(figures0[i].first.x * scale + koeffX, figures0[i].first.y * scale + koeffY);
		glVertex2f(figures0[i].second.x * scale + koeffX, figures0[i].second.y * scale + koeffY);
		glVertex2f(figures0[i].third.x * scale + koeffX, figures0[i].third.y * scale + koeffY);
		glEnd();
	}
	for (int i = 0; i < k1; i++) {
		glBegin(GL_QUADS);
		glVertex2f(figures1[i].first.x * scale + koeffX, figures1[i].first.y * scale + koeffY);
		glVertex2f(figures1[i].second.x * scale + koeffX, figures1[i].second.y * scale + koeffY);
		glVertex2f(figures1[i].third.x * scale + koeffX, figures1[i].third.y * scale + koeffY);
		glVertex2f(figures1[i].fourth.x * scale + koeffX, figures1[i].fourth.y * scale + koeffY);
		glEnd();
	}
	glFinish();
}

//Функція викликається при зміні розмірів вікна
void Reshape(GLint w, GLint h)
{
	Width = w;
	Height = h;

	// установлюємо розміри області відображення
	glViewport(0, 0, w, h);

	// ортографічна проекція
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();// считывает текущую матрицу
	glOrtho(-w/2, w/2, -h/2, h/2, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);// щоб вибрати, яку матрицю треба змінити, використовується команда 
	glLoadIdentity();
}

//Функція обробляє повідомлення від клавіатури
void Keyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_END: exit(0); // Escape
		break;
	
	case GLUT_KEY_UP:
		koeffX -= vect[0] * scale / 4;
		koeffY -= vect[1] * scale / 4;
		glutPostRedisplay();
		break; 
	case GLUT_KEY_DOWN:
		koeffX += vect[0] * scale / 4;
		koeffY += vect[1] * scale / 4;
		glutPostRedisplay();
		break;
	}
}

//Головний цикл додатка
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Зайка");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(Keyboard);
	glutMainLoop();

	return 0;
}
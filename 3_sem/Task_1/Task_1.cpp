#define NOMINMAX

#include <math.h>

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
using namespace std;

#define SIGN(x) ((x < 0) ? -1 : 1)


class comp {
public:
	float a;
	float b;

	comp(float x, float y) {
		a = x;
		b = y;
	}

	comp(float x): comp(x, 0) {}

	comp(): comp(0, 0) {}

	void f(int n, comp C) {  // отображение f^n + C
		float u, v;
		for (int i = 0; i < n; i++) {
			u = a; 
			v = b;
			a = (u * u - v * v) + C.a;
			b = (2 * u * v) + C.b;
		}
		return;
	}

	void g() {               // обратное отображение f
		float u = a;
		float v = b;
		a = sqrt((sqrt(u * u + v * v) + u) / 2);
		b = SIGN(v) * sqrt((sqrt(u * u + v * v) - u) / 2);
		return;
	}
};

CircleShape set_vert(comp z_0, comp C, float s, int size_x, int size_y, float k, int n, bool subtask_3) {
	float R = 1;
	CircleShape vert(R);
	vert.setPosition(z_0.a * k + size_x / 2 - R, size_y / 2 - z_0.b * k - R);
	if (!subtask_3) {
		z_0.f(n, C);
		if ((fabs(z_0.a) > s) || (fabs(z_0.b) > s) || (z_0.a != z_0.a) || (z_0.b != z_0.b))
			vert.setFillColor(Color::Yellow);
		else
			vert.setFillColor(Color::Red);
	}
	else {
		//vert.setFillColor(Color(255, 255, 0));
		int r, g, b;
		for (int i = 0; i < n; i++) {
			z_0.f(1, C);
			if ((fabs(z_0.a) > s) || (fabs(z_0.b) > s) || (z_0.a != z_0.a) || (z_0.b != z_0.b)) {
				r = 51 * i;
				if (r > 255) r = 255;
				g = 40 * i;
				if (g > 255) g = 255;
				b = 0 * i;
				if (b > 255) b = 255;
				vert.setFillColor(Color(r, g, b));
				break;
			}
		}
	}
	return vert;
}

void colorize(int n, comp C, int size_x, int size_y, bool subtask_3 = false) {

	RenderWindow window(VideoMode(size_x, size_y), "Task 1");

	float s = 2;      // координаты квадрата (области) на осях (комплексная плоскость)
	float l = 720;  // длина стороны квадрата (области) (пиксели)
	float h = 150;  // размер сетки

	float k = l / (s * 2);          // константа для масштабирования (поделить на нее при переходе от пикселей)
	float step = (s * 2) / (h - 1); // шаг сетки на комплексной плоскости

	comp z_0(-s + step, s);
	CircleShape vert;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();

		for (int i = 0; i < h - 2; i++) {
			z_0.b -= step;
			vert = set_vert(z_0, C, s, size_x, size_y, k, n, subtask_3);
			window.draw(vert);
			if (z_0.a < 0) {
				for (int j = 0; j < h - 3; j++) {
					z_0.a += step;
					vert = set_vert(z_0, C, s, size_x, size_y, k, n, subtask_3);
					window.draw(vert);
				}
			}
			else {
				for (int j = 0; j < h - 3; j++) {
					z_0.a -= step;
					vert = set_vert(z_0, C, s, size_x, size_y, k, n, subtask_3);
					window.draw(vert);
				}
			}
		}
		z_0.a = (-l / 2) / k + step;
		z_0.b = (l / 2) / k;

		window.display();
	}
	return;
}


typedef struct tree {
	comp value;
	tree* left;
	tree* right;
} tree;

tree* tree_get(comp z, int h, int i = 1) {
	tree* result = (tree*)malloc(sizeof(tree));
	result->left = nullptr;
	result->right = nullptr;
	result->value = z;
	if (i < h) {
		z.g();
		comp root_(-z.a, -z.b);
		result->left = tree_get(root_, h, ++i);
		result->right = tree_get(z, h, i);
	}
	return result;
}

void tree_print(tree* t) {
	if (!t->value.a && !t->value.b) cout << 0;
	if (t->value.a) {
		cout << t->value.a;
		if (t->value.b > 0) cout << "+";
	}
	if (t->value.b) {
		if (abs(t->value.b) != 1) cout << t->value.b;
		else if (t->value.b == -1) cout << "-";
		cout << "i";
	}
	cout << "\n";
	if (t->left) tree_print(t->left);
	if (t->right) tree_print(t->right);
}


int main() {
	int n = 10;
	comp C(0.75, -0.25);

	int size_x = 1280, size_y = 720;

	bool subtask_2 = false;
	bool subtask_3 = true;

	colorize(n, C, size_x, size_y, subtask_3);

	comp z(0, 2);

	tree* t = tree_get(z, 3);
	tree_print(t);

	return 0;
}
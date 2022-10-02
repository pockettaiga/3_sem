#define NOMINMAX

#include <math.h>

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
using namespace std;

// #1
class comp {
public:
	float a;
	float b;

	comp(float x, float y) {
		a = x;
		b = y;
	}

	comp() {
		a = 0;
		b = 0;
	}

	void f(int n, comp C) {   // отображение f^n + C
		float u, v;
		for (int i = 0; i < n; i++) {
			u = a; 
			v = b;
			a = (u * u - v * v) + C.a;
			b = (2 * u * v) + C.b;
		}
		return;
	}
};

// #2
VertexArray set_Oxy(float size_x, float size_y) {
	VertexArray Oxy(Lines, 4);
	Oxy[0].position = Vector2f(0, size_y / 2);
	Oxy[0].color = Color::Black;
	Oxy[1].position = Vector2f(size_x, size_y / 2);
	Oxy[1].color = Color::Black;
	Oxy[2].position = Vector2f(size_x / 2, size_y);
	Oxy[2].color = Color::Black;
	Oxy[3].position = Vector2f(size_x / 2, 0);
	Oxy[3].color = Color::Black;
	return Oxy;
}

VertexArray set_area(int s, float length, float size_x, float size_y) {
	VertexArray sqr(LineStrip, 5);
	if (length > ((size_x > size_y) ? size_y : size_x)) {
		length = size_y;
	}
	sqr[0].position = Vector2f(size_x / 2 - length / 2, size_y / 2 - length / 2);
	sqr[0].color = Color::Black;
	sqr[1].position = Vector2f(size_x / 2 + length / 2, size_y / 2 - length / 2);
	sqr[1].color = Color::Black;
	sqr[2].position = Vector2f(size_x / 2 + length / 2, size_y / 2 + length / 2);
	sqr[2].color = Color::Black;
	sqr[3].position = Vector2f(size_x / 2 - length / 2, size_y / 2 + length / 2);
	sqr[3].color = Color::Black;
	sqr[4].position = Vector2f(size_x / 2 - length / 2, size_y / 2 - length / 2);
	sqr[4].color = Color::Black;
	return sqr;
};

CircleShape set_vert(comp z_0, comp C, int s, float size_x, float size_y, float k, int n, bool subtask_3) {
	float R = 2.4;
	CircleShape vert(R);
	vert.setPosition(z_0.a * k + size_x / 2 - R, size_y / 2 - z_0.b * k - R);
	if (!subtask_3) {
		z_0.f(n, C);
		if ((fabs(z_0.a) > s) || (fabs(z_0.b) > s) || (z_0.a != z_0.a) || (z_0.b != z_0.b))
			vert.setFillColor(Color(0, 0, 0, 255));
		else
			vert.setFillColor(Color::Red);
	}
	else {

		vert.setFillColor(Color::Yellow);
		for (int i = 0; i < n; i++) {
			z_0.f(1, C);
			if ((fabs(z_0.a) > s) || (fabs(z_0.b) > s) || (z_0.a != z_0.a) || (z_0.b != z_0.b)) {
				switch (i) {
				case 0:
					vert.setFillColor(Color::Blue);
					break;
				case 1:
					vert.setFillColor(Color::Green);
					break;
				case 2:
					vert.setFillColor(Color::Magenta);
					break;
				case 3:
					vert.setFillColor(Color::Cyan);
					break;
				case 4:
					vert.setFillColor(Color::Red);
					break;
				case 5:
					vert.setFillColor(Color::Black);
				default:
					vert.setFillColor(Color(15 * i, 15 * i, 0, 255));
					break;
				}
				break;
			}
		}
	}
	return vert;
}



void colorize(int n, comp C, Font font, float size_x, float size_y, bool subtask_3 = false) {
	RenderWindow window(VideoMode(size_x, size_y), "Task 1");

	RectangleShape rect(Vector2f(size_x, size_y));

	int s = 2;     // координаты квадрата (области) на осях (комплексная плоскость)
	float l = 660; // длина стороны квадрата (области) (пиксели)
	float h = 100;  // размер сетки

	float k = l / (s * 2);          // константа для масштабирования (поделить на нее при переходе от пикселей)
	float step = (l / k) / (h - 1); // шаг сетки

	VertexArray Oxy = set_Oxy(size_x, size_y);

	VertexArray sqr = set_area(s, l, size_x, size_y);

	int char_size = 15;  // размер шрифта

	Text num_1(to_string(s), font, char_size);
	num_1.setFillColor(Color::Black);
	num_1.setPosition(Vector2f(size_x / 2 + l / 2, size_y / 2));

	Text num_2("-" + to_string(s), font, char_size);
	num_2.setFillColor(Color::Black);
	num_2.setPosition(Vector2f(size_x / 2 - l / 2 - char_size, size_y / 2));

	Text num_3(to_string(s) + "i", font, char_size);
	num_3.setFillColor(Color::Black);
	num_3.setPosition(Vector2f(size_x / 2, size_y / 2 - l / 2 - (char_size + 2)));

	Text num_4("-" + to_string(s) + "i", font, char_size);
	num_4.setFillColor(Color::Black);
	num_4.setPosition(Vector2f(size_x / 2, size_y / 2 + l / 2));

	comp z_0((-l / 2) / k + step, (l / 2) / k);
	CircleShape vert;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();

		window.draw(rect);
		window.draw(Oxy);
		window.draw(sqr);
		window.draw(num_1);
		window.draw(num_2);
		window.draw(num_3);
		window.draw(num_4);

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

int main() {
	int n = 10;
	comp C(-0.5, 0.25);

	Font font;
	font.loadFromFile("arial.ttf");

	float size_x = 1280, size_y = 720;

	bool subtask_2 = false;
	bool subtask_3 = true;

	colorize(n, C, font, size_x, size_y, subtask_3);

	return 0;
}
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

	comp(float x) : comp(x, 0) {}

	comp() : comp(0, 0) {}

	void f(int n, comp C) {
		float u, v;
		for (int i = 0; i < n; i++) {
			u = a;
			v = b;
			a = (u * u - v * v) + C.a;
			b = (2 * u * v) + C.b;
		}
		return;
	}

	void g() {     
		float u = a;
		float v = b;
		a = sqrt((sqrt(u * u + v * v) + u) / 2);
		b = SIGN(v) * sqrt((sqrt(u * u + v * v) - u) / 2);
		return;
	}

	float heart() {
		return a * a + powf((b - cbrtf(a * a)), 2);
	}
};


CircleShape heart_vert(comp z_0, int size_x, int size_y, float k) {
	float R = 1;
	CircleShape vert(R);
	vert.setPosition(z_0.a * k + size_x / 2 - R, size_y / 2 - z_0.b * k - R);
	float x = z_0.heart();
	if (x > 1) vert.setFillColor(Color(255 / (1.4 * abs(x)), 0, 75 / abs(x)));
	else vert.setFillColor(Color(255 * abs(x), 0, 75 * abs(x)));
	return vert;
}

void for_lera(int size_x, int size_y, Font font) {
	RenderWindow window(VideoMode(size_x, size_y), "For Lera");

	float s = 2.35;
	float l = 720;
	float h = 180;

	float k = l / (s * 2);
	float step = (l / k) / (h - 1);

	comp z_0((-l / 2) / k + step, (l / 2) / k);
	CircleShape vert;

	int char_size = 18;

	Text text_1("I", font, char_size);
	Text text_2("x * x + powf((y - cbrtf(x * x)), 2) = 1", font, char_size);
	Text text_3("you", font, char_size);

	text_1.setFillColor(Color::White);
	text_2.setFillColor(Color::White);
	text_3.setFillColor(Color::White);

	text_1.setPosition(Vector2f(size_x / 2 - 0.5 * char_size, 20));
	text_2.setPosition(Vector2f(size_x / 2 - 8 * char_size, 45));
	text_3.setPosition(Vector2f(size_x / 2 - char_size, 70));

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();

		for (int i = 0; i < h - 2; i++) {
			z_0.b -= step;
			vert = heart_vert(z_0, size_x, size_y, k);
			window.draw(vert);
			if (z_0.a < 0) {
				for (int j = 0; j < h - 3; j++) {
					z_0.a += step;
					vert = heart_vert(z_0, size_x, size_y, k);
					window.draw(vert);
				}
			}
			else {
				for (int j = 0; j < h - 3; j++) {
					z_0.a -= step;
					vert = heart_vert(z_0, size_x, size_y, k);
					window.draw(vert);
				}
			}
		}
		z_0.a = (-l / 2) / k + step;
		z_0.b = (l / 2) / k;

		window.draw(text_1);
		window.draw(text_2);
		window.draw(text_3);

		window.display();
	}
	return;
}

//int main() {
//
//	Font font;
//	font.loadFromFile("arial.ttf");
//
//	int size_x = 1280, size_y = 720;
//
//	for_lera(size_x, size_y, font);
//
//	return 0;
//}
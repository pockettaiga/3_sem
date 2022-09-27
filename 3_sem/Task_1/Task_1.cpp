#define NOMINMAX

#include <Windows.h>
#include <stdlib.h>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

#include <iostream>
using namespace std;

// отображение z^2
void f(float* x, float* y) {
	float u = *x, v = *y;
	*x = u * u - v * v;
	*y = 2 * u * v;
	return;
}

int main() {
	RenderWindow window(VideoMode(600, 600), "Task 1");

	RectangleShape rect(Vector2f(550.f, 550.f));
	rect.setPosition(Vector2f(25.f, 25.f));

	// сетка 10x10
	VertexArray cage(LineStrip, 40);
	float x = 25.f, y = 75.f;
	int i = 0;	
	for (; i < 20; i++) {
		cage[i].position = Vector2f(x += 50.f, y);
		cage[++i].position = Vector2f(x, y += 450.f);
		cage[++i].position = Vector2f(x += 50.f, y);
		cage[++i].position = Vector2f(x, y -= 450.f);
	}
	y = 25.f; x = 75.f;
	for (; i < 40; i++) {
		cage[i].position = Vector2f(x, y += 50.f);
		cage[++i].position = Vector2f(x += 450.f, y);
		cage[++i].position = Vector2f(x, y += 50.f);
		cage[++i].position = Vector2f(x -= 450.f, y);
	}

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();

		window.draw(cage);

		window.display();
	}
	return 0;
}
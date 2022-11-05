отрисовка координатной оси и квадрата со стороной s:

VertexArray set_Oxy(float size_x, float size_y) {
	VertexArray Oxy(Lines, 4);
	Oxy[0].position = Vector2f(0, size_y / 2);
	Oxy[1].position = Vector2f(size_x, size_y / 2);
	Oxy[2].position = Vector2f(size_x / 2, size_y);
	Oxy[3].position = Vector2f(size_x / 2, 0);
	return Oxy;
}

VertexArray set_area(int s, float length, float size_x, float size_y) {
	VertexArray sqr(LineStrip, 5);
	if (length > ((size_x > size_y) ? size_y : size_x)) {
		length = size_y;
	}
	sqr[0].position = Vector2f(size_x / 2 - length / 2, size_y / 2 - length / 2);
	sqr[1].position = Vector2f(size_x / 2 + length / 2, size_y / 2 - length / 2);
	sqr[2].position = Vector2f(size_x / 2 + length / 2, size_y / 2 + length / 2);
	sqr[3].position = Vector2f(size_x / 2 - length / 2, size_y / 2 + length / 2);
	sqr[4].position = Vector2f(size_x / 2 - length / 2, size_y / 2 - length / 2);
	return sqr;
};

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
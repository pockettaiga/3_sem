#include <iostream>
#include <fstream>
using namespace std;

#define IS_DIGIT(x)  (x >= '0' && x <= '9')

const char* FILENAME = "matrix.txt";

class Matrix {
public:
	Matrix(int rows, int columns) {
		this->rows = rows;
		this->columns = columns;
		values = init_array(rows, columns);
	}

	Matrix(int rows) : Matrix(rows, rows) {

	}

	Matrix() : Matrix(1, 1) {

	}

	int get_rows() {
		return rows;
	}

	int get_columns() {
		return columns;
	}

	int get_value(int i, int j) {
		return values[i][j];
	}

	void set_value(int i, int j, int value) {
		values[i][j] = value;
	}

	void print() {
		print_array(values, rows, columns);
	}

	double find_square(int n = 1) {
		int** upper_cover = get_cover(values, "upper");
		int** lower_cover = get_cover(values, "lower");
		
		int volume_1 = 0;
		int volume_2 = find_volume(upper_cover, lower_cover, rows, columns);
		for (int i = 0; i < n - 1; ++i) {
			volume_1 = volume_2;
			upper_cover = get_cover(upper_cover, "upper");
			lower_cover = get_cover(lower_cover, "lower");
			volume_2 = find_volume(upper_cover, lower_cover, rows, columns);
		}
		return ((double)(volume_2 - volume_1)) / 2;
	}

	void set_from_file(const char* filename = FILENAME) {
		ifstream in(filename);
		if (in.is_open()) {
			char buffer = '0';
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < columns; ++j) {
					buffer = in.get();
					while (IS_DIGIT(buffer)) {
						values[i][j] = 10 * values[i][j] + to_int(buffer);
						buffer = in.get();
					}
				}
				if (buffer != '\n') {
					in.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
		}
		in.close();
	}

private:
	int rows = 0;
	int columns = 0;
	int** values = nullptr;

	int** init_array(int rows, int columns) {
		int** result = new int* [rows];
		for (int i = 0; i < rows; ++i) {
			result[i] = new int[columns];
			memset(result[i], 0, sizeof(int) * columns);
		}
		return result;
	}

	void print_array(int** array, int rows, int columns) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				cout << array[i][j];
				if (j != columns - 1) {
					cout << " ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	int to_int(char symbol) {
		int digit = -1;
		switch (symbol) {
		case '0':
			digit = 0;
			break;
		case '1':
			digit = 1;
			break;
		case '2':
			digit = 2;
			break;
		case '3':
			digit = 3;
			break;
		case '4':
			digit = 4;
			break;
		case '5':
			digit = 5;
			break;
		case '6':
			digit = 6;
			break;
		case '7':
			digit = 7;
			break;
		case '8':
			digit = 8;
			break;
		default:
			digit = 9;
			break;
		}
		return digit;
	}

	int get_extremum_value(int* array, int size, const char* mode) {
		int value = -1;
		if (mode == "upper") {
			value = 0;
			for (int i = 0; i < size; ++i) {
				if (array[i] > value) {
					value = array[i];
				}
			}
		}
		else if (mode == "lower") {
			value = numeric_limits<int>::max();
			for (int i = 0; i < size; ++i) {
				if (array[i] < value) {
					value = array[i];
				}
			}
		}
		return value;
	}

	int** get_cover(int** array, const char* mode) {
		int** cover = init_array(rows, columns);
		int* buffer = new int[5];
		int size = 0;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				buffer[size++] = (mode == "upper") ? (array[i][j] + 1) : (array[i][j] - 1);
				if (i != 0) {
					buffer[size++] = array[i - 1][j];
				}
				if (j != 0) {
					buffer[size++] = array[i][j - 1];
				}
				if (i != rows - 1) {
					buffer[size++] = array[i + 1][j];
				}
				if (j != columns - 1) {
					buffer[size++] = array[i][j + 1];
				}
				cover[i][j] = get_extremum_value(buffer, size, mode);
				size = 0;
			}
		}
		return cover;
	}

	int find_volume(int** upper_cover, int** lower_cover, int rows, int columns) {
		int volume = 0;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				volume += upper_cover[i][j] - lower_cover[i][j];
			}
		}
		return volume;
	}
};

int main() {
	int rows = 4;
	int columns = 4;
	Matrix matrix(rows, columns);
	matrix.set_from_file();
	matrix.print();
	cout << matrix.find_square() << endl << matrix.find_square(2);
	return 0;
}
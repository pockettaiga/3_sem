#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// построение транзитивного замыкания графа, представленного в виде матрицы смежности

const char* file = "graph.txt";

class Graph {

	int size;
	char* matrix;

public:

	Graph(int s, const char* f) {

		size = s;
		matrix = nullptr;
		if (size) matrix = new char[size * size];
		
		ifstream in(f);
		
		if (in.is_open()) {
			
			string l;

			for (int i = 0; i < s * s; i++) {

				if (!(i % s)) getline(in, l);
				matrix[i] = l[i % s];
			}
		}

		in.close();
	}

	Graph(int s) : Graph(s, "\0") {

		for (int i = 0; i < s * s; i++) {

			matrix[i] = '0';
		}
	}

	Graph() : Graph(0) {}

	bool is_empty() {
		
		if (size == 0) return true;
		return false;
	}

	void print() {

		if (is_empty()) cout << "empty graph";

		for (int i = 0; i < (size * size); i++) {

			cout << matrix[i];
			if (i % size == size - 1) cout << "\n";
		}

		cout << "\n";
	}

	Graph get_trans_closure() {

		Graph g = Graph(size);
		_memccpy(g.matrix, this->matrix, 0, size * size);

		for (int x = 0; x < size; x++) {

			for (int y = 0; y < size; y++) {

				for (int z = 0; z < size; z++) {

					if (g.matrix[y * size + x] == '1' && g.matrix[x * size + z] == '1')
						g.matrix[y * size + z] = '1';
				}
			}
		}

		return g;
	}

};

int main() {

	Graph g = Graph(4, file);
	g.print();

	Graph tcg = g.get_trans_closure();
	tcg.print();
	
	return 0;
}
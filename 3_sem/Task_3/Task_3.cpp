#include <iostream>
using namespace std;

#include <stack>

int string_check(const char* s) {
	stack <char> stk;
	char* c = (char*) s;
	
	while (*c != '\0') {
		if (*c == '(' || *c == '[' || *c == '{')
			stk.push(*c);
		else {
			if (!stk.size()) return 1;
			switch (*c) {
			case ')':
				if (stk.top() != '(') return 1;
				break;
			case ']':
				if (stk.top() != '[') return 1;
				break;
			case '}':
				if (stk.top() != '{') return 1;
				break;
			}
			stk.pop();
		}
		++c;
	}
	
	if (stk.size()) return 1;
	return 0;
}

int main() {
	const char* s = "[(({}){[]()}()())]";
	cout << "input: " << s << '\n';
	int a = string_check(s);
	if (a) cout << "incorrect";
	else cout << "correct";
	return 0;
}
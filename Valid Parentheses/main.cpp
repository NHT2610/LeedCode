//https://leetcode.com/problems/valid-parentheses/
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int charCode(char ch) {
	if (ch == '(' || ch == ')') { return 1; }
	if (ch == '[' || ch == ']') { return 2; }
	else { return 3; }
}

bool isValid(string s) {
	stack<char> tokens;
	for (int i = 0; i < s.length(); ++i) {
		if ((i == 0 || tokens.empty()) && (s[i] == ')' || s[i] == ']' || s[i] == '}')) {
			return false;
		}
		else if (tokens.empty() || (s[i] == '(' || s[i] == '[' || s[i] == '{')) {
			tokens.push(s[i]);
		}
		else {
			if (charCode(s[i]) != charCode(tokens.top())) {
				return false;
			}
			tokens.pop();
		}
	}
	if (!tokens.empty()) { return false; }
	return true;
}

int main() {
	string s;
	getline(cin, s);

	if (isValid(s)) {
		cout << "true";
	}
	else {
		cout << "false";
	}
	return 0;
}
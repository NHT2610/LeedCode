//https://www.hackerrank.com/challenges/balanced-brackets/problem?isFullScreen=true&h_r=next-challenge&h_v=zen
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

vector<string> ReadFile(const string& FileName) {
    fstream input;
    input.open(FileName, ios::in);
    string line1;
    getline(input, line1);
    int N = stoi(line1);
    vector<string> result(N);
    string element;
    for (int i = 0; i < N; ++i) {
        getline(input, element);
        if (element != "") {
            result[i] = element;
        }
        element = "";
    }
    input.close();
    return result;
}

void WriteResultToFile(const string& FileName, vector<int>& result) {
    fstream output;
    output.open(FileName, ios::out);
    int size = int(result.size());
    for (int i = 0; i < size; ++i) {
        output << result[i] << endl;
    }
    output.close();
}

vector<string> ParseString(string s, char token) {
    vector<string> result;
    int len = int(s.length());
    string temp;
    int j;
    for (int i = 0; i < len; ++i) {
        for (j = i; j < len && s[j] != token; ++j) {
            temp += s[j];
        }
        result.push_back(temp);
        temp = "";
        i = j;
    }
    return result;
}

int BracketCode(char bracket) {
    if (bracket == '(' || bracket == ')') { return 1; }
    if (bracket == '[' || bracket == ']') { return 2; }
    else { return 3; }
}

string isBalanced(string s) {
    int len = int(s.length());
    stack<char> Brackets;
    for (int i = 0; i < len; ++i) {
        if (Brackets.empty() && (s[i] == ')' || s[i] == ']' || s[i] == '}')) {
            return "NO";
        }
        else if (Brackets.empty() || s[i] == '(' || s[i] == '[' || s[i] == '{') {
            Brackets.push(s[i]);
        }
        else {
            if (BracketCode(Brackets.top()) != BracketCode(s[i])) {
                return "NO";
            }
            Brackets.pop();
        }
    }
    if (!Brackets.empty()) { return "NO"; }
    return "YES";
}

int main() {
    int N;
    cin >> N;
    string s;
    vector<string> input;
    cin.ignore();
    for (int i = 1; i <= N; ++i) {
        getline(cin, s);
        input.push_back(s);
        s = "";
    }
    for (int i = 0; i < N; ++i) {
        cout << isBalanced(input[i]) << endl;
    }
    return 0;
}
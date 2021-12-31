//https://www.hackerrank.com/challenges/maximum-element/problem?isFullScreen=true
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

vector<int> getMax(vector<string> operations) {
    vector<int> result;
    stack<int> NumbersStack;
    stack<int> MaxNum;
    int size = int(operations.size());
    for (int i = 0; i < size; ++i) {
        vector<string> element = ParseString(operations[i], ' ');
        if (element[0] == "1") {
            int number = stoi(element[1]);
            NumbersStack.push(number);
            if (MaxNum.empty() || number >= MaxNum.top()) {
                MaxNum.push(number);
            }
        }
        else if (element[0] == "2") {
            if (NumbersStack.top() == MaxNum.top()) {
                MaxNum.pop();
            }
            NumbersStack.pop();
        }
        else {
            result.push_back(MaxNum.top());
        }
    }
    return result;
}


int main() {
    vector<string> operations = ReadFile("testcase26.txt");
    /*int N;
    cin >> N;
    vector<string> operations(N);
    cin.ignore();
    for (int i = 0; i < N; ++i) { getline(cin, operations[i]); }
    int MaxNum = INT_MIN;*/
    int size = int(operations.size());
    vector<int> result = getMax(operations);
    vector<string> a;
    fstream input;
    input.open("a.txt", ios::in);
    string temp;
    while (!input.eof()) {input >> temp;if (temp != "") {a.push_back(temp);}temp = "";}
    input.close();
    int num;
    for (int i = 0; i < int(a.size()); ++i) {
        num = stoi(a[i]);
        if (num - result[i] != 0) {
            cout << i << "error" << endl;
        }
    }
    WriteResultToFile("output26.txt", result);
    /*vector<int> result = getMax(operations);
    for (int i = 0; i < int(result.size()); ++i) {
        cout << result[i] << endl;
    }*/
    return 0;
}
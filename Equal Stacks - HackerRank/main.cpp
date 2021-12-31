//https://www.hackerrank.com/challenges/equal-stacks/problem?isFullScreen=true&h_r=next-challenge&h_v=zen&h_r=next-challenge&h_v=zen
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

int equalStacks(vector<int> h1, vector<int> h2, vector<int> h3) {
    stack<int> s1, s2, s3;
    int height1, height2, height3;
    for (int i = 0; i < int(h1.size()); ++i) { s1.push(h1[i]); height1 += s1.top(); }
    for (int i = 0; i < int(h2.size()); ++i) { s1.push(h2[i]); height2 += s2.top(); }
    for (int i = 0; i < int(h3.size()); ++i) { s1.push(h3[i]); height3 += s3.top(); }

    while (height1 != height2 || height2 != height3 || height3 != height1) {
        
    }
    return height1;
}

int main() {
    string s;
    getline(cin, s);
    vector<string> NumberOfElements = ParseString(s, ' ');
    vector<int> h1(stoi(NumberOfElements[0]));
    vector<int> h2(stoi(NumberOfElements[1]));
    vector<int> h3(stoi(NumberOfElements[2]));
    string s1, s2, s3;
    getline(cin, s1);
    vector<string> temp = ParseString(s1, ' ');
    for (int i = 0; i < int(h1.size()); ++i) {
        h1[i] = stoi(temp[i]);
    }
    getline(cin, s2);
    temp.clear();
    temp = ParseString(s2, ' ');
    for (int i = 0; i < int(h2.size()); ++i) {
        h2[i] = stoi(temp[i]);
    }
    getline(cin, s3);
    temp.clear();
    temp = ParseString(s3, ' ');
    for (int i = 0; i < int(h3.size()); ++i) {
        h3[i] = stoi(temp[i]);
    }
    cout << equalStacks(h1, h2, h3);
    return 0;
}
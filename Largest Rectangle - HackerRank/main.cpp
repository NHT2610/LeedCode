//https://www.hackerrank.com/challenges/largest-rectangle/problem?isFullScreen=true&h_r=next-challenge&h_v=zen&h_r=next-challenge&h_v=zen&h_r=next-challenge&h_v=zen&h_r=next-challenge&h_v=zen
//https://www.codespeedy.com/largest-rectangular-area-in-a-histogram-in-cpp/
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

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

long largestRectangle(vector<int> h) {
    long MaxArea = INT_MIN;
    long CurrentArea;
    stack<int> IndexOfBuildings;
    int Lowest;
    int i = 0;
    while (i < int(h.size())) {
        if (IndexOfBuildings.empty() || h[i] >= h[IndexOfBuildings.top()]) {
            IndexOfBuildings.push(i++);
        }
        else {
            Lowest = IndexOfBuildings.top();
            IndexOfBuildings.pop();
            CurrentArea = h[Lowest] * (IndexOfBuildings.empty() ? 
                i : (i - IndexOfBuildings.top() - 1));
            if (CurrentArea > MaxArea) {
                MaxArea = CurrentArea;
            }
        }
    }
    while (!IndexOfBuildings.empty()) {
        Lowest = IndexOfBuildings.top();
        IndexOfBuildings.pop();
        CurrentArea = h[Lowest] * (IndexOfBuildings.empty() ?
            i : (i - IndexOfBuildings.top() - 1));
        if (CurrentArea > MaxArea) {
            MaxArea = CurrentArea;
        }
    }
    return MaxArea;
}

int main() {
    string temp;
    getline(cin, temp);
    int N = stoi(temp);
    vector<int> h(N);
    temp = "";
    getline(cin, temp);
    vector<string> temp_h = ParseString(temp, ' ');
    for (int i = 0; i < N; ++i) { h[i] = stoi(temp_h[i]); }
    cout << largestRectangle(h);
    return 0;
}
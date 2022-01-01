//https://www.hackerrank.com/challenges/game-of-two-stacks/problem?isFullScreen=true&h_r=next-challenge&h_v=zen&h_r=next-challenge&h_v=zen&h_r=next-challenge&h_v=zen
//Solution2 of https://askatul.com/game-of-two-stacks-solution/#Greedy_Criteria
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

int twoStacks(int maxSum, vector<int> a, vector<int> b) {
    stack<int> s1, s2;
    for (int i = int(a.size()) - 1; i >= 0; --i) { s1.push(a[i]); }
    for (int i = int(b.size()) - 1; i >= 0; --i) { s2.push(b[i]); }

    int CurrentSCORE = 0, BestSCORE, CurrentSUM = 0;
    stack<int> CurrentSUMStack1;
    //Lay gia tri tu stack1 cong vao tong cho den khi khong the lay duoc nua
    //s1: a1 a2 a3 a4 a5 a6 => Lay duoc CurrentSUM = a6 + a5 + a4 + a3, CurrentSUMStack1: a6 a5 a4 a3
    while (CurrentSUM <= maxSum) {
        if (!s1.empty()) {
            if (CurrentSUM + s1.top() > maxSum) {
                break;
            }
            CurrentSUM += s1.top();
            CurrentSUMStack1.push(s1.top());
            s1.pop();
            ++CurrentSCORE;
        }
        else { break; }
    }
    BestSCORE = CurrentSCORE;
    //Thu tong CurrentSUM lan luot voi cac phan tu lay ra tu s2
    //s2: b1 b2 b3 b4 b5 b6 b7 b8
    //Thu a6 + a5 + a4 + a3 + b8 + ...., thu a6 + a5 + a4 + b8 + .... cho den khi CurrentSUMStack1 empty
    while (!CurrentSUMStack1.empty()) {
        while (!s2.empty()) {
            if (CurrentSUM + s2.top() > maxSum) {
                break;
            }
            CurrentSUM += s2.top();
            s2.pop();
            ++CurrentSCORE;
        }
        if (CurrentSCORE > BestSCORE) {
            BestSCORE = CurrentSCORE;
        }
        CurrentSUM -= CurrentSUMStack1.top();
        CurrentSUMStack1.pop();
        --CurrentSCORE;
    }
    //Neu CurrentSUM van con thoa man thi tiep tuc lay phan tu trong s2 cong vao tong den khi > maxSum
    if (CurrentSUMStack1.empty() && CurrentSUM <= maxSum) {
        while (!s2.empty()) {
            if (CurrentSUM + s2.top() > maxSum) {
                break;
            }
            CurrentSUM += s2.top();
            s2.pop();
            ++CurrentSCORE;
        }
        if (CurrentSCORE > BestSCORE) {
            BestSCORE = CurrentSCORE;
        }
    }
    return BestSCORE;
}

int main() {
    string temp;
    getline(cin, temp);
    int g = stoi(temp);
    for (int i = 1; i <= g; ++i) {
        temp = "";
        getline(cin, temp);
        vector<string> NumbersOf = ParseString(temp, ' ');
        int N1 = stoi(NumbersOf[0]);
        int N2 = stoi(NumbersOf[1]);
        int maxSum = stoi(NumbersOf[2]);
        vector<int> a(N1);
        vector<int> b(N2);
        temp = "";
        getline(cin, temp);
        vector<string> a_temp = ParseString(temp, ' ');
        for (int i = 0; i < N1; ++i) { a[i] = stoi(a_temp[i]); }
        temp = "";
        getline(cin, temp);
        vector<string> b_temp = ParseString(temp, ' ');
        for (int i = 0; i < N2; ++i) { b[i] = stoi(b_temp[i]); }
        cout << twoStacks(maxSum, a, b) << endl;
    }
    return 0;
}
//https://www.hackerrank.com/challenges/waiter/problem?isFullScreen=true
#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

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

bool CheckPrime(int number, vector<int>& primes) {
    for (int i = 0; i < int(primes.size()); ++i) {
        if (number % primes[i] == 0) { return false; }
    }
    return true;
}

vector<int> waiter(vector<int> number, int q) {
    vector<int> primes;
    primes.push_back(2);
    int j;
    for (int i = 1; i < q; ++i) {
        for (j = primes[0] + 1; !CheckPrime(j, primes); ++j) {}
        primes.push_back(j);
    }
    vector<int> answers;
    stack<int> A, B;
    int size = int(number.size());
    for (int i = 0; i < size; ++i) { A.push(number[i]); }
    vector<int> temp;
    for (int i = 0; i < q; ++i) {
        while (!A.empty()) {
            if (A.top() % primes[i] == 0) {
                B.push(A.top());
                A.pop();
            }
            else {
                temp.push_back(A.top());
                A.pop();
            }
        }
        while (!B.empty()) {
            answers.push_back(B.top());
            B.pop();
        }
        if (i != q - 1) {
            for (int j = 0; j < int(temp.size()); ++j) { A.push(temp[j]); }
            temp.clear();
        }
        else {
            for (int j = int(temp.size() - 1); j >= 0; --j) {
                answers.push_back(temp[j]);
            }
        }
    }
    return answers;
}

int main() {
    string temp;
    getline(cin, temp);
    vector<string> FirstLine = ParseString(temp, ' ');
    int N = stoi(FirstLine[0]);
    int q = stoi(FirstLine[1]);
    temp = "";
    getline(cin, temp);
    vector<string> tokens = ParseString(temp, ' ');
    vector<int> number(N);
    for (int i = 0; i < N; ++i) { number[i] = stoi(tokens[i]); }
    vector<int> answers = waiter(number, q);
    for (int i = 0; i < int(answers.size()); ++i) {
        cout << answers[i] << " ";
    }
    return 0;
}
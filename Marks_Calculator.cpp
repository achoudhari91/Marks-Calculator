#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

string infixToPostfix(string infix) {
    stack<char> s;
    string postfix = "";

    for (char ch : infix) {
        if (isalnum(ch)) {
            postfix += ch;
            postfix += ' ';
        }
        else if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                postfix += ' ';
                s.pop();
            }
            if (!s.empty())
                s.pop();
        }
        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/') {
            while (!s.empty() && s.top() != '(' &&
                   precedence(s.top()) >= precedence(ch)) {
                postfix += s.top();
                postfix += ' ';
                s.pop();
            }
            s.push(ch);
        }
    }

    while (!s.empty()) {
        postfix += s.top();
        postfix += ' ';
        s.pop();
    }

    return postfix;
}

int evaluatePostfix(string postfix, int marks[]) {
    stack<int> s;

    for (char ch : postfix) {
        if (ch == ' ')
            continue;

        if (ch == 'm') {
            // Marks are entered as m1, m2, and m3.
            // The digit is handled in the next iteration
            // in the simplified expression below.
            continue;
        }
        else if (isdigit(ch)) {
            s.push(marks[ch - '1']);
        }
        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/') {
            int b = s.top();
            s.pop();
            int a = s.top();
            s.pop();

            switch (ch) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
            }
        }
    }

    return s.top();
}

int main() {
    int m1, m2, m3;

    cout << "Enter marks of 3 subjects: ";
    cin >> m1 >> m2 >> m3;

    string infix = "(1+2+3)/3";

    cout << "Infix Expression: " << infix << endl;

    string postfix = infixToPostfix(infix);
    cout << "Postfix Expression: " << postfix << endl;

    int marks[3] = {m1, m2, m3};
    int average = evaluatePostfix(postfix, marks);

    cout << "Average Marks: " << average << endl;

    return 0;
}

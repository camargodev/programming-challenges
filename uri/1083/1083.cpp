#include <iostream>
#include <stack> 

using namespace std;

class TypeChecker {
    public:
        bool isOperand(char c) {
            if (c >= '0' && c <= '9') return true;
            if (c >= 'a' && c <= 'z') return true;
            if (c >= 'A' && c <= 'Z') return true;
            return false;
        }
        bool isLeftParenthesis(char c) {
            return c == '(';
        }
        bool isRightParenthesis(char c){
            return c == ')';
        }
        bool isOperator(char c) {
            if (c == '^') return true;
            if (c == '*') return true;
            if (c == '/') return true;
            if (c == '+') return true;
            if (c == '-') return true;
            if (c == '>') return true;
            if (c == '<') return true;
            if (c == '=') return true;
            if (c == '#') return true;
            if (c == '.') return true;
            if (c == '|') return true;
            return false;
        }
        bool isValidChar(char c) {
            if (isOperand(c)) return true;
            if (isLeftParenthesis(c)) return true;
            if (isRightParenthesis(c)) return true;
            if (isOperator(c)) return true;
            return false;
        }
};

class OperatorPriority {
    public:
        int getPriority(char c) {
            if (c == '^') return 6;
            if (c == '*') return 5;
            if (c == '/') return 5;
            if (c == '+') return 4;
            if (c == '-') return 4;
            if (c == '>') return 3;
            if (c == '<') return 3;
            if (c == '=') return 3;
            if (c == '#') return 3;
            if (c == '.') return 2;
            if (c == '|') return 1;
            return 0;
        }
};

class Parser {
    TypeChecker checker;
    OperatorPriority priority;
    const string SYNTAX_ERROR = "Syntax Error!";
    const string LEXICAL_ERROR = "Lexical Error!";
    public:
        Parser() {}
        string parse(string expression) {
            string postFixedExpression = "";
            stack<char> stack;
            if (expression.length() == 0)
                return SYNTAX_ERROR;
            for (unsigned i = 0; i < expression.length(); i++) 
                if (!checker.isValidChar(expression.at(i))) return LEXICAL_ERROR;
            for (unsigned i = 0; i < expression.length(); i++) {
                char c = expression.at(i);
                if (checker.isOperand(c)) {
                    if (i > 0 && !(checker.isOperator(expression.at(i-1))
                        || checker.isLeftParenthesis(expression.at(i-1))))
                        return SYNTAX_ERROR;
                    postFixedExpression += c;
                } else if (checker.isLeftParenthesis(c)) {
                    stack.push(c);
                } else if (checker.isRightParenthesis(c)) {
                    while (!stack.empty() && !checker.isLeftParenthesis(stack.top())) {
                        postFixedExpression += stack.top();
                        stack.pop();
                    }
                    if (!stack.empty() && checker.isLeftParenthesis(stack.top())) {
                        stack.pop();
                    } else { 
                        return SYNTAX_ERROR;
                    }
                } else if (checker.isOperator(c)) {
                    if (postFixedExpression.length() == 0)
                        return SYNTAX_ERROR;
                    if (i > 0 && !(checker.isRightParenthesis(expression.at(i-1))
                        || checker.isOperand(expression.at(i-1))))
                        return SYNTAX_ERROR;
                    if (i < (expression.length()-1) && !(checker.isLeftParenthesis(expression.at(i+1))
                        || checker.isOperand(expression.at(i+1))))
                        return SYNTAX_ERROR;
                    if (stack.empty() || checker.isLeftParenthesis(stack.top())) {
                        stack.push(c);
                    } else {
                        while (!stack.empty() && !checker.isLeftParenthesis(stack.top())
                            && (priority.getPriority(c) <= priority.getPriority(stack.top()))) {
                            postFixedExpression += stack.top();
                            stack.pop();
                        }
                        stack.push(c);
                    }
                } else {
                    return LEXICAL_ERROR;
                }
            }
            while(!stack.empty()) {
                char stackTop = stack.top();
                if (checker.isLeftParenthesis(stackTop))
                    return SYNTAX_ERROR;
                postFixedExpression += stackTop;
                stack.pop();

            }
            if (postFixedExpression.length() == 0)
                return SYNTAX_ERROR;
            return postFixedExpression;
        }
};


int main()
{
    string expression;
    Parser parser;
    while (cin >> expression) {
        string parsedExpression = parser.parse(expression);
        cout << parsedExpression << endl;
    }
}

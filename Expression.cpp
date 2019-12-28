//
// Created by Dor Refaeli on 22/12/2019.
//

#include "Expression.h"
#include <regex>
#include <stack>
#include <queue>

using namespace std;

Value::Value(double newValue) { this->value = newValue; }

Value::~Value() {}

double Value::calculate() { return this->value; }

Variable::Variable(string newName, double newValue) {
    this->name = newName;
    this->value = newValue;
}

Variable::Variable(Variable const &other) {
    this->name = other.name;
    this->value = other.value;
}

Variable::~Variable() {}

Variable &Variable::operator++() {
    this->value++;
    return *this;
}

double Variable::calculate() { return this->value; }

Variable &Variable::operator--() {
    this->value--;
    return *this;
}

Variable &Variable::operator+=(double num) {
    this->value += num;
    return *this;
}

Variable &Variable::operator-=(double num) {
    this->value -= num;
    return *this;
}

Variable &Variable::operator++(int) {
    this->value++;
    return *this;
}

Variable &Variable::operator--(int) {
    this->value--;
    return *this;
}

UnaryOperator::~UnaryOperator() {
    if (this->expression != nullptr) {
        delete this->expression;
    }
}

UPlus::UPlus(Expression *newExpression) { this->expression = newExpression; }

double UPlus::calculate() { return this->expression->calculate(); }

UMinus::UMinus(Expression *newExpression) { this->expression = newExpression; }

double UMinus::calculate() { return -this->expression->calculate(); }

BinaryOperator::~BinaryOperator() {
    if (this->left != nullptr) {
        delete this->left;
    }
    if (this->right != nullptr) {
        delete this->right;
    }
}

Plus::Plus(Expression *newLeft, Expression *newRight) {
    this->left = newLeft;
    this->right = newRight;
}

double Plus::calculate() { return this->left->calculate() + this->right->calculate(); }

Minus::Minus(Expression *newLeft, Expression *newRight) {
    this->left = newLeft;
    this->right = newRight;
}

double Minus::calculate() { return this->left->calculate() - this->right->calculate(); }

Mul::Mul(Expression *newLeft, Expression *newRight) {
    this->left = newLeft;
    this->right = newRight;
}

double Mul::calculate() { return this->left->calculate() * this->right->calculate(); }

Div::Div(Expression *newLeft, Expression *newRight) {
    this->left = newLeft;
    this->right = newRight;
}

double Div::calculate() {
    double tempRight = this->right->calculate();
    //if the value of the divider is zero throws an exception
    if (tempRight == 0) {
        throw ("division by zero");
    }
    return this->left->calculate() / tempRight;
}

Interpreter::Interpreter() {}

Interpreter::~Interpreter() {
    map<string, Variable *>::iterator it;
    //iterates through the variables mar and delete them one by one
    for (it = this->variables.begin(); it != this->variables.end(); it++) {
        if (it->second != nullptr) {
            delete (it->second);
        }
    }
}

void Interpreter::setVariables(string str) {
    //regex that searches for "something=something" with or without ';' at the end
    regex variableRegex("(.+?)\\=([^;]+);?");
    smatch match;
    //iterates through the matches and adds them to the variables map
    while (regex_search(str, match, variableRegex)) {
        char c = match.str(1).front();
        //if the variable name doesn't starts with a letter throws an exception
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
            throw ("illegal variable assignment!");
        }
        try {
            //tries converting the string into a double, if something goes wrong throws an exception
            double num = stod(match.str(2));
            Variable *variable = new Variable(match.str(1), num);
            //if there is a variable with the same name already deletes his map - value before setting a new one
            if (this->variables[match.str(1)] != nullptr) {
                delete (this->variables[match.str(1)]);
            }
            this->variables[match.str(1)] = variable;
        } catch (...) {
            throw ("illegal variable assignment!");
        }
        str = match.suffix().str();
    }
}

Expression *Interpreter::interpret(string str) {
    //regex that splits the expression into tokens
    regex splitToTokensRegex("[^-+()*/]+|[-+()*/]");
    //regex that check if a string is an operator or not
    regex operatorRegex("[-+*/]");
    smatch match;
    stack<string> operators;
    queue<string *> postfix;
    bool lastWasOpenningParentheses = true;
    while (regex_search(str, match, splitToTokensRegex)) {
        string token = match.str(0);
        //checks if the token is an operator or not
        if (regex_match(token, operatorRegex)) {
            if (lastWasOpenningParentheses && token == "+") {
                //token is unary plus
                token = "+u";
            } else if (lastWasOpenningParentheses && token == "-") {
                //token is unary minus
                token = "-u";
            }
            //while the stack isn't empty and the top of the stack is an operator that as greater precedence than the token
            while (!operators.empty() && this->before(operators.top(), token)) {
                //pop the operator from the top of the stack and add him to the queue
                postfix.push(new string(operators.top()));
                operators.pop();
            }
            operators.push(token);
            lastWasOpenningParentheses = false;
        } else if (token == "(") {
            operators.push(token);
            lastWasOpenningParentheses = true;
        } else if (token == ")") {
            while (operators.top() != "(") {
                if (operators.empty()) {
                    throw ("illegal math expression");
                }
                postfix.push(new string(operators.top()));
                operators.pop();
            }
            operators.pop();
            lastWasOpenningParentheses = false;
        } else {
            postfix.push(new string(token));
            lastWasOpenningParentheses = false;
        }
        //move to the next token
        str = match.suffix().str();
    }
    //moves all operators to the queue
    while (!operators.empty()) {
        postfix.push(new string(operators.top()));
        operators.pop();
    }
    return this->build(postfix);
}

bool Interpreter::before(string a, string b) {
    if (b == "(") {
        return false;
    }
    if (a == "+u" || a == "-u") {
        if (b != "+u" && b != "-u") {
            return true;
        }
    }
    if (a == "*" || a == "/") {
        if (b == "+" || b == "-") {
            return true;
        }
    }
    return false;
}

Expression *Interpreter::build(queue<string *> postfix) {
    stack<Expression *> expressions;
    //regex that check if a string is an operator or not
    regex binaryOperatorRegex("[-+*/]");
    //while the queue isn't empty
    while (!postfix.empty()) {
        //copy the top of the queue than delete is content before poping
        string current = *(postfix.front());
        if (postfix.front() != nullptr) {
            delete postfix.front();
        }
        postfix.pop();
        if (regex_match(current, binaryOperatorRegex)) {
            //if there is a binary operator but no 2 expression for him to operate on:
            // deletes all of the queue and throws an exception
            if (expressions.size() <= 1) {
                while (!postfix.empty()) {
                    if (postfix.front() != nullptr) {
                        delete postfix.front();
                    }
                    postfix.pop();
                }
                throw ("illegal math expression");
            } else {
                Expression *right = expressions.top();
                expressions.pop();
                Expression *left = expressions.top();
                expressions.pop();
                if (current == "*") {
                    expressions.push(new Mul(left, right));
                } else if (current == "/") {
                    expressions.push(new Div(left, right));
                } else if (current == "+") {
                    expressions.push(new Plus(left, right));
                } else if (current == "-") {
                    expressions.push(new Minus(left, right));
                }
            }
        } else if (current == "+u" || current == "-u") {
            //if there is a unary operator but no expression for him to operate on:
            // deletes all of the queue and throws an exception
            if (expressions.size() == 0) {
                while (!postfix.empty()) {
                    if (postfix.front() != nullptr) {
                        delete postfix.front();
                    }
                    postfix.pop();
                }
                throw ("illegal math expression");
            } else {
                Expression *tempExpression = expressions.top();
                expressions.pop();
                if (current == "+u") {
                    expressions.push(new UPlus(tempExpression));
                } else {
                    expressions.push(new UMinus(tempExpression));
                }
            }
        } else if (this->variables.count(current)) {
            //if there is a variable matching the current item in the queue push a copy of him into the stack
            expressions.push(new Variable(*(this->variables[current])));
        } else {
            //if got here then the only other option is that the current item is a number
            // tries converting him, if he isn't a number throws an exception
            try {
                expressions.push(new Value(stod(current)));
            } catch (...) {
                while (!postfix.empty()) {
                    if (postfix.front() != nullptr) {
                        delete postfix.front();
                    }
                    postfix.pop();
                }
                throw ("illegal math expression");
            }
        }
    }
    //returns the top (and only) item in the stack,
    // should be the nested expression because of how the algorithm operates
    return expressions.top();
}

void Interpreter::setVariable(string name, double num) {
    Variable *variable = new Variable(name, num);
    if (this->variables[name] != nullptr) {
        delete (this->variables[name]);
    }
    this->variables[name] = variable;
}

void Interpreter::setVariables(map<string, float> varMap) {
    map<string, float>::iterator it = varMap.begin();
    while (it != varMap.end()) {
        this->setVariable(it->first, it->second);
    }
}

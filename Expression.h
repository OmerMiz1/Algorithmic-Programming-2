//
// Created by Dor Refaeli on 22/12/2019.
//

#ifndef ALGORITHMICPROGRAMMINGPROJECT_EXPRESSION_H
#define ALGORITHMICPROGRAMMINGPROJECT_EXPRESSION_H

#include <string>
#include <map>
#include <queue>

using namespace std;

class Expression {
public:
    virtual double calculate() = 0;

    virtual ~Expression() {}
};

/**
 * A class that describe an expression of type value
 */
class Value : public Expression {
    double value;
public:
    Value(double newValue);

    ~Value();

    double calculate();
};

/**
 * A class that describe an expression of type variable
 */
class Variable : public Expression {
    string name;
    double value;
public:
    Variable(string, double);

    /**
     * copies an existing variable.
     */
    Variable(Variable const &);

    ~Variable();

    double calculate();

    Variable &operator++();

    Variable &operator--();

    Variable &operator+=(double);

    Variable &operator-=(double);

    Variable &operator++(int);

    Variable &operator--(int);
};

/**
 * A class that describe an expression of type unary operator
 * UPlus and UMinus are derived from this class
 * UPlus describes the plus operator and UMinus describe the minus operator
 */
class UnaryOperator : public Expression {
protected:
    Expression *expression;
public:
    ~UnaryOperator();
};

class UPlus : public UnaryOperator {
public:
    UPlus(Expression *);

    double calculate();
};

class UMinus : public UnaryOperator {
public:
    UMinus(Expression *);

    double calculate();
};

/**
 * A class that describe an expression of type binary operator
 * Plus, Minus, Mul and Div are derived from this class each describe a binary operation on 2 expressions
 */
class BinaryOperator : public Expression {
protected:
    Expression *left;
    Expression *right;
public:
    ~BinaryOperator();
};

class Plus : public BinaryOperator {
public:
    Plus(Expression *, Expression *);

    double calculate();
};

class Minus : public BinaryOperator {
public:
    Minus(Expression *, Expression *);

    double calculate();
};

class Mul : public BinaryOperator {
public:
    Mul(Expression *, Expression *);

    double calculate();
};

class Div : public BinaryOperator {
public:
    Div(Expression *, Expression *);

    double calculate();
};

/**
 * A class that ables the user to get a list of variables and a complicated "written" expression
 * and interpret him into a nested expression object
 */
class Interpreter {
    map<string, Variable *> variables;
public:
    Interpreter();

    ~Interpreter();

    void setVariables(string);

    void setVariable(string, double);

    void setVariables(map<string, float>);

    Expression *interpret(string);

    //TODO for debugging
    int varsCount() {
        int count = 0;
        for(auto it : variables) {
            count++;
        }
        return count;
    }

private:

    /**
     * A method that gets 2 operators and decides which one should be done first
     * @param a first operator
     * @param b second operator
     * @return true if a is before b, false otherwise
     */
    static bool before(string a, string b);

    /**
     * Gets a queue of strings describing an expression in a postfix order
     * @return a nested expression object
     */
    Expression *build(queue<string *>);
};


#endif //ALGORITHMICPROGRAMMINGPROJECT_EXPRESSION_H

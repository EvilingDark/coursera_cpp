#ifndef NODE_H
#define NODE_H
#pragma once
#include "date.h"
#include <memory>
#include <string>

using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation {
    And,
    Or
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& c, const Date& d)
        : cmp { c }
        , date_ { d }
    {
    }
    bool Evaluate(const Date& date, const string& event) const override;
    const Comparison cmp;
    const Date date_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& c, const string& event)
        : cmp { c }
        , event_ { event }
    {
    }
    bool Evaluate(const Date& date, const string& event) const override;
    const Comparison cmp;
    const string event_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation& l_op, const shared_ptr<Node>& l, const shared_ptr<Node>& r)
        : logical_operation { l_op }
        , left { l }
        , right { r }
    {
    }
    bool Evaluate(const Date& date, const string& event) const override;
    const LogicalOperation logical_operation;
    const shared_ptr<Node> left;
    const shared_ptr<Node> right;
};

class EmptyNode : public Node {
    bool Evaluate(const Date& date, const string& event) const override;
};

#endif // NODE_H

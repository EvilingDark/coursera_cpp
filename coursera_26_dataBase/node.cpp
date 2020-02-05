#include "node.h"

using namespace std;

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const
{
    switch (cmp) {
    case Comparison::Less:
        return date < date_;
    case Comparison::LessOrEqual:
        return date <= date_;
    case Comparison::Greater:
        return date > date_;
    case Comparison::GreaterOrEqual:
        return date >= date_;
    case Comparison::Equal:
        return date == date_;
    case Comparison::NotEqual:
        return date != date_;
    }
    return 0;
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const
{
    switch (cmp) {
    case Comparison::Less:
        return event < event_;
    case Comparison::LessOrEqual:
        return event <= event_;
    case Comparison::Greater:
        return event > event_;
    case Comparison::GreaterOrEqual:
        return event >= event_;
    case Comparison::Equal:
        return event == event_;
    case Comparison::NotEqual:
        return event != event_;
    }
    return 0;
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const
{
    switch (logical_operation) {
    case LogicalOperation::And:
        return left->Evaluate(date, event) && right->Evaluate(date, event);
    case LogicalOperation::Or:
        return left->Evaluate(date, event) || right->Evaluate(date, event);
    }
}

bool EmptyNode::Evaluate(const Date& date, const string& event) const
{
    return 1;
}

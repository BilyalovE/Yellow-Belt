#pragma once
#include <string>
#include "date.h"

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
    Or,
    And
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cmp, const Date& date_cond);
    bool Evaluate(const Date& date_bd, const string& event_bd) const override;
private:
    Comparison cmp_;
    Date date_cond_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const std::string& event_cond);
    bool Evaluate(const Date& date_bd, const string& event_bd) const override;

private:
    Comparison cmp_;
    string event_cond_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode (const LogicalOperation& logical_operation,
                          const shared_ptr<Node>& lhs,
                          const shared_ptr<Node>& rhs) noexcept;
    bool Evaluate(const Date& date, const string& event) const override;
    
private:
    const LogicalOperation lgc_op;
    const std::shared_ptr<Node> lhs_node;
    const std::shared_ptr<Node> rhs_node;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date& date, const string& event) const override;
};


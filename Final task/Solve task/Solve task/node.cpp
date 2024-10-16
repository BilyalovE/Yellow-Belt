#include "node.h"


DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date_cond)
    : cmp_(cmp), date_cond_(date_cond)
{ }

bool DateComparisonNode::Evaluate(const Date& date_bd, const string& event_bd) const {
    switch (cmp_) {
        case Comparison::Less:
            return date_bd < date_cond_;
        case Comparison::LessOrEqual:
            return date_bd <= date_cond_;
        case Comparison::Greater:
            return date_bd > date_cond_;
        case Comparison::GreaterOrEqual:
            return date_bd >= date_cond_;
        case Comparison::Equal:
            return date_bd == date_cond_;
        case Comparison::NotEqual:
            return date_bd != date_cond_;
    }
    return false;
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const std::string& event_cond)
    : cmp_(cmp), event_cond_(event_cond) { }

bool EventComparisonNode::Evaluate(const Date& date_bd, const string& event_bd) const {
    switch (cmp_) {
        case Comparison::Equal:
            return event_cond_ == event_bd;
        case Comparison::NotEqual:
            return event_cond_ != event_bd;
        default:
            break;
    }
    return false;
}

LogicalOperationNode::LogicalOperationNode (const LogicalOperation& logical_operation,
                      const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs) noexcept
                       : lgc_op(logical_operation), lhs_node(lhs), rhs_node(rhs) {

}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    switch(lgc_op){
        case LogicalOperation::Or:
            return lhs_node->Evaluate(date, event) || rhs_node->Evaluate(date, event);
        case LogicalOperation::And:
            return lhs_node->Evaluate(date, event) && rhs_node->Evaluate(date, event);
    }
}

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}

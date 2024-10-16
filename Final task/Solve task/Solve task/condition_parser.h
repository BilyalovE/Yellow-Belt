#pragma once
#include "node.h"
#include "test_runner.h"


#include <memory>
#include <iostream>

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();

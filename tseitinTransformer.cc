#include "tseitinTransformer.h"

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // your code starts here
  std::string content = subRoot->getContent();
  if (subRoot->isOperator()) {
    int me = varIdCounter++;
    int left = transSubformula(subRoot->getLeftChild());
    if (content == "-") {
      addNegEq(me, left);
    } else {
      int right = transSubformula(subRoot->getRightChild());
      if (content == "+") {
        addOrEq(me, left, right);
      } else {
        addAndEq(me, left, right);
      }
    }
    return me;
  } else {
    if (varIdTable.find(content) == varIdTable.end()) {
      varIdTable[content] = varIdCounter++;
    }
    return varIdTable[content];
  }
}

auto makeVector = [](int v1, int v2) { return std::vector<int>{v1, v2}; };
auto makeVector3 = [](int v1, int v2, int v3) { return std::vector<int>{v1, v2, v3}; };

void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
  cnf.push_back(makeVector(-curID, -childID));
  cnf.push_back(makeVector(curID, childID));
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  cnf.push_back(makeVector3(-curID, leftID, rightID));
  cnf.push_back(makeVector(-leftID, curID));
  cnf.push_back(makeVector(-rightID, curID));
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  cnf.push_back(makeVector(-curID, leftID));
  cnf.push_back(makeVector(-curID, rightID));
  cnf.push_back(makeVector3(-leftID, -rightID, curID));
}

std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here
  cnf.clear();
  transSubformula(formulaRoot);
  cnf.push_back(std::vector<int>{1});
  return cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  // your code starts here
  for (auto &expr: cnf) {
    result += "[";
    for (auto &val: expr) {
      result += std::to_string(val) + ",";
    }
    result.pop_back();
    result += "]";
  }
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  return varIdCounter - 1;
}
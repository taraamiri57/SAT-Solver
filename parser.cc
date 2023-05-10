#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"
#include <iostream>

template <class T>
inline T pop_last(std::vector<T> &vec) {
  T last = vec.back();
  vec.pop_back();
  return last;
}

inline int priority(std::string oper) {
  return std::string("+*-").find(oper);
}

FormulaParser::FormulaParser(std::string ln): tknzr {new Tokenizer{ln}} {}

TreeNode * FormulaParser::getTreeRoot() {
  // your code starts here
  while (tknzr->advanceToken()) {
    Token token = tknzr->getToken();
    if (token.type == "variable") { // if variable, add to operands array
      operands.push_back(new VariableNode(token.content));
    } else if (token.type == "bracket") {
      if (token.content == "(") { // if open, add to operators array
        operators.push_back(token);
      } else { // if close, pop operators until '('
        while (true) {
          if (!operators.size())
            throw std::runtime_error("invalid input");
          Token oper = operators.back();
          if (oper.content == "(")
            break;
          pop_operator();
        }
        operators.pop_back();
      }
    } else if (token.type == "operator") { // if operator, pop priority-higher operators until '(' or empty
      while (operators.size()) {
        Token oper = operators.back();
        if (oper.content == "(")
          break;
        if (priority(oper.content) < priority(token.content))
          break;
        pop_operator();
      }
      operators.push_back(token);
    } else 
      throw std::runtime_error("invalid input");
  }
  while (operators.size()) { // pop remaining operators
    if (operators.back().content == "(") 
      throw std::runtime_error("invalid input");
    pop_operator();
  }
  if (operands.size() != 1) // check if only ope operands exist
    throw std::runtime_error("invalid input");
  return operands[0];
}

void FormulaParser::pop_operator() {
  Token oper = operators.back();
  TreeNode *operNode = new OperatorNode(oper.content);
  if (oper.content == "-") { // pop last operand
    if (operands.size() < 1)
      throw std::runtime_error("invalid input");
    operNode->updateLeftChild(pop_last(operands));
  } else { // pop last 2 operands and add new value
    if (operands.size() < 2)
      throw std::runtime_error("invalid input");
    TreeNode *right = pop_last(operands);
    TreeNode *left = pop_last(operands);
    operNode->updateChildren(left, right);
  }
  operands.push_back(operNode);
  operators.pop_back();
}

FormulaParser::~FormulaParser() {
  // your code starts here
  delete tknzr;
}
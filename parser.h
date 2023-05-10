#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <vector>

#include "tokenizer.h"

class TreeNode;
class Tokenizer;

// Parser for the Boolean Formula
class FormulaParser {
    std::vector<TreeNode*> operands;
    std::vector<Token> operators;
    Tokenizer *tknzr;
    void pop_operator(); // pop last operator
  public:
    FormulaParser(std::string ln);
    TreeNode *getTreeRoot(); // parse the Boolean formula and return the root node of the formula syntax tree
    ~FormulaParser();
};

#endif

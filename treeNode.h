#ifndef TNODE_H
#define TNODE_H

#include <string>
#include <map>

// abstract superclass of the syntax tree node
class TreeNode {
    std::string content;
    TreeNode *leftChild = nullptr;
    TreeNode *rightChild = nullptr;
  public:
    TreeNode *getLeftChild() const;
    TreeNode *getRightChild() const;
  public:
    TreeNode(std::string cntt);
    std::string getContent() const;
    void updateLeftChild(TreeNode *lChild); // for the operator "-", the operand is stored in leftChild
    void updateChildren(TreeNode *lChild, TreeNode *rChild);
    virtual ~TreeNode();
    virtual bool isOperator() const; // return ture if this node is operator
};

// concrete tree node of opertaor type
class OperatorNode : public TreeNode {
  public:
    OperatorNode(std::string cntt);
    bool isOperator() const;
};

// concrete tree node of varibale type
class VariableNode : public TreeNode {
  public:
    VariableNode(std::string cntt);
};

#endif

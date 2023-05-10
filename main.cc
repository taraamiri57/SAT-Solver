#include "tseitinTransformer.h"
#include "satSolver.h"
#include "parser.h"
#include <iostream>

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    // your code starts here
    if(!std::getline(std::cin, line))
      break;

    try {
      // parse formula string
      FormulaParser formulaParser(line);
      TreeNode *root = formulaParser.getTreeRoot();
      // transform
      TseitinTransformer transformer(root);
      std::vector<std::vector<int>> expression = transformer.transform();
      int varNum = transformer.getVarNum();
      // sat
      bool sat = satCallingMiniSat(varNum, expression);
      std::cout << (sat ? "sat" : "unsat") << std::endl;
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
    }
  }
}

#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <memory>
#include <iostream>

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
  // your code starts here
  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());

  for (unsigned int i = 0; i < numVar; ++i) {
    solver->newVar();
  }

  for (auto &expr: cnf) {
    Minisat::vec<Minisat::Lit> lits;
      for (auto &val: expr) {
          if (val > 0) {
            lits.push(Minisat::mkLit(val - 1));
          } else {
            lits.push(~Minisat::mkLit(-val - 1));
          }
      }
      solver->addClause(lits);
  }

  return solver->solve();
}

#include "tokenizer.h"
#include <cctype>
#include <iostream>
#include <map>

Tokenizer::Tokenizer(std::string ln) {
  // complete the constructor
  this->ln = ln;
  this->pos = 0;
}

bool Tokenizer::advanceToken() {
  // your code starts here
  for (; pos < ln.length() && ln[pos] == ' '; pos++);
  return hasToken();
}

bool Tokenizer::hasToken() const {
  // your code starts heres
  return pos < ln.length();
}

// only can be called when hasToken() is true
Token Tokenizer::getToken() {
  Token resultToken;
  // your code starts there
  if (ln[pos] == '(' || ln[pos] ==')') { // check bracket
    resultToken.type = "bracket";
    resultToken.content = ln[pos];
    pos++;
  } else if (ln[pos] == '+' || ln[pos] == '-' || ln[pos] == '*') { // check operators
    resultToken.type = "operator";
    resultToken.content = ln[pos];
    pos++;
  } else if (isalpha(ln[pos])) { // check variable name
    int startpos = pos;
    for (; pos < ln.length() && (isalpha(ln[pos]) || isdigit(ln[pos])); pos++);
    resultToken.type = "variable";
    resultToken.content = ln.substr(startpos, pos - startpos);
  } else // else throw error
    throw std::runtime_error("invalid input");
  return resultToken;
}

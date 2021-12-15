#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "AND1.h"
#include "COMB.h"
#include "GATE.h"

int main (void)
{
  map<string,Gate*> test;
  vector<string> in;

  in.push_back("I1");
  in.push_back("I2");

  test["test"] = &(AND1("DUV",in,"out"));

  test["test"]->afficher();

  return(0);
}

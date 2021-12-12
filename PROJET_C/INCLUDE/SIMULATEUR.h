#ifndef NET_H
  #define NET_H
  #include <iostream>
  #include <sstream>
  #include <string>
  #include <vector>
  #include <map>
  #include "NET.h"
  #include "GATE.h"
  #include "DECOUPAGE.h"

  using namespace std;

  class Simulateur{

  private :
  map<string,*Net> input;
  map<string,*Net> output;
  map<string,*Gate> gate;
  string url_json;
  string url_dot;

  public :
  Simulateur();
  ~Simulateur();

  void obtain_url();
  bool url_valid();
  string get_url_json();
  string get_url_json();

  *Net get_input(string nom);
  *Net get_output(string nom);
  *Gate get_gate(string nom);
  bool add_input(*Net i);
  bool add_output(*Net o);
  bool add_gate(*Gate g);
  void set_input(unsigned int index);
  void set_output(string nom,bool val);

  vector<Decoupage> lexeur_dot ();
  int parsseur_dot (vector<Decoupage> dot);
  vector<Decoupage> lexeur_json ();
  int parsseur_json (vector<Decoupage> json);
  void err_parssing_dot(*Decoupage err_w);
  void err_parssing_json(*Decoupage err_w);

  int Kernel();
  void err_simulation(*Gate err_g,*Net err_n);

  void print();

  };
#endif

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "AND1.h"
#include "OR1.h"
#include "XOR1.h"
#include "NOT1.h"

int main()
{
  map<string,Net> in;
  map<string,Net> out;

  string net1="Net1";
  string net2="Net2";
  string net_1="Net-1";
  string net_2="Net-2";
  string net3="Net3";
  string net20="Net20";

  in[net1]=Net(net1);
  in[net2]=Net(net2);
  in[net3]=Net(net3);
  in[net_1]=Net(net_1);
  in[net_2]=Net(net_2);
  out[net20]=Net(net20);
  vector<string> input_1;
  vector<string> input_2;
  vector<string> input_3;
  input_1.push_back(net_1);
  input_1.push_back(net2);
  input_2.push_back(net3);
  input_2.push_back(net_2);
  input_3.push_back(net1);

  AND1 duv_1 ("MYAND2",input_1,net_2);
  cout << "Porte 1: " ;
  duv_1.afficher() ;
  cout << endl << endl ;
  XOR1 duv_2 ("MYXOR2",input_2,net20);
  cout << "Porte 2: " ;
  duv_2.afficher() ;
  cout << endl << endl ;
  NOT1 duv_3 ("MYNOT",input_3,net_1);
  cout << "Porte 3: " ;
  duv_3.afficher() ;
  cout << endl << endl ;

  in[net1].set_val(0);
  in[net2].set_val(0);
  in[net3].set_val(0);
  in[net_1].set_val(duv_3.calcul_output(in));
  in[net_2].set_val(duv_1.calcul_output(in));
  out[net20].set_val(duv_2.calcul_output(in));
  cout << " 0 0 0  =  " << out[net20].get_val() <<endl;
  in[net1].set_val(0);
  in[net2].set_val(0);
  in[net3].set_val(1);
  in[net_1].set_val(duv_3.calcul_output(in));
  in[net_2].set_val(duv_1.calcul_output(in));
  out[net20].set_val(duv_2.calcul_output(in));
  cout << " 0 0 1  =  " << out[net20].get_val() <<endl;
  in[net1].set_val(0);
  in[net2].set_val(1);
  in[net3].set_val(0);
  in[net_1].set_val(duv_3.calcul_output(in));
  in[net_2].set_val(duv_1.calcul_output(in));
  out[net20].set_val(duv_2.calcul_output(in));
  cout << " 0 1 0  =  " << out[net20].get_val() <<endl;
  in[net1].set_val(0);
  in[net2].set_val(1);
  in[net3].set_val(1);
  in[net_1].set_val(duv_3.calcul_output(in));
  in[net_2].set_val(duv_1.calcul_output(in));
  out[net20].set_val(duv_2.calcul_output(in));
  cout << " 0 1 1  =  " << out[net20].get_val() <<endl;
  in[net1].set_val(1);
  in[net2].set_val(0);
  in[net3].set_val(0);
  in[net_1].set_val(duv_3.calcul_output(in));
  in[net_2].set_val(duv_1.calcul_output(in));
  out[net20].set_val(duv_2.calcul_output(in));
  cout << " 1 0 0  =  " << out[net20].get_val() <<endl;
  in[net1].set_val(1);
  in[net2].set_val(0);
  in[net3].set_val(1);
  in[net_1].set_val(duv_3.calcul_output(in));
  in[net_2].set_val(duv_1.calcul_output(in));
  out[net20].set_val(duv_2.calcul_output(in));
  cout << " 1 0 1  =  " << out[net20].get_val() <<endl;
  in[net1].set_val(1);
  in[net2].set_val(1);
  in[net3].set_val(0);
  in[net_1].set_val(duv_3.calcul_output(in));
  in[net_2].set_val(duv_1.calcul_output(in));
  out[net20].set_val(duv_2.calcul_output(in));
  cout << " 1 1 0  =  " << out[net20].get_val() <<endl;
  in[net1].set_val(1);
  in[net2].set_val(1);
  in[net3].set_val(1);
  in[net_1].set_val(duv_3.calcul_output(in));
  in[net_2].set_val(duv_1.calcul_output(in));
  out[net20].set_val(duv_2.calcul_output(in));
  cout << " 1 1 1  =  " << out[net20].get_val() <<endl;

  return 0;
}

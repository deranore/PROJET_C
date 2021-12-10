#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "MUX1.h"

int main()
{
  map<string,Net> in;
  map<string,Net> out;

  string net1="Net1";
  string net2="Net2";
  string net3="Net3";
  string net4="Net4";
  string net5="Net5";
  string net6="Net6";
  string net10="Net10";

  in[net1]=Net(net1);
  in[net2]=Net(net2);
  in[net3]=Net(net3);
  in[net4]=Net(net4);
  in[net5]=Net(net5);
  in[net6]=Net(net6);
  out[net10]=Net(net10);

  vector<string> input;
  vector<string> selector;
  input.push_back(net3);
  input.push_back(net4);
  input.push_back(net5);
  input.push_back(net6);
  selector.push_back(net1);
  selector.push_back(net2);

  MUX1 duv_1 ("MYMUX4",input,net10,selector);
  cout << "MUX : " ;
  duv_1.afficher() ;
  cout << endl << endl ;
  cout<<" 1  2  3  4  5  6     20"<<endl;
  for (int i = 0; i < 1<<6; i++)
  {
    in[net1].set_val(i&0b100000);
    in[net2].set_val(i&0b010000);
    in[net3].set_val(i&0b001000);
    in[net4].set_val(i&0b100100);
    in[net5].set_val(i&0b100010);
    in[net6].set_val(i&0b100001);
    out[net10].set_val(duv_1.calcul_output(in));
    cout<<" "<< in[net1].get_val()<<" ";
    cout<<" "<< in[net2].get_val()<<" ";
    cout<<" "<< in[net3].get_val()<<" ";
    cout<<" "<< in[net4].get_val()<<" ";
    cout<<" "<< in[net5].get_val()<<" ";
    cout<<" "<< in[net6].get_val()<<" ";
    cout << "  =  "<< out[net10].get_val() <<endl;
  }

  return 0;
}

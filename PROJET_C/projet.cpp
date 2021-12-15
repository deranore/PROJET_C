#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <map>
#include "DECOUPAGE.h"
#include "SIMULATEUR.h"
#include "AND1.h"
#include "OR1.h"

#define ERROR_SIM_URL 20
#define ERROR_SIM_CREATE_FILE 30

using namespace std;
int main (void)
{
  Simulateur simulateur_1;

  simulateur_1.obtain_url();
  if(simulateur_1.url_valid()==1){
    cout << "-Erreur url ou fichier invalide " << endl;
    exit(ERROR_SIM_URL);
  }
  else{
    cout << "-URL et Fichier valide "<<endl;
    cout <<"-JSON : "<<simulateur_1.get_url_json()<<endl;
    cout <<"-DOT : "<<simulateur_1.get_url_dot()<<endl;
    cout <<"-OUT : "<<simulateur_1.get_url_out()<<endl;
  }
  simulateur_1.print();
  simulateur_1.parsseur_dot(simulateur_1.lexeur_dot());
  cout <<"-Traitement du .dot terminé"<<endl<<endl;
  simulateur_1.print();
  simulateur_1.parsseur_json(simulateur_1.lexeur_json());
  cout <<"-Traitement du .json terminé"<<endl<<endl;
  simulateur_1.print();
  simulateur_1.err_simulation(simulateur_1.Kernel());
  cout <<"-Simulation terminé"<<endl<<endl;
  simulateur_1.print();

  if(simulateur_1.create_output_file()){
    cout << "-Erreur lors de la création du fichier de sortie "<<endl;
    exit(ERROR_SIM_CREATE_FILE);
  }
  else{
    cout<< "-Création de fichier terminé"<<endl;
  }

  return 0;
}

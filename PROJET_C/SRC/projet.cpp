#include <SIMULATEUR.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "DECOUPAGE.h"

using namespace std;
#define ERROR_SIM_URL 20;
#define ERROR_SIM_CREATE_FILE 30;


int main (void){
  simulateur simulateur ();

  simulateur.obtain_url();
  if(!simulateur.url_valid()){
    cout << "-Erreur url ou fichier invalide " << endl;
    exit(ERROR_SIM_URL);
  }
  else{
    cout << "-URL et Fichier valide "<<endl;
    cout <<"-JSON : "<<simulateur.get_url_json()<<endl;
    cout <<"-DOT : "<<simulateur.get_url_dot()<<endl;
    cout <<"-OUT : "<<simulateur.get_url_out()<<endl;
  }
  simulateur.print();
  parrseur_dot(lexeur_dot());
  cout <<"-Traitement du .dot terminé"<<endl<<endl;
  simulateur.print();
  parsseur_json(lexeur_json());
  cout <<"-Traitement du .json terminé"<<endl<<endl;
  simulateur.print();
  err_simulation(Kernel());
  cout <<"-Simulation terminé"<<endl<<endl;
  simulateur.print();

  if(create_output_file()){
    cout << "-Erreur lors de la création du fichier de sortie "<<endl;
    exit(ERROR_SIM_CREATE_FILE);
  }
  else{
    cout<< "-Création de fichier terminé"<<endl;
  }

  return 0;
}

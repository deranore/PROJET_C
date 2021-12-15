#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include "NET.h"
#include "SIMULATEUR.h"
#include "DECOUPAGE.h"
#include "AND1.h"
#include "NAND1.h"
#include "OR1.h"
#include "NOR1.h"
#include "XOR1.h"
#include "XNOR1.h"
#include "BUFFER1.h"
#include "MUX1.h"
#include "NOT1.h"

#define  accolade_open_is_missing   1
#define  keyword_signal_is_missing   2
#define  pointpoint_is_missing   3
#define  crochet_open_is_missing   4
#define  return_line_is_missing   5
#define  keyword_name_is_missing   6
#define  accolade_close_or_keyword_name_is_missing   7
#define  variable_deja_defini 8
#define  var_name_is_missing 9
#define  virgule_is_missing 10
#define  wave_is_missing 11
#define  wrong_size_of_value 12
#define  nombre_is_missing 13
#define  accolade_close_is_missing 14
#define  virgule_or_return_line_is_missing 15
#define  crochet_close_is_missing 16
#define  keyword_digraph_or_graph_is_missing   45

#define  name_of_file_is_missing_or_not_correct   2
#define  accolade_open_is_missing_2 42
#define  var_name_is_missing_2     52
#define  vnet_in_is_missing_or_not_define 5
#define  crochet_open_or_fleche_is_missing   6
#define  keyword_label_is_uncorrect 7
#define  keyword_label_is_missing 8
#define  equal_is_missing 58
#define  var_input_already_defined 10
#define  var_output_already_defined 11
#define  var_gate_or2_already_defined 12
#define  var_gate_nand2_already_defined 13
#define  var_gate_xnor2_already_defined 14
#define  var_gate_not1_already_defined 15
#define  var_gate_nor1_already_defined 16
#define  var_gate_and2_already_defined 17
#define  var_gate_xor2_already_defined 18
#define  keyword_typeofgate_input_or_output_is_uncorrect 19
#define  keyword_typeofgate_input_or_output_is_missing 20
#define  crochet_close_is_missing 21
#define  pointv_is_missing 22
#define  waiting_for_a_gate_not_a_input_net 23
#define  waiting_for_a_gate_not_a_output_net 24
#define  gate_to_assign_is_missing 25
#define  pointv_or_fleche_is_missing 26
#define  missing_entries 27
#define  to_much_entries 28

#define LIM_SIMULATION 200
#define SIMU_OK 0
#define ERR_LIMITE_ITERATION 1

using namespace std;
std::stringstream sstream;

Simulateur::Simulateur(){
  cout << " Constructeur de simulateur ";
  url_dot=" ";
  url_out=" ";
  url_json=" ";
}

Simulateur::~Simulateur(){
  for(map<string,Gate*>::iterator it=gate.begin(); it!=gate.end(); ++it){
    delete it->second;
  }
}

void Simulateur::obtain_url(){
  cout << endl << "-  url du fichier dot :  ";
  cin >> url_dot;
  cout << endl << endl << "-  url du fichier json :  ";
  cin >> url_json;
  cout << endl << "- url du fichier de sortie :";
  cin >> url_out;
  cout << endl;
}

bool Simulateur::url_valid(){
  bool valid = 0;
  if(get_url_dot().empty() || get_url_json().empty() || get_url_out().empty()) {
    return 1;
  }
  return valid;
}

string Simulateur::get_url_json(){
  return url_json;
}
string Simulateur::get_url_dot(){
  return url_dot;
}

string Simulateur::get_url_out(){
  return url_out;
}

Net Simulateur::get_input(string nom){
  if(input.find(nom)==(input.end())){
    cout << " Élement inconnu ";
    exit(99);
  }
  else{
    return input[nom];
  }
}

Net Simulateur::get_output(string nom){
  if(output.find(nom)==(output.end())){
    cout << " Élement inconnu ";
    exit(99);
  }
  else{
    return output[nom];
  }
}

Gate* Simulateur::get_gate(string nom){
  if(gate.find(nom)==(gate.end())){
    cout << " Élement inconnu ";
    exit(99);
  }
  else{
    return gate[nom];
  }
}

bool Simulateur::add_input(Net i){
  if(input.find(i.get_name())!=(input.end())){
    cout << " Élement déja présent ";
    return 0;
  }
  else{
    cout<<i.get_name();
    input[i.get_name()]=i;
  }
  return 1;
}

bool Simulateur::add_output(Net o){
  if(output.find(o.get_name())!=(output.end())){
    cout << " Élement déja présent ";
    return 0;
  }
  else{
    output[o.get_name()]=o;
  }
  return 1;
}

bool Simulateur::add_gate(Gate* g){
  if(gate.find(g->get_name())!=(gate.end())){
    cout << " Élement déja présent ";
    return 0;
  }
  else{
    gate[g->get_name()]=g;
  }
  return 1;
}

void Simulateur::set_input(unsigned int index){
  for(map<string,Net>::iterator it = input.begin(); it != input.end(); ++it){
    if((it->first).find("-") == string::npos){
      (it->second).set_val(index);
    }
  }
}

bool Simulateur::set_output(string nom,bool val){
  if(output.find(nom)==(input.end())){
    cout << " Élement inconnu ";
    return 0;
  }
  output[nom].add_val(val);

  return 1;
}

vector<Decoupage> Simulateur::lexeur_dot (){
  ifstream monFlux("and_xor.dot");
  stringstream key;
  int l=0;
  monFlux.seekg(0, ios::end);
  int taille = monFlux.tellg();
  cout << taille <<endl;
  monFlux.seekg(0, ios::beg);
  vector<string> v(2); // def du vecteur de sortie pour le .dot
  vector<Decoupage> v1;
  vector<string> vgate;// vecteur qui stocke les portes définis
  vector<string> vnetin;// vecteur qui stocke les net in définis
  vector<string> vnetout;// vecteur qui stocke les net out définis
  vector<string> vvar(1);// doit commencer a 1 pour la comparaison des namevar
  char buffer1[1000]; // tableau qui recoit les caractères du fichier (sert de buffer)
  int b=0;
  Type mot;
  int i=0;
  int ligne = 1;
  int erreurlexeur=0;
  bool end=0;
  monFlux.get(buffer1[i]);

  do {
    if (isalpha(buffer1[i]) || buffer1[i]== '"')// si c'esrt un alpha num
    {
      key<<buffer1[i];
      //v.push_back(key.str());
      i++;
      monFlux.get(buffer1[i]);
      while(isalpha(buffer1[i])|| buffer1[i]== '"'|| buffer1[i]== '_')
      {
        key<<buffer1[i];
        i++;
        monFlux.get(buffer1[i]);
      }
      while(buffer1[i]=='"')
      {
        key<<buffer1[i];
        i++;
        monFlux.get(buffer1[i]);
      }
      while(isdigit(buffer1[i])|| buffer1[i]== '"')
      {
        key<<buffer1[i];
        i++;
        monFlux.get(buffer1[i]);
      }
      mot = CHAINE;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();
    }
    if (buffer1[i]== ' ')
    {
      //cout << "jai vu un espace" <<endl;
      i++;
      monFlux.get(buffer1[i]);/////
      //mot = ESPACE;
      //Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      //v1.push_back(first);
      //v.push_back(key.str());
      //key.str("");//reinit
      //key.clear();
    }
    if (buffer1[i]== '{')
    {
      key<<buffer1[i];
      i++;
      //ligne++;
      monFlux.get(buffer1[i]);////
      mot = ACCOLADEO;
      //v.push_back(key.str());
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      key.str("");//reinit
      key.clear();
    }
    if (buffer1[i]== '-')
    {
      key<<buffer1[i];
      i++;
      monFlux.get(buffer1[i]);
      if (buffer1[i]== '>')
      {
        key<<buffer1[i];
        i++;
        monFlux.get(buffer1[i]);////////
        //v.push_back(key.str());
        mot = FLECHE;
        Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
        v1.push_back(first);
        key.str("");//reinit
        key.clear();
      }
      else
      {
        cout << "erreur: caractère - non valide sans l'ajout > ligne" <<ligne <<endl;
        i++;
        monFlux.get(buffer1[i]);/////
        //v.push_back(key.str());
        mot = DUMP;
        Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
        v1.push_back(first);
        key.str("");//reinit
        key.clear();
      }
    }
    if (buffer1[i]== ';')
    {
      //ligne++;
      key<<buffer1[i];
      i++;
      monFlux.get(buffer1[i]);////////
      mot = POINTV;
      //v.push_back(key.str());
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      key.str("");//reinit
      key.clear();
    }
    if (buffer1[i]== '[')
    {
      key<<buffer1[i];
      i++;
      monFlux.get(buffer1[i]);//////
      mot = CROCHET0;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();
    }
    if (buffer1[i]== ']')
    {
      key<<buffer1[i];
      i++;
      monFlux.get(buffer1[i]);///////
      mot = CROCHETC;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();
    }
    if (buffer1[i]== '=')
    {
      key<<buffer1[i];
      i++;
      monFlux.get(buffer1[i]);//////
      mot = EQUAL;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();
    }
    if (buffer1[i]== '$')
    {
      cout << "erreur: caratctère $ non valide ligne "<< ligne<<endl;
      i++;
      monFlux.get(buffer1[i]);////////
      mot = DUMP;
      erreurlexeur=2;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();

    }
    if (buffer1[i]== '\n')
    {
      ligne++;
      i++;
      monFlux.get(buffer1[i]);////////
    }
    if (buffer1[i]== '}')
    {
      key<<buffer1[i];
      i++;
      //ligne++;
      monFlux.get(buffer1[i]);//////
      mot = ACCOLADEC;
      Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      v1.push_back(first);
      //v.push_back(key.str());
      key.str("");//reinit
      key.clear();
      end=1;
    }
    if (buffer1[i]== '\t')
    {
      //key<<buffer1[i];
      i++;
      monFlux.get(buffer1[i]);//////
      //mot = TAB;
      //Decoupage first(key.str(),mot,ligne);// on appelle le constructeur pour créer les diff verres
      //v1.push_back(first);
      //v.push_back(key.str());
      //key.str("");//reinit
      //key.clear();
      //end=1;
    }
  } while(i<taille);
  return v1;
}
void Simulateur::parsseur_dot (vector<Decoupage> dot){
  vector<string>::iterator itr2 ;
      unsigned int dark_net = 0;
      vector<string> vgate;// vecteur qui stocke les portes définis
      vector<string> vnetin;// vecteur qui stocke les net in définis
      vector<string> vnetout;// vecteur qui stocke les net out définis
      vector<string> vvar(1);// doit commencer a 1 pour la comparaison des namevar
      map<string,vector<string> > input;
      map<string,string> output;
      map<string,string> type;
      bool end_prog =0;
      int enregistremment=0;
      map<string,string> verif_entre;
      string gate = " ";
      int erreur=0;// entier qui gère les differentes erreurs
      int t=0;// t et u servent dans le système de boucle pour vérifier qu'une déclaration est valable qu'une fois (STATE8)
      int u=0;//
      bool readytosave=1; // variable qui permet d'enregistrer ou non un porte, une entrée ou une sortie   (STATE8)
      enum etat {STATE1, STATE2, STATE3, STATE4, STATE5, STATE6, STATE7, STATE8, STATE9, STATE10, STATE12, STATE13, END, ERREUR};
      etat etat_courant = STATE1;// on début pour le STATE1
      vector <Decoupage>::iterator itr = dot.begin();// on remet l'itarateur au debut du vecteur

      do
      {Decoupage c = *itr;
      while (!end_prog)
      {
        cout << "AHHH"<<endl;
        switch (etat_courant)
           {
            cout<<etat_courant<<endl;
           case STATE1: // on doit detecter le mot digraph
              switch (c.gettype())
              {
                case CHAINE:
                            if (c.getname()=="digraph"||c.getname()=="graph")
                            {
                              cout<<"digraph vu"<<endl;
                              etat_courant = STATE2;
                            }
                            else
                            {
                              erreur=7;
                              etat_courant= ERREUR;
                            }
                            break;
                case ESPACE:etat_courant = STATE1;
                            break;
                case TAB:etat_courant= STATE1;
                         break;
                default:erreur=keyword_digraph_or_graph_is_missing;
                        etat_courant= ERREUR;
              }
              itr++; // on incremnte
              c = *itr; // on regarde le mot suivant stocké dans le vecteur v1 ( C est ici un objet qui contient la ligne, le nom et l'étiquette)
              break;
            case STATE2: // on cherche le nom du fichier
               switch (c.gettype())
               {
                 case CHAINE:
                             cout <<"etape 2 reussi passage a 3 "<<endl;
                             etat_courant=STATE3;
                             break;
                 case ESPACE:cout << "je suis bien un espace" <<endl;
                             etat_courant = STATE2;
                             break;
                 case TAB:etat_courant= STATE2;
                          break;
                 default:erreur=name_of_file_is_missing_or_not_correct;
                         etat_courant= ERREUR;
                }
                itr++;
                c = *itr;
                break;
              case STATE3:// on cherche l'acolade ouverte
                 switch (c.gettype())
                 {
                  case ACCOLADEO:cout<<"acco o vu"<<endl;
                                 etat_courant=STATE4;
                                 break;
                  case ESPACE:etat_courant = STATE3;
                              break;
                  case TAB:erreur= 10;
                            etat_courant= STATE3;
                            break;
                  default:erreur=accolade_open_is_missing;
                          etat_courant= ERREUR;
                  }
                  itr++;
                  c = *itr;
                  break;
              case STATE4: // on cherche un nom de variable comme I1 par exemple
                 switch (c.gettype())
                 {
                   case CHAINE:etat_courant=STATE5;
                               vvar.push_back(c.getname()); // on stocke momentanement le nom de la var
                               u=u+1;// t et u servent dans le système de boucle pour vérifier qu'une déclaration est valable qu'une fois (STATE8)
                               t=u-1;
                               itr++;
                               c = *itr;
                               break;
                   case ESPACE:
                               etat_courant = STATE4;
                               itr++;
                               c = *itr;
                               break;
                   case TAB:
                            etat_courant= STATE4;
                            itr++;
                            c = *itr;
                            break;
                   case ACCOLADEC:
                            cout << " FIIIIIIIIIIIN "<<endl;
                            etat_courant= END; // si on trouve une accolade fermé --> fin du fichier
                            break;
                   default:
                           erreur=var_name_is_missing;
                           etat_courant= ERREUR;
                  }
                break;
                case STATE5: // on doit ici detecter soit [  soit -->
                    switch (c.gettype())
                    {
                      case CROCHET0:
                                   etat_courant=STATE6;
                                   break;
                      case FLECHE:
                                  cout << " FLECHE " <<endl;
                                  itr=itr-1; // on observe le mot juste avant la fleche pour s'assurer que c'est bien un net d'entrée
                                  c = *itr;
                                  cout << c.getname()<<endl;


                                  for(itr2 = vnetin.begin() ; itr2 != vnetin.end() ; ++itr2) // on balait le vecteur qui contient les déclaration de net d'entrée
                                  {
                                    if (c.getname()==*itr2)  // si le net qu'on veut assigner est bien un net d'entré et bien déjà déclaré
                                    {
                                      cout << *itr2 <<endl;
                                      etat_courant= STATE12;
                                    }
                                  }
                                  if(etat_courant!=STATE12) {// si ce n'est pas le cas on a une erreur
                                    etat_courant=ERREUR; // si on ne rempli pas la condition suivante c'est une erreur
                                    erreur=vnet_in_is_missing_or_not_define;
                                  }
                                  itr=itr+1; // on observe de nouveau le mot actuel
                                  c = *itr;
                                  break;
                      case ESPACE:
                                  etat_courant = STATE5;
                                  break;
                      case TAB:
                               etat_courant= STATE5;
                               break;
                      default:
                              erreur=crochet_open_or_fleche_is_missing;
                              etat_courant= ERREUR;
                     }
                  itr++;
                  c = *itr;
                  break;
                case STATE6: // have to detect label
                   switch (c.gettype())
                   {
                       case CHAINE:
                                   if (c.getname()=="label")
                                   {
                                     cout<<"label vu"<<endl;
                                     etat_courant = STATE7;
                                   }
                                   else
                                   {
                                     erreur=keyword_label_is_uncorrect;
                                     etat_courant= ERREUR;
                                   }
                                   break;
                       case ESPACE:
                                   etat_courant = STATE6;
                                   break;
                       case TAB:
                                etat_courant= STATE6;
                                break;
                       default:
                               erreur=keyword_label_is_missing;
                               etat_courant= ERREUR;
                    }
                  itr++;
                  c = *itr;
                  break;
                 case STATE7: // have to detect equal
                    switch (c.gettype())
                    {
                        case EQUAL:
                                    if (c.getname()=="=")
                                    {
                                      cout <<"egal vu"<<endl;
                                      etat_courant = STATE8;
                                    }
                                    break;
                        case ESPACE:
                                    etat_courant = STATE7;
                                    break;
                        case TAB:
                                 etat_courant= STATE7;
                                 break;
                        default:
                                erreur=equal_is_missing;
                                etat_courant= ERREUR;
                    }
                    itr++;
                    c = *itr;
                    break;
                 case STATE8: // have to detect type: "output" / "input" / "gate"
                    switch (c.gettype())
                    {
                        case CHAINE:  if (c.getname()=="\"INPUT\"")
                                      {
                                        // on verifie que le nom n'ai pas déjà été déclaré
                                        for(t; t!=0 ; t=t-1)
                                        {
                                          if (vvar[u] != vvar[t])
                                          {
                                            cout<<"le nom est valide pour un input"<<endl;

                                            // while name var isn't used --> possible to save net
                                          }
                                          else
                                          {
                                            cout<<"la variable " << vvar[t] << " est déja définie"<<endl;
                                            readytosave=0; // if bool =0 , var already define, impossible to save
                                            erreur=var_input_already_defined;
                                            etat_courant=ERREUR;
                                          }
                                        }
                                        if (readytosave==1)
                                        {
                                          //var does not exist --> possible to assign
                                          // have to create the net here
                                          vnetin.push_back(vvar[u]); // save the gate in a vector
                                          cout << " on enregistre la valeur ici" << endl;
                                          cout << c.getname() <<endl;
                                          etat_courant=STATE9;
                                        }

                                      }

                                      else if (c.getname()=="\"OUTPUT\"")
                                      {
                                        // check if var is not alreay assigned
                                        for(t; t!=0 ; t=t-1)
                                        {
                                          if (vvar[u] != vvar[t])
                                          {
                                            cout<<"le nom est valide pour un OUTPUT"<<endl;
                                            // while name var isn't used --> possible to save net
                                          }
                                          else
                                          {
                                            cout<<"la variable " << vvar[t] << " est déja définie"<<endl;
                                            readytosave=0; // if bool ==0 , var already define, impossible to save
                                            erreur=var_output_already_defined;
                                            etat_courant=ERREUR;
                                          }
                                        }
                                        if (readytosave==1)
                                        {
                                          //var does not exist --> possible to assign
                                          // have to create the net here
                                          vnetout.push_back(vvar[u]); // save the gate in a vector
                                          cout << " on enregistre la valeur du OUTPUT ici" << endl;
                                          etat_courant=STATE9;
                                        }

                                      }

                                      else if (c.getname()=="\"AND2\"")
                                      {
                                        // check if var is not alreay assigned
                                        for(t; t!=0 ; t=t-1)
                                        {
                                          if (vvar[u] != vvar[t])
                                          {
                                            cout<<"le nom est valide pour un AND2"<<endl;
                                            // while name var isn't used --> possible to save net
                                            verif_entre[vvar[u]]="2";// on stocke MYAND et 2 pour comparer avec la map en sortie
                                          }
                                          else
                                          {
                                            cout<<"la variable " << vvar[t] << " est déja définie"<<endl;
                                            readytosave=0; // if bool ==0 , var already define, impossible to save
                                            erreur=var_gate_and2_already_defined;
                                            etat_courant=ERREUR;
                                          }
                                        }
                                        if (readytosave==1)
                                        {
                                          //var does not exist --> possible to assign
                                          // have to create the net here
                                          vgate.push_back(vvar[u]); // save the gate in a vector
                                          type[vvar[u]]="AND";
                                          cout << " on enregistre la valeur du AND2 ici" << endl;
                                          etat_courant=STATE9;
                                        }
                                      }

                                      else if (c.getname()=="\"OR2\"")
                                      {
                                        // check if var is not alreay assigned
                                        for(t; t!=0 ; t=t-1)
                                        {
                                          if (vvar[u] != vvar[t])
                                          {
                                            cout<<"le nom est valide pour un OR2"<<endl;
                                            verif_entre[vvar[u]]="2";// on stocke MYAND et 2 pour comparer avec la map en sortie
                                            // while name var isn't used --> possible to save net
                                          }
                                          else
                                          {
                                            cout<<"la variable " << vvar[t] << " est déja définie"<<endl;
                                            readytosave=0; // if bool ==0 , var already define, impossible to save
                                            erreur=var_gate_or2_already_defined;
                                            etat_courant=ERREUR;
                                          }
                                        }
                                        if (readytosave==1)
                                        {
                                          //var does not exist --> possible to assign
                                          // have to create the net here
                                          vgate.push_back(vvar[u]); // save the gate in a vector
                                          type[vvar[u]]="OR";
                                          cout << " on enregistre la valeur du OR2 ici" << endl;
                                          etat_courant=STATE9;
                                        }
                                      }
                                      else if (c.getname()=="\"NAND2\"")
                                      {
                                        // check if var is not alreay assigned
                                        for(t; t!=0 ; t=t-1)
                                        {
                                          if (vvar[u] != vvar[t])
                                          {
                                            cout<<"le nom est valide pour une NAND2"<<endl;
                                            verif_entre[vvar[u]]="2";// on stocke MYAND et 2 pour comparer avec la map en sortie
                                            // while name var isn't used --> possible to save net
                                          }
                                          else
                                          {
                                            cout<<"la variable " << vvar[t] << " est déja définie"<<endl;
                                            readytosave=0; // if bool ==0 , var already define, impossible to save
                                            erreur=var_gate_nand2_already_defined;
                                            etat_courant=ERREUR;
                                          }
                                        }
                                        if (readytosave==1)
                                        {
                                          //var does not exist --> possible to assign
                                          // have to create the net here
                                          vgate.push_back(vvar[u]); // save the gate in a vector
                                          type[vvar[u]]="NAND";
                                          cout << " on enregistre la valeur du NAND2 ici" << endl;
                                          etat_courant=STATE9;
                                        }

                                      }

                                      else if (c.getname()=="\"NOT1\"")
                                      {
                                        // check if var is not alreay assigned
                                        for(t; t!=0 ; t=t-1)
                                        {
                                          if (vvar[u] != vvar[t])
                                          {
                                            cout<<"le nom est valide pour une NOT1"<<endl;
                                            verif_entre[vvar[u]]="1";// on stocke MYNOT1 et 1 pour comparer avec la map en sortie
                                            // while name var isn't used --> possible to save net
                                          }
                                          else
                                          {
                                            cout<<"la variable " << vvar[t] << " est déja définie"<<endl;
                                            readytosave=0; // if bool ==0 , var already define, impossible to save
                                            erreur=var_gate_not1_already_defined;
                                            etat_courant=ERREUR;
                                          }
                                        }
                                        if (readytosave==1)
                                        {
                                          //var does not exist --> possible to assign
                                          // have to create the net here
                                          vgate.push_back(vvar[u]); // save the gate in a vector
                                          type[vvar[u]]="NOT1";
                                          cout << " on enregistre la valeur du NOT1 ici" << endl;
                                          etat_courant=STATE9;
                                        }

                                      }

                                      else if (c.getname()=="\"NOR1\"")
                                      {
                                        // check if var is not alreay assigned
                                        for(t; t!=0 ; t=t-1)
                                        {
                                          if (vvar[u] != vvar[t])
                                          {
                                            cout<<"le nom est valide pour une NOR1"<<endl;
                                            verif_entre[vvar[u]]="1";// on stocke MYNOR1 et 1 pour comparer avec la map en sortie
                                            // while name var isn't used --> possible to save net
                                          }
                                          else
                                          {
                                            cout<<"la variable " << vvar[t] << " est déja définie"<<endl;
                                            readytosave=0; // if bool ==0 , var already define, impossible to save
                                            erreur=var_gate_nor1_already_defined;
                                            etat_courant=ERREUR;
                                          }
                                        }
                                        if (readytosave==1)
                                        {
                                          //var does not exist --> possible to assign
                                          // have to create the net here
                                          vgate.push_back(vvar[u]); // save the gate in a vector
                                          type[vvar[u]]="NOR1";
                                          cout << " on enregistre la valeur du NOR1 ici" << endl;
                                          etat_courant=STATE9;
                                        }

                                      }
                                      else if (c.getname()=="\"XNOR2\"")
                                      {
                                        // check if var is not alreay assigned
                                        for(t; t!=0 ; t=t-1)
                                        {
                                          if (vvar[u] != vvar[t])
                                          {
                                            cout<<"le nom est valide pour une XNOR2"<<endl;
                                            verif_entre[vvar[u]]="2";// on stocke MYAND et 2 pour comparer avec la map en sortie
                                            // while name var isn't used --> possible to save net
                                          }
                                          else
                                          {
                                            cout<<"la variable " << vvar[t] << " est déja définie"<<endl;
                                            readytosave=0; // if bool ==0 , var already define, impossible to save
                                            erreur=var_gate_xnor2_already_defined;
                                            etat_courant=ERREUR;
                                          }
                                        }
                                        if (readytosave==1)
                                        {
                                          //var does not exist --> possible to assign
                                          // have to create the net here
                                          vgate.push_back(vvar[u]); // save the gate in a vector
                                          type[vvar[u]]="XNOR2";
                                          cout << " on enregistre la valeur du XNOR2 ici" << endl;
                                          etat_courant=STATE9;
                                        }

                                      }
                                      else if (c.getname()=="\"XOR2\"")
                                      {
                                        // check if var is not alreay assigned
                                        for(t; t!=0 ; t=t-1)
                                        {
                                          if (vvar[u] != vvar[t])
                                          {
                                            cout<<"le nom est valide pour un XOR2"<<endl;
                                            verif_entre[vvar[u]]="2";// on stocke MYAND et 2 pour comparer avec la map en sortie
                                            // while name var isn't used --> possible to save net
                                          }
                                          else
                                          {
                                            cout<<"la variable " << vvar[t] << " est déja définie"<<endl;
                                            readytosave=0; // if bool ==0 , var already define, impossible to save
                                            erreur=var_gate_xor2_already_defined;
                                            etat_courant=ERREUR;
                                          }
                                        }
                                        if (readytosave==1)
                                        {
                                          //var does not exist --> possible to assign
                                          // have to create the net here
                                          vgate.push_back(vvar[u]); // save the gate in a vector
                                          type[vvar[u]]="XOR";
                                          cout << " on enregistre la valeur du XOR2 ici" <<endl;
                                          etat_courant=STATE9;
                                        }

                                      }
                                      else
                                      {
                                        erreur=keyword_typeofgate_input_or_output_is_uncorrect;
                                        etat_courant=ERREUR;
                                        erreur= 10;
                                      }
                                      break;
                        case ESPACE:
                                    etat_courant = STATE8;
                                    break;
                        case TAB:
                                 etat_courant= STATE8;
                                 break;
                         default:
                                 erreur=keyword_typeofgate_input_or_output_is_missing;
                                 etat_courant= ERREUR;
                         }
                      itr++;
                      c = *itr;
                      break;
                case STATE9: // have to detect ]
                  switch (c.gettype())
                  {
                      case CROCHETC:
                                    etat_courant=STATE10;
                                    cout<< "crochet vu "<<endl;
                                    break;
                      case ESPACE:
                                  etat_courant = STATE9;
                                  break;
                      case TAB:
                               etat_courant= STATE9;
                               break;
                      default:
                              erreur=crochet_close_is_missing;
                              etat_courant= ERREUR;
                  }
                  itr++;
                  c = *itr;
                  break;
                case STATE10: // have to detect ;
                  switch (c.gettype())
                  {
                      case POINTV:
                                    etat_courant=STATE4;// au point virgule on revient dans l'etape 4 pour traiter une nouvelle ligne
                                    cout<< "point v "<<endl;
                                    break;
                      case ACCOLADEC:
                                    etat_courant=ERREUR; // pas supposé avoir d'acolade de fin juste après les déclarations
                                    break;
                      case ESPACE:
                                  etat_courant = STATE9;
                                  break;
                      case TAB:
                               etat_courant= STATE9;
                               break;
                      default:
                              erreur=pointv_is_missing;
                              etat_courant= ERREUR;
                   }
                   itr++;
                   c = *itr;
                   break;


               case STATE12: // on doit vérifier qu'on a une porte
                  switch (c.gettype())
                  {
                        case CHAINE:
                                    for(itr2 = vgate.begin() ; itr2 != vgate.end() ; ++itr2) // on balait le vecteur de porte pour voir si le mot qu'on observe fait partie des portes déjà déclaré
                                    {
                                      if (c.getname()==*itr2)// si le mot actuel est une porte déjà déclaré --> parfait
                                      {
                                        gate=c.getname();
                                        cout << c.getname();
                                        itr-=2;
                                        c = *itr;
                                        cout << c.getname();
                                        input[gate].push_back(c.getname());
                                        itr+=2;
                                        c = *itr;
                                        etat_courant=STATE13;
                                      }
                                    }

                                    for(itr2 = vnetin.begin() ; itr2 != vnetin.end() ; ++itr2)// on vérifie qu'on ait pas une net d'entrée à la place d'une porte
                                    {
                                      if (c.getname()==*itr2)
                                      {
                                        etat_courant= ERREUR;  // on attend une porte et on a une net d'entrée
                                        erreur=waiting_for_a_gate_not_a_input_net;
                                      }
                                    }

                                    for(itr2 = vnetout.begin() ; itr2 != vnetout.end() ; ++itr2)// on vérifie qu'on ait pas une net de sortie à la place d'une porte
                                    {
                                      if (c.getname()==*itr2)
                                      {
                                        //on place un buffer entre la net et la sortie
                                        dark_net+=1;
                                        sstream << dark_net;
                                        gate=c.getname();
                                        itr-=2;
                                        c = *itr;
                                        type["WIRE"+sstream.str()]="WIRE";
                                        input["WIRE"+sstream.str()].push_back(c.getname());
                                        output["WIRE"+sstream.str()])=gate;
                                        itr+=2;
                                        c = *itr;
                                        etat_courant=STATE13;
                                      }
                                    }
                                    break;
                        case ESPACE:
                                    etat_courant = STATE9;
                                    break;
                           case TAB:
                                    etat_courant= STATE9;
                                    break;
                           default:
                                   erreur=gate_to_assign_is_missing;
                                   etat_courant= ERREUR;
                  }
                  itr++;
                  c = *itr;
                  break;

                case STATE13: // on doit trouver un ; ou une -->
                  switch (c.gettype())
                  {
                      case POINTV:etat_courant=STATE4;// au point virgule on revient dans l'etape 4 pour traiter une nouvelle ligne
                                  //stockage dans le sous vecteur correspondent
                                  cout << " POINT VIRGULE APRES DES DOUBLE FLECHE "<<endl;
                                  break;
                      case FLECHE:etat_courant=STATE12; // si on a une fleche  après une porte, on peut soit avoir de nouveau une porte soit une sortie
                                  cout << " VRAI FLECHE "<<endl;
                                  itr=itr+1; // on observe le mot juste après la fleche pour savoir si il s'agit d'une porte ou d'une sortie
                                  c = *itr;
                                  for(itr2 = vgate.begin() ; itr2 != vgate.end() ; ++itr2) // on balait le vecteur qui contient les gates
                                  {
                                    if (c.getname()==*itr2)  // si il s'agit bien d'une gate on créer une net intermediaire pour la porte précedente et cette porte
                                    {
                                      dark_net+=1;
                                      sstream << dark_net;
                                      vnetin.push_back("net-"+sstream.str());
                                      input[c.getname()].push_back("net-"+sstream.str());
                                      itr-=2;
                                      c = *itr;
                                      output[c.getname()]=("net-"+sstream.str());
                                      itr+=2;
                                      c = *itr;
                                      etat_courant= STATE13; //  on peut avoir après la porte ou autre porte ou une sortie donc on reste en STATE 13
                                    }
                                  }
                                  for(itr2 = vnetout.begin() ; itr2 != vnetout.end() ; ++itr2) // on balait le vecteur qui contient les net de sortie
                                  {
                                      if (c.getname()==*itr2){// si il s'agit bien d'une net de sortie
                                        itr-=2;
                                        c = *itr;
                                        gate=c.getname();
                                        itr+=2;
                                        c = *itr;
                                        output[gate]=c.getname();
                                      }
                                      etat_courant = STATE13; //  après la net de sortie on peut avoir qu'un point virgule donc on reste en state 13 pour le detecter
                                    }
                                  }
                                  itr=itr+1; // on observe de nouveau le mot actuel
                                  c = *itr;
                                  cout << c.getname() << endl;
                                  cout << etat_courant << " | " <<STATE4 << endl;
                                  break;
                      case END:
                          cout << " JE SUIS A LA FIN !!!! "<<endl;
                          cout << *itr2 << endl;
                          cout << dot.size()<<endl;

                     /*for(map< string,string>::iterator it = verif_entre.begin() ; it!= verif_entre.end(); ++it)// on balait la map input
                        {
                          if (input[it->first].size()==stoi(it->second))
                          {
                            enregistremment=1;
                            cout << "on peut enregristrer "<< endl;
                          }

                          if (input[it->first].size()<stoi(it->second))
                          {
                            cout << "il manque des entrées pour "<< it->first << endl;
                            erreur=missing_entries;
                          }

                          if (input[it->first].size()>stoi(it->second))
                          {
                            cout << "trop d'entrée ont ete assigné pour "<< it->first << endl;
                            erreur=to_much_entries;
                          }
                        }*/
                              enregistremment=1;
                              if(enregistremment == 1)
                               {
                                for(map< string,vector<string> >::iterator it = input.begin() ;it!= input.end(); ++it){//Pourte toutes les portes
                                  for(vector<string>::iterator it_in=it->second.begin() ;it_in!=it->second.end(); ++it_in){//Pour toutes les entrée de chaque porte
                                    add_input(Net(*it_in));
                                  }
                                }
                                for(map<string,string>::iterator it = output.begin() ;it!= output.end(); ++it){//Sortie
                                  if(it->second.find("-") == string::npos){//Si ce n'est pas une net non impicite
                                    add_output(it->second);
                                  }
                                }
                                for(map<string,string>::iterator it = type.begin() ;it!= type.end(); ++it){
                                  cout << it->first<<endl;
                                  cout << it->second<<endl;

                                  if(it->second=="AND"){
                                    add_gate(new AND1(it->first,input[it->first],output[it->first]));
                                  }
                                  if(it->second=="OR"){
                                    add_gate(new OR1(it->first,input[it->first],output[it->first]));
                                  }
                                  if(it->second=="XOR"){
                                    add_gate(new XOR1(it->first,input[it->first],output[it->first]));
                                  }
                                  if(it->second=="NAND"){
                                    add_gate(new NAND1(it->first,input[it->first],output[it->first]));
                                  }
                                  if(it->second=="NOR"){
                                    add_gate(new NOR1(it->first,input[it->first],output[it->first]));
                                  }
                                  if(it->second=="XNOR"){
                                    add_gate(new XNOR1(it->first,input[it->first],output[it->first]));
                                  }
                                  if(it->second=="NOT"){
                                    add_gate(new NOT1(it->first,input[it->first],output[it->first]));
                                  }
                                  if(it->second=="WIRE"){
                                    add_gate(new BUFFER1(it->first,input[it->first],output[it->first]));
                                  }
                                }
                              }
                              itr++;
                              cout<<"FIN DE FIN"<<endl;
                              end_prog=1;
                              return;
                              break;
                      case ERREUR:cout<< "je suis dans une erreur et je devrais sortir"<<endl;//
                                   itr++;
                                   c = *itr;
                                   break;
                      default:erreur=pointv_or_fleche_is_missing;
                              etat_courant= ERREUR;
                   }
            switch (erreur)
            {
              case keyword_digraph_or_graph_is_missing:cout <<"erreur1: on attend le mot clé digraphe ou graphe et on a recu "<< c.getname()<<" a la ligne "<<c.getline() << endl;
                     break;
              case name_of_file_is_missing_or_not_correct:cout <<"erreur2: on attend le nom du fichier et on a recu "<< c.getname()<<" a la ligne "<<c.getline() << endl;
                     break;
              case accolade_open_is_missing:cout <<"erreur3: on attend le caractère { et on a recu "<< c.getname()<<" a la ligne "<< c.getline() << endl;
                     break;
              case var_name_is_missing_2:cout <<"erreur4: on attend un nom pour une variable et on a recu "<< c.getname()<<" a la ligne "<< endl;
                     break;
              case vnet_in_is_missing_or_not_define:cout <<"erreur5: on attend un net d'entrée et on a recu "<< c.getname()<<" a la ligne "<< endl;
                     break;
              case crochet_open_or_fleche_is_missing:cout <<"erreur6: on attend le caractère [ ou -> et on a recu "<< c.getname()<<" a la ligne "<<c.getline() << endl;
                     break;
              case keyword_label_is_uncorrect:cout <<"erreur7: on attend le mot label et on a recu comme mot: "<< c.getname()<<" a la ligne "<<c.getline() << endl;
                     break;
              case keyword_label_is_missing:cout <<"erreur8: on attend le mot label mais on a recu: "<< c.getname()<<" a la ligne "<< c.getline() << endl;
                     break;
              case equal_is_missing:cout <<"erreur9: on attend le caractère = et on a recu: "<< c.getname() << " a la ligne "<< c.getline()<< endl;
                     break;
              case var_input_already_defined:cout <<"erreur10: la variable d'entrée "<< c.getname()<<" de la ligne"<< c.getline() << " a deja été définie" << endl;
                     break;
              case var_output_already_defined:cout <<"erreur11: la variable de sortie "<< c.getname()<<" de la ligne"<< c.getline() << " a deja été définie" << endl;
                     break;

              case var_gate_or2_already_defined:cout <<"erreur12: la variable "<< c.getname()<<" de la ligne"<< c.getline() << "définissant un or2 a déja été définie" << endl;
                     break;
              case var_gate_nand2_already_defined:cout <<"erreur13: la variable "<< c.getname()<<" de la ligne"<< c.getline() << "définissant un nand2 a déja été définie" << endl;
                     break;

              case var_gate_xnor2_already_defined:cout <<"erreur14: la variable "<< c.getname()<<" de la ligne"<< c.getline() << "définissant un xnor2 a déja été définie" << endl;
                     break;

              case var_gate_not1_already_defined:cout <<"erreur15: la variable "<< c.getname()<<" de la ligne"<< c.getline() << "définissant un not1 a déja été définie" << endl;
                     break;
              case var_gate_nor1_already_defined:cout <<"erreur16: la variable "<< c.getname()<<" de la ligne"<< c.getline() << "définissant un nor1 a déja été définie" << endl;
                     break;

              case var_gate_and2_already_defined:cout <<"erreur17: la variable "<< c.getname()<<" de la ligne"<< c.getline() << "définissant un and2 a déja été définie" << endl;
                     break;
              case var_gate_xor2_already_defined:cout <<"erreur18: la variable "<< c.getname()<<" de la ligne"<< c.getline() << "définissant un xor2 a déja été définie" << endl;
                     break;
              case keyword_typeofgate_input_or_output_is_uncorrect:cout <<"erreur19: on attend le mot clé input, ouput ou un type de gate et on a recu comme mot: "<< c.getname()<<" a la ligne "<<c.getline() << endl;
                     break;
              case keyword_typeofgate_input_or_output_is_missing:cout <<"erreur20: on attend le mot clé input, ouput ou un type de gate et on a recu: "<< c.getname()<<" a la ligne "<<c.getline() << endl;
                     break;
              case crochet_close_is_missing:cout <<"erreur21: on attend le mot label mais on a recu: "<< c.getname()<<" a la ligne "<< c.getline() << endl;
                     break;
              case pointv_is_missing:cout <<"erreur22: on attend le caractère ; et on a recu: "<< c.getname() << " a la ligne "<< c.getline()<< endl;
                     break;
              case waiting_for_a_gate_not_a_input_net:cout <<"erreur23: on attend une porte et on a recu une  net d'entrée" << c.getname() << " a la ligne " << c.getline() << endl;
                     break;
              case waiting_for_a_gate_not_a_output_net:cout <<"erreur24: on attend une porte et on a recu une  net de sortie" << c.getname() << " a la ligne " << c.getline() << endl;
                     break;
              case gate_to_assign_is_missing:cout <<"erreur25: on attend une porte et on a recu " << c.getname() << " a la ligne " << c.getline() << endl;
                     break;
             case pointv_or_fleche_is_missing:cout <<"erreur26: on attend un point virgule ou une fleche et on a recu " << c.getname() << " a la ligne " << c.getline() << endl;
                    break;
             case missing_entries:cout <<"erreur27: il manque des entrées dans une porte " << endl;
                     break;
             case to_much_entries:cout <<"erreur28: une entrée a trop de porte" <<  endl;
                    break;
            }
          }
          cout << c.getname()<<endl;
          cout << etat_courant << endl;
          if(c.gettype()!=ACCOLADEC){
              itr++;
          }
        }while (itr <= dot.end());
      }

vector<Decoupage> Simulateur::lexeur_json (){
    ifstream Fichier2(get_url_json().c_str());// ouverture du flux du Fichier2
    stringstream save2;
    ////////////////////////////////detection de la taille du Fichier2
    Fichier2.seekg(0, ios::end);
    int taille2 = Fichier2.tellg();
    cout << taille2 <<endl;
    Fichier2.seekg(0, ios::beg);
    ///////////////////////////////curseur remis au debut du Fichier2
    vector<Decoupage> v2; // def du vecteur de sortie pour le .dot
    char buffer2[1000]; // rempli de la saisie
    Type etiquette2; // creation de l'etiquette (chaine, nombre,accoladeo...)
    int i2=0; // increment du buffer2
    int ligne2 = 1;// increment de la ligne

    Fichier2.get(buffer2[i2]);
    do {
      if (buffer2[i2]== '\'')// si le caractère commence par des guillemets
      {
        save2<<buffer2[i2];// on enregistre le caractere actuel dans le stringstream
        i2++; // on incremente
        Fichier2.get(buffer2[i2]); // on observe le caractère suivant
        while(isalpha(buffer2[i2])|| buffer2[i2]== '_') {// tant qu'on a des lettres ou des guillemets  ou des tiret du bas on continue a scrutter
          save2<<buffer2[i2];
          i2++;
          Fichier2.get(buffer2[i2]);
          while(isdigit(buffer2[i2])|| buffer2[i2]=='\'')//tant que c'est un nombre ou une entrecote de fin
          {
            save2<<buffer2[i2];
            i2++;
            Fichier2.get(buffer2[i2]);
          }
          etiquette2 = NOM;
        }
        while(isdigit(buffer2[i2])|| buffer2[i2]=='\''|| buffer2[i2]=='.'){
          save2<<buffer2[i2];
          i2++;
          Fichier2.get(buffer2[i2]);
          etiquette2 = NOMBRE;
        }
        Decoupage morceau2(save2.str(),etiquette2,ligne2);// on appelle le constructeur pour un morceau à partir d'un nom, d'un type(chaine) et d'une ligne
        v2.push_back(morceau2); // on stocke notre objet "morceau" dans un vecteur
        save2.str("");//reinitialisation de streamstring save --> on le vide pour réccuperer le prochain etiquette
        save2.clear();// on le clear
      }
      if (isalpha(buffer2[i2])){// si le caractère est un alpha num
        save2<<buffer2[i2];// on enregistre le caractere actuel dans le stringstream
        i2++; // on incremente
        Fichier2.get(buffer2[i2]); // on observe le caractère suivant
        while(isalpha(buffer2[i2])|| buffer2[i2]== '_') // tant qu'on a des lettres ou des guillemets  ou des tiret du bas on continue a scrutter
        {
          save2<<buffer2[i2];
          i2++;
          Fichier2.get(buffer2[i2]);
        }
        etiquette2 = CHAINE; // tout ces cas correspondent à des chaines
        Decoupage morceau2(save2.str(),etiquette2,ligne2);// on appelle le constructeur pour un morceau à partir d'un nom, d'un type(chaine) et d'une ligne
        v2.push_back(morceau2); // on stocke notre objet "morceau" dans un vecteur
        save2.str("");//reinitialisation de streamstring save --> on le vide pour réccuperer le prochain etiquette
        save2.clear();// on le clear
      }
      if (buffer2[i2]== ' '){// detection d'un espace
        i2++;
        Fichier2.get(buffer2[i2]);
        etiquette2 = ESPACE;
        Decoupage morceau2(save2.str(),etiquette2,ligne2);
        v2.push_back(morceau2);
        save2.str("");
        save2.clear();
      }
      if (buffer2[i2]== '{'){
        save2<<buffer2[i2];
        i2++;
        Fichier2.get(buffer2[i2]);
        etiquette2 = ACCOLADEO;
        Decoupage morceau2(save2.str(),etiquette2,ligne2);
        v2.push_back(morceau2);
        save2.str("");
        save2.clear();
      }
      if (buffer2[i2]== ','){
        save2<<buffer2[i2];
        i2++;
        Fichier2.get(buffer2[i2]);
        etiquette2 = VIRGULE;
        Decoupage morceau2(save2.str(),etiquette2,ligne2);
        v2.push_back(morceau2);
        save2.str("");
        save2.clear();
      }
      if (buffer2[i2]== '['){
        save2<<buffer2[i2];
        i2++;
        Fichier2.get(buffer2[i2]);
        etiquette2 = CROCHET0;
        Decoupage morceau2(save2.str(),etiquette2,ligne2);
        v2.push_back(morceau2);
        save2.str("");
        save2.clear();
      }
      if (buffer2[i2]== ']'){
        save2<<buffer2[i2];
        i2++;
        Fichier2.get(buffer2[i2]);
        etiquette2 = CROCHETC;
        Decoupage morceau2(save2.str(),etiquette2,ligne2);
        v2.push_back(morceau2);
        save2.str("");
        save2.clear();
      }
      if (buffer2[i2]== ':'){
        save2<<buffer2[i2];
        i2++;
        Fichier2.get(buffer2[i2]);
        etiquette2 = POINTPOINT;
        Decoupage morceau2(save2.str(),etiquette2,ligne2);
        v2.push_back(morceau2);
        save2.str("");
        save2.clear();
      }
      if (buffer2[i2]== '\n'){
        save2<<buffer2[i2];
        ligne2++;
        i2++;
        Fichier2.get(buffer2[i2]);
        etiquette2 = ENDLINE;
        Decoupage morceau2(save2.str(),etiquette2,ligne2);
        v2.push_back(morceau2);
        save2.str("");
        save2.clear();
      }
      if (buffer2[i2]== '}'){
        save2<<buffer2[i2];
        i2++;
        Fichier2.get(buffer2[i2]);
        etiquette2 = ACCOLADEC;
        Decoupage morceau2(save2.str(),etiquette2,ligne2);
        v2.push_back(morceau2);
        save2.str("");
        save2.clear();
      }
      if (buffer2[i2]== '\t'){
        save2<<buffer2[i2];
        i2++;
        Fichier2.get(buffer2[i2]);
        etiquette2 = TAB;
        Decoupage morceau2(save2.str(),etiquette2,ligne2);
        v2.push_back(morceau2);
        save2.str("");
        save2.clear();
      }
    } while(i2<taille2);

    return v2;
  }

void Simulateur::parsseur_json (vector<Decoupage> v3){
    int erreur2;
    vector<string> vnomjson(1); // def du vecteur qui contient les noms des signaux --> doit commencer a 1 piour faciliter la comparaison
    vector<bool> vvaleurjson;
    int t2=0;
    int u2=0;
    int z=0;
    string valeur;
    int code=0;
    bool chiffre=0;
    string nom;
    string nomfinal;
    int q;
    int taillevaleur;
    int taillevaleurfixe=0;
    map< string,vector<bool> > mymap;
    int p=0;
    bool readytosave2=1; // by default it is possible to save
    enum etat {STATE1, STATE2, STATE3, STATE4, STATE4DEMI, STATE5, STATE6, STATE7, STATE8, STATE9, STATE10, STATE11, STATE12, STATE13, STATE14, STATE15, STATE16, END, ERREUR};
    etat etat_courant2 = STATE1;
    vector<Decoupage>::iterator itr2 ;
    itr2 = v3.begin();
    do
    {Decoupage c2 = *itr2;

    while (etat_courant2!=END)
    {
      switch (etat_courant2)
         {
         case STATE1: // have to detect {
            switch (c2.gettype())
            {
              case ACCOLADEO:
                             etat_courant2= STATE2;
                             break;
              case ESPACE:
                          etat_courant2 = STATE1;
                          break;
              case TAB:
                       etat_courant2= STATE1;
                       break;
              default:
                      erreur2=accolade_open_is_missing_2;
                      etat_courant2= ERREUR;
            }
            itr2++;
            c2 = *itr2;
            break;
        case STATE2: // have to detect signal
           switch (c2.gettype())
           {
             case CHAINE:if (c2.getname()=="signal")
                          {
                            cout<<"signal vu"<<endl;
                            etat_courant2 = STATE3;
                          }
                         break;
             case ESPACE:
                         etat_courant2 = STATE2;
                         break;
                case TAB:
                         etat_courant2= STATE2;
                         break;
                 default:
                         erreur2=keyword_signal_is_missing;
                         etat_courant2= ERREUR;
               }
               itr2++;
               c2 = *itr2;
               break;
            case STATE3: // have to detect :
              switch (c2.gettype())
              {
                case POINTPOINT:etat_courant2 = STATE4;
                                break;
                case ESPACE:
                            etat_courant2 = STATE3;
                            break;
                case TAB:
                         etat_courant2= STATE3;
                        break;
                default:
                            erreur2=pointpoint_is_missing;
                            etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
           case STATE4: // have to detect [
             switch (c2.gettype())
             {
               case CROCHET0:etat_courant2 = STATE4DEMI;
                             break;
               case ESPACE:etat_courant2 = STATE4;
                           break;
               case TAB:etat_courant2= STATE4;
                        break;
               default:erreur2=crochet_open_is_missing;
                       etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
            case STATE4DEMI: // have to detect '\n'
              switch (c2.gettype())
              {
                case ENDLINE:etat_courant2= STATE5;
                             break;
                case ESPACE:etat_courant2 = STATE4DEMI;
                            break;
                case TAB:etat_courant2= STATE4DEMI;
                         break;
                default:erreur2=return_line_is_missing;
                        etat_courant2= ERREUR;
               }
               itr2++;
               c2 = *itr2;
               break;
            case STATE5: // have to detect {
              switch (c2.gettype())
              {
                case ACCOLADEO:etat_courant2 = STATE6;
                               break;
                case ESPACE:
                            etat_courant2 = STATE5;
                            break;
                case TAB:
                         etat_courant2= STATE5;
                         break;
                case ENDLINE:etat_courant2= STATE5;
                             break;
                default:
                        erreur2=accolade_open_is_missing_2;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
            case STATE6: // have to detect name or }
              switch (c2.gettype())
              {
                case CHAINE:if (c2.getname()=="name")
                             {
                               cout<<"name vu"<<endl;
                               etat_courant2 = STATE7;
                             }
                             else
                             {
                               erreur2=keyword_name_is_missing;
                               etat_courant2=ERREUR;
                             }
                             break;
                case ESPACE:etat_courant2 = STATE6;
                            break;
                case TAB:etat_courant2= STATE6;
                        break;
                case ACCOLADEC:etat_courant2= STATE14; //--> declaration vide on attend une , après donc state14
                               break;
                default:erreur2=accolade_close_or_keyword_name_is_missing;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
            case STATE7: // have to detect :
              switch (c2.gettype())
              {
                case POINTPOINT:etat_courant2 = STATE8;
                                break;
                case ESPACE:etat_courant2 = STATE7;
                            break;
                case TAB:etat_courant2= STATE7;
                         break;
                default:erreur2=pointpoint_is_missing;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
            case STATE8: // have to detect nom
              switch (c2.gettype())
              {
                case NOM:u2=u2+1;
                         t2=u2-1;
                         for(t2; t2!=0 ; t2=t2-1)
                         {
                            if (c2.getname() != vnomjson[t2])// on verifie si la variable n'est pas déjà défini
                           {
                             cout<<"le nom est valide pour un input"<<endl;
                             // tant que le nom de variable n'est pas deja utilisé --> possible to save
                           }
                            else
                            {
                              cout<<"la variable " << vnomjson[t2] << " est déja définie"<<endl;
                              readytosave2=0; // if bool =0 , var already define, impossible to save
                              erreur2=variable_deja_defini;
                              etat_courant2=ERREUR;
                            }
                         }
                        if (readytosave2==1)// comme aucune variable defini a ce nom on peut l'enregistrer
                          {
                              nom = c2.getname();// save the name
                              nom.erase( 0, 1); // on supprime les simple quote ' '
                              nom.erase( nom.size() - 1);
                              mymap[nom];//
                              vnomjson.push_back(nom);// on recupere le nom pour etre sur de ne pas avoir de prochaine variable avec ce nom
                          }
                        etat_courant2=STATE9;
                        break;
                case ESPACE:etat_courant2 = STATE8;
                            break;
                case TAB:etat_courant2= STATE8;
                         break;
                default:erreur2=var_name_is_missing_2;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
            case STATE9: // have to detect ,
              switch (c2.gettype())
              {
                case VIRGULE:etat_courant2 = STATE10;
                             break;
                case ESPACE:etat_courant2 = STATE9;
                            break;
                case TAB:etat_courant2= STATE9;
                         break;
                default:erreur2=virgule_is_missing;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
            case STATE10: // have to detect wave
              switch (c2.gettype())
              {
                case CHAINE:if (c2.getname()=="wave")
                             {
                               etat_courant2 = STATE11;
                             }
                            break;
                case ESPACE:etat_courant2 = STATE10;
                            break;
                case TAB:etat_courant2= STATE10;
                         break;
                default:erreur2=wave_is_missing;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
            case STATE11: // have to detect ':'
              switch (c2.gettype())
              {
                case POINTPOINT:etat_courant2 = STATE12;
                             break;
                case ESPACE:etat_courant2 = STATE11;
                            break;
                case TAB:etat_courant2= STATE11;
                         break;
                default:erreur2=pointpoint_is_missing;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
            case STATE12: // have to detect nombre
              switch (c2.gettype())
              {
                case NOMBRE: valeur = c2.getname();// on recupere la chaine dans un string
                             taillevaleur = valeur.size();// on recupere la taille de la chaines
                             if (taillevaleurfixe!=0)// la taille à deja été fixe par la premiere serie de chiffre
                             {
                               if (taillevaleurfixe!=taillevaleur)// les series de chiffre ne font pas la meme taile --> erreur
                               {
                                etat_courant2==ERREUR;
                                erreur2=wrong_size_of_value;
                                break;
                               }
                             }
                             do
                             { cout << valeur[p]<<endl;
                               if(isdigit(valeur[p]))// si c'est un chiffre
                               {
                                 if (valeur[p]=='0')// le chiffre est un 0
                                 {
                                   chiffre=0;// le bool chiffre vaut 0
                                   mymap[nom].push_back(chiffre);
                                 }
                                 if (valeur[p]=='1')// le chiffre est un 0
                                 {
                                   chiffre=1;// le bool chiffre vaut 0
                                   mymap[nom].push_back(chiffre);
                                 }
                               }
                               if(valeur[p]=='.')//si mon caractère est un point
                               {
                                 mymap[nom].push_back(chiffre);
                               }
                               if (valeur[p]== '\'')
                               {
                                 //on ne fait rien
                               }
                               p++;
                             } while(p<taillevaleur);
                             p=0; // remise a 0 du compteur pour changer de vecteur
                             taillevaleurfixe=taillevaleur; // la premiere serie de chiffre donne la taille pour les autres
                             etat_courant2 = STATE13;
                             break;
                case ESPACE:etat_courant2 = STATE12;
                            break;
                case TAB:etat_courant2= STATE12;
                         break;
                default:erreur2=nombre_is_missing;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
            case STATE13: // have to detect '}'
              switch (c2.gettype())
              {
                case ACCOLADEC:etat_courant2 = STATE14;
                               break;
                case ESPACE:etat_courant2 = STATE13;
                            break;
                case TAB:etat_courant2= STATE13;
                         break;
                default:erreur2=accolade_close_is_missing;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
            case STATE14: // have to detect ',' or '\n'
              switch (c2.gettype())
              {
                case VIRGULE:etat_courant2 = STATE5;
                             break;
                case ESPACE:etat_courant2 = STATE14;
                            break;
                case TAB:etat_courant2= STATE14;
                         break;
                case ENDLINE:etat_courant2= STATE15;
                             break;
                default:erreur2=virgule_or_return_line_is_missing;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
            case STATE15: // have to detect ']'
              switch (c2.gettype())
              {
                case CROCHETC:etat_courant2 = STATE16;
                              break;
                case ESPACE:etat_courant2 = STATE15;
                            break;
                case TAB:etat_courant2= STATE15;
                         break;
                default:erreur2=crochet_close_is_missing;
                        etat_courant2 = ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
            case STATE16: // have to detect '}'
              switch (c2.gettype())
              {
                case ACCOLADEC:etat_courant2 = END;
                               break;
                case ESPACE:etat_courant2 = STATE16;
                            break;
                case TAB:etat_courant2= STATE16;
                         break;
                default:erreur2=accolade_close_is_missing;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;
            case END:cout<< "je suis a al fin"<<endl;
                     itr2++;
                     for(map< string,vector<bool> >::iterator itmap=mymap.begin();itmap!=mymap.end();++itmap){
                       for (vector<bool>::iterator itvec=itmap->second.begin();itvec!=itmap->second.end();++itvec){
                         input[itmap->first].add_val(*itvec);
                       }
                     }
                     break;
            case ERREUR:cout<< "je suis dans une erreur et je sors"<<endl;
                        code=1;// pour faire un exit 1 juste après le switch d'erreur
                        break;
          }
              switch (erreur2)
              {
                case accolade_open_is_missing_2:cout <<"erreur1: on attend le caractère '{' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case keyword_signal_is_missing:cout <<"erreur2: on attend le mot clé 'signal' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case pointpoint_is_missing:cout <<"erreur3: on attend le caractère ':' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case crochet_open_is_missing:cout <<"erreur4: on attend le caractère '[' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case return_line_is_missing:cout <<"erreur5: on attend le caractère '\n' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case keyword_name_is_missing:cout <<"erreur6: on attend le mot 'name' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case accolade_close_or_keyword_name_is_missing:cout <<"erreur7: on attend le caractere { ou un nom de variable et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case variable_deja_defini:cout <<"erreur8: Cette variable est déjà défini "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case var_name_is_missing_2:cout <<"erreur9: on attend un nom  de variable valable comme 'I1' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case virgule_is_missing:cout <<"erreur10: on attend le caractère ',' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case wave_is_missing:cout <<"erreur11: on attend le caractère 'wave' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case wrong_size_of_value:cout <<"erreur12: on attend la meme taille de bool pour chaque entrée   "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case nombre_is_missing:cout <<"erreur13: on attend une serie de 0 et de 1 (ou de .) et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case accolade_close_is_missing:cout <<"erreur14: on attend le caractère '}' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case virgule_or_return_line_is_missing:cout <<"erreur15: on attend le caractère ',' ou returnline et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
                case crochet_close_is_missing:cout <<"erreur16: on attend le caractère ']' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;
              }
              if (code==1){// si on est rentré dans l'état erreur
                exit(1); // on sort du programme
              }
        }
        itr2++;// tant que l'état de la fsm est différent de END on regarde le mot suivant
    } while (itr2 < v3.end());
}

int Simulateur::Kernel(){
  int index = 0;//variable d'incrémentation pour l'apliquation des entrée
  bool enable_calcul;
  vector<string> gate_end;
  vector<string> input_end;
  vector<string> output_end;//Vecteur dans le but de mémorisé ce qui à déja été calculé
  map<string,Net>::iterator it_input = input.begin();
  map<string,Net>::iterator it_output = ++output.begin();
  map<string,Gate*>::iterator it_gate = gate.begin();//Création et initlisation des itérateur pour la lisibilité(...)

  for (unsigned int i=0 ; i<it_input->second.get_val().size() ; i++){//Pour chaque valeur du vecteur d'entrée
    set_input(i);
    for(it_input ; it_input != input.end() ; ++it_input){
      input_end.push_back(it_input->second.get_name());//initlisation du vecteur d'entrée avec les valeurs déja disponible
    }
    while(index<LIM_SIMULATION && output_end.size()<it_output->second.get_val().size()){// Tant que l'on à pas calculé toutes les sortie ou err
      for(it_gate ; it_gate!=gate.end() ; ++it_gate){//Pour toutes les portes
        enable_calcul=1;
        if(std::find(gate_end.begin(),gate_end.end(),it_gate->second->get_name()) == gate_end.end()){//Si la porte à pas déja été calculé
          for(vector<string>::iterator it=it_gate->second->get_input().begin() ;it!=it_gate->second->get_input().end(); ++it){//pour toutes les entrée de la porte
            if(std::find(input_end.begin(),input_end.end(),*it) == input_end.end()){//Si l'entrée est pas disponible
              enable_calcul=0;
            }
          }
        }
        else{//si la porte à déja été calculé
          enable_calcul=0;
        }
        if(enable_calcul){//Si la porte à pas déja été calculé et que c'est entrée sont dispo
          if(it_gate->second->get_output().find("-") != string::npos){//si c'est une net non implicite
            input[it_gate->second->get_output()].set_val(it_gate->second->calcul_output(input));
            input_end.push_back(it_gate->second->get_output());
            gate_end.push_back(it_gate->second->get_name());
          }
          else{//Si c'est une sortie classique
            output[it_gate->second->get_output()].add_val(it_gate->second->calcul_output(input));
            input[it_gate->second->get_output()].add_val(it_gate->second->calcul_output(input));
            output_end.push_back(it_gate->second->get_output());
            input_end.push_back(it_gate->second->get_output());
            gate_end.push_back(it_gate->second->get_name());
          }//verification à faire dans les dernier if avec surrement des modif dans le net.h
        }
      }
      index++;
    }
    if(index>=LIM_SIMULATION){
      return ERR_LIMITE_ITERATION;    //Autres erreur possibles...
    }
    gate_end.clear();
    input_end.clear();
    output_end.clear();
  }
  return SIMU_OK;
}

void Simulateur::err_simulation(int err_g){
  switch(err_g){
    case SIMU_OK :  cout << "SIMULATION OK (code 0)"<<endl;
                    break;
    case ERR_LIMITE_ITERATION : cout << "ERREUR DE SIMULATION (code 1) : Limite d'itération de simulation atteinte, vérifier les boucles comibanatoire " <<endl;
                                exit(ERR_LIMITE_ITERATION);
                                break;
    default: cout << " cas pas possible ";
  }

}

bool Simulateur::create_output_file(){
    ofstream monFlux(get_url_out());
    if(monFlux)//si mon fichier existe et que le chemin est valide on écrit dans ce fichier
    {
      monFlux <<"{signal: ["<< endl;
      map<string,Net>::iterator itmap ;
      for(itmap=output.begin() ; itmap!=output.end() ; ++itmap)
      {
          monFlux<< " {name: '";
          monFlux<<itmap->first; // accede à la clé
          monFlux<< "',  wave: '";
          for (vector<bool>::iterator itvec=itmap->second.get_val().begin();itvec!=itmap->second.get_val().end();++itvec){
            if(itvec!=itmap->second.get_val().begin())
            {
              if(*(itvec-1)==*itvec)
              { monFlux <<".";}
              else{monFlux<< *itvec;}
            }
            else{ monFlux<< *itvec;}
          }
          monFlux<<"},"<<endl;; // accede à la valeur
      }
      monFlux <<"]}"<< endl;
      monFlux.close();

    }
    else // sinon on créer un nouveau fichier
    {
         cout << "Impossible d'ouvrir le fichier. Creation d'un fichier de sortie" << endl;
    }
  return 0;
}

void Simulateur::print(){
  cout << endl << " ___________________________________________________________ "<< endl;
  cout << "Simulateur : " << endl ;
  cout << " - Adresse : " << this << endl ;
  cout << " - URL du JSON : " << url_json << endl;
  cout << " - URL du DOT : " << url_dot << endl;
  cout << " - Entree : " << endl;
  for(map<string,Net>::iterator it = input.begin(); it != input.end(); ++it){
    cout <<" [ ";
    it->second.afficher();
    cout <<" ] "<< endl ;
  }
  cout << " - Sortie : " << endl;
  for(map<string,Net>::iterator it = output.begin(); it != output.end(); ++it){
    cout <<" [ ";
    it->second.afficher() ;
    cout <<" ] "<< endl ;
  }
  cout << " - Porte : " << endl;
  for(map<string,Gate*>::iterator it = gate.begin(); it!=gate.end() ; ++it){
    cout <<" [ ";
    it->second->afficher();
     cout <<" ] "<< endl ;
  }
  cout << endl << " ___________________________________________________________ "<< endl;
}

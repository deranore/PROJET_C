#include "DECOUPAGE.h"
#include <algorithm>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "NET.h"


#define  keyword_digraph_or_graph_is_missing   1
#define  name_of_file_is_missing_or_not_correct   2
#define  accolade_open_is_missing   3
#define  var_name_is_missing     4
#define  vnet_in_is_missing_or_not_define 5
#define  crochet_open_or_fleche_is_missing   6
#define  keyword_label_is_uncorrect 7
#define  keyword_label_is_missing 8
#define  equal_is_missing 9
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
using namespace std;



parseur_dot(vector<Decoupage> &v3) // v3 correspond ici au vecteur du lexeur du dot
{

    vector<string>::iterator itr2 ;
    unsigned int dark_net = 0;
    vector<string> vgate;// vecteur qui stocke les portes définis
    vector<string> vnetin;// vecteur qui stocke les net in définis
    vector<string> vnetout;// vecteur qui stocke les net out définis
    vector<string> vvar(1);// doit commencer a 1 pour la comparaison des namevar
    map<string,vector<string> > input;
    map<string,string> output;
    map<string,string> type;
    int enregistremment=0;
    map<string,string> verif_entre;
    string gate = " ";
    int erreur=0;// entier qui gère les differentes erreurs
    int t=0;// t et u servent dans le système de boucle pour vérifier qu'une déclaration est valable qu'une fois (STATE8)
    int u=0;//
    bool readytosave=1; // variable qui permet d'enregistrer ou non un porte, une entrée ou une sortie   (STATE8)
    enum etat {STATE1, STATE2, STATE3, STATE4, STATE5, STATE6, STATE7, STATE8, STATE9, STATE10, STATE12, STATE13, END, ERREUR};
    etat etat_courant = STATE1;// on début pour le STATE1
    itr = v3.begin();// on remet l'itarateur au debut du vecteur

    do
    {Decoupage c = *itr;
    while (etat_courant!=END)
    {
      switch (etat_courant)
         {
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
                             break;
                 case ESPACE:
                             etat_courant = STATE4;
                             break;
                 case TAB:
                          etat_courant= STATE4;
                          break;
                 case ACCOLADEC:
                          etat_courant= END; // si on trouve une accolade fermé --> fin du fichier
                          break;
                 default:
                         erreur=var_name_is_missing;
                         etat_courant= ERREUR;
                }
              itr++;
              c = *itr;
              break;
              case STATE5: // on doit ici detecter soit [  soit -->
                  switch (c.gettype())
                  {
                    case CROCHET0:
                                 etat_courant=STATE6;
                                 break;
                    case FLECHE:
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
                                      itr-=2;
                                      c = *itr;
                                      input[c.getname()].push_back(gate);
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
                                      etat_courant= ERREUR;  // on attend une porte et on a une net de sortie
                                      erreur=waiting_for_a_gate_not_a_output_net;
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
                                break;
                    case FLECHE:etat_courant=STATE12; // si on a une fleche  après une porte, on peut soit avoir de nouveau une porte soit une sortie
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
                                break;
                    case END:

                    for(map< string,string>::iterator it = verif_entre.begin() ; it!= verif_entre.end(); ++it)// on balait la map input
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
                    }


                            if(enregistremment == 1)
                             {
                              for(map< string,vector<string> >::iterator it = input.begin() ;it!= input.end(); ++it){//Pourte toutes les portes
                                for(vector<string>::interator it_in=*it->second.begin() ;it_in!=*it->secod.end(); ++it_in){//Pour toutes les entrée de chaque porte
                                  add_input(Net(*it_in));
                                }
                              }
                              for(map<string,string>::iterator it = output.begin() ;it!= output.end(); ++it){//Sortie
                                if(*(it->second).find("-") == string::npos){//Si ce n'est pas une net non impicite
                                  add_output(*(it->second));
                                }
                              }
                              for(map<string,string>::iterator it = output.begin() ;it!= output.end(); ++it){
                                switch(*(it->second)){
                                  case "AND": add_gate(new *AND1(*(it->first),input[*(it->first),output[*(it->first)]));
                                              break;
                                  case "OR":  add_gate(new *OR1(*(it->first),input[*(it->first),output[*(it->first)]));
                                              break;
                                  case "XOR": add_gate(new *XOR1(*(it->first),input[*(it->first),output[*(it->first)]));
                                              break;
                                  case "NAND":add_gate(new *NAND1(*(it->first),input[*(it->first),output[*(it->first)]));
                                              break;
                                  case "NOR": add_gate(new *NOR1(*(it->first),input[*(it->first),output[*(it->first)]));
                                              break;
                                  case "XNOR":add_gate(new *XNOR1(*(it->first),input[*(it->first),output[*(it->first)]));
                                              break;
                                  case "NOT":add_gate(new *NOT1(*(it->first),input[*(it->first),output[*(it->first)]));
                                              break;
                                  case "WIRE":add_gate(new *BUFFER1(*(it->first),input[*(it->first),output[*(it->first)]));
                                              break;
                                  default: cout <<" Pas possible ";

                                }
                              }
                            }
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
            case var_name_is_missing:cout <<"erreur4: on attend un nom pour une variable et on a recu "<< c.getname()<<" a la ligne "<< endl;
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
        itr++;
      }while (itr < v3.end());
    }

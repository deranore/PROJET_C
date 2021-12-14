#include <iostream>
using namespace std;
using namespace std;
#include "decoupage.h"
#include <algorithm>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


vector<Decoupage> lexeur_json()
{ ifstream Fichier2("Inputs.json");// ouverture du flux du Fichier2
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

      while(isalpha(buffer2[i2])|| buffer2[i2]== '_') // tant qu'on a des lettres ou des guillemets  ou des tiret du bas on continue a scrutter
      {
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
      while(isdigit(buffer2[i2])|| buffer2[i2]=='\''|| buffer2[i2]=='.')
      {
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
    if (isalpha(buffer2[i2]))// si le caractère est un alpha num
    {
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



    if (buffer2[i2]== ' ')// detection d'un espace
    {
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = ESPACE;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }

    if (buffer2[i2]== '{')// detection de l'accoladeo
    {
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = ACCOLADEO;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }

    if (buffer2[i2]== ',')
    {
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = VIRGULE;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }

    if (buffer2[i2]== '[')
    {
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = CROCHET0;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }
    if (buffer2[i2]== ']')
    {
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = CROCHETC;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }

    if (buffer2[i2]== ':')
    {
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = POINTPOINT;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }

    if (buffer2[i2]== '\n')
    {
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

    if (buffer2[i2]== '}')
    {
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = ACCOLADEC;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }

    if (buffer2[i2]== '\t')
    {
      //cout << "tab"<<endl;
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


map< string, vector<bool> >parseur_json(vector<Decoupage> &v3)
{ int erreur2;
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
                    erreur2=accolade_open_is_missing;
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
                      erreur2=accolade_open_is_missing;
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

              default:erreur2=var_name_is_missing;
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
                   break;




          case ERREUR:cout<< "je suis dans une erreur et je sors"<<endl;
                      code=1;// pour faire un exit 1 juste après le switch d'erreur
                      break;
        }





            switch (erreur2)
            {
              case accolade_open_is_missing:cout <<"erreur1: on attend le caractère '{' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
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

              case var_name_is_missing:cout <<"erreur9: on attend un nom  de variable valable comme 'I1' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
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

            if (code==1)// si on est rentré dans l'état erreur
            {
              exit(1); // on sort du programme
            }

      }
      itr2++;// tant que l'état de la fsm est différent de END on regarde le mot suivant
  } while (itr2 < v3.end());
return mymap;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


vector<Decoupage> lexeur_dot()
  { ifstream monFlux("and_xor.dot");
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

/////////////////////////////////////////////////////////////////////////////////////////////////














int main()
{
    vector<Decoupage> v3; // vecteur qui va récuperer le lexeur du json
    v3=lexeur_json();// recupere le vecteur du json
    vector<Decoupage>::iterator itr3 ;
    for(itr3 = v3.begin() ; itr3 != v3.end() ; ++itr3)// affichage du vecteur recu
    {
      Decoupage c2 = *itr3;// déréférencement de l'iterateur
      cout<<c2.getname()<<endl;
      cout<<c2.gettype()<<endl;
      cout<<c2.getline()<<endl;
    }

    map< string,vector<bool> > recupmymap;// recupere la map du json
    recupmymap=parseur_json(v3);

    map<string, vector<bool> >::const_iterator itMap ;// definition de l'iterateur de la map
    for(itMap = recupmymap.begin() ; itMap!=recupmymap.end() ; ++itMap) {
          cout << itMap->first<<endl;// affichage des nom de variable
          for (int i=0; i<9; i++)
          {
            cout<<itMap->second[i]<<endl; // affichage des vecteur de bool
          }
       }
///////////////////////////////////////////////////////////////////////////////////////////////// affichage du lexeur puis parseur json

vector<Decoupage> v4; // vecteur qui va récuperer le lexeur du dot
v4=lexeur_dot();// recupere le vecteur du json
vector<Decoupage>::iterator itr4 ;
for(itr4 = v4.begin() ; itr4 != v4.end() ; ++itr4)// affichage du vecteur recu
{
  Decoupage c3 = *itr4;// déréférencement de l'iterateur
  cout<<c3.getname()<<endl;
  cout<<c3.gettype()<<endl;
  cout<<c3.getline()<<endl;
}

    return 0;
}

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
#define  accolade_open_is_missing2   6




int main () {



  ifstream Fichier2("Inputs.json");// ouverture du flux du Fichier2
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
      //cout << "chaine"<<endl;
      etiquette2 = CHAINE; // tout ces cas correspondent à des chaines
      Decoupage morceau2(save2.str(),etiquette2,ligne2);// on appelle le constructeur pour un morceau à partir d'un nom, d'un type(chaine) et d'une ligne
      v2.push_back(morceau2); // on stocke notre objet "morceau" dans un vecteur
      save2.str("");//reinitialisation de streamstring save --> on le vide pour réccuperer le prochain etiquette
      save2.clear();// on le clear
    }



    if (buffer2[i2]== ' ')// detection d'un espace
    {
      //cout << "space"<<endl;
      //save2<<buffer2[i2];
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
      //cout << "accoo"<<endl;
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
      //cout << "virg"<<endl;
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
      //cout << "crocheto"<<endl;
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
      //cout << "crochetc"<<endl;
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
      //cout << "pointpoint"<<endl;
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
      //cout << "crochetc"<<endl;
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

/////////////////////////////////////////////partie test pour l'affichage du nom, du type et de la ligne de chaque morceau
  vector<Decoupage>::iterator itr2 ;
  for(itr2 = v2.begin() ; itr2 != v2.end() ; ++itr2)
  {
    Decoupage c2 = *itr2;// déréférencement de l'iterateur
    cout<<c2.getname()<<endl;
    cout<<c2.gettype()<<endl;
    cout<<c2.getline()<<endl;
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Parseur Json

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  int erreur2;
  vector<string> vnomjson(1); // def du vecteur qui contient les noms des signaus --> doit commencer a 1 piour faciliter la comparaison
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
    //vector<Decoupage>::iterator itr ;
    itr2 = v2.begin();

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
                        erreur2=accolade_open_is_missing2;
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
                            break;


                case ESPACE:etat_courant2 = STATE6;
                            break;


                case TAB:etat_courant2= STATE6;
                        break;

                case ACCOLADEC:etat_courant2= STATE14; //--> declaration vide on attend une , après donc state14
                               break;

                default:erreur2=6;
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

                default:erreur2=7;
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
                            if (c2.getname() != vnomjson[t2])
                           {
                             cout<<"le nom est valide pour un input"<<endl;
                             // while name var isn't used --> possible to save net
                           }
                            else
                            {
                              cout<<"la variable " << vnomjson[t2] << " est déja définie"<<endl;
                              readytosave2=0; // if bool =0 , var already define, impossible to save
                              erreur2=15;
                              etat_courant2=ERREUR;
                            }
                         }
                        if (readytosave2==1)//
                          {
                              nom = c2.getname();// save the name
                              nom.erase( 0, 1);
                              nom.erase( nom.size() - 1);
                              mymap[nom];
                              vnomjson.push_back(nom);
                          }
                        etat_courant2=STATE9;
                        break;


                case ESPACE:etat_courant2 = STATE8;
                            break;


                case TAB:etat_courant2= STATE8;
                         break;

                default:erreur2=7;
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

                default:erreur2=7;
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
                               cout<<"wave vu"<<endl;
                               etat_courant2 = STATE11;
                             }
                            break;


                case ESPACE:etat_courant2 = STATE10;
                            break;


                case TAB:etat_courant2= STATE10;
                         break;

                default:erreur2=7;
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

                default:erreur2=7;
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
                                erreur2=10;
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
                             p=0; // remise a 0 du compteur

                             taillevaleurfixe=taillevaleur; // la premiere serie de chiffre donne la taille pour les autres
                             etat_courant2 = STATE13;
                             break;


                case ESPACE:etat_courant2 = STATE12;
                            break;


                case TAB:etat_courant2= STATE12;
                         break;

                default:erreur2=7;
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

                default:erreur2=7;
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

                default:erreur2=7;
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

                default:erreur2=7;
                        etat_courant2 = ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;


            case STATE16: // have to detect '}'
              switch (c2.gettype())
              {
                case ACCOLADEC:etat_courant2 = END;
                              cout<< "vers la fin"<<endl;
                              break;


                case ESPACE:etat_courant2 = STATE16;
                            break;


                case TAB:etat_courant2= STATE16;
                         break;

                default:erreur2=7;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;

            case END:cout<< "je suis a al fin"<<endl;
                     itr2++;
                     break;




            case ERREUR:cout<< "je suis dans une erreur et je sors"<<endl;
                        code=1;
                        break;
          }





              switch (erreur2)
              {
                case 1:cout <<"erreur1: on attend le caractère '{' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

                case 2:cout <<"erreur2: on attend le mot clé 'signal' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

                case 3:cout <<"erreur3: on attend le caractère ':' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

                case 4:cout <<"erreur4: on attend le caractère '[' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

                case 5:cout <<"erreur5: on attend le caractère '\n' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

                case 14:cout <<"erreur6: on attend le caractère '{' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

                case 6:cout <<"erreur6: on attend le mot 'name' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

                case 7:cout <<"erreur7: on attend le caractère ':' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

                case 8:cout <<"erreur8: on attend un nom valable comme 'I1' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

                case 9:cout <<"erreur9: on attend le caractère ',' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

                case 10:cout <<"erreur10: on attend le caractère 'wave' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

                case 11:cout <<"erreur11: on attend le caractère ':' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

                case 12:cout <<"erreur12: on attend une serie de 0 et de 1 (ou de .) et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

                case 13:cout <<"erreur13: on attend le caractère '}' et on a recu "<< c2.getname()<<" à la ligne "<< c2.getline() << endl;
                break;

              }

              if (code==1)// si on est rentré dans erreur
              {
                exit(1);
              }

        }
        itr2++;
    } while (itr2 < v2.end());




    map<string, vector<bool> >::const_iterator itMap ;
    for(itMap = mymap.begin() ; itMap!=mymap.end() ; ++itMap) {
    // un iterateur sur map permet de récupérer la clé et la valeur
    //      *itMap est de type pair<string, int>(
    // itMap->first ou (*itMap).first : accès à la clé
    // itMap->second ou (*itMap).sedond : accès à la valeur
          cout << itMap->first<<endl;
          for (int i=0; i<9; i++)
          {
             cout<<itMap->second[i]<<endl;
          }

       }




}

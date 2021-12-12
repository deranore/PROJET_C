using namespace std;
#include "decoupage.h"
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
  int erreur2;
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
      cout << "chaine"<<endl;
      etiquette2 = CHAINE; // tout ces cas correspondent à des chaines
      Decoupage morceau2(save2.str(),etiquette2,ligne2);// on appelle le constructeur pour un morceau à partir d'un nom, d'un type(chaine) et d'une ligne
      v2.push_back(morceau2); // on stocke notre objet "morceau" dans un vecteur
      save2.str("");//reinitialisation de streamstring save --> on le vide pour réccuperer le prochain etiquette
      save2.clear();// on le clear
    }



    if (buffer2[i2]== ' ')// detection d'un espace
    {
      cout << "space"<<endl;
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
      cout << "accoo"<<endl;
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
      cout << "virg"<<endl;
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
      cout << "crocheto"<<endl;
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
      cout << "crochetc"<<endl;
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
      cout << "pointpoint"<<endl;
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
      cout << "return"<<endl;
      ligne2++;
      i2++;
      Fichier2.get(buffer2[i2]);
    }

    if (buffer2[i2]== '}')
    {
      cout << "crochetc"<<endl;
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
      cout << "tab"<<endl;
      save2<<buffer2[i2];
      i2++;
      Fichier2.get(buffer2[i2]);
      etiquette2 = TAB;
      Decoupage morceau2(save2.str(),etiquette2,ligne2);
      v2.push_back(morceau2);
      save2.str("");
      save2.clear();
    }
  } while(i2<100);

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

vector
enum etat {STATE1, STATE2, STATE3, STATE4, STATE5, STATE6, STATE7, STATE8, STATE9, STATE10, ERREUR};
     etat etat_courant2 = STATE1;
    //vector<Decoupage>::iterator itr ;
    itr2 = v2.begin();

    do
    {Decoupage c2 = *itr2;

    while (etat_courant2!=ERREUR)
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
                      erreur2=1;
                      etat_courant2= ERREUR;

            }
            itr2++;
            c2 = *itr2;
            break;

        case STATE2: // have to detect signal

           switch (c2.gettype())
           {
             case CHAINE:if (c.getname()=="signal")
                          {
                            cout<<"signal vu"<<endl;
                            etat_courant = STATE3;
                          }
                         break;


             case ESPACE:
                         etat_courant2 = STATE2;
                         break;


                case TAB:
                         etat_courant2= STATE2;
                         break;

                 default:
                         erreur2=2;
                         etat_courant2= ERREUR;

               }
               itr2++;
               c2 = *itr2;
               break;

            case STATE3: // have to detect :

              switch (c2.gettype())
              {
                case POINTPOINT:etat_courant = STATE4;
                                break;


                case ESPACE:
                            etat_courant2 = STATE3;
                            break;


                case TAB:
                         etat_courant2= STATE3;
                        break;

                default:
                            erreur2=3;
                            etat_courant2= ERREUR;

              }
              itr2++;
              c2 = *itr2;
              break;

           case STATE4: // have to detect [

             switch (c2.gettype())
             {
               case CROCHET0:etat_courant = STATE5;
                             break;


               case ESPACE:etat_courant2 = STATE4;
                           break;


               case TAB:etat_courant2= STATE4;
                        break;

               default:erreur=4;
                       etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;

            case STATE5: // have to detect {

              switch (c2.gettype())
              {
                case ACCOLADEO:etat_courant = STATE6;
                               break;

                case ESPACE:
                            etat_courant2 = STATE5;
                            break;


                case TAB:
                         etat_courant2= STATE5;
                         break;

                default:
                        erreur=5;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;

            case STATE6: // have to detect name

              switch (c2.gettype())
              {
                case CHAINE:if (c.getname()=="name")
                             {
                               cout<<"name vu"<<endl;
                               etat_courant = STATE7;
                             }
                            break;


                case ESPACE:etat_courant2 = STATE6;
                            break;


                case TAB:etat_courant2= STATE6;
                        break;

                default:erreur=6;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;



            case STATE7: // have to detect :

              switch (c2.gettype())
              {
                case POINTPOINT:etat_courant = STATE8;
                                break;


                case ESPACE:etat_courant2 = STATE7;
                            break;


                case TAB:etat_courant2= STATE7;
                         break;

                default:erreur=7;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;


            case STATE8: // have to detect nom

              switch (c2.gettype())
              {
                case NOM:;
                         break;


                case ESPACE:etat_courant2 = STATE7;
                            break;


                case TAB:etat_courant2= STATE7;
                         break;

                default:erreur=7;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;


            case STATE8: // have to detect nom

              switch (c2.gettype())
              {
                case NOM:etat_courant = STATE8;
                                break;


                case ESPACE:etat_courant2 = STATE7;
                            break;


                case TAB:etat_courant2= STATE7;
                         break;

                default:erreur=7;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;


            case STATE8: // have to detect nom

              switch (c2.gettype())
              {
                case NOM:etat_courant = STATE8;
                                break;


                case ESPACE:etat_courant2 = STATE7;
                            break;


                case TAB:etat_courant2= STATE7;
                         break;

                default:erreur=7;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;



            case STATE8: // have to detect nom

              switch (c2.gettype())
              {
                case NOM:etat_courant = STATE8;
                                break;


                case ESPACE:etat_courant2 = STATE7;
                            break;


                case TAB:etat_courant2= STATE7;
                         break;

                default:erreur=7;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;



            case STATE8: // have to detect nom

              switch (c2.gettype())
              {
                case NOM:etat_courant = STATE8;
                                break;


                case ESPACE:etat_courant2 = STATE7;
                            break;


                case TAB:etat_courant2= STATE7;
                         break;

                default:erreur=7;
                        etat_courant2= ERREUR;
              }
              itr2++;
              c2 = *itr2;
              break;





              }
              switch (erreur2)
              {
                case 1:cout <<"erreur1: on attend le caractère '{' et on a recu "<< c.getname()<<" à la ligne "<< c.getline() << endl;
                break;

                case 2:cout <<"erreur2: on attend le mot clé 'signal' et on a recu "<< c.getname()<<" à la ligne "<< c.getline() << endl;
                break;

                case 3:cout <<"erreur3: on attend le caractère ';' et on a recu "<< c.getname()<<" à la ligne "<< c.getline() << endl;
                break;

                case 4:cout <<"erreur4: on attend le caractère '[' et on a recu "<< c.getname()<<" à la ligne "<< c.getline() << endl;
                break;

                case 5:cout <<"erreur5: on attend le caractère '{' et on a recu "<< c.getname()<<" à la ligne "<< c.getline() << endl;
                break;

                case 6:cout <<"erreur6: on attend le mot 'name' et on a recu "<< c.getname()<<" à la ligne "<< c.getline() << endl;
                break;

                case 7:cout <<"erreur7: on attend le caractère ':' et on a recu "<< c.getname()<<" à la ligne "<< c.getline() << endl;
                break;

                case 8:cout <<"erreur8: on attend un nom valable comme 'I1' et on a recu "<< c.getname()<<" à la ligne "<< c.getline() << endl;
                break;

                case 9:cout <<"erreur9: on attend le caractère ',' et on a recu "<< c.getname()<<" à la ligne "<< c.getline() << endl;
                break;

                case 10:cout <<"erreur10: on attend le caractère 'wave' et on a recu "<< c.getname()<<" à la ligne "<< c.getline() << endl;
                break;

                case 11:cout <<"erreur11: on attend le caractère ':' et on a recu "<< c.getname()<<" à la ligne "<< c.getline() << endl;
                break;

                case 12:cout <<"erreur12: on attend une serie de 0 et de 1 (ou de .) et on a recu "<< c.getname()<<" à la ligne "<< c.getline() << endl;
                break;

                case 13:cout <<"erreur13: on attend le caractère '}' et on a recu "<< c.getname()<<" à la ligne "<< c.getline() << endl;
                break;

              }



        }itr2++;
    } while (itr2 < v2.end());
}

#include "decoupage.h"
#include <iostream>
#include<algorithm>
#include <vector>
#include <list>
using namespace std;


int main()
{


  int nmbline=2;
  string name = "digraph";
  string recup1;
  string recup2;
  int recup3;
  Type e=CHAINE;
  Type g;
  Decoupage c(name,e,nmbline);



  int erreur=0;
  enum etat {STATE1, STATE2, STATE3, STATE4, STATE5, STATE6, STATE7, STATE8, ERREUR};
  etat etat_courant = STATE1;
while (etat_courant!=ERREUR)
{
  switch (etat_courant)
     {
     case STATE1: // have to detect digraphe keyword

        switch (c.gettype())
        {
          case CHAINE:
                      if (c.getname()=="digraph")
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


          case ESPACE:
                      etat_courant = STATE1;
                      break;

          case TAB:
                   etat_courant= STATE1;
                   break;

          default:
                  erreur=1;
                  etat_courant= ERREUR;
        }

      case STATE2: // have to detect namefile

         switch (c.gettype())
         {
           case CHAINE:
                       etat_courant=STATE3;
                       break;

           case ESPACE:
                       etat_courant = STATE2;
                       break;

           case TAB:
                    etat_courant= STATE2;
                    break;

           default:
                   erreur=2;
                   etat_courant= ERREUR;
          }

        case STATE3:// have to detect accoladeo

           switch (c.gettype())
          {
            case ACCOLADEO:
                           etat_courant=STATE4;
                           break;

            case ESPACE:
                        etat_courant = STATE3;
                        break;

            case TAB:
                      etat_courant= STATE3;
                      break;

            default:
                    erreur=3;
                    etat_courant= ERREUR;
            }



        case STATE4: // have to detect namevar

           switch (c.gettype())
           {
             case CHAINE:
                         etat_courant=STATE5;
                             // gerer le stockage de la first var
                         break;

             case ESPACE:
                         etat_courant = STATE4;
                         break;

             case TAB:
                      etat_courant= STATE4;
                      break;

             default:
                     erreur=4;
                     etat_courant= ERREUR;
            }

          case STATE5: // have to detect [

              switch (c.gettype())
              {
                case CROCHET0:
                            etat_courant=STATE6;
                            break;

                case ESPACE:
                            etat_courant = STATE5;
                            break;

                case TAB:
                         etat_courant= STATE5;
                         break;

                default:
                        erreur=5;
                        etat_courant= ERREUR;
               }



          case STATE6: // have to detect label

             switch (c.gettype())
             {
                 case CHAINE:
                             if (c.getname()=="label")
                             {
                               cout<<"label vu"<<endl;
                               etat_courant = STATE2;
                             }

                             else
                             {
                               erreur=6;
                               etat_courant= ERREUR;
                             }
                             break;

                 case ESPACE:
                             etat_courant = STATE5;
                             break;

                 case TAB:
                          etat_courant= STATE5;
                          break;

                 default:
                         erreur=8;
                         etat_courant= ERREUR;
                }

                case STATE7: // have to detect label

                   switch (c.gettype())
                   {
                       case CHAINE:
                                   if (c.getname()=="label")
                                   {
                                     cout<<"label vu"<<endl;
                                     etat_courant = STATE2;
                                   }

                                   else
                                   {
                                     erreur=6;
                                     etat_courant= ERREUR;
                                   }
                                   break;

                       case ESPACE:
                                   etat_courant = STATE5;
                                   break;

                       case TAB:
                                etat_courant= STATE5;
                                break;

                       default:
                               erreur=8;
                               etat_courant= ERREUR;
                      }

        }





      switch (erreur)
      {

        case 1:cout <<"erreur1: on attend le mot clé digraphe et on a recu "<< c.getname()<<" a la ligne"<<c.getline() << "qui est un" << c.gettype()<< endl;
               break;

        case 2:cout <<"erreur2: on attend le nom du fichier et on a recu "<< c.getname()<<" a la ligne"<<c.getline() << "qui est un" << c.gettype()<< endl;
               break;

        case 3:cout <<"erreur3: on attend le caractère { et on a recu "<< c.getname()<<" a la ligne"<< c.getline() << "qui est un" << c.gettype()<< endl;
               break;

        case 4:cout <<"erreur4: on attend un nom et on a recu "<< c.getname()<<" a la ligne"<<c.getline() << endl;
               break;

        case 5:cout <<"erreur5: on attend le caractère [ et on a recu "<< c.getname()<<" a la ligne"<<c.getline() << "qui est un" << c.gettype()<< endl;
               break;


      }
    }

  }

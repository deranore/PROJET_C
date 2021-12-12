#ifndef DECOUPAGE_H_
#define DECOUPAGE_H_


#include <string>

using namespace std;
enum Type {CHAINE, NOMBRE, ACCOLADEO, ACCOLADEC, CROCHET0, CROCHETC, ESPACE, FLECHE, POINTV, EQUAL, DUMP, TAB, POINTPOINT, VIRGULE, NOM} ;

class Decoupage {


public:
  //Verre();
  Decoupage (string name,Type poss, int nmbline);
  ~Decoupage();



  string getname() const;
  Type gettype() const;
  int getline() const;


  private:
      string nom;
      Type type;
      int line;


};

#endif
//class Etat {
//public:
//   enum Possibilite {
//      AVANT, PENDANT, APRES
//   };
//private:
//   Possibilite valeur_;
//public:
//   Etat(Possibilite poss) : valeur_{ poss }  {
//   }
//   bool est_avant() const noexcept {
//      return valeur_ == AVANT;
//   }
   // ...
//};
//int main() {
//  Etat etat = Etat::PENDANT;
//  Etat::Possibilite poss = Etat::APRES;
//

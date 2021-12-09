#ifndef DECOUPAGE_H_
#define DECOUPAGE_H_

#include <string>

using namespace std;

class Decoupage {
  private:
      string nom, type;
      int line;

  public:
    //Verre();
    Decoupage (string name,string typede, int nmbline);
    ~Decoupage();


    string getname() const;
    string gettype() const;
    int getline() const;
};

#endif

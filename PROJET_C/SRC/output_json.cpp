#include <fstream>
#include <iostream>
#include <string>
#include<unistd.h>
#include<map>
using namespace std;



void sortie_json()
{
  ofstream monFlux(get_url_out());
  if(monFlux)//si mon fichier existe et que le chemin est valide on écrit dans ce fichier
  {
    monFlux <<"{signal: ["<< endl;
    map<string,Net>::const_iterator itmap ;
        for(itmap=output.begin() ; it!=output.end() ; ++itmap)
    {
        monFlux<< " {name: '";
        monFlux<<it->first; // accede à la clé
        monFlux<< "',  wave: '";
        for (vector<bool>::iterator itvec=it->second.get_val().begin();itvec!=it->second.get_val().end();++itvec){
          if(itvec!=it->second.get_val().begin())
          {
            if(*(itvec-1)==*itvec)
            { monFlux <<".";}
            else{monFlux<< *itvec;}
          }
          else{ monFLux<< *itvec;}
        }
        monFlux<<*it->get; // accede à la valeur$
        monFlux<<"},"<<endl;; // accede à la valeur
    }
    monFlux <<"]}"<< endl;
    monFlux.close();

  }
  else // sinon on créer un nouveau fichier
  {
       cout << "Impossible d'ouvrir le fichier. Creation d'un fichier de sortie" << endl;
  }
}

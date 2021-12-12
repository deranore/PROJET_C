

    cout <<"still out there"<<endl;
    //vector<string>::iterator itr2 ;
    int erreur=0;
    int t=0;
    int u=0;
    bool readytosave=1; // by default it is possible to save

    enum etat {STATE1, STATE2, STATE3, STATE4, STATE5, STATE6, STATE7, STATE8, STATE9, STATE10, ERREUR};
    etat etat_courant = STATE1;
    //vector<Decoupage>::iterator itr ;
    itr = v1.begin();

    do
    {Decoupage c = *itr;

    while (etat_courant!=ERREUR)
    {
      switch (etat_courant)
         {
         case STATE1: // have to detect digraphe keyword

            switch (c.gettype())
            {
              case CHAINE:
                          if (c.getname()=="digraph"||c.getname()=="graph")
                          {
                            cout<<"digraph vu"<<endl;
                            //itr++;
                            //c = *itr;
                            etat_courant = STATE2;
                          }
                          else
                          {
                            erreur=7;
                            //itr++;
                            //c = *itr;
                            etat_courant= ERREUR;
                          }
                          break;


              case ESPACE://itr++;
                          //c = *itr;
                          etat_courant = STATE1;
                          break;

              case TAB://itr++;
                       //c = *itr;
                       etat_courant= STATE1;
                       break;

              default://itr++;
                      //c = *itr;
                      erreur=1;
                      etat_courant= ERREUR;

            }
            itr++;
            c = *itr;
            break;
          //itr++;
        //  c = *itr;

          case STATE2: // have to detect namefile

             switch (c.gettype())
             {
               case CHAINE:
                           cout <<"etape 2 reussi passage a 3 "<<endl;
                           //itr++;
                           //c = *itr;
                           etat_courant=STATE3;
                           break;

               case ESPACE://itr++;
                           //c = *itr;
                           cout << "je suis bien un espace" <<endl;
                           etat_courant = STATE2;
                           break;

               case TAB://itr++;
                        //c = *itr;
                        etat_courant= STATE2;
                        break;

               default://itr++;
                       //c = *itr;
                       erreur=2;
                       etat_courant= ERREUR;
              }
              itr++;
              c = *itr;
              break;


            case STATE3:// have to detect accoladeo

               switch (c.gettype())
               {
                case ACCOLADEO:cout<<"acco o vu"<<endl;
                               etat_courant=STATE4;
                               break;

                case ESPACE://itr++;
                            //c = *itr;
                            etat_courant = STATE3;
                            break;

                case TAB:
                          etat_courant= STATE3;
                          break;

                default:
                        erreur=3;
                        etat_courant= ERREUR;
                }
                itr++;
                c = *itr;
                break;




            case STATE4: // have to detect namevar

               switch (c.gettype())
               {
                 case CHAINE:
                             etat_courant=STATE5;
                             vvar.push_back(c.getname()); // on stocke momentanement le nom de la var
                                 // gerer le stockage de la first var
                             u=u+1;
                             t=u-1;
                             break;

                 case ESPACE:
                             etat_courant = STATE4;
                             break;

                 case TAB:
                          etat_courant= STATE4;
                          break;

                 case ACCOLADEC:

                          etat_courant= ERREUR; // to modify by end of fsm
                          break;

                 default:
                         erreur=4;
                         etat_courant= ERREUR;
                }
              itr++;
              c = *itr;
              break;

              case STATE5: // have to detect [ or ->

                  switch (c.gettype())
                  {
                    case CROCHET0:
                                 etat_courant=STATE6;
                                 break;

                    case FLECHE:

                                  etat_courant=STATE11;
                                  itr=itr-1; // on observe la var juste avant
                                  for(itr2 = vnetin.begin() ; itr2 != vnetin.end() ; ++itr2)
                                  {
                                    if (c.getname()==vnetin[itr2] )
                                    {
                                      // net is valid (was declared before)
                                      ////////////////////////////
                                      // if net is input continue (check with Brian class)
                                      vnetinfinal.pushback(c.getname()); //save in good order the input net
                                      // increment demarre à 0 et ++
                                      etat_courant= STATE12;
                                    }
                                  }
                                  itr=itr+1; // on observe  de nouveau la var actuelle
                                  // je dois verifier avant d'aller en state 11 que
                                  // le nom de var existe bien dans le vecteur input

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
                                   erreur=6;
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
                             erreur=8;
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
                                    cout<<"egal vu"<<endl;
                                    etat_courant = STATE8;
                                  }

                                  else
                                  {
                                    cout<<"pas de egal vu"<<endl;
                                    erreur=6;
                                    etat_courant= ERREUR;
                                  }
                                  break;

                      case ESPACE:
                                  etat_courant = STATE7;
                                  break;

                      case TAB:
                               etat_courant= STATE7;
                               break;

                      default:
                              erreur=8;
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
                                          erreur=10;
                                          etat_courant=ERREUR;
                                        }
                                      }
                                      if (readytosave==1)
                                      {
                                        //var does not exist --> possible to assign
                                        // have to create the net here
                                        vnetin.push_back(vvar[u]) // save the gate in a vector
                                        cout << " on enregistre la valeur ici" << endl;
                                      }
                                      etat_courant=STATE9;
                                    }

                                    if (c.getname()=="\"OUTPUT\"")
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
                                          erreur=10;
                                          etat_courant=ERREUR;
                                        }
                                      }
                                      if (readytosave==1)
                                      {
                                        //var does not exist --> possible to assign
                                        // have to create the net here
                                        vnetout.push_back(vvar[u]) // save the gate in a vector
                                        cout << " on enregistre la valeur du OUTPUT ici" << endl;
                                      }
                                      etat_courant=STATE9;
                                    }

                                    if (c.getname()=="\"AND2\"")
                                    {
                                      // check if var is not alreay assigned
                                      for(t; t!=0 ; t=t-1)
                                      {
                                        if (vvar[u] != vvar[t])
                                        {
                                          cout<<"le nom est valide pour un AND2"<<endl;
                                          // while name var isn't used --> possible to save net
                                        }
                                        else
                                        {
                                          cout<<"la variable " << vvar[t] << " est déja définie"<<endl;
                                          readytosave=0; // if bool ==0 , var already define, impossible to save
                                          erreur=10;
                                          etat_courant=ERREUR;
                                        }
                                      }
                                      if (readytosave==1)
                                      {
                                        //var does not exist --> possible to assign
                                        // have to create the net here
                                        vgate.push_back(vvar[u]) // save the gate in a vector
                                        cout << " on enregistre la valeur du AND2 ici" << endl;
                                      }
                                      etat_courant=STATE9;
                                    }

                                    if (c.getname()=="\"XOR2\"")
                                    {
                                      // check if var is not alreay assigned
                                      for(t; t!=0 ; t=t-1)
                                      {
                                        if (vvar[u] != vvar[t])
                                        {
                                          cout<<"le nom est valide pour un XOR2"<<endl;
                                          // while name var isn't used --> possible to save net
                                        }
                                        else
                                        {
                                          cout<<"la variable " << vvar[t] << " est déja définie"<<endl;
                                          readytosave=0; // if bool ==0 , var already define, impossible to save
                                          erreur=10;
                                          etat_courant=ERREUR;
                                        }
                                      }
                                      if (readytosave==1)
                                      {
                                        //var does not exist --> possible to assign
                                        // have to create the net here
                                        vgate.push_back(vvar[u]) // save the gate in a vector
                                        cout << " on enregistre la valeur du XOR2 ici" << endl;
                                      }
                                      etat_courant=STATE9;
                                    }

                                    else
                                    {
                                      erreur=10;
                                      etat_courant=ERREUR;
                                    }
                                    break;

                      case ESPACE:
                                  etat_courant = STATE8;
                                  break;

                      case TAB:
                               etat_courant= STATE8;
                               break;

                       default:
                               erreur=5;
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
                                  break;

                    case ESPACE:
                                etat_courant = STATE9;
                                break;

                    case TAB:
                             etat_courant= STATE9;
                             break;

                    default:
                            erreur=5;
                            etat_courant= ERREUR;
                }
                itr++;
                c = *itr;
                break;

              case STATE10: // have to detect ;

                switch (c.gettype())
                {
                    case POINTV:
                                  etat_courant=STATE4;
                                  break;

                    case ACCOLADEC:
                                  etat_courant=ERREUR;
                                  break;

                    case ESPACE:
                                etat_courant = STATE9;
                                break;

                    case TAB:
                             etat_courant= STATE9;
                             break;

                    default:
                            erreur=5;
                            etat_courant= ERREUR;
                 }
                 itr++;
                 c = *itr;
                 break;


              case STATE11: // have to detect if the net is valid

                switch (c.gettype())
                {
                    case CHAINE:
                                for(itr2 = vnet.begin() ; itr2 != vnet.end() ; ++itr2)
                                {
                                  if (c.getname()==vnet[itr2])
                                  {
                                    // net is valid (was declared before)
                                    ////////////////////////////
                                    // if net is input continue (check with Brian class)
                                    vnetinfinal.pushback(c.getname()); //save in good order the input net
                                    // increment demarre à 0 et ++
                                    etat_courant= STATE12;
                                  }
                                }

                                for(itr2 = vgate.begin() ; itr2 != vgate.end() ; ++itr2)
                                {
                                  if (c.getname()==vgate[itr2])

                                  {
                                    // this is not a net but a gate
                                    erreur= 10;
                                    etat_courant=ERREUR;
                                  }
                                }
                                break;

                    case ESPACE:
                                etat_courant = STATE11;
                                break;

                       case TAB:
                                etat_courant= STATE11;
                                break;

                       default:
                               erreur=10;
                               etat_courant= ERREUR;
                }
                itr++;
                c = *itr;
                break;


             case STATE12: // have to detect namegate

                switch (c.gettype())
                {
                      case CHAINE:
                                  for(itr2 = vgate.begin() ; itr2 != vgate.end() ; ++itr2)
                                  {
                                    if (c.getname()==vgate[itr2])

                                    {
                                      // this name of gate is valid (was declared before)
                                      // x= how many entries for the gate ? (brian classes)
                                      // while x !=0  (il reste des entrées disponible)
                                      //{
                                      // gate = vnetinfinal[i] // gate recupere le net associé
                                      //}
                                      //
                                      etat_courant=STATE13;
                                    }
                                  }

                                  for(itr2 = vnet.begin() ; itr2 != vnet.end() ; ++itr2)
                                  {
                                    if (c.getname()==vnet[itr2])
                                    {
                                      // this is not a gate but a net (waiting for a gate)
                                      etat_courant= STATE12;
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
                                 erreur=5;
                                 etat_courant= ERREUR;
                }
                itr++;
                c = *itr;
                break;






              case ERREUR: // have to detect equal
                          cout<< "je suis dans une erreur et je devrais sortir"<<endl;
                          itr++;
                          c = *itr;
                          break;


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

        } itr++;
      } while (itr < v1.end());
    }

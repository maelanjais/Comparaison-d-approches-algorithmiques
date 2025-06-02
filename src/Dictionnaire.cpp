#include "Image.h"
#include <string>
#include "Moteur.h"
#include "Dictionnaire.h"
#include <vector>
#include <iostream>
using namespace std;

Dictionnaire::Dictionnaire(string nom) {
    ifstream entree;
    entree.open(nom);
    if (!(entree.is_open())) {
        throw string ("Dictionnaire.txt n'est pas ouvert");
    }
    int nbInt;
    if (!(entree.eof())) {
        entree >> nbInt;
    }
    for (int i=0; i<nbInt && !entree.eof(); i++) {
        string nom;
        int x;
        int y;
        string prop;
        entree >> nom >> x >> y >> prop;
        Tuile t(nom, x, y, prop);
        _tuiles.push_back(t);
    }
    entree.close();
}

void Dictionnaire::afficher() const{
    for (int i = 0; i < _tuiles.size(); i++) {
        cout << " " << endl;
        _tuiles[i].afficher();
    }

}

//l'algorithme de recherche utilisé et une recherche dichotomique parce que c'est efficace et que c'est déjà trié.
bool Dictionnaire::recherche(string nom, Tuile& t) const{

    int debut = 0;
    int fin = _tuiles.size() - 1;
    int milieu;
    bool found = false;
    int ind = -1;

    while (!found && debut <= fin)
    {

        milieu = (debut + fin)/2;
        found = (nom == _tuiles[milieu].getNom());
        if (found){
            ind = milieu;
        }
        if (!found){
            if (nom < _tuiles[milieu].getNom())
                fin = milieu - 1;
            else
                debut = milieu + 1;
        }
    }

    if (found) t = _tuiles[ind];
    return (found);

}

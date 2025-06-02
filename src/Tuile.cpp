#include "Image.h"
#include <string>
#include "Moteur.h"
#include "Tuile.h"
#include <vector>
using namespace std;

Tuile::Tuile() {}

Tuile::Tuile(string nom, int x, int y, string propriete) {
    cout << "contruction d'une tuile"<<endl;
    _nom = nom;
    _x = x;
    _y = y;
    _propriete = propriete;
}

void Tuile::afficher() const{

    cout<<" nom : "<<_nom<<"\n x : "<<_x<< "\n y : "<<_y<<"\n propriete : "<<_propriete<<endl;

}

string Tuile::getNom() const {
    return _nom;
}

int Tuile::getX () const {
    return _x;
}

int Tuile::getY () const {
    return _y;
}

string Tuile::getProp() const {
    return _propriete;
}

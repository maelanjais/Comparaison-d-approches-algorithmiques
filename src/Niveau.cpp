#include "Image.h"
#include <string>
#include "Moteur.h"
#include "Dictionnaire.h"
#include <vector>
#include <iostream>
#include "Objet.h"
#include "Niveau.h"
using namespace std;

Niveau::Niveau(Image& image, string nomf, Dictionnaire& dico) {
    ifstream entree;
    entree.open(nomf);
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
        entree >> nom >> x >> y;
        Objet o(image, nom, dico, x*16, y*16);
        _decor.push_back(o);
    }
    entree.close();

    _bonus = nbBonus();
}

void Niveau::dessiner() {
    for (int i=0; i<_decor.size(); i++) {
        if (_decor.at(i).getProp() != "cache") {
            _decor.at(i).dessiner();
        }
    }
}
bool Niveau::caseEstLibre(int posX, int posY) {
    return indiceObjet(posX, posY, "solide") == -1;
}

int Niveau::nbBonus() {
    int bonus=0;
    for (int i=0; i<_decor.size(); i++) {
        if (_decor.at(i).getProp() == "bonus") {
            bonus++;
        }
    }
    return bonus;
}



int Niveau::compterBonus() {
    int totalBonus = 0;
    for (size_t i = 0; i < _decor.size(); ++i) {
        if (_decor[i].getProp() == "bonus") {
            totalBonus++;
        }
    }
    return totalBonus;
}


void Niveau::testerBonusEtPrendre(int posX, int posY) {
    int index = indiceObjet(posX, posY, "bonus");
    if (index != -1) {
        _bonus--;
        _decor[index].cache();
    }
}

bool Niveau::gagne() {
    return _bonus == 0;
}

int Niveau::indiceObjet(int x, int y, const string prop) {
    for (size_t i = 0; i < _decor.size(); ++i) {
        const auto& objet = _decor[i];
        if (objet.getProp() == prop && x == objet.getX() && y == objet.getY()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}





#include <vector>
#include <iostream>
#include "Moteur.h"
#include "Image.h"
#include "Personnage.h"
#include "Tuile.h"
#include "Dictionnaire.h"
#include "Niveau.h"
#include "Objet.h"

using namespace std;

int main(int, char**) {

    Tuile t("zaza", 10,88,"ZOZO");
    t.afficher();
    Dictionnaire D("assets/dictionnaire.txt");
    D.afficher();
    cout <<D.recherche("zobinho",t);
    cout <<"\n"<<D.recherche("Fleurs",t);
    return 0;
}

#ifndef _PERSONNAGE_H_
#define _PERSONNAGE_H_
#include "Image.h"
#include "Moteur.h"
#include "Niveau.h"

using namespace std;

const int MINXY = 0;
const int MAXY = 112;
const int MAXX = 144;

class Personnage {
private:
    int _PersPosx;
    int _PersPosy;
    Image _perso;
    int _skin_x;
    int _skin_y;
    char _direction;
    int _etat_animation;
    int _animationX;
    int _animationY;

public:
    Personnage();

    Personnage(Image perso, int PersPosx, int PersPosy, int skin_x, int skin_y, char direction);
    void dessine() const;
    void allerBas(Niveau& niveau);
    void allerDroite(Niveau& niveau);
    void allerGauche(Niveau& niveau);
    void allerHaut(Niveau& niveau);
    void mettreJourDirection(char direction);
    void avancer(Niveau& niveau);
    bool bordatteint();
    int getPosx();
    int getPosy();
    bool touche(Personnage& J);
    void mettreAjourAnimation();
};


#endif

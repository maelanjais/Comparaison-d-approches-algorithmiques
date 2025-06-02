#include "Image.h"
#include "Personnage.h"
#include <string>
#include "Moteur.h"
using namespace std;

Personnage::Personnage() {
    _PersPosx = 64;
    _PersPosy = 64;
    _direction = 8;
    _etat_animation = 0;
}

Personnage::Personnage(Image perso, int PersPosx, int PersPosy, int skin_x, int skin_y, char direction) {
    _perso = perso;
    _PersPosx = PersPosx;
    _PersPosy = PersPosy;
    _skin_x = skin_x;
    _skin_y = skin_y;
    _direction = direction;
    _perso.selectionnerRectangle(_skin_x,_skin_y,16,16);
    _animationX = skin_x;
    _animationY = skin_y;
}



void Personnage::dessine() const{
    _perso.dessiner(_PersPosx, _PersPosy);
}

bool Personnage::bordatteint() {
    switch (_direction) {
    case 'H': return _PersPosy <= MINXY;
    case 'B': return _PersPosy >= MAXY;
    case 'D': return _PersPosx >= MAXX;
    case 'G': return _PersPosx <= MINXY;
    default: return false;
    }
}

void Personnage::allerDroite(Niveau& niveau) {
    _PersPosx += 16;
    if (!niveau.caseEstLibre(_PersPosx, _PersPosy)) _PersPosx -= 16;
}

void Personnage::allerGauche(Niveau& niveau) {
    _PersPosx -= 16;
    if (!niveau.caseEstLibre(_PersPosx, _PersPosy)) _PersPosx += 16;
}

void Personnage::allerBas(Niveau& niveau) {
    _PersPosy += 16;
    if (!niveau.caseEstLibre(_PersPosx, _PersPosy)) _PersPosy -= 16;
}

void Personnage::allerHaut(Niveau& niveau) {
    _PersPosy -= 16;
    if (!niveau.caseEstLibre(_PersPosx, _PersPosy)) _PersPosy += 16;
}

void Personnage::mettreJourDirection(char direction) {
    _direction = direction;
    int deltaY = 0;
    switch (_direction) {
    case 'H': deltaY = 0; break;
    case 'B': deltaY = 48; break;
    case 'D': deltaY = 32; break;
    case 'G': deltaY = 16; break;

    }
    _animationY = _skin_y + deltaY;
    _perso.selectionnerRectangle(_skin_x, _animationY, 16, 16);
}

void Personnage::avancer(Niveau& niveau) {
    char directions[] = {'H', 'B', 'D', 'G'};
    char nouvelle_direction = directions[rand() % 4];
    mettreJourDirection(nouvelle_direction);

    int dx = 0, dy = 0;
    switch (_direction) {
    case 'H': dy = -16; break;
    case 'B': dy = 16; break;
    case 'D': dx = 16; break;
    case 'G': dx = -16; break;
    }

    _PersPosx += dx;
    _PersPosy += dy;
    if (!niveau.caseEstLibre(_PersPosx, _PersPosy)) {
        _PersPosx -= dx;
        _PersPosy -= dy;
    }
}

int Personnage::getPosx() {
    return _PersPosx;
}

int Personnage::getPosy() {
    return _PersPosy;
}

bool Personnage::touche(Personnage& J) {
    return _PersPosx == J.getPosx() && _PersPosy == J.getPosy();
}

void Personnage::mettreAjourAnimation() {
    _etat_animation = (_etat_animation + 1) % 4;
    int deltaX = (_etat_animation == 1 || _etat_animation == 3) ? 0 : (_etat_animation == 0 ? -TAILLE_CASE : TAILLE_CASE);
    _perso.selectionnerRectangle(_skin_x + deltaX, _animationY, TAILLE_CASE, TAILLE_CASE);
}


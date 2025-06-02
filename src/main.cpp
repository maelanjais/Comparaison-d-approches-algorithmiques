#include <vector>
#include "Dictionnaire.h"
#include "Moteur.h"
#include "Image.h"
#include "Personnage.h"
#include "Objet.h"
#include "Niveau.h"

using namespace std;

// modification de moteur.cpp :   constexpr int IMAGES_PAR_SECONDE = 4; valeur de base = 8, c'est pour avoir un jeu plus lent et plus facile

int main(int, char**) // Version special du main, ne pas modifier
{
  // Initialisation du jeu
  Moteur moteur("Mon super jeu vidéo");

  // TODO: charger images, creer personnages, etc.
    Image image;
    Image coffref;
    Image coffreo;
    Image skin;
    Image GameOver;
    Image objet;
    Image Bravo;
    try {
        image = Image(moteur, "./assets/fond.png");
        coffref = Image(moteur, "./assets/coffre_ferme.png");
        coffreo = Image(moteur, "./assets/coffre_ouvert.png");
        skin = Image(moteur, "./assets/personnages.png");
        GameOver = Image(moteur, "./assets/donpollo.jpg");
        objet = Image(moteur, "./assets/objets.png");
        Bravo = Image(moteur, "./assets/donpolloWIN.jpg");
    }
    // (... et le catch pour traiter l'exception)
    catch (runtime_error n) {
        cerr << n.what();
    }

    Personnage chevalier(skin,32,16,4*16,0*16,'H');
    Personnage ennemi1(skin,5*16,16,1*16,4*16,'B');
    Personnage ennemi2(skin,16,5*16,7*16,4*16,'D');
    Dictionnaire dico("./assets/dictionnaire.txt");
    Niveau obstacle(objet, "./assets/niveau1.txt", dico);

    bool quitter = false;

  // Boucle de jeu, appelee a chaque fois que l'ecran doit etre mis a jour
  // (en general, 60 fois par seconde)
  while (!quitter)
  {

    // I. Gestion des evenements
    Evenement evenement = moteur.evenementRecu();
    while (evenement != AUCUN)
    {
      switch (evenement)
      {
        // QUITTER = croix de la fenetre ou Echap
        case QUITTER_APPUYE:
          quitter = true;
          break;
        // TODO: gerer les autres evenements
        /*case ESPACE_APPUYE:
            etatcoffre = !etatcoffre;
            break;*/
        case GAUCHE_APPUYE:
            obstacle.testerBonusEtPrendre(chevalier.getPosx(), chevalier.getPosy());
            chevalier.mettreJourDirection('G');
            chevalier.allerGauche(obstacle);
            break;
        case DROITE_APPUYE:
            obstacle.testerBonusEtPrendre(chevalier.getPosx(), chevalier.getPosy());
            chevalier.mettreJourDirection('D');
            chevalier.allerDroite(obstacle);
            break;
        case HAUT_APPUYE:
            obstacle.testerBonusEtPrendre(chevalier.getPosx(), chevalier.getPosy());
            chevalier.mettreJourDirection('B');
            chevalier.allerHaut(obstacle);
            break;
        case BAS_APPUYE:
            obstacle.testerBonusEtPrendre(chevalier.getPosx(), chevalier.getPosy());
            chevalier.mettreJourDirection('H');
            chevalier.allerBas(obstacle);
            break;
        case ESPACE_APPUYE:
            quitter = true;
        default:
          break;
        }



      evenement = moteur.evenementRecu();
    }


    // II. Mise à jour de l'état du jeu

    // TODO: faire bouger vos personnages, etc.
    if (moteur.animationsAmettreAjour() == true) {
        ennemi1.avancer(obstacle);
        ennemi2.avancer(obstacle);
        chevalier.mettreAjourAnimation();
    }


    // III. Generation de l'image à afficher

    moteur.initialiserRendu(); // efface ce qui avait ete affiche precedemment et reinitalise en ecran noir

    // TODO: afficher vos personnages, objets, etc.
    obstacle.dessiner();

    chevalier.dessine();
    ennemi1.dessine();
    ennemi2.dessine();
    if (chevalier.touche(ennemi1) || chevalier.touche(ennemi2)) {

        GameOver.dessiner(32, 16);
        quitter = true;
    }
    if (obstacle.gagne() == true) {

        Bravo.dessiner(32, 16);
        quitter = true;
    }
    /*
      Affiche l'image en se cadencant sur la frequence de
      rafraichissement de l'ecran (donc va en general mettre le
      programme en pause jusqu'a ce que l'ecran soit rafraichi). En
      general, 60 images fois par seconde, mais ca peut dependre du
      materiel
    */
    moteur.finaliserRendu();
  }
  if (quitter == true) {
    moteur.attendre(2);
  }

  return 0;
}

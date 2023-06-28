#include <Gamebuino-Meta.h>

// Caractèristiques de la raquette
int raquetteX;
const int RAQUETTE_Y = 58;
const int RAQUETTE_LARGEUR = 10;
const int RAQUETTE_HAUTEUR = 2;

// Caractéristiques de la balle
int balleX;
int balleY;
int balleVX;
int balleVY;
const int BALLE_TAILLE = 3;
int BriqueX = 2;
int BriqueY = 25;
int j = 0;

void setup() {
  gb.begin();
  reinitialiser();  // Situé dans miseAJour.ino
}

void loop() {
  while (!gb.update());
  // INPUTS //
  entrees();

  // LOGIC //
  miseAJour();

  // DRAW //
  affichage();
}

// entrees.ino //
void entrees() {
    if (gb.buttons.repeat(BUTTON_LEFT, 1) && raquetteX > 0 || gb.buttons.repeat(BUTTON_A, 1) && raquetteX > 0) {
        raquetteX -= 3;
    }
    else if (gb.buttons.repeat(BUTTON_RIGHT, 1) && raquetteX < gb.display.width() - RAQUETTE_LARGEUR || gb.buttons.repeat(BUTTON_B, 1) && raquetteX < gb.display.width() - RAQUETTE_LARGEUR) {
        raquetteX += 3;
    }
}

// miseAJour.ino //
void miseAJour() {
  // MAJ Balle
  balleX += balleVX;
  balleY += balleVY;

  // Collisions avec les murs
  if (balleX < 0 || balleX > gb.display.width() - BALLE_TAILLE) {
    balleVX *= -1;
  }
  if (balleY < 0) {
    balleVY *= -1;
  }
  else if (balleY > gb.display.height()) {
    reinitialiser();
  }

  // Collision avec la raquette
  if (gb.collideRectRect(balleX, balleY, BALLE_TAILLE, BALLE_TAILLE,
                          raquetteX, RAQUETTE_Y, RAQUETTE_LARGEUR, RAQUETTE_HAUTEUR)) {
    balleVY = -1;  // Haut
  }
}

void reinitialiser() {
  balleX = random(0, gb.display.width() - BALLE_TAILLE);
  balleY = RAQUETTE_Y - BALLE_TAILLE - 1;  // Juste au dessus de la raquette
  balleVX = 1;  // Droite
  balleVY = -1;  // Haut
}


// affichage.ino //
void affichage() {
  gb.display.clear();

  // Tableau de Brique
  int tableauBrique[8]={1,1,1,1,1,1,1,1};
  for (int j=0; j<3; j++){
    


  for (int i=0; i < 9; i++){  
       gb.display.fillRect (BriqueX, BriqueY, 5, 3); 
       BriqueX = BriqueX + 10;
  }
  BriqueX = 2;
  BriqueY = BriqueY - 8; 
  }
  BriqueY = 25; 
  /*for ( int j=0; j < 4; j++) {
    gb.display.fillRect (BriqueX, BriqueY, 5, 3); 
    BriqueY = BriqueY - 8;
  }*/


   
  
  
  // Raquette
  gb.display.fillRect(raquetteX, RAQUETTE_Y, RAQUETTE_LARGEUR, RAQUETTE_HAUTEUR);

  // Balle
  gb.display.fillRect(balleX, balleY, BALLE_TAILLE, BALLE_TAILLE);
}




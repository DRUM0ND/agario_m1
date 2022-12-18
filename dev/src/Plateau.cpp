#include <SDL.h>
#include "Plateau.hpp"
#include "Jeu.hpp"
#include <iostream>



Plateau::Plateau(){
}


Plateau::~Plateau(){
}

void Plateau::draw(SDL_Renderer *renderer){
    
}
  

bool
Plateau::estJoueurDansFenetre(const Joueur &joueur)
{
    return joueur.corps.x > fenetreXorigin
    && joueur.corps.y > fenetreYorigin
    && joueur.corps.x < fenetreXorigin + ReglageJeu::LARGEUR_FENETRE
    && joueur.corps.y < fenetreYorigin + ReglageJeu::HAUTEUR_FENETRE;
}


void
Plateau::ajoutStaticElem(int nb){
    for (int i=0; i < nb; i++){
          double x  = (double) (rand()%ReglageJeu::LARGEUR_MONDE_JEU);
          double y  = (double) (rand()%ReglageJeu::HAUTEUR_MONDE_JEU);
          double t  = 5.0;
          double vx  = 0.0;
          double vy = 0.0;
          Joueur j;
          joueurs.push_back(j);
          Joueur &jj = joueurs.at(joueurs.size()-1);
          jj.vx = vx;
          jj.vy = vy;
          jj.corps.x = x;
          jj.corps.y = y;
          jj.corps.w = t;
          jj.corps.h = t;

          jj.r = 128.0;
          jj.g = 0.0;
          jj.b = 0.0;
          jj.vy = 0.0;
          jj.vy = 0.0;
          
      }
}

void
Plateau::generationJoueur(int t) //ajout variable pour specifier la taille du joueur
{
    double x = (double)(rand() % ReglageJeu::LARGEUR_MONDE_JEU);
    double y = (double)(rand() % ReglageJeu::HAUTEUR_MONDE_JEU);

    Uint8 r = rand() % 255;
    Uint8 g = rand() % 255;
    Uint8 b = rand() % 255;
    double vx = (double)((rand() % 4000) / 1000.0) * (rand() % 2 == 0 ? 1.0 : -1.0);
    double vy = (double)((rand() % 4000) / 1000.0) * (rand() % 2 == 0 ? 1.0 : -1.0);
    Joueur j;
    joueurs.push_back(j);
    Joueur& jj = joueurs.at(joueurs.size() - 1);
    jj.vx = vx;
    jj.vy = vy;
    jj.corps.x = x;
    jj.corps.y = y;
    jj.corps.w = t;
    jj.corps.h = t;

    jj.r = r;
    jj.g = g;
    jj.b = b;
    jj.vy = vx;
    jj.vy = vy;
    jj.updateVitesse();
}

void
Plateau::generationJoueurs(int nb)
{
    for (int i=0; i < nb; i++){
        generationJoueur(rand() % 30);
    }
}

void
Plateau::convertToFenetreCoords(double &x, double &y)
{
    x = x - fenetreXorigin;
    y = y - fenetreYorigin;
}

void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int rayon, int r, int g, int b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	for (int y = -rayon; y <=rayon; y++) {
		int x = sqrt(rayon*rayon - y*y); // longueur du trait horizontal à la hauteur y
		SDL_RenderDrawLine(renderer, cx - x, cy + y, cx + x, cy + y);
	}
}

void
Plateau::afficheJoueur(Joueur j, SDL_Renderer *renderer){
    if (j.estVisible){
        SDL_SetRenderDrawColor(renderer, j.r, j.g, j.b, 255);
        double xx = j.corps.x+j.corps.w/2, yy = j.corps.y+j.corps.w/2;
        convertToFenetreCoords(xx, yy);
        drawFilledCircle(renderer, xx, yy, j.corps.w/2, j.r, j.g, j.b);
    }
}

void
Plateau::lacheDeLest(Joueur &joueur) {
    if (joueur.corps.w > 25) {
        joueur.diviseTaille();
        generationJoueur(joueur.corps.w);
    }
}

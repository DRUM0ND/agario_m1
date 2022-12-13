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
Plateau::generationJoueur(int t) //ajout variable pour spécifier la taille du joueur
{
    double x = (double)(rand() % ReglageJeu::LARGEUR_MONDE_JEU);
    double y = (double)(rand() % ReglageJeu::HAUTEUR_MONDE_JEU);
    std::cout << "valeur t : " << t << std::endl;
    //double t  = (double) (rand()%30);
    //std::cout << "valeur t apres : " << t << std::endl;

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

    std::cout << "CREATION JOUEUR" << std::endl;
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


void
Plateau::afficheJoueur(Joueur j, SDL_Renderer *renderer){
    if (j.estVisible){
        SDL_SetRenderDrawColor(renderer, j.r, j.g, j.b, 255);
        double xx = j.corps.x, yy = j.corps.y;
        convertToFenetreCoords(xx, yy);
        SDL_Rect cd = { (int)xx, (int)yy, (int)j.corps.w, (int)j.corps.h };
        SDL_RenderFillRect(renderer, &cd);
    }
}

void
Plateau::lacheDeLest(Joueur &joueur) {
    if (joueur.corps.w > 25) {
        joueur.diviseTaille();
        generationJoueur(joueur.corps.w);
    }
}
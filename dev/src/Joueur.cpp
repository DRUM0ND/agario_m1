
#include <SDL.h>
#include "Joueur.hpp"
#include <iostream>

Joueur::Joueur()
{
    
}

Joueur::Joueur(double x, double y, double taille): taille(taille)
{
    corps.x = x;
    corps.y = y;
    updateVitesse();
}


Joueur::~Joueur(){
}

void
Joueur::changeDirectionVitesse(double nx, double ny){
    double normeN = sqrt(nx*nx+ny*ny);
    double nxx = nx/normeN;
    double nyy = ny/normeN;
    double norme = sqrt(vx*vx+vy*vy);
    vx = nxx*norme;
    vy = nyy*norme;
    updateVitesse();
}

void Joueur::stop() {
	// FIXME si on met 0 tout crash
	vx = 0.0000000000000001;
	vy = 0.0000000000000001;
}


// Regulation de la norme de la vitesse en fonction du la taille.
void Joueur::updateVitesse()
{
    double norme = sqrt(vx*vx+vy*vy);
    double regulNorme = 25.0/corps.w * vboost;
    vx = (vx/norme)*regulNorme;
    vy = (vy/norme)*regulNorme;
}

bool
Joueur::collision(const Joueur joueur)
{
	SDL_Rect cd = {(int)corps.x, (int)corps.y, (int)corps.w, (int)corps.h };
	SDL_Rect cdj = {(int)joueur.corps.x, (int)joueur.corps.y, (int)joueur.corps.w, (int)joueur.corps.h };
	return SDL_HasIntersection(&cd, &cdj);
}

void
Joueur::mange(Joueur &joueur)
{
    joueur.estVisible = false;
    corps.w += (joueur.corps.w/100.0)*30.0;
    corps.h += (joueur.corps.h/100.0)*30.0;
    vx -= vx/50.0;
    vy -= vy/50.0;

}

void
Joueur::deplace(){
    corps.x += vx;
    corps.y += vy; 
    if (corps.x + corps.w > ReglageJeu::LARGEUR_MONDE_JEU)
    {
        corps.x = ReglageJeu::LARGEUR_MONDE_JEU - corps.w;
    }
    if (corps.y + corps.h > ReglageJeu::HAUTEUR_MONDE_JEU)
    {
        corps.y = ReglageJeu::HAUTEUR_MONDE_JEU -  corps.h;
    }
    if (corps.x < 0.0)
    {
        corps.x = 0.0;
    }
    if (corps.y < 0.0)
    {
        corps.y = 0.0;
    }
}

void
Joueur::incrementeVitesse(double varX, double varY){
    vx += varX;
    vy += varY;
}

bool
Joueur::peutManger(const Joueur &joueur){
    return corps.w > joueur.corps.w;
}

void
Joueur::diviseTaille() {
    corps.h /= 2;
    corps.w /= 2;
    updateVitesse();
}

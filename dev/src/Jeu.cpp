#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include "Jeu.hpp"
#include "ReglageJeu.hpp"

Jeu::Jeu(): joueurPrincipal(ReglageJeu::LARGEUR_FENETRE/2.0, ReglageJeu::HAUTEUR_FENETRE/2.0, 30.0)
{
	srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("AgarIO CPP",
                           SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           ReglageJeu::LARGEUR_FENETRE, ReglageJeu::HAUTEUR_FENETRE, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
    joueurPrincipal.r = 255; joueurPrincipal.g = 255;  joueurPrincipal.b = 255;
    joueurPrincipal.corps.w = 20.0;
    joueurPrincipal.corps.h = 20.0;
    joueurPrincipal.vboost = 2;

    joueurPrincipal.updateVitesse();
    plateau.generationJoueurs(ReglageJeu::NB_PLAYER);
}

Jeu::~Jeu(){
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Jeu::mouseInsidePlayerBody(double dx, double dy) {
	return dx > 0 && dy > 0 && dx < joueurPrincipal.corps.w && dy < joueurPrincipal.corps.h;
}

bool Jeu::tick()
{
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
    SDL_RenderClear(renderer);
    SDL_Event e;
    plateau.fenetreXorigin = joueurPrincipal.corps.x - (ReglageJeu::LARGEUR_FENETRE/2);
    plateau.fenetreYorigin = joueurPrincipal.corps.y - (ReglageJeu::HAUTEUR_FENETRE/2);
    for (int i = 0 ; i <=ReglageJeu::HAUTEUR_MONDE_JEU; i++)
    {
      if (i >= plateau.fenetreYorigin &&
          i <= plateau.fenetreYorigin+ReglageJeu::HAUTEUR_FENETRE && i%50==0){
          SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
          
          SDL_RenderDrawLine(renderer, 0-plateau.fenetreXorigin, i-plateau.fenetreYorigin,
                             ReglageJeu::LARGEUR_MONDE_JEU-plateau.fenetreXorigin, i-plateau.fenetreYorigin);
      }
    }
    for (int i = 0 ; i <= ReglageJeu::LARGEUR_MONDE_JEU; i++)
    {
      if (i >= plateau.fenetreXorigin &&
          i <= plateau.fenetreXorigin+ReglageJeu::LARGEUR_FENETRE && i%50==0){
          SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
          SDL_RenderDrawLine(renderer, i-plateau.fenetreXorigin,-plateau.fenetreYorigin,
                             i-plateau.fenetreXorigin, ReglageJeu::HAUTEUR_MONDE_JEU-plateau.fenetreYorigin);
      }
    }
    while ( SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_MOUSEMOTION:
            {
                double px = joueurPrincipal.corps.x, py = joueurPrincipal.corps.y;
                plateau.convertToFenetreCoords(px, py);
                double dx = e.motion.x - px;
                double dy = e.motion.y - py;
                if(mouseInsidePlayerBody(dx, dy))
                	joueurPrincipal.stop();
                else
                	joueurPrincipal.changeDirectionVitesse(dx, dy);
            }
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_SPACE)
                {
                    plateau.lacheDeLest(joueurPrincipal);
                    break;
                }
            case SDL_QUIT:
                return false;
        }
        
    }
    joueurPrincipal.deplace();
    plateau.afficheJoueur(joueurPrincipal,renderer);
    
    for (auto &i: plateau.joueurs){
        if (i.estVisible){
            i.deplace();
        }
        int applyRandomisation = rand()%100 == 1;
        if (applyRandomisation) {
        	double newRandomX = rand()%100-50;
        	double newRandomY = rand()%100-50;
        	i.changeDirectionVitesse(newRandomX, newRandomY);
		}
        
        if (i.collision(joueurPrincipal) && i.estVisible && joueurPrincipal.estVisible){
            if (i.peutManger(joueurPrincipal)){
                i.mange(joueurPrincipal);
            }else{
                joueurPrincipal.mange(i);
            }
        }
        if(plateau.estJoueurDansFenetre(i)){
            plateau.afficheJoueur(i,renderer);
        }
        if ((rand()%10000) == 0) {
            plateau.ajoutStaticElem(1);
        }
        
    }
    
    SDL_RenderPresent(renderer);
    return joueurPrincipal.estVisible;
}

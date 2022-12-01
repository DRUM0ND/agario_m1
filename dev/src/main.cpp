#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <SDL.h>

#include "Jeu.hpp"

int main(int argc, char *argv[])
{    
    Jeu jeu;
    srand (time(NULL));
    bool is_running = true;
    while (is_running) {
        is_running = jeu.tick();
    }
    
    return EXIT_SUCCESS;
}


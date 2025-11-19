
#ifndef BATALHA_H
#define BATALHA_H

#include "Personagem.h"

class Batalha {
public:
    // Retorna true se o heroi venceu, false se morreu ou fugiu
    static bool iniciarCombate(Personagem& heroi, Inimigo& inimigo);
};

class Jogo {
public:
    void iniciar();
};

#endif
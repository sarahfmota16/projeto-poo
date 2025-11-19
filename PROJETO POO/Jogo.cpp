#include <iostream>
#include <string>
#include <ctime>
#include "Habilidade.h"
#include "Personagem.h"
#include "Batalha.h"

using namespace std;

void Jogo::iniciar() {
    srand(time(0));

    cout << "Bem-vindo ao RPG de Turno no Terminal!\n";
    cout << "Escolha sua classe:\n1. Guerreiro\n2. Mago\n3. Arqueiro\nOpcao: ";

    int classe;
    cin >> classe;

    Personagem* jogador = nullptr;

    if (classe == 1) jogador = new Guerreiro("Arthur", 120, 20, 10, 5);
    else if (classe == 2) {
        jogador = new Mago("Merlin", 80, 10, 5, 40);
        jogador->adicionarHabilidade(Habilidade("Bola de Fogo", "Fogo", 35));
    }
    else jogador = new Arqueiro("Legolas", 100, 15, 8, 10);

    // Lista de inimigos
    vector<Inimigo*> inimigos;
    inimigos.push_back(new Inimigo("Goblin", "Monstro", "Terra", 50, 10, 2, 30));
    inimigos.push_back(new Inimigo("Orc", "Monstro", "Terra", 80, 15, 5, 60));
    inimigos.push_back(new Inimigo("Dragao de Gelo", "Chefe", "Gelo", 200, 25, 10, 500));

    // Loop principal
    for (Inimigo* inimigo : inimigos) {
        if (!jogador->estaVivo()) break;

        bool vitoria = Batalha::iniciarCombate(*jogador, *inimigo);
        if (!vitoria && !jogador->estaVivo()) break;

        if (vitoria) {
            cout << "\nPressione 1 para continuar para a proxima batalha: ";
            int dummy; cin >> dummy;
        }
    }

    cout << "\nFim de jogo. Obrigado por jogar!\n";

    // Libera memória
    delete jogador;
    for (auto i : inimigos) delete i;
}
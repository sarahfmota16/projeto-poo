#include <iostream>
#include <string>
#include <ctime>
#include "Habilidade.h"
#include "Personagem.h"
#include "Batalha.h"

using namespace std;

// Cores ANSI
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define BOLD    "\033[1m"

void Jogo::iniciar() {
    srand(time(0));

    cout << CYAN << "\n==============================================\n" << RESET;
    cout << BOLD << "           BEM-VINDO AO RPG DE TURNO!\n" << RESET;
    cout << CYAN << "==============================================\n\n" << RESET;

    cout << YELLOW << "Escolha sua classe:\n" << RESET;
    cout << "1. " << GREEN << "Guerreiro" << RESET << "\n";
    cout << "2. " << MAGENTA << "Mago" << RESET << "\n";
    cout << "3. " << CYAN << "Arqueiro" << RESET << "\n";
    cout << "4. " << RED << "Sair do jogo" << RESET << "\n";
    cout << YELLOW << "Opcao: " << RESET;

    int classe;
    cin >> classe;

    Personagem* jogador = nullptr;

    cout << "\n";

    if (classe == 4) {
        cout << RED << "\nVoce escolheu sair do jogo.\n" << RESET;
        cout << CYAN << "Encerrando programa...\n\n" << RESET;
        return; 
    }

    if (classe == 1) {
        cout << GREEN << ">> Voce escolheu o caminho do GUERREIRO!\n\n" << RESET;
        jogador = new Guerreiro("Arthur", 120, 20, 10, 5);
    }
    else if (classe == 2) {
        cout << MAGENTA << ">> Voce escolheu o caminho do MAGO!\n\n" << RESET;
        jogador = new Mago("Merlin", 80, 10, 5, 40);
        jogador->adicionarHabilidade(Habilidade("Bola de Fogo", "Fogo", 35));
    }
    else {
        cout << CYAN << ">> Voce escolheu o caminho do ARQUEIRO!\n\n" << RESET;
        jogador = new Arqueiro("Legolas", 100, 15, 8, 10);
    }

    // Lista de inimigos
    vector<Inimigo*> inimigos = {
        new Inimigo("Goblin", "Monstro", "Terra", 50, 10, 2, 30),
        new Inimigo("Orc", "Monstro", "Terra", 80, 15, 5, 60),
        new Inimigo("Dragao de Gelo", "Chefe", "Gelo", 200, 25, 10, 500)
    };

    // Loop principal
    for (Inimigo* inimigo : inimigos) {
        if (!jogador->estaVivo()) break;

        cout << CYAN << "\n==============================================\n" << RESET;
        cout << BOLD << "           NOVO INIMIGO NO CAMINHO!\n" << RESET;
        cout << CYAN << "==============================================\n" << RESET;

        bool vitoria = Batalha::iniciarCombate(*jogador, *inimigo);

        // Caso derrota
        if (!vitoria && !jogador->estaVivo()) break;

        // Vitória — pausa antes do próximo inimigo
        if (vitoria) {
            cout << GREEN << "\n>> Voce venceu esta batalha!\n" << RESET;
            cout << YELLOW << "Digite 1 para seguir para a proxima luta ou (0 para sair): " << RESET;

            int temp;
            cin >> temp;

            cout << "\n";

            if (temp == 0) {
                cout << RED << "\nVoce escolheu sair do jogo.\n" << RESET;
                cout << CYAN << "Encerrando programa...\n\n" << RESET;
                return;
            }
        }
    }

    cout << RED << "\n==============================================\n" << RESET;
    cout << BOLD << "                 FIM DE JOGO\n" << RESET;
    cout << RED << "==============================================\n" << RESET;
    cout << CYAN << "Obrigado por jogar!\n\n" << RESET;

    // Libera memória
    delete jogador;
    for (auto i : inimigos) delete i;
}

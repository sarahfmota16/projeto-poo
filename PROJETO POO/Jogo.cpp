#include <iostream>
#include <string>
#include <ctime>
#include "Habilidade.h"
#include "Personagem.h"
#include "Batalha.h"

using namespace std;

// Cores ANSI simples
#define RESET   "\033[0m"
#define RED     "\033[31m"   // Avisos / derrotas
#define GREEN   "\033[32m"   // Vitórias
#define YELLOW  "\033[33m"   // Menus / prompts
#define BLUE    "\033[34m"   // Títulos
#define BOLD    "\033[1m"

void Jogo::iniciar() {
    srand(static_cast<unsigned int>(time(0)));

    cout << BLUE << BOLD << "\n==============================\n" << RESET;
    cout << BOLD << "       BEM-VINDO AO RPG!\n" << RESET;
    cout << BLUE << BOLD << "==============================\n\n" << RESET;

    string nomeJogador;
    cout << YELLOW << "Digite o nome do seu personagem: " << RESET;
    getline(cin, nomeJogador);

    // Escolha de classe
    cout << YELLOW << "\nEscolha sua classe:\n" << RESET;
    cout << "1. Guerreiro\n";
    cout << "2. Mago\n";
    cout << "3. Arqueiro\n";
    cout << "4. Sair do jogo\n";
    cout << YELLOW << "Opcao: " << RESET;

    int classe;
    cin >> classe;

    Personagem* jogador = nullptr;

    if (classe == 4) {
        cout << RED << "\nVoce escolheu sair do jogo.\n" << RESET;
        cout << "Encerrando programa...\n\n";
        return;
    }

    if (classe == 1) {
        cout << "\n>> Voce escolheu o caminho do GUERREIRO!\n\n" << RESET;
        // Guerreiro: Mais vida (150), bom ataque físico
        jogador = new Guerreiro(nomeJogador, 150, 25, 15, 5);

        // Adicionando 3 Habilidades para o Guerreiro
        jogador->adicionarHabilidade(Habilidade("Golpe Devastador", "Terra", 40));
        jogador->adicionarHabilidade(Habilidade("Corte Flamejante", "Fogo", 35)); // Cobre fraqueza contra Gelo
        jogador->adicionarHabilidade(Habilidade("Investida de Escudo", "Neutro", 30));
    }
    else if (classe == 2) {
        cout << "\n>> Voce escolheu o caminho do MAGO!\n\n" << RESET;
        // Mago: Menos vida (90), muito ataque e mana
        jogador = new Mago(nomeJogador, 90, 10, 5, 50);

        // Adicionando 3 Habilidades para o Mago
        jogador->adicionarHabilidade(Habilidade("Bola de Fogo", "Fogo", 50));
        jogador->adicionarHabilidade(Habilidade("Lanca de Gelo", "Gelo", 45));
        jogador->adicionarHabilidade(Habilidade("Relampago", "Eletrico", 45));
    }
    else {
        cout << "\n>> Voce escolheu o caminho do ARQUEIRO!\n\n" << RESET;
        // Arqueiro: Equilibrado (110), rápido
        jogador = new Arqueiro(nomeJogador, 110, 18, 8, 15);

        // Adicionando 3 Habilidades para o Arqueiro
        jogador->adicionarHabilidade(Habilidade("Flecha Eletrica", "Eletrico", 45));
        jogador->adicionarHabilidade(Habilidade("Disparo Venenoso", "Terra", 35));
        jogador->adicionarHabilidade(Habilidade("Tiro Congelante", "Gelo", 35));
    }
    // Inimigos
    vector<Inimigo*> inimigos = {
        new Inimigo("Goblin", "Monstro", "Terra", 100, 10, 2, 30),
        new Inimigo("Orc", "Monstro", "Terra", 160, 15, 5, 60),
        new Inimigo("Dragao de Gelo", "Chefe", "Gelo", 400, 25, 10, 500)
    };

    // Loop principal
    for (Inimigo* inimigo : inimigos) {
        if (!jogador->estaVivo()) break;

        bool vitoria = Batalha::iniciarCombate(*jogador, *inimigo);

        if (!vitoria && !jogador->estaVivo()) break;

        if (vitoria) {
            cout << GREEN << "\n>> Voce venceu esta batalha!\n" << RESET;
            cout << YELLOW << "Digite 1 para seguir ou 0 para sair: " << RESET;

            int temp;
            cin >> temp;
            cout << "\n";

            if (temp == 0) {
                cout << RED << "\nVoce escolheu sair do jogo.\n" << RESET;
                cout << "Encerrando programa...\n\n";
                return;
            }
        }
    }

    cout << RED << "\n==============================\n" << RESET;
    cout << BOLD << "           FIM DE JOGO\n" << RESET;
    cout << RED << "==============================\n" << RESET;
    cout << "Obrigado por jogar!\n\n";

    // Libera memória
    delete jogador;
    for (auto i : inimigos) delete i;
}

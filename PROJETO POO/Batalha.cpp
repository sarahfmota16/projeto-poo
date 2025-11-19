#include <iostream>
#include <ctime>
#include "Personagem.h"
#include "Batalha.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define BOLD    "\033[1m"

bool Batalha::iniciarCombate(Personagem& heroi, Inimigo& inimigo) {

    cout << CYAN << "\n==============================================\n" << RESET;
    cout << BOLD << "        !!! INIMIGO ENCONTRADO !!!\n" << RESET;
    cout << MAGENTA << "              " << inimigo.getNome() << "\n" << RESET;
    cout << CYAN << "==============================================\n" << RESET;

    int rodada = 1;

    while (heroi.estaVivo() && inimigo.estaVivo()) {

        cout << YELLOW << "\n---------------[ RODADA " << rodada << " ]---------------\n" << RESET;

        // Status do herói
        cout << GREEN << "\n=== STATUS DO HEROI ===\n" << RESET;
        heroi.mostrarStatus();

        // Status do inimigo
        cout << RED << "\n=== STATUS DO INIMIGO ===\n" << RESET;
        cout << inimigo.getNome() << " (HP: "
            << inimigo.getPV() << "/" << inimigo.getPVMax() << ")\n";

        // MENU
        cout << CYAN << "\n---------- SUA VEZ ----------\n" << RESET;
        cout << "1. " << GREEN << "Atacar" << RESET << "\n";
        cout << "2. " << YELLOW << "Defender" << RESET << "\n";
        cout << "3. " << RED << "Fugir" << RESET << "\n";
        cout << CYAN << "Escolha: " << RESET;

        int escolha;
        cin >> escolha;

        cout << "\n";

        if (escolha == 3) {
            cout << RED << "➡ Voce fugiu da batalha!\n" << RESET;
            return false;
        }

        if (escolha == 2) {
            cout << YELLOW << "[Você adotou postura defensiva!]\n" << RESET;
            heroi.defender();
        }

        if (escolha == 1) {
            heroi.atacar(inimigo);
        }

        if (!inimigo.estaVivo()) break;

        // Turno do inimigo
        cout << RED << "\n-------------[ VEZ DO INIMIGO ]-------------\n" << RESET;
        inimigo.atacar(heroi);

        if (!heroi.estaVivo()) break;

        rodada++;
    }

    // RESULTADO FINAL
    if (heroi.estaVivo()) {
        cout << GREEN << "\n==============================================\n";
        cout << "               *** VITORIA! ***\n";
        cout << "==============================================\n" << RESET;

        heroi.ganharXP(inimigo.recompensaXP);
        return true;
    }
    else {
        cout << RED << "\n==============================================\n";
        cout << "               *** GAME OVER ***\n";
        cout << "==============================================\n";
        cout << "Voce foi derrotado...\n" << RESET;
        return false;
    }
}

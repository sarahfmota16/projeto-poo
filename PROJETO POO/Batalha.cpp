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

    cout << CYAN << "\n======================================\n" << RESET;
    cout << BOLD << "   INIMIGO ENCONTRADO, PREPARE-SE... \n" << RESET;
    cout << CYAN << "======================================\n" << RESET;

    int rodada = 1;

    while (heroi.estaVivo() && inimigo.estaVivo()) {

        // ============================================================
        // ➤ EXTRA D – Estados: aplicar veneno, queimadura etc no turno
        // ============================================================
        heroi.atualizarEstados();
        inimigo.atualizarEstados();

        // Se o herói está atordoado, ele perde turno
        if (heroi.estaStunado()) {
            cout << YELLOW << "\n " << heroi.getNome() << " esta atordoado e perdeu o turno!\n" << RESET;

            // Inimigo faz o turno sozinho
            cout << RED << "\n-------------[ VEZ DO INIMIGO ]-------------\n" << RESET;
            inimigo.atacar(heroi);

            rodada++;
            continue; // Volta para o começo do while (próxima rodada)
        }

        // ============================================================

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
        cout << "1. Atacar\n2. Defender\n3. Fugir\n4. Usar habilidade\nEscolha: ";


        int escolha;
        cin >> escolha;

        cout << "\n";

        if (escolha == 3) {
            cout << RED << "➡ Voce fugiu da batalha!\n" << RESET;
            return false;
        }

        if (escolha == 2) {
            cout << YELLOW << "[Voce adotou postura defensiva!]\n" << RESET;
            heroi.defender();
        }

        if (escolha == 1) {
            heroi.atacar(inimigo);

            // EXEMPLO: 20% de chance de aplicar Poison ao inimigo
            if (rand() % 100 < 20) {
                cout << YELLOW << ">> O inimigo foi ENVENENADO!\n" << RESET;
                inimigo.adicionarEstado("Poison", 3);
            }
        }

        if (escolha == 4) {
            if (heroi.habilidades.empty()) {
                cout << "\nVoce nao possui habilidades!\n";
            }
            else {
                cout << "\n--- HABILIDADES DISPONIVEIS ---\n";

                for (int i = 0; i < heroi.habilidades.size(); i++) {
                    cout << i + 1 << ". " << heroi.habilidades[i].nome
                        << " | Tipo: " << heroi.habilidades[i].tipo
                        << " | Dano Base: " << heroi.habilidades[i].danoBase << "\n";
                }

                cout << "Escolha: ";
                int idx;
                cin >> idx;
                idx--;

                if (idx >= 0 && idx < heroi.habilidades.size()) {
                    heroi.usarHabilidade(heroi.habilidades[idx], inimigo);

                    // EXEMPLO: habilidades aplicam Burn
                    if (rand() % 100 < 25) {
                        cout << YELLOW << ">> O inimigo sofreu QUEIMADURA!\n" << RESET;
                        inimigo.adicionarEstado("Burn", 2);
                    }
                }
                else {
                    cout << "Escolha invalida! Perdeu a vez.\n";
                }
            }
        }


        if (!inimigo.estaVivo()) break;

        // Turno do inimigo
        if (inimigo.estaStunado()) {
            cout << RED << "\n " << inimigo.getNome() << " está atordoado e perdeu o turno!\n" << RESET;
            rodada++;
            continue;
        }

        cout << RED << "\n-------------[ VEZ DO INIMIGO ]-------------\n" << RESET;
        inimigo.atacar(heroi);

        if (rand() % 100 < 10) {
            cout << YELLOW << ">> Você foi ATORDOADO e perderá o próximo turno!\n" << RESET;
            heroi.adicionarEstado("Stun", 1);
        }

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
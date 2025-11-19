#include <iostream>
#include <ctime>
#include "Personagem.h"
#include "Batalha.h"





bool Batalha::iniciarCombate(Personagem& heroi, Inimigo& inimigo) {
            cout << "\n========================================\n";
            cout << "!!! INIMIGO ENCONTRADO: " << inimigo.getNome() << " !!!\n";
            cout << "========================================\n";

            int rodada = 1;
            while (heroi.estaVivo() && inimigo.estaVivo()) {
                cout << "\n--- RODADA " << rodada << " ---\n";
                heroi.mostrarStatus();
                cout << "Inimigo: " << inimigo.getNome() << " (HP: " << inimigo.getPV() << "/" << inimigo.getPVMax() << ")\n";

                // MENU INTERATIVO
                cout << "\nSua vez! O que deseja fazer?\n";
                cout << "1. Atacar\n2. Fugir\nEscolha: ";

                int escolha;
                cin >> escolha;

                if (escolha == 2) {
                    cout << "Voce fugiu da batalha!\n";
                    return false;
                }

                // 1. Turno do Jogador
                heroi.atacar(inimigo);

                if (!inimigo.estaVivo()) break;

                // 2. Turno do Inimigo (Simples delay pode ser adicionado com sleep se quiser)
                cout << "\n[Turno do Inimigo]\n";
                inimigo.atacar(heroi);

                if (!heroi.estaVivo()) break;

                rodada++;
            }

            if (heroi.estaVivo()) {
                cout << "\n*** VITORIA! ***\n";
                heroi.ganharXP(inimigo.recompensaXP);
                return true;
            }
            else {
                cout << "\n*** GAME OVER ***\nVoce foi derrotado...\n";
                return false;
            }



}


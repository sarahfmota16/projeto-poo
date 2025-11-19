#include <iostream>
#include "Batalha.h"

using namespace std;

int main() {
    Jogo jogo;

    cout << "==============================\n";
    cout << "      RPG DE TERMINAL        \n";
    cout << "==============================\n\n";

    jogo.iniciar();   // inicia o jogo

    cout << "\nPrograma finalizado.\n";
    return 0;
}
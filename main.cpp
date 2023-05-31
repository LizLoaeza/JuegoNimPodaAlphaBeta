/*
    Juego de los palitos, hecho para la materia de inteligencia artificial.
    Por Elizabeth Loaeza Morales.
*/

#include <iostream>
#include <limits>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int maxDepht = 10;
const int infinte = numeric_limits<int>::max();
int sticks;
int actPlayer;

vector<pair<int, int>> getTree(int sticks, int actPlayer) {
    vector<pair<int, int>> branches;
    for (int i = 1; i <= 3; i++) {
        if (i <= sticks) {
            branches.push_back(make_pair(sticks - i, actPlayer == 1 ? 2 : 1));
        }
    }
    return branches;
}

int alphaBeta(int sticks, int actPlayer, int depth, int alpha, int beta, bool isAI) {
    if (sticks == 0) {
        return isAI ? 1 : -1;
    }
    if (depth == 0) {
        return 0;
    }
    vector<pair<int, int>> branches = getTree(sticks, actPlayer);
    if (isAI) {
        int bestScore = -infinte;
        for (const auto& v : branches) {
            int score = alphaBeta(v.first, v.second, depth - 1, alpha, beta, false);
            bestScore = max(bestScore, score);
            alpha = max(alpha, score);
            if (beta <= alpha) {
                break;
            }
        }
        return bestScore;
    } else {
        int bestScore = infinte;
        for (const auto& v : branches) {
            int score = alphaBeta(v.first, v.second, depth - 1, alpha, beta, true);
            bestScore = min(bestScore, score);
            beta = min(beta, score);
            if (beta <= alpha) {
                break;
            }
        }
        return bestScore;
    }
}

int ia(int stick) {
    int m = -infinte;
    int bestMove = 1;
    vector<pair<int, int>> branches = getTree(stick, 1);
    for (const auto& v : branches) {
        int t = alphaBeta(v.first, v.second, maxDepht, -infinte, infinte, false);
        if (t > m) {
            m = t;
            bestMove = stick - v.first;
        }
    }
    return bestMove;
}

int main() {
    srand(time(NULL));
    int sticks = 12 + rand() % 9;
    int actPlayer = rand() % 2 + 1;

    cout << "Palitos iniciales: " << sticks << endl;
    cout << (actPlayer == 1 ? "Humano" : "IA") << " inicia el juego." << endl;

    while (sticks > 1) {
        cout << "Palitos restantes: " << sticks << endl;

        int sticksOut;
        if (actPlayer == 1) {
            cout << "Humano, ingrese el numero de palitos que desea tomar, puede tomar solo 1, 2 o 3: ";
            cin >> sticksOut;
            while (sticksOut < 1 || sticksOut > 3 || sticksOut > sticks) {
                cout << " No sabe leer? ingrese un numero valido, puede tomar solo 1, 2 o 3: ";
                cin >> sticksOut;
            }
            sticks -= sticksOut;
            actPlayer = 2;
        } else {
            sticksOut = ia(sticks);
            sticks -= sticksOut;
            cout << "La IA toma " << sticksOut << " palito(s)." << endl;
            actPlayer = 1;
        }

        if (sticks == 1) {
            cout << (actPlayer == 1 ? "IA" : "Humano") << " gana!" << endl;
            break;
        }
    }

    return 0;
}

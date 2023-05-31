#include <iostream>
#include "Board.h"
#include "Player.h"
using namespace std;

int main() {
    Player* player = new Player('X');
    Board board;

    player->makeMove(board);
    board.display();
    player->makeMove(board);

    board.display();

    cout << "Hello world!" << endl;
    return 0;
}

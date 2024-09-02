#include "data/game_process.h"

int main() {
    // Установка размеров консольного окна игры
    system("mode con cols=200 lines=60");
    // Для правильного вывода русских символов в консоль
    setlocale(LC_ALL, "Russian");

    Game game;
    game.BeginGame();

    return 0;
}

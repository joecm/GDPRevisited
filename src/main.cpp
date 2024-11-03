#include "../include/Game.hpp"

int main() {
    Game game;

    while (!(game.GetWindow()->IsDone())) // true = end game
    {
        // game.HandleInput();
        game.Update();
        game.Render();
        // game.RestartClock();
        game.LateUpdate();
    }

    return 0;
}
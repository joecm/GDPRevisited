#ifndef GAME_H
#define GAME_H

#include "Window.hpp"

// #include "EventManager.hpp"
#include "StateManager.hpp"


class Game
{
    public:
        Game();
        ~Game();

        // void HandleInput();
        void Update();
        void Render();

        Window* GetWindow();
        
        sf::Time GetElapsed();
        // void RestartClock();

        // void MoveSprite(EventDetails* l_details);
        void LateUpdate();

    private:
        Window m_window;
        sf::Clock m_clock;
        // sf::Texture m_texture;
        // sf::Sprite m_sprite;
        sf::Time m_elapsed;
        // sf::Font font;
        // sf::Text overlayText;
        // sf::View vHud;
        SharedContext m_context;
        StateManager m_stateManager;
        

        void RestartClock();

        
        //sf::View gameView;
        //sf::View hudView;
};

#endif
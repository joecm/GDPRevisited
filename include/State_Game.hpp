#ifndef __STATE_GAME_H__
#define __STATE_GAME_H__

#include "BaseState.hpp"
#include "EventManager.hpp"

class State_Game : public BaseState
{
public:
    State_Game(StateManager* l_StateMgr);
    ~State_Game();

    void OnCreate() final;
    void OnDestroy() final;

    void Activate() final;
    void Deactivate() final;

    void Update(const sf::Time& l_time) final;
    void Draw() final;

    void MainMenu(EventDetails* l_details);
    void Pause(EventDetails* l_details);
private:
    sf::Texture m_Texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_increment;
    sf::Font m_font;
    sf::Text m_deltaTime;
};

#endif // __STATE_GAME_H__
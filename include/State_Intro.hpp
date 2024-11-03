#ifndef __STATE_INTRO_H__
#define __STATE_INTRO_H__

#include "BaseState.hpp"
#include "EventManager.hpp"

class State_Intro : public BaseState
{
public:
    State_Intro(StateManager* l_stateManager);
    ~State_Intro();

    void OnCreate() final;
    void OnDestroy() final;

    void Activate() final;
    void Deactivate() final;

    void Update(const sf::Time& l_time) final;
    void Draw() final;

    void Continue(EventDetails* l_details);
private:
    sf::Texture m_introTexture;
    sf::Sprite m_introSprite;
    sf::Font m_font;
    sf::Text m_text;
    sf::Text m_deltaTime;
    float m_timePassed;
};

#endif // __STATE_INTRO_H__
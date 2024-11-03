#ifndef __STATE_CREDITS_H__
#define __STATE_CREDITS_H__

#include "BaseState.hpp"
#include "EventManager.hpp"

class State_Credits : public BaseState
{
public:
    State_Credits(StateManager* l_stateManager);
    ~State_Credits();

    void OnCreate() final;
    void OnDestroy() final;

    void Activate() final;
    void Deactivate() final;

    void Update(const sf::Time& l_time) final;
    void Draw() final;

    void Continue(EventDetails* l_details);
private:
    sf::Texture m_creditTexture;
    sf::Sprite m_creditSprite;
    sf::Font m_font;
    sf::Text m_text;
    float m_timePassed;
};

#endif // __STATE_CREDITS_H__
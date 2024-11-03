#ifndef __STATE_MAINMENU_H__
#define __STATE_MAINMENU_H__

#include "BaseState.hpp"
#include "EventManager.hpp"

class State_MainMenu : public BaseState
{
public:
    State_MainMenu(StateManager* l_stateManager);
    ~State_MainMenu();

    void OnCreate() final;
    void OnDestroy() final;

    void Activate() final;
    void Deactivate() final;

    void Update(const sf::Time& l_time) final;
    void Draw() final;

    void MouseClick(EventDetails* l_details);

private:
    sf::Font m_font;
    sf::Text m_text;

    sf::Vector2f m_buttonSize;
    sf::Vector2f m_buttonPos;
    unsigned int m_buttonPadding;

    sf::RectangleShape m_rects[3];
    sf::Text m_labels[3];
};

#endif // __STATE_MAINMENU_H__
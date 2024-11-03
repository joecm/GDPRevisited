#ifndef __STATE_PAUSED_H__
#define __STATE_PAUSED_H__

#include "BaseState.hpp"
#include "EventManager.hpp"

class State_Paused : public BaseState
{
    public:
        State_Paused(StateManager* l_stateManager);
        ~State_Paused();

        void OnCreate() final;
        void OnDestroy() final;

        void Activate() final;
        void Deactivate() final;

        void Update(const sf::Time& l_time) final;
        void Draw() final;
        // Callbacks
        void Unpause(EventDetails* l_details);
    private:
        sf::Font m_font;
        sf::Text m_text;
        sf::RectangleShape m_rect;
};

#endif // __STATE_PAUSED_H__
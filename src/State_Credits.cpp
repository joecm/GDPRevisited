#include "../include/State_Credits.hpp"
#include "../include/StateManager.hpp"
#include "../include/Utilities.hpp"

State_Credits::State_Credits(StateManager* l_stateManager) : BaseState(l_stateManager)
{}

State_Credits::~State_Credits()
{}

void State_Credits::OnCreate() 
{
    m_timePassed=0.0;
    sf::Vector2u windowSize = m_StateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
    // Image Intro State
    m_creditTexture.loadFromFile(Utils::GetWorkingDirectory()+"../graphics/Mushroom.png");
    m_creditSprite.setTexture(m_creditTexture);
    m_creditSprite.setOrigin(sf::Vector2f(m_creditTexture.getSize())/2.0f);
    m_creditSprite.setPosition(windowSize.x/2.0, windowSize.y/2.0);

    // Text Credits State
    m_font.loadFromFile(Utils::GetWorkingDirectory()+ "../graphics/arial.ttf");
    m_text.setFont(m_font);
    m_text.setString("Jose Antonio COSTA DE MOYA");
    m_text.setCharacterSize(15);
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left+(textRect.width/2.0f), textRect.top + (textRect.height/2.0f));
    m_text.setPosition(windowSize.x/2.0f, 0.0f);

    // Load Credit State Events
    EventManager* evMgr = m_StateMgr->GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::CREDITS, "Key_Escape", &State_Credits::Continue, this);
}

void State_Credits::OnDestroy()
{
    EventManager* evMgr = m_StateMgr->GetContext()->m_eventManager;
    evMgr->RemoveCallback(StateType::CREDITS, "Key_Escape");
}

void State_Credits::Activate() {}

void State_Credits::Deactivate() {}

void State_Credits::Update(const sf::Time& l_time)
{
    if (m_timePassed < 5.0)
    {
        m_timePassed += l_time.asSeconds();
        m_text.setPosition(m_text.getPosition().x, m_text.getPosition().y + (48 * l_time.asSeconds()));
    }
    
}

void State_Credits::Draw()
{
    sf::RenderWindow* window = m_StateMgr->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_creditSprite); 
    window->draw(m_text);
}

void State_Credits::Continue(EventDetails* l_details)
{
    (void) l_details;
    if (m_timePassed > 5.0f)
    {
        m_StateMgr->SwitchTo(StateType::MAIN_MENU);
        m_StateMgr->Remove(StateType::CREDITS);
    }
}
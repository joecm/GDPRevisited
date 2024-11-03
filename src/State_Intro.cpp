#include "../include/State_Intro.hpp"
#include "../include/StateManager.hpp"
#include "../include/Utilities.hpp"

State_Intro::State_Intro(StateManager* l_stateManager) : BaseState(l_stateManager)
{}

State_Intro::~State_Intro(){}

void State_Intro::OnCreate() 
{
    m_timePassed = 0.0;
    sf::Vector2u windowSize = m_StateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
    // Image Intro State
    m_introTexture.loadFromFile(Utils::GetWorkingDirectory() + "../graphics/intro.png");
    m_introSprite.setTexture(m_introTexture);
    m_introSprite.setOrigin(m_introTexture.getSize().x/2.0f, m_introTexture.getSize().y/2.0f);
    m_introSprite.setPosition(windowSize.x/2.0f, 0.0f);

    // Text Intro State
    m_font.loadFromFile(Utils::GetWorkingDirectory() + "../graphics/arial.ttf");
    m_text.setFont(m_font);
    m_text.setString("Press SPACE to continue");
    m_text.setCharacterSize(15);
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left+ (textRect.width/2.0f), textRect.top + (textRect.height/2.0f));
    m_text.setPosition(windowSize.x/2.0f, windowSize.y/2.0f);

    // Text Frame Time
    m_deltaTime.setFont(m_font);
    m_deltaTime.setCharacterSize(12);
    m_deltaTime.setPosition(sf::Vector2f(10.f,10.f));
    m_deltaTime.setFillColor(sf::Color::White);

    // Load Intro State Events    
    EventManager* evMgr = m_StateMgr->GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::INTRO, "Intro_Continue", &State_Intro::Continue, this);
}

void State_Intro::OnDestroy()
{
    EventManager* evMgr = m_StateMgr->GetContext()->m_eventManager;
    evMgr->RemoveCallback(StateType::INTRO, "Intro_Continue");
}

void State_Intro::Activate() {}
void State_Intro::Deactivate() {}

void State_Intro::Update(const sf::Time& l_time)
{
    
    m_deltaTime.setString("frame time: " +std::to_string(l_time.asSeconds()) + " .s \n");
    if (m_timePassed < 5.0 )
    {
        m_timePassed += l_time.asSeconds();
        m_introSprite.setPosition(m_introSprite.getPosition().x, m_introSprite.getPosition().y + (48 * l_time.asSeconds()));
    }
}

void State_Intro::Draw() 
{
    sf::RenderWindow* window = m_StateMgr->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_introSprite);
    if (m_timePassed >= 5.0f)
    {
        window->draw(m_text);
    }
    window->draw(m_deltaTime);

}

void State_Intro::Continue (EventDetails* l_details)
{
    (void) l_details;
    if (m_timePassed > 5.0f )
    {
        m_StateMgr->SwitchTo(StateType::MAIN_MENU);
        m_StateMgr->Remove(StateType::INTRO);
    }
}
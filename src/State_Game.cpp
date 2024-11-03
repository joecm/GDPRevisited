#include "../include/State_Game.hpp"
#include "../include/StateManager.hpp"
#include "../include/Utilities.hpp"

State_Game::State_Game(StateManager* l_StateMgr) : BaseState(l_StateMgr)
{
}

State_Game::~State_Game(){}

void State_Game::OnCreate() 
{
    m_Texture.loadFromFile(Utils::GetWorkingDirectory() + "../graphics/Mushroom.png");
    m_sprite.setTexture(m_Texture);
    m_sprite.setPosition(0.0f, 0.0f);
    m_increment=sf::Vector2f(400.0f, 400.0f);

    m_font.loadFromFile(Utils::GetWorkingDirectory() + "../graphics/arial.ttf");
    m_deltaTime.setFont(m_font);
    m_deltaTime.setCharacterSize(15);
    m_deltaTime.setPosition(sf::Vector2f(5.f, 20.f));


    EventManager* evMgr = m_StateMgr->GetContext()->m_eventManager;
    // Callbacks
    evMgr->AddCallback(StateType::GAME, "Key_Escape", &State_Game::MainMenu, this);
    evMgr->AddCallback(StateType::GAME, "Key_P", &State_Game::Pause, this);
}

void State_Game::OnDestroy()
{
    EventManager* evMgr = m_StateMgr->GetContext()->m_eventManager;
    evMgr->RemoveCallback(StateType::GAME, "Key_Escape");
    evMgr->RemoveCallback(StateType::GAME, "key_P");
}

void State_Game::Activate() {}
void State_Game::Deactivate() {}


void State_Game::Update(const sf::Time& l_time) // l_time = m_elapsed (delta time o time step)
{

    sf::Vector2u l_windSize = m_StateMgr->GetContext()->m_wind->GetWindowSize();
    sf::Vector2u l_textSize = m_Texture.getSize();

    if ((m_sprite.getPosition().x > l_windSize.x -l_textSize.x && m_increment.x > 0)
        ||  (m_sprite.getPosition().x < 0 && m_increment.x <0))
    {
        m_increment.x = -m_increment.x;
    }
    
    if ((m_sprite.getPosition().y > l_windSize.y -l_textSize.y && m_increment.y > 0)
        ||  (m_sprite.getPosition().y < 0 && m_increment.y <0))
    {
        m_increment.y = -m_increment.y;
    }

    m_sprite.setPosition(m_sprite.getPosition().x + (m_increment.x * l_time.asSeconds()),
                        m_sprite.getPosition().y + (m_increment.y * l_time.asSeconds()));

    m_deltaTime.setString("Step Time: " + std::to_string(l_time.asSeconds()));
}
void State_Game::Draw() 
{
    m_StateMgr->GetContext()->m_wind->GetRenderWindow()->draw(m_sprite);
    m_StateMgr->GetContext()->m_wind->GetRenderWindow()->draw(m_deltaTime);
}
 // Callbacks 
void State_Game::MainMenu(EventDetails* l_details)
{
    (void) l_details;
    m_StateMgr->SwitchTo(StateType::MAIN_MENU);
}

void State_Game::Pause(EventDetails* l_details)
{
    (void) l_details;
    m_StateMgr->SwitchTo(StateType::PAUSED);
}

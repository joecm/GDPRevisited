#include "../include/Game.hpp"
#include "../include/Utilities.hpp"
#include <iostream>
#include <sstream>


Game::Game() : m_window("Chapter 5", sf::Vector2u(800,600)), m_elapsed{sf::Time::Zero}, 
m_stateManager(&m_context) 
{
    m_clock.restart();
    srand(time(nullptr));
    
    /*
    if (!m_texture.loadFromFile(Utils::GetWorkingDirectory() + "../graphics/Mushroom.png"))
        throw std::runtime_error("file not found");
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture.getSize().x/2, m_texture.getSize().y/2);
    m_sprite.setPosition(0,0);
    */
    m_context.m_wind = &m_window;
    m_context.m_eventManager =m_window.GetEventManager();
    m_stateManager.SwitchTo(StateType::INTRO);

    /*
    // Bind y CallBack
    m_window.GetEventManager()->AddCallback("Move",&Game::MoveSprite,this);
    */
    /*
    // Text Debug
    if (!font.loadFromFile(Utils::GetWorkingDirectory() + "../graphics/arial.ttf"))
        throw std::runtime_error("file not found");
    
    overlayText.setFont(font);
    overlayText.setCharacterSize(10);
    overlayText.setFillColor(sf::Color::White);
    overlayText.setPosition(50,50);

    // HUD
    */
}

Game::~Game()
{

}

/*
void Game::HandleInput()
{
    m_window.Update();
    m_stateManager.Update(m_elapsed);
}
*/

void Game::Update()
{
    /*
    float frameTime= 1.0f/60.0f;
    if (m_elapsed.asSeconds() >=frameTime)
    {
        // do something
        
        m_elapsed-=sf::seconds(frameTime);
    }
    */
    m_window.Update();
    m_stateManager.Update(m_elapsed);
}

void Game::Render()
{
    m_window.BeginDraw();
    //m_window.GetRenderWindow()->setView(gameView);
    m_stateManager.Draw();
    /*
    m_window.GetRenderWindow()->draw(overlayText);
    m_window.GetRenderWindow()->draw(m_sprite);
    */
    m_window.EndDraw();
}

Window* Game::GetWindow()
{
    return &m_window;
}

sf::Time Game::GetElapsed()
{
    return m_clock.getElapsedTime();
    // return m_elapsed;
}

void Game::RestartClock()
{
    // m_elapsed += m_clock.restart();
    m_elapsed = m_clock.restart();
}

/*
void Game::MoveSprite(EventDetails* l_details)
{
    (void) l_details;

    sf::Vector2i mousepos=m_window.GetEventManager()->GetMousePos(m_window.GetRenderWindow());
    m_sprite.setPosition(mousepos.x, mousepos.y);
    std::stringstream ssPos;
    ssPos << "Moving sprite to: " << mousepos.x << ":" << mousepos.y << std::endl;
    overlayText.setString(ssPos.str());
}
*/
void Game::LateUpdate() {
    m_stateManager.ProcessRequest();
    RestartClock();
}
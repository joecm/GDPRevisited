#include "../include/State_MainMenu.hpp"
#include "../include/StateManager.hpp"
#include "../include/Utilities.hpp"

State_MainMenu::State_MainMenu(StateManager* l_stateManager) : BaseState(l_stateManager)
{

}

State_MainMenu::~State_MainMenu()
{

}

void State_MainMenu::OnCreate()
{
    m_font.loadFromFile(Utils::GetWorkingDirectory() + "../graphics/arial.ttf");
    m_text.setFont(m_font);
    m_text.setString(sf::String("MAIN MENU"));
    m_text.setCharacterSize(18);

    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left+(textRect.width/2.0f),
                    textRect.top+(textRect.height/2.0f));
    m_text.setPosition(400.0f,100.0f);

    m_buttonSize.x = 300.0f; m_buttonSize.y=32.0f;

    m_buttonPos = sf::Vector2f(400.0f,200.0f);
    m_buttonPadding = 4; // 4 px

    std::string str[3];
    str[0] = "PLAY";
    str[1] = "CREDITS";
    str[2] = "EXIT";

    for (int i = 0; i < 3; ++i)
    {
        sf::Vector2f buttonPosition (m_buttonPos.x, 
                                     m_buttonPos.y + (i*(m_buttonSize.y + m_buttonPadding )));
        m_rects[i].setSize(m_buttonSize);
        m_rects[i].setFillColor(sf::Color::Red);

        m_rects[i].setOrigin(m_buttonSize.x/2.0f, m_buttonSize.y/2.0f);
        m_rects[i].setPosition(buttonPosition);

        m_labels[i].setFont(m_font);
        m_labels[i].setString(sf::String(str[i]));
        m_labels[i].setCharacterSize(12);

        sf::FloatRect rect = m_labels[i].getLocalBounds();
        m_labels[i].setOrigin(rect.left+rect.width/2.0f, rect.top + rect.height / 2.0f);

        m_labels[i].setPosition(buttonPosition);
    }
    EventManager* evMgr = m_StateMgr->GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::MAIN_MENU, "Mouse_Left", &State_MainMenu::MouseClick, this);
}

void State_MainMenu::OnDestroy()
{
    EventManager* evMgr = m_StateMgr->GetContext()->m_eventManager;
    evMgr->RemoveCallback(StateType::MAIN_MENU, "Mouse_Left");
}

void State_MainMenu::Activate()
{
    if (m_StateMgr->HasState(StateType::GAME) && 
        m_labels[0].getString() =="PLAY")
    {
        m_labels[0].setString(sf::String("RESUME"));
        sf::FloatRect rect = m_labels[0].getLocalBounds();
        m_labels[0].setOrigin(rect.left + rect.width/2.0F, rect.top + rect.height/2.0F);
    }
    
}

void State_MainMenu::Deactivate() {}

void State_MainMenu::Update(const sf::Time& l_time) { (void) l_time; }

void State_MainMenu::MouseClick(EventDetails* l_details)
{
    // get mouse position
    sf::Vector2i mousePos = l_details->m_mouse;

    float halfX = m_buttonSize.x / 2.0f;
    float halfY = m_buttonSize.y / 2.0f;

    for (int i = 0; i < 3; ++i)
    {
        if (mousePos.x >= m_rects[i].getPosition().x - halfX &&
            mousePos.x <= m_rects[i].getPosition().x + halfX &&
            mousePos.y >= m_rects[i].getPosition().y - halfY &&
            mousePos.y <= m_rects[i].getPosition().y + halfY)
        {
            if (i == 0)
            {
                m_StateMgr->SwitchTo(StateType::GAME);
            } else if (i == 1)
            {
                // Credits State
                m_StateMgr->SwitchTo(StateType::CREDITS); 
            } else if (i == 2)
            {
                m_StateMgr->GetContext()->m_wind->Close();
            }
        }
    }
}

void State_MainMenu::Draw()
{
    sf::RenderWindow* window = m_StateMgr->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_text);
    for (int i = 0; i < 3; i++)
    {
        window->draw(m_rects[i]);
        window->draw(m_labels[i]);
    }
}
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "EventManager.hpp"

class Window
{
public:
    Window(); // default constructor
    Window (const std::string& title, const sf::Vector2u& size );
    ~Window();
    
    void BeginDraw();
    void EndDraw();
    
    void Update();

    bool IsDone();
    bool IsFullScreen();
    bool IsFocused();

    void ToggleFullScreen(EventDetails* l_details);
    void Close(EventDetails* l_details=nullptr);

    sf::RenderWindow* GetRenderWindow();
    EventManager* GetEventManager();
        
    sf::Vector2u GetWindowSize();

    

private:
    sf::RenderWindow m_window;
    std::string m_windowTitle;
    EventManager m_eventManager;
    sf::Vector2u m_windowSize;
    bool m_isDone;
    bool m_isFullScreen;
    bool m_isFocused;

    void Setup (const std::string& title, const sf::Vector2u& size);
    void Create ();
    //sf::View viewDefault;
};

#endif
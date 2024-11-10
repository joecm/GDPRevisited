#include "../include/Window.hpp"
#include <iostream>

Window::Window()
{
    Setup("Window", sf::Vector2u(640,480));
}

Window::Window(const std::string& title, const sf::Vector2u& size)
{
    Setup(title, size);
}

Window::~Window()
{
    m_window.close();  
}

void Window::Setup(const std::string& title, const sf::Vector2u& size) 
{
    m_windowTitle=title;
    m_windowSize=size;
    m_isFullScreen=false;
    m_isDone=false;
    m_isFocused=true;
    // m_window.setFramerateLimit(60); // Set frame rate limit

    // AddCallbacks
    m_eventManager.AddCallback(StateType(0), "Fullscreen_toggle" , &Window::ToggleFullScreen, this);
    m_eventManager.AddCallback(StateType(0), "Window_close", &Window::Close, this);

    Create();
}

void Window::Create()
{
    sf::Uint32 style = sf::Style::Default;
    
    if(m_isFullScreen) 
    {
        style = sf::Style::Fullscreen;
    }
    // auto style = (m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, style);
    /*
    // View
    viewDefault=m_window.getDefaultView();
    const sf::FloatRect rect=viewDefault.getViewport();
    std::cout << " Origin(" << rect.left << ", " << rect.top << ") " \
              << " WxH (" << rect.width << ", " << rect.height << ") " << std::endl;
    
    sf::Vector2f viewCenter=viewDefault.getCenter();
    std::cout << "Center (" << viewCenter.x << ", " << viewCenter.y << ") " << std::endl;
    sf::Vector2f viewSize=viewDefault.getSize();
    std::cout << "Width: " << viewSize.x << " Height: " << viewSize.y << std::endl;
    */
}


void Window::BeginDraw()
{
    m_window.clear(sf::Color::Black);
}

void Window::EndDraw()
{
    m_window.display();
}

void Window::Update()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::LostFocus) {
            m_isFocused=false;
            m_eventManager.SetFocus(false);
            std::cout << "¡No tengo el foco!" << std::endl;
        } else if (event.type == sf::Event::GainedFocus)
        {
            m_isFocused=true;
            m_eventManager.SetFocus(true);
            std::cout << "¡Tengo el foco!" << std::endl;
        } 
        m_eventManager.HandleEvent(event);
    }
    m_eventManager.Update();
}

bool Window::IsDone()
{
    return m_isDone;
}

bool Window::IsFullScreen() 
{
    return m_isFullScreen;
}

bool Window::IsFocused()
{
    return m_isFocused;
}

void Window::ToggleFullScreen(EventDetails* l_details)
{
    (void) l_details;
    m_isFullScreen = !m_isFullScreen;
    m_window.close();
    Create();
}

void Window::Close(EventDetails* l_details) 
{
    (void) l_details;
    m_isDone=true;
}

sf::RenderWindow* Window::GetRenderWindow() 
{
    return &m_window;
}

EventManager* Window::GetEventManager()
{
    return &m_eventManager;
}

sf::Vector2u Window::GetWindowSize()
{
    return m_windowSize;
}

sf::FloatRect Window::GetViewSpace()
{
    sf::Vector2f viewCenter = m_window.getView().getCenter();
    sf::Vector2f viewSize = m_window.getView().getSize();
    sf::Vector2f viewSizeHalf (viewSize.x/2.f, viewSize.y/2);
    sf::FloatRect viewSpace (viewCenter-viewSizeHalf, viewSize); // Top Left Corner & size

    return viewSpace;
}
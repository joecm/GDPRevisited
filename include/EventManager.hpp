#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include "XmlManager.hpp"


enum class EventType { // sf::Event enumeration
    Closed=sf::Event::Closed,
    WindowResized=sf::Event::Resized,
    LostFocus=sf::Event::LostFocus,
    GainedFocus=sf::Event::GainedFocus,
    TextEntered=sf::Event::TextEntered,
    KeyDown=sf::Event::KeyPressed,
    KeyUp=sf::Event::KeyReleased,
    MouseWheel=sf::Event::MouseWheelMoved,
    MButtonDown=sf::Event::MouseButtonPressed,
    MButtonUp=sf::Event::MouseButtonReleased,
    MouseEntered = sf::Event::MouseEntered,
    MouseLeft=sf::Event::MouseLeft,
    Keyboard=sf::Event::Count +1, Mouse, Joystick
    // from here (24) events'll be analyzed in real time
};

struct EventInfo{
	EventInfo(){ m_code = 0; }
	EventInfo(int l_event){ m_code = l_event; }
	union{
		int m_code;
	};
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails 
{
	EventDetails(const std::string& l_bindName) : m_name(l_bindName){
		Clear();
	}
	std::string m_name;
	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;
	int m_keyCode; // Single key code.

	void Clear()
	{
		m_size = sf::Vector2i(0, 0);
		m_textEntered = 0;
		m_mouse = sf::Vector2i(0, 0);
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

struct Binding{
	Events m_events;
	std::string m_name;
	EventDetails m_details;
	int c; // Count of events that are "happening".

	Binding(const std::string& l_name): m_name(l_name), m_details(l_name), c(0) {
	}
	~Binding() {m_events.clear();};
	void BindEvent(EventType l_type, EventInfo l_info = EventInfo()) {
		m_events.emplace_back(l_type, l_info);
	}
};

using Bindings = std::unordered_map<std::string, std::shared_ptr<Binding>>;

using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
enum class StateType;

// using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager : public XmlManager {
public:
	EventManager();
	~EventManager();

	bool AddBinding(std::shared_ptr<Binding> l_binding);
	bool RemoveBinding(std::string l_name);

	void SetCurrentState(StateType l_state);
	void SetFocus(const bool& l_focus);

	// Needs to be defined in the header!
	template<class T>
	bool AddCallback(StateType l_state, const std::string& l_name,
		void(T::*l_func)(EventDetails*), T* l_instance)
	{
		auto itr = m_callbacks.emplace(l_state, CallbackContainer()).first;
				
		auto temp = std::bind(l_func,l_instance, std::placeholders::_1);
		// return m_callbacks.emplace(l_name, temp).second;
		return itr->second.emplace(l_name,temp).second;
	}

	bool RemoveCallback(StateType l_state, const std::string& l_name){
		// m_callbacks.erase(l_name);
		auto itr = m_callbacks.find(l_state);
		if (itr == m_callbacks.end()) { return false; }
		auto itr2 = itr->second.find(l_name);
		if (itr2 == itr->second.end()) { return false; }
		itr->second.erase(l_name);
		return true;
	}

	void HandleEvent(sf::Event& l_event);
	void Update();

	sf::Vector2i GetMousePos(sf::RenderWindow* l_wind = nullptr){
		return (l_wind ? sf::Mouse::getPosition(*l_wind) : sf::Mouse::getPosition());
	}

	void CrossBindings();
private:
	void LoadBindings();

	Bindings m_bindings;
	Callbacks m_callbacks;
	bool m_hasFocus;
	StateType m_currentState;
};


#endif // __EVENTMANAGER_H__
#include "../include/EventManager.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

EventManager::EventManager() : XmlManager(), m_hasFocus(true), m_currentState(StateType(0))	{
	LoadBindings();
}

EventManager::~EventManager() {

	for (auto &itr : m_bindings ) {
		// delete itr.second;
		itr.second = nullptr;
	}
	m_bindings.clear(); // TODO review
	m_callbacks.clear(); // TODO review

	XmlManager::releaseParser();
}

void EventManager::LoadBindings() {
	XmlManager::initParser("/home/joe/VisualCode/GDPRevisited/data/keysXml.xml");

    XMLCh* event_ch = xercesc::XMLString::transcode("event");
    XMLCh* bname_ch = xercesc::XMLString::transcode("b_name");
    XMLCh* etype_ch = xercesc::XMLString::transcode("e_type");
    XMLCh* einfo_ch = xercesc::XMLString::transcode("e_info");

    for (XMLSize_t i = 0; i < elementRoot->getChildNodes()->getLength(); ++i)
    {
        // Get the children
        xercesc::DOMNode* EventNode = elementRoot->getChildNodes()->item(i);
		if ((EventNode->getNodeType() == xercesc::DOMNode::ELEMENT_NODE) &&
			(xercesc::XMLString::equals(EventNode->getNodeName(), event_ch)))
		{
			std::string name = XmlManager::getAttributeValue(EventNode, bname_ch);
			// Create binding
			std::shared_ptr<Binding> bind=std::make_shared<Binding>(name);
			EventType typeEvent; bool flagET=false;
			EventInfo infoEvent; bool flagEI=false;
			// Necesitamos flag para que complete el bind cuando haya leido ambos

			for (XMLSize_t j = 0; j < EventNode->getChildNodes()->getLength(); ++j)
			{
				xercesc::DOMNode* pairNode = EventNode->getChildNodes()->item(j);
				if ((pairNode->getNodeType() ==xercesc::DOMNode::ELEMENT_NODE) && 
					(xercesc::XMLString::equals(pairNode->getNodeName(), etype_ch)))
				{
					typeEvent= EventType(std::atoi(XmlManager::getNodeValue(pairNode)));
					flagET=true;
				} else if ((pairNode->getNodeType() == xercesc::DOMNode::ELEMENT_NODE) &&
                    (xercesc::XMLString::equals(pairNode->getNodeName(),einfo_ch)))
				{
					infoEvent.m_code = std::atoi(XmlManager::getNodeValue(pairNode));
					flagEI=true;
				}
				if (flagET && flagEI) {
					bind->BindEvent(typeEvent, infoEvent);
					flagET=false;
					flagEI=false;
				}
				else
					continue;
			}
			if (!AddBinding(bind))
			{
				std::cerr << "Binding exist, don't added!" << std::endl;
			}
		}
    }
    xercesc::XMLString::release(&event_ch);
	xercesc::XMLString::release(&bname_ch);
	xercesc::XMLString::release(&etype_ch);
	xercesc::XMLString::release(&einfo_ch);
}


bool EventManager::AddBinding(std::shared_ptr<Binding> l_binding)	{
	if (m_bindings.find(l_binding->m_name) != m_bindings.end())
		return false;

	return m_bindings.emplace(l_binding->m_name, l_binding).second;
}

bool EventManager::RemoveBinding(std::string l_name)	{
	auto itr = m_bindings.find(l_name);
	if (itr == m_bindings.end()) {
		return false;
	}
	//delete itr->second;
	m_bindings.erase(itr);
	return true;
}

void EventManager::SetCurrentState(StateType l_state) { m_currentState = l_state; }
void EventManager::SetFocus(const bool& l_focus){ m_hasFocus = l_focus; }

void EventManager::HandleEvent(sf::Event& l_event){
	// Handling SFML events.
	for (auto &b_itr : m_bindings)	{
		std::shared_ptr<Binding> bind = b_itr.second;
		for (auto &e_itr : bind->m_events)	{
			EventType sfmlEvent = (EventType)l_event.type;
			if (e_itr.first != sfmlEvent) {
				continue;
			}
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp){
				if (e_itr.second.m_code == l_event.key.code){
					// Matching event/keystroke.
					// Increase count.
					if (bind->m_details.m_keyCode != -1){
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
					break;
				}
			} else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp){
				if (e_itr.second.m_code == l_event.mouseButton.button){
					// Matching event/keystroke.
					// Increase count.
					bind->m_details.m_mouse.x = l_event.mouseButton.x;
					bind->m_details.m_mouse.y = l_event.mouseButton.y;
					if (bind->m_details.m_keyCode != -1){
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
					break;
				}
			} else {
				// No need for additional checking.
				if (sfmlEvent == EventType::MouseWheel){
					bind->m_details.m_mouseWheelDelta = l_event.mouseWheel.delta;
				} else if (sfmlEvent == EventType::WindowResized){
					bind->m_details.m_size.x = l_event.size.width;
					bind->m_details.m_size.y = l_event.size.height;
				} else if (sfmlEvent == EventType::TextEntered){
					bind->m_details.m_textEntered = l_event.text.unicode;
				}
				++(bind->c);
			}
		}
	}
}
void EventManager::Update(){
	if (!m_hasFocus){ return; }
	for (auto &b_itr : m_bindings) {
		std::shared_ptr<Binding> bind = b_itr.second;
		for (auto &e_itr : bind->m_events)
		{
			switch (e_itr.first)
			{
				case(EventType::Keyboard) :
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.m_code)))
					{
						if (bind->m_details.m_keyCode != -1)
						{
							bind->m_details.m_keyCode = e_itr.second.m_code;
						}
						++(bind->c);
					}
				break;
				case(EventType::Mouse) :
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.m_code)))
					{
						if (bind->m_details.m_keyCode != -1)
						{
							bind->m_details.m_keyCode = e_itr.second.m_code;
						}
						++(bind->c);
					}
				break;
				case(EventType::Joystick) :
					// Up for expansion.
					break;
                default: // para quitar el Warning de -Wswitch por no estar contemplados esos valores en el switch
                    break;
				}
		}
		if (bind->m_events.size() == (long unsigned int)bind->c){
			/*
			auto callItr = m_callbacks.find(bind->m_name);
			if(callItr != m_callbacks.end()){
				callItr->second(&bind->m_details);
			}
			*/
			auto stateCallbacks = m_callbacks.find(m_currentState);
			auto otherCallbacks = m_callbacks.find(StateType(0));

			if (stateCallbacks != m_callbacks.end())
			{
				auto callItr = stateCallbacks->second.find(bind->m_name);
				if (callItr != stateCallbacks->second.end())
				{
					/* Pass in information about events */
					callItr->second(&bind->m_details);
				}
				
			}
			if (otherCallbacks != m_callbacks.end())
			{
				auto callItr = otherCallbacks->second.find(bind->m_name);
				if (callItr != otherCallbacks->second.end())
				{
					/* Pass in information about events */
					callItr->second(&bind->m_details);
				}
			}
		}
		bind->c = 0;
		bind->m_details.Clear();
	}
}

void EventManager::CrossBindings()
{
	for(auto itr : m_bindings)
	{
		std::cout << "b_name=" << itr.first << std::endl;
		for(auto var : itr.second->m_events)
		{
			std::cout << "e_type: " << (int) var.first << " e_info: " << var.second.m_code << std::endl;
		}
	}
}
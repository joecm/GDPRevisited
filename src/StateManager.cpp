#include "../include/StateManager.hpp"

StateManager::StateManager(SharedContext* l_shared) : m_Shared(l_shared)
{
    RegisterState<State_Intro>(StateType::INTRO);
    RegisterState<State_MainMenu>(StateType::MAIN_MENU);
    RegisterState<State_Game>(StateType::GAME);
    RegisterState<State_Paused>(StateType::PAUSED);
    // RegisterState<State_GameOver>(StateType::GAME_OVER);
    RegisterState<State_Credits>(StateType::CREDITS);
}

StateManager::~StateManager() 
{
    for(auto& itr : m_States)
    {
        itr.second->OnDestroy();
    }
    // removes all elements in containers StateContainer, TypeContainer, StateFactory
    m_States.clear(); // TODO review
    m_ToRemove.clear(); // TODO review
    m_StateFactory.clear(); // TODO review
}

void StateManager::Update(const sf::Time& l_time)
{
    if (m_States.empty()) 
        return;
    
    if (m_States.back().second->IsTranscendent() && m_States.size() > 1)
    {
        auto itr = m_States.end();
        while (itr != m_States.begin())
        {
            if (itr != m_States.end())
            {
                if (!itr->second->IsTranscendent())
                    break; // out of while
            }
            --itr;
        }

        for (; itr !=m_States.end(); ++itr)
            itr->second->Update(l_time);
    }
    else {
        m_States.back().second->Update(l_time);
    }
}

void StateManager::Draw() 
{
    if (m_States.empty()) 
        return;

    if (m_States.back().second->IsTransparent() && m_States.size() >1)
    {
        /*
        auto r_Itr = m_States.rbegin();
        for (; r_Itr!=m_States.rend(); ++r_Itr) {
			if (!r_Itr->second->IsTransparent())
				break;
		}
        for (; r_Itr!=m_States.rbegin(); --r_Itr)
        {
            r_Itr->second->Draw();
        }
        */
        auto itr= m_States.end();
        while (itr != m_States.begin())
        {
            if (itr != m_States.end())
            {
                if (!itr->second->IsTransparent())
                    break; // out of while
            }
            --itr;
        }

        for (; itr !=m_States.end(); ++itr) 
        {
            m_Shared->m_wind->GetRenderWindow()->setView(itr->second->GetView());
            itr->second->Draw();
        }
    }
    else {
        m_States.back().second->Draw();
    }
}

void StateManager::ProcessRequest()
{
    while (m_ToRemove.begin() != m_ToRemove.end())
    {
        RemoveState(*m_ToRemove.begin());
        m_ToRemove.erase(m_ToRemove.begin());
    }
}

SharedContext* StateManager::GetContext() const
{
    return m_Shared;
}

bool StateManager::HasState(const StateType& l_type)
{
    for (auto itr = m_States.begin(); itr != m_States.end() ; ++itr)
    {
        if (itr->first == l_type) // state match!
        {
            auto removed = std::find(m_ToRemove.begin(), m_ToRemove.end(), l_type);
            if (removed == m_ToRemove.end()) {return true;} // state not for delete
            return false;  // state for delete
        }

    }
    return false; // state no match!
}

void StateManager::SwitchTo(const StateType& l_type)
{
    m_Shared->m_eventManager->SetCurrentState(l_type);
    for (auto itr = m_States.begin(); itr != m_States.end(); ++itr)
    {
        if (itr->first == l_type)
        {
            m_States.back().second->Deactivate();
            StateType tmp_Type = itr->first;
            std::shared_ptr<BaseState> tmp_State = itr->second;
            m_States.erase(itr);
            m_States.emplace_back(tmp_Type, tmp_State);
            tmp_State->Activate();
            // pass the State view to window (RenderWindow) via Context
            m_Shared->m_wind->GetRenderWindow()->setView(tmp_State->GetView());
            return;
        }
    }
    // State with l_type wasn't found
    if (!m_States.empty()) { m_States.back().second->Deactivate(); }
    CreateState(l_type);
    m_States.back().second->Activate();
    // pass the view to window via Context
    m_Shared->m_wind->GetRenderWindow()->setView(m_States.back().second->GetView());
}

void StateManager::Remove(const StateType& l_type) 
{
    m_ToRemove.push_back(l_type);
}

void StateManager::CreateState(const StateType& l_type)
{
    auto newState = m_StateFactory.find(l_type);
    if (newState == m_StateFactory.end())
    {
        return; // State no math in StateFactory (Register)
    }
    std::shared_ptr<BaseState> state = newState->second();
    // Default view for all states
    state->m_view = m_Shared->m_wind->GetRenderWindow()->getDefaultView();
    m_States.emplace_back(l_type, state);
    state->OnCreate();
}

void StateManager::RemoveState(const StateType& l_type)
{
    for (auto itr=m_States.begin(); itr != m_States.end(); ++itr)
    {
        if (itr->first == l_type)
        {
            itr->second->OnDestroy();
            //delete itr->second;
            itr->second = nullptr;
            m_States.erase(itr);
            return;
        }
    }
}
#ifndef __STATEMANAGER_H__
#define __STATEMANAGER_H__

#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include "State_Intro.hpp"
#include "State_MainMenu.hpp"
#include "State_Game.hpp"
#include "State_Paused.hpp"
#include "SharedContext.hpp"
#include "State_Credits.hpp"


#include "BaseState.hpp"

enum class StateType { INTRO =1 , MAIN_MENU, GAME, PAUSED, GAME_OVER, CREDITS };

// State Container 
using StateContainer = std::vector<std::pair<StateType, std::shared_ptr<BaseState>>>;
// Type Container
using TypeContainer = std::vector<StateType>;

// Container for custom functions
using StateFactory = std::unordered_map<StateType, std::function<std::shared_ptr<BaseState> (void)>>;

class StateManager {
    private:
        SharedContext* m_SharedContext; // will be created in Game Class
        StateContainer m_States; 
        TypeContainer m_ToRemove; // ensure smooth transitions
        StateFactory m_StateFactory;
        // Methods
        void CreateState(const StateType& l_type);
        void RemoveState(const StateType& l_type);

        template<class T>
        void RegisterState(const StateType& l_type) {
            m_StateFactory [l_type] = [this]() -> std::shared_ptr<T>
            {
                return std::make_shared<T>(this);
            }; 
        }

    public:
        StateManager(SharedContext* l_shared);
        ~StateManager();

        void Update(const sf::Time& l_time); // will be operated by Game Class
        void Draw(); // will be operated by Game Class

        void ProcessRequest();

        SharedContext* GetContext() const;
        bool HasState(const StateType& l_type);

        void SwitchTo(const StateType& l_type);
        void Remove(const StateType& l_type);
};

#endif // __STATEMANAGER_H__
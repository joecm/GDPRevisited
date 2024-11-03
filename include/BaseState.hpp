#ifndef __BASESTATE_H__
#define __BASESTATE_H__

#include <SFML/Graphics.hpp>
#include <memory>

class StateManager;

class BaseState {
friend class StateManager;

protected:
    StateManager* m_StateMgr;
    bool m_transparent;
    bool m_transcendent;

public:
    BaseState (StateManager* l_StateManager) : m_StateMgr(l_StateManager),
        m_transparent(false), m_transcendent(false) {}
    ~BaseState() {}

    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;

    virtual void Activate() = 0;
    virtual void Deactivate() = 0;

    virtual void Update(const sf::Time& l_time) = 0;
    virtual void Draw() = 0;

    void SetTransparent(const bool& l_transparent) {
        m_transparent = l_transparent;
    }

    bool IsTransparent() const {
        return m_transparent;
    }

    void SetTranscendent(const bool& l_transcendent) {
        m_transcendent = l_transcendent;
    }

    bool IsTranscendent() const {
        return m_transcendent;
    }

    StateManager* GetStateManager() const {
        return m_StateMgr;
    }
};
#endif // __BASESTATE_H__
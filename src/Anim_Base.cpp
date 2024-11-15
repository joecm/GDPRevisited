#include "Anim_Base.hpp"
#include "SpriteSheet.hpp"

Anim_Base::Anim_Base() : m_frameCurrent(0), m_frameStart(0), m_frameEnd(0),
m_frameRow(0), m_frameActionStart(-1), m_frameActionEnd(-1), m_frameTime(0.f), 
m_elapsedTime(0.f), m_loop(false), m_playing(false)
{
}

Anim_Base::~Anim_Base()
{
}

void Anim_Base::SetSpriteSheet(SpriteSheet* l_sheet) { m_spriteSheet = l_sheet; }
void Anim_Base::SetFrame(const Frame l_frame)
{
    if ((l_frame >= m_frameStart && l_frame <= m_frameEnd) || 
        (l_frame >= m_frameEnd && l_frame <= m_frameStart))
    {
        m_frameCurrent = l_frame;
    }   
}
void Anim_Base::SetEndFrame (const Frame l_frame) { m_frameEnd = l_frame; }
void Anim_Base::SetFrameRow(const Frame l_row) { m_frameRow = l_row; }
void Anim_Base::SetActionStart (const Frame l_frame) { m_frameActionStart = l_frame; }
void Anim_Base::SetActionEnd (const Frame l_frame) { m_frameActionEnd = l_frame; }
void Anim_Base::SetFrameTime (const float l_time) { m_frameTime = l_time; }
void Anim_Base::SetLooping (const bool l_loop) { m_loop = l_loop; }
void Anim_Base::SetName (const std::string& l_name) { m_name = l_name; }

SpriteSheet* Anim_Base::GetSpriteSheet() const {return m_spriteSheet; }

Frame Anim_Base::GetFrame() const { return m_frameCurrent; }
Frame Anim_Base::GetStartFrame() const { return m_frameStart; }
Frame Anim_Base::GetEndFrame() const { return m_frameEnd; }
Frame Anim_Base::GetFrameRow() const { return m_frameRow; }
int Anim_Base::GetActionStart() const { return m_frameActionStart; }
int Anim_Base::GetActionEnd() const { return m_frameActionEnd; }
float Anim_Base::GetFrameTime() const { return m_frameTime; }
float Anim_Base::GetElapsedTime() const { return m_elapsedTime; }
std::string Anim_Base::GetName() const { return m_name; }


bool Anim_Base::IsLooping(){ return m_loop; }
bool Anim_Base::IsPlaying(){ return m_playing; }
bool Anim_Base::IsInAction()
{
    if (m_frameActionStart == -1 || m_frameActionEnd == -1) 
    {
        return true;
    }
    
    return ((int)m_frameCurrent >= m_frameActionStart && (int)m_frameCurrent <= m_frameActionEnd);
}

void Anim_Base::Play()  { m_playing = true; }
void Anim_Base::Pause() { m_playing = false; }
void Anim_Base::Stop() { m_playing = false, Reset(); }

void Anim_Base::Reset() 
{
    m_frameCurrent = m_frameStart;
    m_elapsedTime = 0.0f;
    CropSprite();
}

void Anim_Base::Update(const float& l_dT)
{
    if (!m_playing) { return; }
    m_elapsedTime += l_dT;
    if (m_elapsedTime < m_frameTime) { return; }
    FrameStep();
    CropSprite();
    m_elapsedTime = 0;
}
#pragma once

class Game;

class InputEngine
{
private:
    
public:
    InputEngine() = default;
    ~InputEngine() = default;

    bool    m_mouseRight = false;
    bool    m_mouseRightPressed = false;
    bool    m_mouseLeft = false;
    bool    m_mouseLeftPressed = false;

    void    update(Game*);
    void    changeGameState(Game*);
    void    changeGameSpeed(Game*);
};

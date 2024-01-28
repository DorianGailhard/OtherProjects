#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "PCH.h"

class InputHandler
{
    public:
        enum ButtonState {Pressed,Held,Released,None};

                            InputHandler();
        virtual             ~InputHandler();

        static void         Update();
        static ButtonState  GetButtonState(const sf::Mouse::Button& Button);

    protected:

    private:
        static std::map<sf::Mouse::Button,ButtonState>     _mouseButtonState;
};

#endif // INPUTHANDLER_H

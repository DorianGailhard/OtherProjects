#include "InputHandler.h"

InputHandler::InputHandler()
{
    //ctor
}

InputHandler::~InputHandler()
{
    //dtor
}

void InputHandler::Update()
{
    for (std::map<sf::Mouse::Button,ButtonState>::iterator itr = _mouseButtonState.begin();itr != _mouseButtonState.end();itr++) {
        if (itr->second == Released) {
            itr->second = None;
        }

        if (itr->second == Pressed) {
            switch (sf::Mouse::isButtonPressed(itr->first)) {
                case false : itr->second = Released;
                case true : itr->second = Held;
            }
        }

        if (itr->second == None && sf::Mouse::isButtonPressed(itr->first)) {
            itr->second = Pressed;
        }

        if (itr->second == Held && !sf::Mouse::isButtonPressed(itr->first)) {
            itr->second = Released;
        }
    }
}

InputHandler::ButtonState InputHandler::GetButtonState(const sf::Mouse::Button& button)
{
    std::map<sf::Mouse::Button,ButtonState>::iterator itr = _mouseButtonState.find(button);

    return itr->second;
}

std::map<sf::Mouse::Button,InputHandler::ButtonState> InputHandler::_mouseButtonState = {
    std::pair<sf::Mouse::Button,InputHandler::ButtonState>(sf::Mouse::Button::Left,InputHandler::ButtonState::None),
    std::pair<sf::Mouse::Button,InputHandler::ButtonState>(sf::Mouse::Button::Middle,InputHandler::ButtonState::None),
    std::pair<sf::Mouse::Button,InputHandler::ButtonState>(sf::Mouse::Button::Right,InputHandler::ButtonState::None),
    std::pair<sf::Mouse::Button,InputHandler::ButtonState>(sf::Mouse::Button::XButton1,InputHandler::ButtonState::None),
    std::pair<sf::Mouse::Button,InputHandler::ButtonState>(sf::Mouse::Button::XButton2,InputHandler::ButtonState::None),
    std::pair<sf::Mouse::Button,InputHandler::ButtonState>(sf::Mouse::Button::ButtonCount,InputHandler::ButtonState::None)
};

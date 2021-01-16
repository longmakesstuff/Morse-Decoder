#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <optional>
#include "Common.hpp"

typedef enum State {
    STATE_ZERO,
    STATE_ONE
} State;

class StateMachine {
private:
    State currentState = STATE_ZERO;
    sf::Clock clock;
public:
    StateMachine();

    std::optional<std::string> enter(fpt last, fpt mean, fpt std);
};
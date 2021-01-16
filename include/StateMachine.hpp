#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <optional>
#include "Speed.hpp"
#include "Common.hpp"

typedef enum State {
    STATE_ZERO,
    STATE_ONE
} State;

class StateMachine {
private:
    State currentState = STATE_ZERO;
    sf::Clock clock;
    SpeedController * speedController;
public:
    explicit StateMachine(SpeedController * _speed);

    std::optional<std::string> enter(fpt last, fpt mean, fpt std);
};
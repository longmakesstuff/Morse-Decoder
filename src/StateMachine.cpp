#include "StateMachine.hpp"

StateMachine::StateMachine() = default;
std::optional<std::string> StateMachine::enter(fpt last, fpt mean) {
    switch (currentState) {
        // Currently low
        case STATE_ZERO:
            if (last < mean) {
                return std::nullopt;
            }
            break;
        case STATE_ONE:
            if (last > mean) {
                return std::nullopt;
            }
            break;
        default:
            throw std::runtime_error("State machine is at the wrong state. Abort!");
    }
    int32_t elapsed = clock.restart().asMilliseconds();
    switch (currentState) {
        // Switch from low to high
        case STATE_ZERO:
            this->currentState = STATE_ONE;
            if(elapsed < 1000) {
                return std::optional(" ");
            } else {
                return std::optional("/");
            }
            // Switch from high to low
        case STATE_ONE:
            this->currentState = STATE_ZERO;
            if(elapsed < 300) {
                return std::optional(".");
            } else {
                return std::optional("-");
            }
        default:
            throw std::runtime_error("State machine is at the wrong state. Abort!");
    }
}

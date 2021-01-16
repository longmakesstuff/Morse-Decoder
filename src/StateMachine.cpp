#include "StateMachine.hpp"

StateMachine::StateMachine() = default;

std::optional<std::string> StateMachine::enter(fpt last, fpt mean, fpt std) {
    if (std > 200) {
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
                if (elapsed < 3000 && elapsed > 1000) {
                    return std::optional(" ");
                } else if (elapsed < 4000 && elapsed > 3000) {
                    return std::optional(" /");
                } else {
                    return std::nullopt;
                }
                // Switch from high to low
            case STATE_ONE:
                this->currentState = STATE_ZERO;
                if (elapsed < 1000) {
                    return std::optional(".");
                } else if (elapsed < 2000) {
                    return std::optional("-");
                } else {
                    return std::nullopt;
                }
            default:
                throw std::runtime_error("State machine is at the wrong state. Abort!");
        }
    } else {
        clock.restart().asMilliseconds();
        this->currentState = STATE_ZERO;
        return std::nullopt;
    }
}

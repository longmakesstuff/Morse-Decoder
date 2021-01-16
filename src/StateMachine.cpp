#include "StateMachine.hpp"

StateMachine::StateMachine(SpeedController * _speed) : speedController(_speed){};

std::optional<std::string> StateMachine::enter(fpt last, fpt mean, fpt std) {
    auto& speedInformation = speedController->speedInformation();

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
                //std::cout << "Signal low: " <<  elapsed << std::endl;

                this->currentState = STATE_ONE;
                if (elapsed < speedInformation.between_letter_high && elapsed > speedInformation.between_letter_low) {
                    return std::optional(" ");
                } else if (elapsed < speedInformation.between_word_high && elapsed > speedInformation.between_word_low) {
                    return std::optional(" /");
                } else {
                    return std::nullopt;
                }
                // Switch from high to low
            case STATE_ONE:
                this->currentState = STATE_ZERO;
                if (elapsed > speedInformation.between_dot_low && elapsed < speedInformation.between_dot_high) {
                    return std::optional(".");
                } else if (elapsed > speedInformation.between_dash_low && elapsed < speedInformation.between_dash_high) {
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

#include "Speed.hpp"

SpeedController::SpeedController(SpeedLevel speedLevel) : speedLevel(speedLevel) {}

const SpeedInformation &SpeedController::speedInformation() const {
    switch (this->speedLevel) {
        case SLOW:
            return slow;
        case MIDDLE:
            return middle;
        case FAST:
            return fast;
        default:
            throw std::runtime_error("Invalid speed");
    }
}

std::ostream &operator<<(std::ostream &os, const SpeedController &controller) {
    os << "[SpeedController]{";
    switch (controller.speedLevel) {
        case SLOW:
            os << "Slow}";
            break;
        case MIDDLE:
            os << "Middle}";
            break;
        case FAST:
            os << "Fast}";
            break;
        default:
            throw std::runtime_error("Invalid speed");
    }
    return os;
}

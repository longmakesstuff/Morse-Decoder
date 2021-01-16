#pragma once

#include <stdexcept>
#include <ostream>

typedef enum SpeedLevel {
    SLOW,
    MIDDLE,
    FAST
} SpeedLevel;

typedef struct SpeedInformation {
    int32_t between_letter_low;
    int32_t between_letter_high;
    int32_t between_word_low;
    int32_t between_word_high;
    int32_t between_dot_low;
    int32_t between_dot_high;
    int32_t between_dash_low;
    int32_t between_dash_high;
} SpeedInformation;

class SpeedController {
private:
    SpeedLevel speedLevel;
    SpeedInformation slow{
            .between_letter_low=10,
            .between_letter_high=10,
            .between_word_low=10,
            .between_word_high=10,
            .between_dot_low=10,
            .between_dot_high=10,
            .between_dash_low=10,
            .between_dash_high=10
    };
    SpeedInformation middle{
            .between_letter_low=10,
            .between_letter_high=10,
            .between_word_low=10,
            .between_word_high=10,
            .between_dot_low=10,
            .between_dot_high=10,
            .between_dash_low=10,
            .between_dash_high=10
    };
    SpeedInformation fast{
            .between_letter_low=200,
            .between_letter_high=500,
            .between_word_low=600,
            .between_word_high=1000,

            .between_dot_low=50,
            .between_dot_high=200,
            .between_dash_low=200,
            .between_dash_high=400
    };

public:
    explicit SpeedController(SpeedLevel speedLevel);

    [[nodiscard]] const SpeedInformation& speedInformation() const;

    friend std::ostream &operator<<(std::ostream &os, const SpeedController &controller);
};


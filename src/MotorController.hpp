#ifndef MOTOR_CONTROLLER_HPP
#define MOTOR_CONTROLLER_HPP

typedef enum ButtonState {
    NOT_PRESSED,
    UP,
    DOWN,
    BOTH,
} ButtonState;


class MotorController {
    public:
    MotorController();
    ButtonState readButtonState();
};

#endif
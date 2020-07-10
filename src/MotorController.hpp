#ifndef MOTOR_CONTROLLER_HPP
#define MOTOR_CONTROLLER_HPP


class MotorController {
    public:
    MotorController();
    bool readButtonState();
    void setButtonInputVoltageState(int state);
};

#endif
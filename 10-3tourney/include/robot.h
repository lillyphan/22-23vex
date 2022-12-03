#include "main.h"

//controllers
    extern pros::Controller con1;

//motors
    extern pros::Motor driveLF;
    extern pros::Motor driveLB;
    extern pros::Motor driveRF;
    extern pros::Motor driveRB;
    extern pros::Motor flywheel;
    extern pros::Motor intake;
    extern pros::Motor roller;

//motor groups
    extern pros::MotorGroup driveMotors;
    extern pros::MotorGroup leftMotors;
    extern pros::MotorGroup rightMotors;

//SUBSYSTEM FUNCTIONS

    // void setDrive();
    void setDrive(int leftPct, int rightPct);
    int intakeDirection(int power);
    int setIntake(int power, bool intakeOn);
    bool setRollers(bool rollerOn);
    bool setFlywheel(bool fwOn);
    void tankDriverControl();
    void index();

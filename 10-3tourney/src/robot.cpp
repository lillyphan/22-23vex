#include "functions.h"
#include "robot.h"

	pros::Controller con1(pros::E_CONTROLLER_MASTER);

	pros::Motor driveLF(2, pros::E_MOTOR_GEARSET_36, true);
	pros::Motor driveLB(4, pros::E_MOTOR_GEARSET_36, true);
	pros::Motor driveRF(1, pros::E_MOTOR_GEARSET_36, false);
	pros::Motor driveRB(3, pros::E_MOTOR_GEARSET_36, false);
	pros::Motor flywheel(10, pros::E_MOTOR_GEARSET_06, true);
	pros::Motor intake(6, pros::E_MOTOR_GEARSET_18, false);
	pros::Motor roller(5, pros::E_MOTOR_GEARSET_18, true);

    pros::MotorGroup driveMotors({driveLF, driveRF, driveLB, driveRB});
	pros::MotorGroup leftMotors({driveLF, driveLB});
	pros::MotorGroup rightMotors({driveRF, driveRB});

    int setIntake(int power){
        //get_digital
        //ask charlie where he prefers this
        if (con1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
            power *= -1;
        }

        intake = power * (con1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2));
        return power;
    }

    bool setFlywheel(bool fwOn){
        if (con1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) { //flywheel acitvate)
            flywheel = -127 * !fwOn;
            return !fwOn;
		}
        return fwOn;
    }

    void setRollers(){
        roller = 127 * (con1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2));
    }

    void setDrive(){
        int deadzone = 8;
        int moveF = pros::E_CONTROLLER_ANALOG_LEFT_Y / 127 * 100;
	    int moveS = pros::E_CONTROLLER_ANALOG_RIGHT_X / 127 * 100; //check this conversion rate and the motors, almost positive we didn't use red inserts for drive
        if (!(abs(moveF) >= deadzone && abs(moveS)) >= deadzone) {
            moveF = 0;
            moveS = 0;
		}
        rightMotors.move_velocity(moveF-moveS); //if drive doesn't work, switch up right motors and left 
		leftMotors.move_velocity(moveF+moveS); //and if that doesn't work, switch the moveS and moveF with eachother
    }

    void haveEthanLookOverThis(){
        pros::ADIDigitalOut fieldExpansion('A');
	    pros::ADIDigitalOut indexer('B');
        if (con1.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
			fieldExpansion.set_value(LOW);
		} else {
			fieldExpansion.set_value(HIGH);
		}
		if (con1.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
			indexer.set_value(LOW);
		} else {
			indexer.set_value(HIGH);
		}

    }
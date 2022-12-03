#include "main.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"

	pros::Controller con1(pros::E_CONTROLLER_MASTER);

	pros::Motor driveLF(2, pros::E_MOTOR_GEARSET_36, true);
	pros::Motor driveLB(4, pros::E_MOTOR_GEARSET_36, true);
	pros::Motor driveRF(1, pros::E_MOTOR_GEARSET_36, false);
	pros::Motor driveRB(3, pros::E_MOTOR_GEARSET_36, false);
	pros::Motor flywheelRight(10, pros::E_MOTOR_GEARSET_36, true);
    pros::Motor flywheelLeft(7, pros::E_MOTOR_GEARSET_36, false);
	pros::Motor intake(5, pros::E_MOTOR_GEARSET_36, false);
	pros::Motor indexer(20, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

    pros::MotorGroup driveMotors({driveLF, driveRF, driveLB, driveRB});
	pros::MotorGroup leftMotors({driveLF, driveLB});
	pros::MotorGroup rightMotors({driveRF, driveRB});

    int intakeDirection(int power){
        //get_digital
        //ask charlie where he prefers this
        if (con1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
            power *= -1;
        }
        return power;
    }
    //flywheel intake and roller

    bool setIntake(int power, bool intakeOn){
        if (con1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) { // if R2 is pressed
            intake = power * !intakeOn; //turn intake on/off according to current state
            return !intakeOn;
		}
        return intakeOn;

    }

    bool setFlywheel(bool fwOn){
        if (con1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) { // if A is pressed
            flywheelRight = -127 * !fwOn; //turn flywheels on/off according to current state
            flywheelLeft = -127 * !fwOn;
            return !fwOn;
		}
        return fwOn;
    }

    // bool setRollers(bool rollerOn){
    //     if (con1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) { if L1 is pressed
    //         roller = 127 * !rollerOn; //turn roller on/off according to current state
    //         return !rollerOn;
	// 	}
    //     return rollerOn;
    // }

    void setDrive(int leftPct, int rightPct){
        leftPct = leftPct * 2;
        rightPct = rightPct * 2;
        driveLB.move_velocity(leftPct);
        driveLF.move_velocity(leftPct);
        driveRB.move_velocity(rightPct);
        driveRF.move_velocity(rightPct);
    }

    void tankDriverControl(){
        int leftPower = (con1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)*100)/127;
        int rightPower = (con1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)*100)/127;
        setDrive(leftPower,rightPower);
    }

    void index(){
        if (con1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
            indexer.move_absolute(45, 100);
            indexer.move_relative(45, 100);
            pros::delay(300);
            indexer.move_relative(-45, 100);
        }
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


#include "main.h"
#include "robot.h"
#include "auton.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "here");

	pros::lcd::register_btn1_cb(on_center_button);
	// autonomous();
	opcontrol();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */

void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

void competition_initialize() {
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    // driveMotors.move_relative(10 * 360 / 12.56637061, 100);
	leftMotors.move_velocity(-100);
	rightMotors.move_velocity(100);
    pros::delay(500);
	driveMotors.move_velocity(0);
	leftMotors.move_velocity(100);
	rightMotors.move_velocity(100);
	pros::delay(1000);
	leftMotors.move_velocity(-100);
	rightMotors.move_velocity(100);
	pros::delay(2000);
	driveMotors.move_velocity(0);
	intake.move_velocity(100);
	pros::delay(300);
	intake.move_velocity(0);
	leftMotors.move_velocity(100);
	rightMotors.move_velocity(-100);
	pros::delay(2000);
	driveMotors.move_velocity(0);
	leftMotors.move_velocity(100);
	rightMotors.move_velocity(100);
	pros::delay(500);
	leftMotors.move_velocity(-100);
	rightMotors.move_velocity(100);
	pros::delay(1000);
	driveMotors.move_velocity(0);
	intake.move_velocity(100);
	pros::delay(300);
	intake.move_velocity(0);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 * 
 * 
 * 
 */


void opcontrol() {

	int power = 127;
	bool intakeOn = false;
	bool flywheelActive = false;
	bool intakeActive = false;
	bool rollerActive = false;

	while (1) {
		power = intakeDirection(power);
		intakeActive = setIntake(power, intakeActive);
		flywheelActive = setFlywheel(flywheelActive);
		index();

		// rollerActive = setRollers(rollerActive);
		tankDriverControl();

		pros::delay(20);
	}
}

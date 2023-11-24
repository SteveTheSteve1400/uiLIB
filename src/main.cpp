#include "main.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/differential.hpp"
#include "lemlib/logger/stdout.hpp"
#include "pros/misc.h"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

// motor groups
// left motors on ports 8, 20, and 19. Motors on ports 8 and 20 are reversed. Using blue gearbox
auto leftMotors = lemlib::makeMotorGroup({-8, -20, 19}, pros::v5::MotorGears::blue);
// right motors on ports 2, 11, and 13. Motor on port 13 is reversed. Using blue gearbox
auto rightMotors = lemlib::makeMotorGroup({2, 11, -13}, pros::v5::MotorGears::blue);

// Inertial Sensor on port 11
pros::Imu imu(11);

// horizontal tracking wheel. Port 4, 2.75" diameter, 3.7" offset, back of the robot
lemlib::TrackingWheel horizontal(4, lemlib::Omniwheel::NEW_275, -3.7);

// drivetrain settings
lemlib::Drivetrain_t drivetrain{
    leftMotors, // left motor group
    rightMotors, // right motor group
    10, // 10 inch track width
    lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
    360, // drivetrain rpm is 360
    2 // chase power is 2. If we had traction wheels, it would have been 8
};

// linear motion controller
lemlib::ChassisController_t linearController{
    10, // proportional gain (kP)
    30, // derivative gain (kD)
    1, // small error range, in inches
    100, // small error range timeout, in milliseconds
    3, // large error range, in inches
    500, // large error range timeout, in milliseconds
    20 // maximum acceleration (slew)
};

// angular motion controller
lemlib::ChassisController_t angularController{
    2, // proportional gain (kP)
    10, // derivative gain (kD)
    1, // small error range, in degrees
    100, // small error range timeout, in milliseconds
    3, // large error range, in degrees
    500, // large error range timeout, in milliseconds
    20 // maximum acceleration (slew)
};

// sensors for odometry
// note that in this example we use internal motor encoders, so we don't pass vertical tracking wheels
lemlib::OdomSensors_t sensors{
    nullptr, // vertical tracking wheel 1, set to nullptr as we don't have one
    nullptr, // vertical tracking wheel 2, set to nullptr as we don't have one
    &horizontal, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
    &imu // inertial sensor
};

// create the chassis
lemlib::Differential chassis(drivetrain, linearController, angularController, sensors);


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {

}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	
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
void competition_initialize() {}

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
void autonomous() {}

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
 */
void opcontrol() {
	
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({1,-2,3}); // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({-4,5,-6}); // Creates a motor group with forwards port 4 and reversed ports 4 & 6

	while (true) {
		 
		// Arcade control scheme
		int dir = master.get_analog(ANALOG_LEFT_Y); // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_RIGHT_X); // Gets the turn left/right from right joystick
		left_mg = dir - turn; // Sets left motor voltage
		right_mg = dir + turn; // Sets right motor voltage
		pros::delay(20); // Run for 20 ms then update
	}
}
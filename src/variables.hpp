#include "main.h"
#include "lemlib/api.hpp"
#include "pros/optical.hpp"
#include "pros/motors.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::Motor RightFront(3);
pros::Motor RightMid(1);
pros::Motor RightBack(-2);
    pros::MotorGroup RDrive({3, 1, -2}); 

pros::Motor LeftFront(-4);
pros::Motor LeftMid(-5);
pros::Motor LeftBack(6);
    pros::MotorGroup LDrive({-4, -5, 6});

pros::Motor intake(7);    
pros::Motor midlifter(10, pros::v5::MotorGears::red);

#define mogo 3 // C
pros::adi::DigitalOut mogomech (mogo);

#define doinkerport 4 // D
pros::adi::DigitalOut doinker (doinkerport); // this is the thing that clears the corner

#define intakeport 6 // F
pros::adi::DigitalOut intakeLifter (intakeport); // this is the thing that changes if we get the top or bottom ring

bool intakePOS = false;
int intaking = 0;
//speed of intake
int intakespeed = 127;
int maxauto = 4;
int auton = 0;
int midliftPOS = 0;
double lowmid = 0;
double midmid = -105;
double highmid = -420;
double liftpos;
bool mogovalue = false;
bool doinkerValue = false;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////Lemlib stuff//////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Drivetrain config 
lemlib::Drivetrain drivetrain {
	&LDrive, // left motor group
	&RDrive, // right motor group
	14.497386, // 14.5 inch track width
	lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
	400, // drivetrain rpm is 400
	8 // Its 8 because we have traction wheels
};
		
// left tracking using drive motors
lemlib::TrackingWheel left_tracking(
	&LDrive, //Look at the left drive
	3.25, //3.25 inch wheels
	-7.251, //6.2875 incheas left of the center
	400  //Max RPM of 400
);

// right tracking using drive motors
lemlib::TrackingWheel right_tracking(
	&RDrive, //Look at the left drive
	3.25, //3.25 inch wheels
	7.251, //6.2875 incheas right of the center
	400 //Max RPM of 400
);
		
// inertial sensor
pros::Imu inertial(11);
		
// Sensors for odometry 
lemlib::OdomSensors sensors {
	&left_tracking, // vertical tracking wheel 1
	&right_tracking, // vertical tracking wheel 2
	nullptr, // no horizontal tracking
	nullptr, // no second horizontal tracking wheel
	&inertial // inertial sensor
};


// forward/backward PID
lemlib::ControllerSettings lateralController {
	10, // proportional gain (kP)
	0, // integral gain (kI)
	3, // derivative gain (kD)
	3, // anti windup
	0.5, // small error range, in inches
	500, // small error range timeout, in milliseconds
	1, // large error range, in inches
	500, // large error range timeout, in milliseconds
	20 // maximum acceleration (slew)
};

// turning PID
lemlib::ControllerSettings angularController {
	2, // proportional gain (kP)
	0, // integral gain (kI)
	10, // derivative gain (kD)
	3, // anti windup
	1, // small error range, in degrees
	200, // small error range timeout, in milliseconds
	3, // large error range, in degrees
	500, // large error range timeout, in milliseconds
	0 // maximum acceleration (slew
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);

pros::Optical optical_sensor(12);
#include "main.h"
//#include "lemlib/api.hpp"
#include "pros/optical.hpp"
#include "autons.hpp"
#include "liblvgl/llemu.hpp"


void on_center_button() {
	if (team == 'r'){team = 'b';} else {team = 'r';}
	lightsCheck();
}

void on_right_button() {
	if (auton != maxauto){
		auton++;
	} else{
		auton = 0;
	}
}
void on_left_button() {
	if (auton != 0){
		auton--;
	} else{
		auton = maxauto;
	}

}

void midlift(){
	while (true) {
		if (midlifter.get_position() != liftpos*5){
			midlifter.move_absolute(liftpos*5, 100);
		} else {
			midlifter.brake();
		}
		pros::delay(20);
	}
}


void ringcheckers(){
	while(true){
		if (intaking == 1){
			if (team == 'b'){
				if (round(optical_sensor.get_hue() / 15) == 0){
					intake.move(-127);

				} else {
					intake.move(127);
				}
			} else {
				if (round(optical_sensor.get_hue() / 15) == round(225 / 15)){
					intake.move(-127);
				} else {
					intake.move(127);
				}
			}	
		} else if(intaking == 0) {
			intake.brake();
		}
		pros::delay(20);	
	}
}

void printinf(){
	while(true){
		if (page == 0) {
			info.print(0,0, "auton:%d  team:%c"                         , auton, team);
			pros::delay(50);
			if (confirm){info.print(1,0, "confirmed                           ");}
			else {info.print(1,0, "not confirmed                                ");}
			pros::delay(50);
			info.print(2,0,"                                                        ");
		} else if (page == 1) {
			info.print(0,0, "f: %d, %d                                 ", (int)std::round(LeftFront.get_temperature()),(int)std::round(RightFront.get_temperature()));pros::delay(50);
			info.print(1,0, "m: %d, %d                                ", (int)std::round(LeftMid.get_temperature()),(int)std::round(RightMid.get_temperature()));pros::delay(50);
			info.print(2,0, "b: %d, %d                                ", (int)std::round(LeftBack.get_temperature()),(int)std::round(RightBack.get_temperature()));pros::delay(50);
		}else if (page == 2) {
			info.print(0,0, "intake	: %d                                ", (int)std::round(intake.get_temperature()));pros::delay(50);
			info.print(1,0, "                                          ");pros::delay(50);
			info.print(2,0, "                                          ");pros::delay(50);
		}
		pros::lcd::print(0, "x=%f, y=%f, theta=%f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
		pros::delay(50);
	}
}

void initialize() {
	pros::lcd::initialize();
	info.clear();
	pros::lcd::register_btn0_cb(on_left_button);
	pros::lcd::register_btn1_cb(on_center_button);
	pros::lcd::register_btn2_cb(on_right_button);

	chassis.calibrate();

	pros::Task liftTask(midlift);
	pros::Task ringcheck(ringcheckers);
	pros::Task printing(printinf);
	lightsCheck();
	midlifter.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intakeLifter.set_value(true);

	mogomech.set_value(mogovalue);
	optical_sensor.set_led_pwm(100);
}

void disabled() {
	while (true) {
		cycle();
		pros::delay(20);
	}
}

void competition_initialize() {
	lightsCheck();
}

void autonomous() {
	
	autonselect(auton);
}

void opcontrol() {
	while (true) {

		int dir = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = -controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		LDrive.move(dir - turn);
		RDrive.move(dir + turn);

		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intaking = 1;
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			intake.move(-127);
			intaking = 2;
		} else {
			intaking = 0;
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			midliftPOS += 1;
			if (midliftPOS == 3) {
				midliftPOS = 0;
			}
			if (midliftPOS == 0){
				liftpos = lowpos;
			}
			if (midliftPOS == 1){
				liftpos = midpos;
			}
			if (midliftPOS == 2){
				liftpos = highpos;
			}
		}
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
			mogovalue =!mogovalue;
			mogomech.set_value(mogovalue);
		}
		
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
			doinkerValue = !doinkerValue;
			doinker.set_value(doinkerValue);
		}
		if (info.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){
			if (page != 0){
				page--;
			} else {
				page = pagenums;
			}
			
		}
		if (info.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
			if (page != pagenums){
				page++;
			} else{
				page = 0;
			}
		}
		if (info.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
			if (!confirm) {
				if (auton != maxauto){
					auton++;
				} else{
					auton = 0;
				}
			}
		}
		if (info.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
			if (!confirm) {
				if (auton != 0){
					auton--;
				} else{
					auton = maxauto;
				}
			}
		}
		if (info.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
			if (!confirm) {
				if (team == 'r'){team = 'b';} else {team = 'r';}
				lightsCheck();
			}
		}
		if (info.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
			if (!confirm) {
				confirm = true;
			}
		}
		if (info.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
			intakeLifter.set_value(false);
		}
		if (info.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
			if (!confirm) {
				if (team == 'r'){
					chassis.setPose(0,0,0);
					chassis.moveToPoint(0,10,2000,{},true);
					chassis.turnToPoint(20,33, 2000,{},true);
				} else {
					liftpos = midpos;
					chassis.setPose(0,0,0);
					chassis.moveToPoint(0,3,2000,{},true);
					chassis.swingToHeading(80, DriveSide::RIGHT,2000,{},true);
				}
			}
		}
		pros::delay(20);

	}
}

#include "variables.hpp"
ASSET(redrush_txt);
//pid tuning
void auton_0() {
    //chassis.setPose(0,0,45);
    intaking = 1;
    chassis.moveToPose(25,40,40,2000,{}, false);
    pros::delay(300);
    intaking = 0;
    chassis.turnToPoint(25,62,2000,{.forwards = false}, false);
    chassis.moveToPose(25,62,theta(),2000,{.forwards = false}, false);
    mogovalue = true;
    mogomech.set_value(mogovalue);
    intaking = 1;
    pros::delay(200);
    chassis.moveToPose(25,50,180,2000,{.forwards = true}, false);
    mogovalue = false;
    mogomech.set_value(mogovalue);
    pros::delay(200);
    chassis.turnToPoint(0,45,2000,{.forwards = false}, false);
    chassis.moveToPose(0,45,theta(), 2000,{.forwards = false}, false);
    
    mogovalue = true;
    mogomech.set_value(mogovalue);
    pros::delay(200);
}

void auton_1() {

}

void auton_2() {

}

void auton_3() {

}

void auton_4() {//crosby's skills auton

}

void autonselect(int auton) {
    if (auton == 0){auton_0();}
    if (auton == 1){auton_1();}
    if (auton == 2){auton_2();}
    if (auton == 3){auton_3();}
    if (auton == 4){auton_4();}
    
}
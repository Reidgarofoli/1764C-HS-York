#include "variables.hpp"
ASSET(redrush_txt);
//pid tuning
void auton_0() {
    chassis.setPose(0,0,45);
    intaking = 1;
    chassis.moveiToPose(24,24,45,2000,{}, false);
    pros::delay(200);
    intaking = 0;
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
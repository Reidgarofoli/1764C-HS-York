#include "variables.hpp"

//pid tuning
void auton_0() { // this is for red side right side WP auton
    if (team == 'r'){
        intaking = 1;// start intake so that we can egt the first ring.
        chassis.moveToPoint(25,39,2000,{}, false);//go to first ring.
        intaking = 0;//stop intake.
        chassis.turnToHeading(180, 2000, {}, false);//turn to mobile goal.
        chassis.moveToPose(28,62,180,2000,{.forwards = false, .lead=0.3}, false);// go to mobile goal.
        mogovalue = true;//activate mogo. grabs and holds on to mobile goal 
        mogomech.set_value(mogovalue);
        pros::delay(500);//wait .5 seconds before intaking.
        intaking = 1; //starts intakeing.
        chassis.moveToPose(28,40, 180, 10000,{},false);//go toward our side and bring mogo with us.
        pros::delay(500);//wait 0.5 seconds.
        mogovalue = false;//open mogo to release mobile goal.
        mogomech.set_value(mogovalue);
        chassis.turnToHeading(240,2000,{.minSpeed=50, .earlyExitRange=5},false);//turn toward preload. 
        chassis.moveToPose(-1,20,270,2000,{.lead=0.2, .earlyExitRange=2},false);//go to preload
        intaking = 0;//stop intaking 
        chassis.turnToHeading(188,2000,{.minSpeed=50, .earlyExitRange=5},false);//turn to second mobile goal
        chassis.moveToPoint(5,36,2000,{false},false);// go to second mobile goal
        pros::delay(200);//wait .2 seconds.
        mogovalue = true;//close mogo to grab mobile goal
        mogomech.set_value(mogovalue);
        pros::delay(200);//wait .2 seconds.
        intaking = 1;//start intake. pre load should be scored from this
        pros::delay(1400);//wait 1.4 seconds. 
        intakePOS = true;//lift the first stage of intake to grab top red ring 
        intakeLifter.set_value(intakePOS);
        chassis.turnToHeading(225,2000,{},false);//turn to to the top red ring
        chassis.moveToPoint(-6,25,2000,{},false); //go to top red ring
        pros::delay(200);
        intakePOS = false;//lower the first stage of intake to grab top red ring 
        intakeLifter.set_value(intakePOS);
        chassis.moveToPose(-1,28, 270, 3000,{.forwards=false, .minSpeed=50, .earlyExitRange=3},false);
        chassis.turnToHeading(320,2000,{},false);
        chassis.moveToPose(-9,30, 320, 2000,{},false);
   } else {//blue team leftside 

        intaking = 1;// start intake so that we can egt the first ring.
        chassis.moveToPoint(-24,36,2000,{}, false);//go to first ring.
        intaking = 0;//stop intake.
        chassis.turnToPoint(-21, 47, 2000, {.forwards = false}, false);
        chassis.moveToPose(-21, 47, 180,2000, {.forwards = false, .lead=0.3,}, false);
        mogovalue = true;//activate mogo. grabs and holds on to mobile goal 
        mogomech.set_value(mogovalue);
        pros::delay(500);
        intaking = 1;
        chassis.moveToPose(-21,32, 180, 10000,{},false);//go toward our side and bring mogo with us.
        pros::delay(500);//wait 0.5 seconds.
        mogovalue = false;//open mogo to release mobile goal.
        mogomech.set_value(mogovalue);
        pros::delay(500);
        chassis.turnToHeading(-90, 2000, {}, false);
        chassis.moveToPoint(-5, 30, 2000, {.forwards = false, .minSpeed=80, .earlyExitRange=3}, false);
        pros::delay(600);
        mogovalue = true;//activate mogo. grabs and holds on to mobile goal 
        mogomech.set_value(mogovalue);
        chassis.moveToPoint(3, 30, 2000, {.forwards = false}, false);
        chassis.turnToHeading(180,2000,{},false);
        chassis.moveToPose(15, 7, 90, 2000, {}, false);

        pros::delay(500);
        // chassis.turnToHeading(-220, 2000, {}, false);
        // chassis.moveToPose(17, 8, 90, 2000, {}, false);
        intakePOS = true; //lift the first stage of intake to grab top red ring 
        intakeLifter.set_value(intakePOS);
        pros::delay(200);
        chassis.moveToPoint(25,7,2000,{},false);
        pros::delay(200);
        intakePOS = false;//drop the first stage of intake to grab top red ring 
        intakeLifter.set_value(intakePOS);
        chassis.moveToPoint(15,7,2000,{.forwards = false},false);
        chassis.turnToHeading(-320, 2000, {}, false);
        chassis.moveToPoint(27, 26, 2000, {.maxSpeed = 50}, false);
   }
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
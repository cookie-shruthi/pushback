#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

///
// Constants
///
void default_constants() {
 // P, I, D, and Start I
 chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
 chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
 chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
 chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
 chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
 chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions


 // Exit conditions
 chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
 chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
 chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
 chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
 chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
 chassis.pid_turn_chain_constant_set(3_deg);
 chassis.pid_swing_chain_constant_set(5_deg);
 chassis.pid_drive_chain_constant_set(3_in);


 // Slew constants
 chassis.slew_turn_constants_set(3_deg, 70);
 chassis.slew_drive_constants_set(3_in, 70);
 chassis.slew_swing_constants_set(3_in, 80);


 // The amount that turns are prioritized over driving in odom motions
 // - if you have tracking wheels, you can run this higher.  1.0 is the max
 chassis.odom_turn_bias_set(0.9);


 chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
 chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
 chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are


 chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}


//conveyor clog checker
void conveyor_clog(int desired){
 //runtime variable
 int runtime = 0;


 //run intake
 while (runtime < desired) {
   //run intake
   conveyor.move(127);


   pros::delay(300);
   runtime += 300;


   //check if clogged
   if (conveyor.get_actual_velocity() <= 5) {
     //reverse intake
     conveyor.move(-127);


     pros::delay(300);
     runtime += 300;
   }
 }


 //stop motors
 conveyor.move(0);
}


///
// Drive Example
///
void left_auton_1() {
 // The first parameter is target inches
 // The second parameter is max speed the robot will drive at
 // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
 // for slew, only enable it when the drive distance is greater than the slew distance + a few inches


 //put preload near bottom of conveyor
 //position bot 12 inches from back wall along parking zone


 chassis.drive_angle_set(180_deg);  // Start the robot facing 45 degrees


//drive to center blocks
//drive forward 16 inches
chassis.pid_drive_set(16_in, 90);
chassis.pid_wait();


//collect center blocks
//turn to head 160 deg
chassis.pid_turn_set(160_deg, 90);
chassis.pid_wait();
//in conveyor
conveyor.move(127);
//drive forward 4 inches
chassis.pid_drive_set(4_in, 48);
chassis.pid_wait();
//turn to head 152
chassis.pid_turn_set(145_deg, 50); //og 152
chassis.pid_wait();
chassis.pid_drive_set(6_in, 40); //2nd turn to blocks; og 4
chassis.pid_wait();
pros::delay(500);
conveyor.move(0);


//back up from center
//drive backwards 20 inches
chassis.pid_drive_set(-20_in, 90);
chassis.pid_wait();


//drive to long goal
//turn to head 90 deg
chassis.pid_turn_set(90_deg, 90);
chassis.pid_wait();
//drive forward 37.5 inches
chassis.pid_drive_set(39.5_in, 90); //og 40
chassis.pid_wait();


//score in long goal
//turn to head 0 deg
chassis.pid_turn_set(0_deg, 90);
chassis.pid_wait();
//drive backwards 15 inches
chassis.pid_drive_set(-15_in, 90);
chassis.pid_wait();
//score
conveyor.move(127);
middle.move(127);
outtake.move(127);
pros::delay(4500); //og 3500


//back from goal
chassis.pid_drive_set(5, 30);
chassis.pid_wait();
}


void right_auton_1() {
 master.print(0, 0, "downloaded1");
 //put preload near bottom of conveyor
 //position bot 12 inches from back wall along parking zone
 chassis.drive_angle_set(180_deg);


 //drive to center blocks
 //drive forward 16 inches
 chassis.pid_drive_set(16_in, 110);
 chassis.pid_wait();


 //collect center blocks
 //turn to head 200 deg
 chassis.pid_turn_set(200_deg, 90);
 chassis.pid_wait();
 //in conveyor
 conveyor.move(127);
 //drive forward 4 inches
 chassis.pid_drive_set(4_in, 48); //CHANGE-2/15
 chassis.pid_wait();
 //turn to head 208 deg
 chassis.pid_turn_set(215_deg, 50); //CHANGE-2/15
 chassis.pid_wait();
 //drive forward 4 inches (slower?)
 chassis.pid_drive_set(6_in, 40); //2nd turn to blocks
 chassis.pid_wait();
 pros::delay(500);
 conveyor.move(0);


 //back up from center
 //drive backwards 20 inches
 chassis.pid_drive_set(-20_in, 90);
 chassis.pid_wait();
  //drive to long goal
 //turn to head 270 deg
 chassis.pid_turn_set(270_deg, 90);
 chassis.pid_wait();
 //drive forward 37.5 inches
 chassis.pid_drive_set(40.5_in, 90); //og 37.5
 chassis.pid_wait();


 //score in long goal
 //turn to head 0 deg
 chassis.pid_turn_set(0_deg, 90);
 chassis.pid_wait();
 //drive backwards 15 inches
 chassis.pid_drive_set(-15_in, 90);
 chassis.pid_wait();
 //score
 conveyor.move(127);
 middle.move(127);
 outtake.move(127);
 pros::delay(4500);


 //back from goal
 chassis.pid_drive_set(5, 30);
 chassis.pid_wait();
}


void left_auton_2() {
 //put preload near bottom of conveyor
 //position bot facing matchloader along the black mark of parking zone


 chassis.drive_angle_set(270_deg);


 //turn to matchloader
 chassis.pid_drive_set(30_in, 90);
 chassis.pid_wait();


 chassis.pid_turn_set(180_deg, 80);
 chassis.pid_wait();


 //drive to matchloader
 scraper.set (true);
 pros::delay (600);


 chassis.pid_drive_set(9.5_in, 90); //NEW-2/19
 chassis.pid_wait();


 //intake from matchloader
 conveyor_clog(1800);


 //drive to long goal
 chassis.pid_drive_set(-27_in, 110);
 chassis.pid_wait();


 //score in long goal
 conveyor.move(127);
 middle.move(127);
 outtake.move(127);
 pros::delay(2500);


 //drive to center blocks
 scraper.set(false);
 middle.move(0);
 outtake.move(0);


 chassis.pid_drive_set(10_in, 90);
 chassis.pid_wait();
 chassis.pid_turn_set(55_deg, 90);
 chassis.pid_wait();


 //collect center blocks
 chassis.pid_drive_set(21_in, 90); //OG 19.5-2/19
 chassis.pid_wait();


 scraper.set(true);
 pros::delay(300);
 chassis.pid_drive_set(5_in, 50);
 chassis.pid_wait();
 pros::delay(500); //200 ON THE OTHER ONE, CHANGE?


 //scraper.set(false); helps collect blocks


 //outtake center blocks
 chassis.pid_turn_set(225.5_deg, 90); //OG 232.5-2/19
 chassis.pid_wait();


 chassis.pid_drive_set(-22_in, 100);
 chassis.pid_wait();


 //conveyor is still moving up
 conveyor.move(127);
 middle.move(-127);
 outtake.move(-127);
}


void right_auton_2() {
 //put preload near bottom of conveyor
 //position bot facing matchloader along the black mark of parking zone


 chassis.drive_angle_set(90_deg);


 //turn to matchloader
 chassis.pid_drive_set(30_in, 90);
 chassis.pid_wait();


 chassis.pid_turn_set(180_deg, 80);
 chassis.pid_wait();


 //drive to matchlaoder
 scraper.set (true);
 pros::delay (600);


 chassis.pid_drive_set(8_in, 90); //new-2/19
 chassis.pid_wait();


 //intake from matchloader
 conveyor_clog(1800);
  //drive to long goal
 chassis.pid_drive_set(-27_in, 110);
 chassis.pid_wait();


 //score in long goal
 conveyor.move(127);
 middle.move(127);
 outtake.move(127);
 pros::delay(2500);


 //drive to center blocks
 scraper.set(false);
 middle.move(0);
 outtake.move(0);


 chassis.pid_drive_set(10_in, 90);
 chassis.pid_wait();
 chassis.pid_turn_set(305_deg, 90);
 chassis.pid_wait();
 //collect center blocks
 chassis.pid_drive_set(21_in, 90);
 chassis.pid_wait();


 scraper.set(true);
 pros::delay(300);
 chassis.pid_drive_set(5_in, 50);
 chassis.pid_wait();
 pros::delay(200); //CAN REMOVE


 scraper.set(false);


 //outtake center blocks
 chassis.pid_turn_set(308.5_deg, 90);
 chassis.pid_wait();


 chassis.pid_drive_set(17_in, 80); //new-2/19
 chassis.pid_wait();


 conveyor.move(-127);
 outtake.move(-127);
}


void left_auton_4() {

 //put preload near bottom of conveyor
 //position bot 12 inches from back wall along parking zone


 chassis.drive_angle_set(180_deg);  // Start the robot facing 45 degrees


 //drive to center blocks
 //drive forward 16 inches
 chassis.pid_drive_set(16_in, 110); //CHANGE-2/15
 chassis.pid_wait();


 //collect center blocks
 //turn to head 160 deg
 chassis.pid_turn_set(160_deg, 60);
 chassis.pid_wait();
 //in conveyor
 conveyor.move(127);
 //drive forward 4 inches
 chassis.pid_drive_set(4_in, 55); //CHANGE-2/15
 chassis.pid_wait();
 //turn to head 152
 chassis.pid_turn_set(145_deg, 55); //CHANGE-2/15
 chassis.pid_wait();
 chassis.pid_drive_set(6_in, 45); //2nd turn to blocks; CHANGE-2/15
 chassis.pid_wait();
 pros::delay(500);
 conveyor.move(0);


 //back up from center
 //drive backwards 20 inches
 chassis.pid_drive_set(-20_in, 110);
 chassis.pid_wait();


 //drive to long goal
 //turn to head 90 deg
 chassis.pid_turn_set(90_deg, 115); //og 90 speed
 chassis.pid_wait();
 //drive forward 37.5 inches
 chassis.pid_drive_set(39.5_in, 120); //CHANGE-2/15
 chassis.pid_wait();


 //score in long goal
 //turn to head 0 deg
 chassis.pid_turn_set(0_deg, 90);
 chassis.pid_wait();
 //drive backwards 15 inches
 chassis.pid_drive_set(-15_in, 122); //CHANGE-2/15
 chassis.pid_wait();
 //score
 conveyor.move(127);
 middle.move(127);
 outtake.move(127);
 scraper.set(true); //early prep for matchloader
 pros::delay(2600); //NEW-2/19
/*
 //back from goal
 chassis.pid_drive_set(5, 30);
 chassis.pid_wait();
*/


 //drive to matchloader
 //drive forward 27 inches
 chassis.pid_drive_set(27_in, 80); //CHANGE-2/15
 chassis.pid_wait();


 //use matchloader
 //in conveyor, wait 1.5 sec
 conveyor.move(127);
 pros::delay(800);


 //drive to long goal
 //drive backward 27 inches
 chassis.pid_drive_set(-27_in, 120); //NEW-2/19
 chassis.pid_wait();


 //score 3 long goal
 //outtake, 2 sec
 middle.move(127);
 outtake.move(127);
 pros::delay(1600);


 conveyor.move(-127);
 middle.move(-127);
 outtake.move(-127);
 pros::delay(100);


 conveyor.move(127);
 middle.move(127);
 outtake.move(127);
 pros::delay(1000);


 //back from goal
 /*
 chassis.pid_drive_set(5, 30);
 chassis.pid_wait();
 */
}


void right_auton_4() {


 //put preload near bottom of conveyor
 //position bot 12 inches from back wall along parking zone


 chassis.drive_angle_set(180_deg);  // Start the robot facing 45 degrees


 //drive to center blocks
 //drive forward 16 inches
 chassis.pid_drive_set(16_in, 110);
 chassis.pid_wait();


 //collect center blocks
 //turn to head 200 deg
 chassis.pid_turn_set(200_deg, 90);
 chassis.pid_wait();
 //in conveyor
 conveyor.move(127);
 //drive forward 4 inches
 chassis.pid_drive_set(4_in, 60);
 chassis.pid_wait();
 //turn to head 152
 chassis.pid_turn_set(215_deg, 55); //og 152
 chassis.pid_wait();
 chassis.pid_drive_set(6_in, 45); //2nd turn to blocks; og 4
 chassis.pid_wait();
 pros::delay(500);
 conveyor.move(0);


 //back up from center
 //drive backwards 20 inches
 chassis.pid_drive_set(-20_in, 90);
 chassis.pid_wait();


 //drive to long goal
 //turn to head 90 deg
 chassis.pid_turn_set(270_deg, 115);
 chassis.pid_wait();
 //drive forward 37.5 inches
 chassis.pid_drive_set(39.5_in, 120); //og 40
 chassis.pid_wait();


 //score in long goal
 //turn to head 0 deg
 chassis.pid_turn_set(0_deg, 90);
 chassis.pid_wait();
 //drive backwards 15 inches
 chassis.pid_drive_set(-15_in, 122); //og 90
 chassis.pid_wait();
 //score
 conveyor.move(127);
 middle.move(127);
 outtake.move(127);
 scraper.set(true); //early prep for matchloader
 pros::delay(2600); //og 3500 CAN CHANGE
/*
 //back from goal
 chassis.pid_drive_set(5, 30);
 chassis.pid_wait();
*/


 //drive to matchloader
 //drive forward 27 inches
 chassis.pid_drive_set(27_in, 85);
 chassis.pid_wait();


 //use matchloader
 //in conveyor, wait 1.5 sec
 conveyor.move(127);
 pros::delay(800); //og 1500


 //drive to long goal
 //drive backward 27 inches
 chassis.pid_drive_set(-27_in, 120); //og 90
 chassis.pid_wait();


 //score 3 long goal
 //outtake, 2 sec
 middle.move(127);
 outtake.move(127);
 pros::delay(1600);


 conveyor.move(-127);
 middle.move(-127);
 outtake.move(-127);
 pros::delay(200);


 conveyor.move(127);
 middle.move(127);
 outtake.move(127);
 pros::delay(1000);


 //back from goal
 chassis.pid_drive_set(5, 30);
 chassis.pid_wait();
}


void skills_auton_1() {
 master.print(0, 0, "c");
 //set heading
 chassis.drive_angle_set(180_deg);


 //turn to matchloader
 chassis.pid_drive_set(30_in, 63.5);
 chassis.pid_wait();


 chassis.pid_turn_set(270_deg, 60);
 chassis.pid_wait();


 //drive to matchlaoder
 scraper.set (true);
 pros::delay (1000);


 chassis.pid_drive_set(8.75_in, 63.5); //og 9-2/19
 chassis.pid_wait();


 //intake from matchloader
 conveyor_clog(6000);
 /*
 conveyor.move (127);
 pros::delay (3000); // picked up from first match loader


 conveyor.move (-127);
 pros::delay (500); 


 conveyor.move (127);
 pros::delay (1500);
 */


 chassis.pid_drive_set(-15_in, 63.5);
 chassis.pid_wait();


 chassis.pid_turn_set(180_deg, 60);
 chassis.pid_wait();


 //scraper.set (false); might help with getting all blocks
 //pros::delay (1000);


 //conveyor.move (0);


 //drive to other side
 //chassis.pid_turn_relative_set(180, 60);
 //chassis.pid_turn_set(270_deg, 60);
 //chassis.pid_wait();
 chassis.pid_drive_set(-48_in, 63.5);
 chassis.pid_wait();


 pros::delay(500);


 chassis.pid_drive_set(-48.5_in, 63.5); //at second side
 chassis.pid_wait();


 //drive to long goal
 chassis.pid_turn_set(270, 60);
 chassis.pid_wait();


 pros::delay (500);
 chassis.pid_drive_set(-15.5_in, 63.5); //og -18 -2/12
 chassis.pid_wait();


 conveyor.move (127); //scoreTop
 middle.move (127); //scoreTop
 outtake.move (127); //scoreTop
 pros::delay (1500); // scored first match loader


 conveyor.move(-127);
 pros::delay(700);
 conveyor.move(127);
 pros::delay(1800);


 //prep for matchloader
 //scraper.set (true); removed b/c never closed above
 pros::delay (3000);
 conveyor.move (0); //stopAll
 middle.move (0); //stopAll
 outtake.move (0); //stopAll


 //drive to matchloader 2
 chassis.pid_drive_set(5_in, 63.5); //going to match loader 2 pt 1
 chassis.pid_wait();
 chassis.pid_turn_set(270, 60);
 chassis.pid_wait();
 chassis.pid_drive_set(23_in, 63.5); //going to match loader 2 pt2; og 22 -2/12
 chassis.pid_wait();


 //intake from matchloader
/*
 conveyor.move (127);
 pros::delay (3000); // picked up from first match loader
 conveyor.move (-127);
 pros::delay (500); 
 conveyor.move (127);
 pros::delay (1500);
 conveyor.move (0);
*/


 conveyor_clog(6000); //og 2300


 //drive to long goal
 chassis.pid_drive_set(-27_in, 63.5); //backing to goal to score match loader 2
 chassis.pid_wait();
 conveyor.move (127); //scoreTop
 middle.move (127); //scoreTop
 outtake.move (127); //scoreTop
 pros::delay (1500); // scored first match loader


 conveyor.move(-127);
 middle.move(0); //NEW-2/16
 outtake.move(-127); //NEW-2/16
 pros::delay(800);


 conveyor.move(127);
 middle.move(127); //NEW-2/16
 outtake.move(127); //NEW-2/16
 pros::delay(3900); //og 3300-2/16


 //new 2/19
 conveyor.move(-127);
 middle.move(0);
 outtake.move(-127);
 pros::delay(500);


 conveyor.move(127);
 middle.move(127);
 outtake.move(127);
 pros::delay(1000);
 //end of new 2/19


 scraper.set (false);
 pros::delay (1500); //og 1000-2/16


 //NA: bc want to outtake all existing blocks NEW-2/16
 conveyor.move (0); //stopAll
 middle.move (0); //stopAll
 outtake.move (0); //stopAll


 pros::delay (500);


/*
 //repel blocks
 conveyor.move(-127);
 outtake.move(-127);
*/


 conveyor.move (127);
 middle.move (127);
 outtake.move (127);//outtake parking blocks


 //NEW PARKING
 chassis.pid_drive_set(8_in, 63.5);
 chassis.pid_wait();
 chassis.pid_turn_set(225_deg, 60);
 chassis.pid_wait();
 chassis.pid_drive_set(31_in, 63.5);
 chassis.pid_wait();
 chassis.pid_turn_set(186_deg, 60);
 chassis.pid_wait();
 chassis.pid_drive_set(42_in, 75); //og 41-2/19
 chassis.pid_wait();


 /* OLD PARKING
 //prep for parking
 chassis.pid_drive_set(8_in, 63.5);
 chassis.pid_wait();
 chassis.pid_turn_set(245_deg, 60);
 chassis.pid_wait();
 chassis.pid_drive_set(26_in, 63.5); //og 30 //18
 chassis.pid_wait();
  //parking
 //chassis.pid_drive_set(5_in, 63.5);//20
 //chassis.pid_wait();
 chassis.pid_turn_set(14_deg, 60);
 chassis.pid_wait();
 chassis.pid_drive_set(-10_in, 63.5);//-26
 chassis.pid_wait();


 chassis.pid_swing_set(ez::LEFT_SWING,0_deg, 60);
 chassis.pid_wait();
 //chassis.pid_turn_relative_set(3, 60);
 //chassis.pid_wait();
 chassis.pid_drive_set(-40_in, 110);//63.5
 chassis.pid_wait();
 */
}


void backup_auton() {
 //for when the alliance has a SAWP


 chassis.pid_drive_set(10_in, 90);
 chassis.pid_wait();
}


void skills_auton_2() {
 /*master.print(0, 0, "abc");


 chassis.pid_drive_set(-26_in, 90);
 chassis.pid_wait();


 conveyor.move(127);
 middle.move(127);
 outtake.move(127);
 chassis.pid_drive_set(26_in, 90);
 chassis.pid_wait();*/
 chassis.pid_drive_set(-9_in, 75);
 chassis.pid_wait();


 conveyor.move(127);
 middle.move(127);
 outtake.move(127);


 chassis.pid_drive_set(39_in, 75);
 chassis.pid_wait();
}

void clog_tester_auton() {
 scraper.set(true);
 pros::delay(200);


 chassis.pid_drive_set(10_in, 60);
 chassis.pid_wait();
 conveyor_clog(8000);
}
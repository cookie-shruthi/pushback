#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor conveyor(-17); //intake+conveyor
inline pros::Motor outtake(-20); //hood
inline pros::Motor middle(1); //middle roller

inline ez::Piston scraper('A'); //matchloader
inline ez::Piston descore('B'); //wing

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');
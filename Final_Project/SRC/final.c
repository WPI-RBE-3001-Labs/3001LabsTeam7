///*
// * final.c
// *
// *  Created on: Feb 18, 2017
// *      Author: coshea
// */
//#define SERVO_PIN 1 //end effector servo pin
//#define CLOSE 0 //servo value for closed
//#define OPEN 1 //servo value for Open
//#define SPEED 200 //amount of time it takes weight to go from IR sensor to arm x-plane
//#define VCONST 6 //voltage constant used to determine the weight of the block
//#define IRCHAN 5 //ir channel
//
//#include "Periph.h"
//
//
//int voltage;
//
//void finalmain(){
//
//waitForIR();
//systemTime = 0;
//while(systemTime < SPEED){
//inverse(generateXY());
//}
//setServo(SERVO_PIN, CLOSE);
//homePos();
//initCurrentSense(0);
//while(systemTime < 10000){
//voltage += currentToVolts(currentSense(0));
//}
//float volts = voltage/10000;
//if(volts > VCONST){
//	drop();
//}
//else dropOtherSide();
//homePos();
//}
//
//void waitForIR(){
//	while(IRDist(IRCHAN) == 0){}
//}
//
//void generateXY(){
//
//}
//
//float currentToVolts(int current){
//	float resistance = 51;
//	float v = current * resistance;
//	return v;
//}
//
//void dropOtherSide(){
//	inverse();
//	drop();
//}
//

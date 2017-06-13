//   Version 1.1  (31th January 2014)
// Done by Luis Ródenas <luisrodenaslorda@gmail.com>
// Based on the I2Cdev library and previous work by Jeff Rowberg <jeff@rowberg.net>
// Updates (of the library) should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
 
// These offsets were meant to calibrate MPU6050's internal DMP, but can be also useful for reading sensors. 
// The effect of temperature has not been taken into account so I can't promise that it will work if you 
// calibrate indoors and then use it outdoors. Best is to calibrate and use at the same room temperature.
 
/* ==========  LICENSE  ==================================
 I2Cdev device library code is placed under the MIT license
 Copyright (c) 2011 Jeff Rowberg
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 =========================================================
 */
 

// I2Cdev and MPU6050 must be installed as libraries
#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <wiringPi.h> 
#include <signal.h>
#include "GestionMPU6050.h"
 
using namespace std;

///////////////////////////////////   CONFIGURATION   /////////////////////////////
//Change this 3 variables if you want to fine tune the skecth to your needs.
int buffersize=1000;     //Amount of readings used to average, make it higher to get more precision but sketch will be slower  (default:1000)
int acel_deadzone=8;     //Acelerometer error allowed, make it lower to get more precision, but sketch may not converge  (default:8)
int giro_deadzone=2;     //Giro error allowed, make it lower to get more precision, but sketch may not converge  (default:1)
 
// default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
//MPU6050 accelgyro;
GestionMPU6050 accelgyro(ADDRESS_AD0_HIGH); // <-- use for AD0 high
 
int16_t ax, ay, az,gx, gy, gz;
 
int mean_ax,mean_ay,mean_az,mean_gx,mean_gy,mean_gz,state=0;
int ax_offset,ay_offset,az_offset,gx_offset,gy_offset,gz_offset;
 
// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
    cout << "FIN signal: " << sig << endl;
   cout << "getXAccelOffset: " << accelgyro.getXAccelOffset() << endl;
     cout << "getYAccelOffset: " << accelgyro.getYAccelOffset() << endl;
     cout << "getZAccelOffset: " << accelgyro.getZAccelOffset() << endl;
     cout << "getXGyroOffset: " << accelgyro.getXGyroOffset() << endl;
     cout << "getYGyroOffset: " << accelgyro.getYGyroOffset() << endl;
     cout << "getZGyroOffset: " << accelgyro.getZGyroOffset() << endl;
   exit(0);
}

///////////////////////////////////   SETUP   ////////////////////////////////////
void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  
  // initialize device
  accelgyro.defaultInitialize();
 
  // start message
  cout << "\nMPU6050 Calibration Sketch" << endl;
  delay(2000);
  cout << "\nYour MPU6050 should be placed in horizontal position, with package letters facing up. \nDon't touch it until you see a finish message.\n" << endl;
  delay(3000);
  // verify connection
  if (accelgyro.isConnectionOK()) {
	  cout << "MPU6050 connection successful" << endl;
  } else {
	  cout << "MPU6050 connection failed" << endl;
  }
  delay(1000);
  // reset offsets
  accelgyro.setXAccelOffset(0);
  accelgyro.setYAccelOffset(0);
  accelgyro.setZAccelOffset(0);
  accelgyro.setXGyroOffset(0);
  accelgyro.setYGyroOffset(0);
  accelgyro.setZGyroOffset(0);
}
 
///////////////////////////////////   FUNCTIONS   ////////////////////////////////////
void meansensors(){
  long i=0,buff_ax=0,buff_ay=0,buff_az=0,buff_gx=0,buff_gy=0,buff_gz=0;
 
  while (i<(buffersize+101)){
    // read raw accel/gyro measurements from device
    // accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	ax = accelgyro.getAccelX();
	ay = accelgyro.getAccelY();
	az = accelgyro.getAccelZ();
	gx = accelgyro.getGyroX();
	gy = accelgyro.getGyroY();
	gz = accelgyro.getGyroZ();
   
    if (i>100 && i<=(buffersize+100)){ //First 100 measures are discarded
      buff_ax=buff_ax+ax;
      buff_ay=buff_ay+ay;
      buff_az=buff_az+az;
      buff_gx=buff_gx+gx;
      buff_gy=buff_gy+gy;
      buff_gz=buff_gz+gz;
    }
    if (i==(buffersize+100)){
      mean_ax=buff_ax/buffersize;
      mean_ay=buff_ay/buffersize;
      mean_az=buff_az/buffersize;
      mean_gx=buff_gx/buffersize;
      mean_gy=buff_gy/buffersize;
      mean_gz=buff_gz/buffersize;
    }
    i++;
    delay(2); //Needed so we don't get repeated measures
  }
}
 
void calibration(){
  ax_offset=-mean_ax/8;
  ay_offset=-mean_ay/8;
  az_offset=(16384-mean_az)/8;
 
  gx_offset=-mean_gx/4;
  gy_offset=-mean_gy/4;
  gz_offset=-mean_gz/4;
  while (1){
    int ready=0;
    accelgyro.setXAccelOffset(ax_offset);
    accelgyro.setYAccelOffset(ay_offset);
    accelgyro.setZAccelOffset(az_offset);
 
    accelgyro.setXGyroOffset(gx_offset);
    accelgyro.setYGyroOffset(gy_offset);
    accelgyro.setZGyroOffset(gz_offset);
 
    meansensors();
    cout << "..." << endl;
	
	cout << "ax: " << abs(mean_ax) << endl;
	cout << "ay: " << abs(mean_ay) << endl;
	cout << "az: " << abs(16384-mean_az) << endl;
	cout << "gx: " << abs(mean_gx) << endl;
	cout << "gy: " << abs(mean_gy) << endl;
	cout << "gz: " << abs(mean_gz) << endl;
 
    if (abs(mean_ax)<=acel_deadzone) ready++;
    else ax_offset=ax_offset-mean_ax/acel_deadzone;
 
    if (abs(mean_ay)<=acel_deadzone) ready++;
    else ay_offset=ay_offset-mean_ay/acel_deadzone;
 
    if (abs(16384-mean_az)<=acel_deadzone) ready++;
    else az_offset=az_offset+(16384-mean_az)/acel_deadzone;
 
    if (abs(mean_gx)<=giro_deadzone) ready++;
    else gx_offset=gx_offset-mean_gx/(giro_deadzone+1);
 
    if (abs(mean_gy)<=giro_deadzone) ready++;
    else gy_offset=gy_offset-mean_gy/(giro_deadzone+1);
 
    if (abs(mean_gz)<=giro_deadzone) ready++;
    else gz_offset=gz_offset-mean_gz/(giro_deadzone+1);
 
    if (ready==6) break;
  }
}

///////////////////////////////////   LOOP   ////////////////////////////////////
int  main() {
    // Ecoute du CTRL-C avec fonction à lancer
	// Au cas ou le programme ne converge pas
    signal(SIGINT, fin);
	setup();
  if (state==0){
    cout << "\nReading sensors for first time..." << endl;
    meansensors();
    state++;
    delay(1000);
  }
 
  if (state==1) {
    cout << "\nCalculating offsets..." << endl;
    calibration();
    state++;
    delay(1000);
  }
 
  if (state==2) {
    meansensors();
    cout << "\nFINISHED!" << endl;
    cout << "\nSensor readings with offsets:\t" << endl;
    cout << mean_ax << endl;
    cout << mean_ay << endl;
    cout << mean_az << endl;
    cout << mean_gx << endl;
    cout << mean_gy << endl;
    cout << mean_gz << endl << endl;
    cout << "Your offsets:\t" << endl;
    cout << "Ax: " << ax_offset << endl;
    cout << "Ay: " << ay_offset << endl;
    cout << "Az: " << az_offset << endl;
    cout << "Gx: " << gx_offset << endl;
    cout << "Gy: " << gy_offset << endl;
    cout << "Gz: " << gz_offset << endl << endl;
    cout << "\nData is printed as: acelX acelY acelZ giroX giroY giroZ" << endl;
    cout << "Check that your sensor readings are close to 0 0 16384 0 0 0" << endl;
    cout << "If calibration was succesful write down your offsets so you can set them in your projects using something similar to mpu.setXAccelOffset(youroffset)" << endl;
    exit(0);
  }
}
 

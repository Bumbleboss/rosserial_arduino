#include <ros.h>
#include <Stepper.h>
#include <std_msgs/String.h>

// 28BYJ-48 step motor revolution and pins setup
const int stepsPerRevolution = 2038;
Stepper myStepper = Stepper(stepsPerRevolution, 9, 11, 10, 12);

// setup node
ros::NodeHandle nh;

// message callback
// when a message is received in the topic, proceed to do something with message value
// in this example, rotate clockwise or counter-clockwise depending on message
void messageCb(const std_msgs::String& arrow){
	// CLOCKWISE
	if (strcmp(arrow.data, "c")==0) {
		myStepper.setSpeed(11);
		myStepper.step(-stepsPerRevolution);
	}

	// COUNTER CLOCKWISE
	else if (strcmp(arrow.data, "cc")==0) {
		myStepper.setSpeed(11);
		myStepper.step(stepsPerRevolution);
	}
}

// define subscriber
ros::Subscriber<std_msgs::String> sub("/stepper_controller", &messageCb);

// initialize node and subscribe to topics
void setup() {
  nh.initNode();
  nh.subscribe(sub);
}

// handle communication with ros
void loop() {
  nh.spinOnce();
  delay(1);
}
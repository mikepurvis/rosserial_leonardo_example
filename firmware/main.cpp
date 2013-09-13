#include "ros.h"
#include <std_msgs/Bool.h>
#include <std_msgs/UInt32.h>

#include <Arduino.h>

ros::NodeHandle nh;

std_msgs::UInt32 num_msg;
ros::Publisher num_pub("/sense", &num_msg);

void reset_cb(const std_msgs::Bool& reset_msg) {
  if (reset_msg.data == 1) {
    num_msg.data = 0; 
  }
}

ros::Subscriber<std_msgs::Bool> reset_sub("reset", reset_cb);

void setup(){
  nh.initNode();
  nh.subscribe(reset_sub);
  nh.advertise(num_pub); 
}

void loop() {
  nh.spinOnce();

  static uint32_t last_tick = 0;
  if (millis() - last_tick >= 100) {  // 50 Hz
    last_tick = millis();
    num_pub.publish(&num_msg);
  }
}

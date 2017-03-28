#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "sensor_msgs/LaserScan.h"
#include <sstream>

void callback(const sensor_msgs::LaserScan::ConstPtr& input, ros::Publisher pub){
	
	int size = (input->ranges).size();
	//ROS_INFO("Size: %d", size);
	
	//float* vec = (input->ranges);
	float min = (input->ranges)[0];
	
	for(int i = 1; i < size; ++i){
	  if((input->ranges)[i] < min) min = (input->ranges)[i];
	}
	
	std_msgs::Float32 output;
	output.data = min;

	//ROS_INFO("Min: %f", output.data);

	pub.publish(output);

	ros::spinOnce();
  
}

int main(int argc, char **argv){

	ros::init(argc, argv, "vnode");

	ros::NodeHandle n;
	
	ros::Publisher pub = n.advertise<std_msgs::Float32>("min_val", 1000);

	ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("base_scan", 1000, boost::bind(callback, _1, pub));
	
	ros::spin();

  return 0;
}

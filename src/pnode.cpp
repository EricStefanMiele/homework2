#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "std_msgs/String.h"
#include <tf/transform_listener.h>
#include "sensor_msgs/LaserScan.h"
#include <sstream>

void callback(const sensor_msgs::LaserScan::ConstPtr& input, ros::Publisher pub){
	
	tf::TransformListener listener;
	
	tf::StampedTransform transform;
	
	ros::Time t = (input->header).stamp;
	
	//ROS_INFO("%u",t.sec);
	
	//if(listener.canTransform("/odom", "/base_laser_link", t, NULL)){
		
		listener.lookupTransform("/odom", "/base_laser_link", t, transform);
		
		std_msgs::String output;
	
		std::stringstream ss;
		
		ss << "Timestamp: " << transform.stamp_;
		
		output.data = ss.str();

		//ROS_INFO("Min: %f", output.data);

		pub.publish(output);

		ros::spinOnce();
	//}
	//else ROS_INFO("Could not transform");
	
}

int main(int argc, char **argv){

	ros::init(argc, argv, "pnode");

	ros::NodeHandle n;
	
	ros::Publisher pub = n.advertise<std_msgs::String>("pos_val", 1000);

	ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("base_scan", 1000, boost::bind(callback, _1, pub));
	
	ros::spin();

  return 0;
}

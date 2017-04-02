#include <tf/transform_broadcaster.h>
#include "std_msgs/String.h"
#include <tf/transform_listener.h>
#include "sensor_msgs/LaserScan.h"
#include <sstream>

void callback(const sensor_msgs::LaserScan::ConstPtr& input, ros::Publisher pub){
	
	tf::TransformListener listener;
	tf::StampedTransform transform;
	
	if(listener.canTransform("/odom", "/base_laser_link", ros::Time(0), NULL)){
		
		listener.lookupTransform("/odom", "/base_laser_link", ros::Time(0), transform);
		
		tf::Vector3 coordinates = transform.getOrigin();
		
		float x = coordinates.getX();
		float y = coordinates.getY();
		float z = coordinates.getZ();
		
		std_msgs::String output;
	
		std::stringstream ss;
		
		ss << "Timestamp: " << (input->header).stamp << " - ";
		ss << "X: " << x << " - ";
		ss << "Y: " << y << " - ";
		ss << "X: " << z;
		
		output.data = ss.str();
		
		pub.publish(output);

		ros::spinOnce();
	}
	else printf("Unable to transform\n");
	
}

int main(int argc, char **argv){

	ros::init(argc, argv, "pnode");

	ros::NodeHandle n;

	ros::Publisher pub = n.advertise<std_msgs::String>("pos_val", 1000);

	ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("base_scan", 1000, boost::bind(callback, _1, pub));

	ros::spin();

	return 0;
}

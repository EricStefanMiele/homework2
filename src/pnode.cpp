#include <tf/transform_broadcaster.h>
#include "std_msgs/String.h"
#include <tf/transform_listener.h>
#include "sensor_msgs/LaserScan.h"
#include <sstream>

void callback(const sensor_msgs::LaserScan::ConstPtr& input, ros::Publisher pub, tf::TransformListener* listener){
	
	tf::StampedTransform transform;
	
	ros::Time stamp = (input->header).stamp;
	
	if(listener->canTransform("/odom", "/base_laser_link", stamp, NULL)){
	
		//listener->waitForTransform("/odom", "/base_laser_link", stamp, ros::Duration(10));
			
		listener->lookupTransform("/odom", "/base_laser_link", stamp, transform);
		
		tf::Vector3 coordinates = transform.getOrigin();
				
		float x = coordinates.getX();
		float y = coordinates.getY();
		//float z = coordinates.getZ();
		
		tf::Quaternion q = transform.getRotation();
		
		float theta = q.getAngle();
		
		std_msgs::String output;
	
		std::stringstream ss;
		
		ss << "Timestamp: " << stamp << " - ";
		ss << "X: " << x << " - ";
		ss << "Y: " << y << " - ";
		ss << "Theta: " << theta;
		
		output.data = ss.str();
		
		//printf("%s\n",output.data.c_str());
		
		pub.publish(output);

		ros::spinOnce();
	}
	else printf("Transformation not available\n");
	
}

int main(int argc, char **argv){

	ros::init(argc, argv, "pnode");
	
	tf::TransformListener listener;

	ros::NodeHandle n;

	ros::Publisher pub = n.advertise<std_msgs::String>("pos_val", 1000);

	ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("base_scan", 1000, boost::bind(callback, _1, pub, &listener));

	ros::spin();

	return 0;
}

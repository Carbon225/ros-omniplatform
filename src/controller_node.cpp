#include <ros/ros.h>

#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>


ros::Publisher cmdVelPub;

void joyCallback(const sensor_msgs::Joy &joy);

int main(int argc, char **argv)
{

    ros::init(argc, argv, "controller_node");
    ros::NodeHandle nh;

    ros::Subscriber joySub = nh.subscribe("joy", 128, joyCallback);

    cmdVelPub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 128);

    ros::spin();

    return 0;
}

void joyCallback(const sensor_msgs::Joy &joy)
{
    geometry_msgs::Twist twist;
    twist.linear.y = abs(joy.axes[0]) > 0.1 ? joy.axes[0] : 0.f;
    twist.linear.x = abs(joy.axes[1]) > 0.1 ? joy.axes[1] : 0.f;
    twist.angular.z = abs(joy.axes[3]) > 0.1 ? joy.axes[3] : 0.f;

    double speed = (-joy.axes[5] + 1.f) / 2.f;
    twist.linear.x *= speed;
    twist.linear.y *= speed;
    twist.angular.z *= speed;

    cmdVelPub.publish(twist);
}

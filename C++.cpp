#include "mas_solarsystem/celestial_body.h"

CelestialBody::CelestialBody()
  :Node("celestial_body_node",rclcpp::NodeOptions().allow_undeclared_parameters(true).automatically_declare_parameters_from_overrides(true))
{
 orb_ = this->get_parameter("rad").as_double();
 p_rev_ = this->get_parameter("per_rev").as_double();
 rayon_ = this->get_parameter("rayons").as_double();
 p_rot_ = this->get_parameter("per_rot").as_double();
 parentframe_id_ = this->get_parameter("parentframe_id").as_string();
 childframe_id_ = this->get_parameter("childframe_id").as_string();
 
 marker.header.frame_id = childframe_id_;  
marker.header.stamp = this->get_clock()->now();
marker.ns = "namespace";  
marker.id = 0;  

marker.type = visualization_msgs::msg::Marker::SPHERE;  
marker.action = visualization_msgs::msg::Marker::ADD;  


marker.pose.position.x = 0.0;
marker.pose.position.y = 0.0;
marker.pose.position.z = 0.0;  


marker.pose.orientation.x = 0.0;
marker.pose.orientation.y = 0.0;  
marker.pose.orientation.z = 0.0;
marker.pose.orientation.w = 1.0;  

marker.scale.x = rayon_;  
marker.scale.y = rayon_;  
marker.scale.z = rayon_;  

marker.color.r = 1.0;  
marker.color.g = 1.0;
marker.color.b = 0.0;
marker.color.a = 0.5;  

marker.lifetime = rclcpp::Duration(10,0);  
   double xx = rad_ * cos(pos_ang_);
    double yy = rad_ * sin(pos_ang_);
    double zz = 0.0;
 
   
    tf2::Quaternion orientation;
    orientation.setRPY(0.0, 0.0, pos_ang_);
   
    transform_.header.stamp = this->now();
   transform_.header.frame_id = parentframe_id_;
    transform_.child_frame_id = childframe_id_;
    transform_.transform.translation.x = x ;
    transform_.transform.translation.y = y;
    transform_.transform.translation.z = z;
    transform_.transform.rotation.x = 0.0;
    transform_.transform.rotation.y = 0.0;
    transform_.transform.rotation.z = 0.0;
    transform_.transform.rotation.w = 0.0;
 



 marker_pub_ = this->create_publisher<visualization_msgs::msg::Marker>("marker", 1);
 tf_broadcaster_ =std::make_shared<tf2_ros::TransformBroadcaster>(this);
 timer_pub_ =  this->create_wall_timer(std::chrono::milliseconds(50), std::bind(&CelestialBody::publishMarker, this));

}

void CelestialBody::pubMarkerTransform()
{
 
  marker.header.stamp = this->get_clock()->now();
 
   marker_pub_->publish(marker);

  transform_.header.stamp = this->now();
  transform_.header.frame_id = parentframe_id_;
  transform_.child_frame_id = childframe_id_;


 
transform_.transform.translation.x = orb_ * cos(pos_ang_);
transform_.transform.translation.y = orb_ * sin(pos_ang_);
 
 
 
  tf_broadcaster_->sendTransform(transform_);
pos_ang_ += 2.0 * M_PI / (orb_ * 50);
}
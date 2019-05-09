#include <string>
#include <ros/ros.h>
#include "behaviortree_cpp/bt_factory.h"

#include "ApproachObject.h"
#include "InitialiserRobot.h"
#include "IsNotTimeOut.h"
#include "AfficherLeScore.h"
#include "robot_sensors_nodes.h"

using namespace BT;

// WORK :
// catkin_make then
// roscore &
// rosrun sd_behavior maintree src/sd_behavior/config/bt_demo.xml

ros::Subscriber test_subscriber_;
//ros::Subscriber subscriber_camp;

int main(int argc, char* argv[])
{
	ros::init(argc, argv, "robot_behavior");
  	ros::NodeHandle nh;

  	BehaviorTreeFactory factory;
	factory.registerNodeType<RobotNodes::ApproachObject>("ApproachObject");
	factory.registerNodeType<RobotNodes::InitialiserRobot>("InitialiserRobot");
	factory.registerNodeType<RobotNodes::AfficherLeScore>("AfficherLeScore");
	factory.registerSimpleCondition("IsTirettePresente", std::bind(RobotSensors::IsTirettePresente));
	factory.registerSimpleCondition("IsPaletCentre", std::bind(RobotSensors::IsPaletCentre));
	factory.registerSimpleCondition("IsPaletGauche", std::bind(RobotSensors::IsPaletGauche));
	factory.registerSimpleCondition("IsPaletDroit", std::bind(RobotSensors::IsPaletDroit));
	factory.registerSimpleCondition("IsVentouseGauche", std::bind(RobotSensors::IsVentouseGauche));
	factory.registerSimpleCondition("IsVentouseDroit", std::bind(RobotSensors::IsVentouseDroit));
	factory.registerSimpleCondition("IsVentouseCentre", std::bind(RobotSensors::IsVentouseCentre));
	factory.registerSimpleCondition("IsNotTimeOut", std::bind(RobotNodes::IsNotTimeOut));
	factory.registerSimpleCondition("IsCampViolet", std::bind(RobotSensors::IsCampViolet));
	
	//RobotSensors::init(factory, nh);

 

	test_subscriber_ = nh.subscribe("/r1/pilo/switches", 1, RobotSensors::rosUpdateSwitch);
//	subscriber_camp = nh.subscribe("/test_topic2", 1, RobotSensors::rosUpdateCampViolet);

	//	GripperInterface gripper;
	//	factory.registerSimpleAction("OpenGripper", std:bind(&GripperInteface::open, &gripper));
	//	factory.registerSimpleAction("CloseGripper", std:bind(&GripperInteface::close, &gripper));
	
	std::string fn = argv[1];
	auto tree = factory.createTreeFromFile(fn);

	BT::NodeStatus status = NodeStatus::RUNNING;
	
	ros::Rate rate(100);
    while(ros::ok() && status != NodeStatus::FAILURE) {
      ros::spinOnce();
      status = tree.root_node->executeTick();
      rate.sleep();
    }

    // Wait for ROS threads to terminate
  	ros::waitForShutdown();

	return 0;
}

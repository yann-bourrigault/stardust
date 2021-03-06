#!/bin/bash

# If used with a parameter, this script remove all ros services at startup
if [ "$#" -eq 0 ]; then
	if [ -f /tmp/ros.pid ]; then
		echo "Stopping ROS..."
		kill -n SIGINT `cat /tmp/ros.pid`
		sleep 1
		ROS_COUNT=`ps -aux | grep roslaunch | wc -l`
		while [ ! "$ROS_COUNT" -eq 1 ]; do
			echo "ROS is still stopping... please WAIT"
			sleep 1
			ROS_COUNT=`ps -aux | grep roslaunch | wc -l`
		done
		rm /tmp/ros.pid
		echo "ROS stopped"
	else
		echo "ROS is stopped or was not started by this script"
	fi
elif [ "$#" -eq 1 ]; then
	echo "Removing all ROS services at statup"
	sudo systemctl list-unit-files | awk '{if ($2 == "enabled" && $1 ~ /^ *ros_/) { print $1 } }' | xargs sudo systemctl disable
	echo "Successfully removed all ROS services at statup"
fi

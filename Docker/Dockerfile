# docker build -t ros2:foxy .
# docker run --rm -it ros2:foxy

FROM ubuntu:20.04
ENV TZ Asia/Tokyo
ENV DEBIAN_FRONTEND=noninteractive

ENV ROS_DISTRO foxy

# Local setup
RUN apt update -y
RUN apt upgrade -y

# install ROS2
RUN apt update && apt install curl gnupg2 lsb-release -y
RUN curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add -
RUN sh -c 'echo "deb [arch=$(dpkg --print-architecture)] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" > /etc/apt/sources.list.d/ros2-latest.list'
RUN apt update -y
RUN apt install ros-$ROS_DISTRO-ros-base -y tzdata

RUN apt install python3-colcon-common-extensions -y
RUN apt install -y python3-pip -y
RUN pip3 install -U argcomplete

# set environment
RUN echo "source /opt/ros/$ROS_DISTRO/setup.bash" >> ~/.bashrc
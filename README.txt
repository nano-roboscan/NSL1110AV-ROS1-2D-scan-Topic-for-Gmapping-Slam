#Gmapping 2D scan topic (ros1)
**2D scan data를 사용하는 Gmapping slam을 사용하기 위해 3D data를 2D scan topic에 맞는 데이터로 변환하였습니다.**
**발행된 2D scan data를 이용하여 자신의 로봇에 맞게 gmapping slam을 적용하시면 됩니다.**

1. ros 환경 설치
- source.list 설정
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'​
- key 설정
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654​
- 패키지 업데이트
sudo apt update
- ros melodic 버전 풀패키지 설치
sudo apt install ros-melodic-desktop-full
- 패키지 작성을 위한 툴 설치
sudo apt-get install python-rosinstall python-rosinstall-generator python-wstool build-essential
- rosdep 설치
sudo apt install python-rosdep
- rosdep 초기화
sudo rosdep init
rosdep update


------------------------------ 추가 gmapping을 위한 패키지 설치 ------------------------------
sudo apt install -y ros-melodic-tf \
    ros-melodic-joy \
    ros-melodic-teleop-twist-joy \
    ros-melodic-teleop-twist-keyboard ros-melodic-laser-proc \
    ros-melodic-rgbd-launch ros-melodic-depthimage-to-laserscan \
    ros-melodic-rosserial-arduino ros-melodic-rosserial-python \
    ros-melodic-rosserial-server \
    ros-melodic-rosserial-client \
    ros-melodic-rosserial-msgs ros-melodic-amcl \
    ros-melodic-map-server \
    ros-melodic-move-base \
    ros-melodic-urdf \
    ros-melodic-xacro \
    ros-melodic-compressed-image-transport \
    ros-melodic-rqt-image-view \
    ros-melodic-gmapping \
    ros-melodic-navigation \
    ros-melodic-interactive-markers \
    ros-melodic-ar-track-alvar \
    ros-melodic-ar-track-alvar-msgs \
    ros-melodic-usb-cam
-------------------------------------------------------------------------------------------------------

2. build 환경
**catkin_make**
- 홈 디렉토리로 이동
cd ~
- 빌드 폴더 생성
mkdir catkin_n/src -p
- 빌드 폴더 이동
cd catkin_n/src
- 작업환경 생성
catkin_init_workspace
- 패키지 생성
catkin_create_pkg catkin_n roscpp
- /catkin_n/src/catkin_n의 하위 디렉토리와 파일을 참고하여 소스 및 파일 수정
 CMakeList.txt, package.xml, src/roboscan_publish_node.cpp, msg 폴더 
- 작업 디렉토리로 이동
cd ~/catkin_n
- 빌드
catkin_make
- 수정된 사항 적용
source ./devel/setup.bash
- ros 2D scan topic 발행
rosrun catkin_n roboscan_publish_node



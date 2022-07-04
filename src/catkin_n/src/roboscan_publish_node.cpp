#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/types.hpp>

#include <ros/ros.h>
#include <std_msgs/UInt8MultiArray.h>
#include <std_msgs/Float32.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <time.h>
#include <vector>


#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud.h>


//control + C event
#include <cstdio>
#include <sys/stat.h>
#include <cstdlib>
#include <unistd.h>
#include "std_msgs/String.h"


using namespace std;
using namespace cv;

// Lidar Parameter
#define ADC_OVERFLOW		65500
#define SATURATION		65400
#define MAX_DISTANCE_MM_12Mhz 	12500
#define MAX_DISTANCE_MM_24Mhz 	6250
#define MAX_PASE  				30000
#define IMAGE_WIDTH 				320
#define IMAGE_HEIGHT				240
#define IMAGE_SIZE				76800 	// 320x240
#define DISTANCE_OFFSET			0 		// 거리정보의 OFFSET 만큼 보정한다.
#define AMPLITUDE_THRESHOLD		20  	// 경계값이하의 약한 신호는 사용하지 않음. 20 100
#define DISTANCE_THRESHOLD		200  	// 경계값이하의 약한 신호는 사용하지 않음.
#define BUFF_SIZE   				153600
static uint8_t *distanceBuff;
static uint8_t *amplutudeBuff;
static uint8_t *response;
static int *dist;
/////////////////////////////////////////////////
clock_t start = clock();

	uint16_t *pMemDistance = 0;
	uint16_t *pMemAmplitude = 0;

float cntVel = 0.0;
float cntAng = 0.0;

void (*breakCapture)(int);

void signalingHandler(int signo) {
  printf("'Ctrl + C' processing...");

  exit(1);
}


// Lidar Function
void lidar_init(void)
{
	response = (uint8_t *)malloc(sizeof(char)*BUFF_SIZE*2);
	distanceBuff = (uint8_t *)malloc(sizeof(char)*BUFF_SIZE);
	amplutudeBuff = (uint8_t *)malloc(sizeof(char)*BUFF_SIZE);	
	dist = (int *)malloc(sizeof(char)*BUFF_SIZE);	
}

void lidar_close(void)
{
	free(response);
	free(distanceBuff);
	free(amplutudeBuff);
	free(dist);
}

inline int lidar_calcDistance(int phase)
{
	int data = MAX_DISTANCE_MM_12Mhz * phase/MAX_PASE;

	if(phase < 0)
		return -1;

	if(data > DISTANCE_OFFSET) data -= DISTANCE_OFFSET;
	else data = 0;

	return data;
}

int* lidar_getDistanceAndAmplitudeSorted()
{
	int client_socket;
	struct sockaddr_in   server_addr;

	int sum = 0;
	int nbyte = 256;
	static unsigned char  buff[1024];

#if 1
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(50660);
	server_addr.sin_addr.s_addr = inet_addr("192.168.7.2");

	client_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(-1 == client_socket)
	{
		printf("Can not open socket\n");
		exit( 1);
	}
   
	if(-1 == connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
	{
		printf("Socket not connect\n");
		exit(1);
   	}

	send(client_socket, "getDistanceAndAmplitudeSorted", strlen("getDistanceAndAmplitudeSorted")+1, 0); // +1: NULL까지 포함해서 전송
   
	while(nbyte!=0)
	{
		nbyte = recv( client_socket, buff, 1024, 0);
		memcpy(response+sum , buff , sizeof(buff));
		sum += nbyte;
	}

	memcpy(distanceBuff, response, BUFF_SIZE);
	memcpy(amplutudeBuff, response+BUFF_SIZE, BUFF_SIZE);

	close(client_socket);

	pMemDistance = (uint16_t *)distanceBuff;
	pMemAmplitude = (uint16_t *)amplutudeBuff;


	for(int y = 0; y < IMAGE_HEIGHT; y++)
	{
		for(int x = 0; x < IMAGE_WIDTH; x++)
		{
			// if(x == 160 && y == 120)
			// 		printf("(160, 120) Distance : %%d\n", dist[320*y + x]);

			if((pMemDistance[y*IMAGE_WIDTH + x] == ADC_OVERFLOW) || (pMemDistance[y*IMAGE_WIDTH + x] == SATURATION))
				dist[y*IMAGE_WIDTH + x] = 0;
			else
				dist[y*IMAGE_WIDTH + x] = lidar_calcDistance(pMemDistance[y*IMAGE_WIDTH + x]);
			
			if(pMemDistance[y*IMAGE_WIDTH + x] < DISTANCE_THRESHOLD)
				dist[y*IMAGE_WIDTH + x] = 0;
			// else if(pMemDistance[y*IMAGE_WIDTH + x] < DISTANCE_THRESHOLD)
			// 	dist[y*IMAGE_WIDTH + x] = 0;
			else if(pMemAmplitude[y*IMAGE_WIDTH + x] < AMPLITUDE_THRESHOLD) // max 6M
			 	dist[y*IMAGE_WIDTH + x] = 0;
			
				

//			if(x == 160 && y == 120)
//				printf("(160, 120) Distance : %.2f cm\n", dist[320*y + x]*0.1);
		}
	}
#endif

	return dist;
}

typedef struct _RGB888Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB888Pixel;

int Convert_To_RGB24_2( float fValue, RGB888Pixel *nRGBData, float fMinValue, float fMaxValue)
{
    if(fValue == 0) //Invalide Pixel
    {
        nRGBData->r = 0;//R
        nRGBData->g = 0;//G
        nRGBData->b = 0;//B
    }
    else if(fValue < fMinValue)
    {
        nRGBData->r = 255;//R
        nRGBData->g = 0;//G
        nRGBData->b = 0;//B
    }
    else if(fValue > fMaxValue)
    {
        nRGBData->r = 255;//R
        nRGBData->g = 0;//G
        nRGBData->b = 255;//B
    }
    else
    {
        float fColorWeight;
        fColorWeight = (fValue-fMinValue) / (fMaxValue-fMinValue);

        if( (fColorWeight <= 1.0f) && (fColorWeight > 0.8f) )
        {
            nRGBData->r = (unsigned char)(255 * ((fColorWeight - 0.8f) / 0.2f));//값에 따라 증가
            nRGBData->g = 0;
            nRGBData->b = 255;
        }
        else if( (fColorWeight <= 0.8f) && (fColorWeight > 0.6f) )
        {
            nRGBData->r = 0;
            nRGBData->g = (unsigned char)(255 * (1.0f - (fColorWeight - 0.6f) / 0.2f));//값에 따라 감소
            nRGBData->b = 255;
        }
        else if( (fColorWeight <= 0.6f) && (fColorWeight > 0.4f) )
        {
            nRGBData->r = 0;
            nRGBData->g = 255;
            nRGBData->b = (unsigned char)(255 * ((fColorWeight - 0.4f) / 0.2f));//값에 따라 증가
        }
        else if( (fColorWeight <= 0.4f) && (fColorWeight > 0.2f) )
        {
            nRGBData->r = (unsigned char)(255 * (1.0f - (fColorWeight - 0.2f) / 0.2f));//값에 따라 감소
            nRGBData->g = 255;
            nRGBData->b = 0;
        }
        else if( (fColorWeight <= 0.2f) && (fColorWeight >= 0.0f) )
        {
            nRGBData->r = 255;
            nRGBData->g = (unsigned char)(255 * ((fColorWeight - 0.0f) / 0.2f));//값에 따라 증가
            nRGBData->b = 0;
        }
        else
        {
            nRGBData->r = 0;
            nRGBData->g = 0;
            nRGBData->b = 0;
        }
    }

    return true;
}
/*
std::vector<geometry_msgs::PoseStamped::ConstPtr> pose;
void odomCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
	ROS_INFO("I heard: [%s]", msg->data.c_str());
	//ROS_INFO("x : %f", msg->x);
	//ROS_INFO("y : %f", msg->y);
	//ROS_INFO("z : %f", msg->z);
	//ROS_INFO("Receive pose : "<< msg);
	//ROS_INFO_STREAM(x_current);
	//pose.push_back(msg);
}
*/
/*
void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
	ROS_INFO("Seq: [%d]", msg->header.seq);
	ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
	ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x, msg->twist.twist.angular.z);
}
*/

int main(int argc, char** argv)
{
	// Initialize
	lidar_init();
	ros::init(argc, argv, "roboscan_publish_node");
    	
	ros::NodeHandle n;
	ros::Publisher pubScan = n.advertise<sensor_msgs::LaserScan>("scan", 50);

	unsigned int num_readings = 320;
	double laser_frequency = 200;
	double ranges[num_readings];
	double intensities[num_readings];

	int count = 0;    	



	cv::Mat imageLidar(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC3, Scalar(255,255,255));
	
	RGB888Pixel* pTex = new RGB888Pixel[1];

	float dist2D[320] = {0.0f, };
		
	

    while (n.ok())
    {
		for(unsigned int i = 0; i < num_readings; ++i)
		{
			ranges[i] = count;
			intensities[i] = 100 + count;
		}
		ros::Time scan_time = ros::Time::now();



		int *arr = lidar_getDistanceAndAmplitudeSorted();
		
		int i = 0;
		int j = 0;
		int p = 0;
		for(int y = 0; y < IMAGE_HEIGHT; y++)
		{
			for(int x = 0; x < IMAGE_WIDTH; x++)
			{				
				i = 320*y + (320-x);
				j = 320*y + x;
				Convert_To_RGB24_2((double)arr[320*y + (320-x)], pTex, 0.0f, 15000.0f);
				imageLidar.at<Vec3b>(y, x)[0] = pTex->b; // 해당 픽셀을 파란색으로 변경
				imageLidar.at<Vec3b>(y, x)[1] = pTex->g; // BGR 순서 
				imageLidar.at<Vec3b>(y, x)[2] = pTex->r; 
				
				if(x == 160 && y == 120) {
					//std_msgs::Float32 center_dist;
				//modi
				//	printf("(160, 120) Distance : %.2f cm\n", arr[320*y + (319-x)]*0.1);
					//center_dist.data = arr[320*y + (320-x)]*0.1;
					//center_pub.publish(center_dist);
				}
				// Generate the data
				if(y==120)
				{
					dist2D[p++] = arr[j];
				}
				
			}
		}
	


		// Show OpenCV Window
		//namedWindow("roboscan", WINDOW_NORMAL);
		//resizeWindow("roboscan", 320*2, 240*2);
		//imshow("roboscan", imageLidar);
		printf("1\n");
	
		sensor_msgs::LaserScan scan;
		scan.header.stamp = scan_time;
		scan.header.frame_id = "base_footprint"; //laser_frame
		scan.angle_min = -0.959; //90xPI/180=-1.57 -> 45xPI/180=0.785  
		scan.angle_max = 0.959;
		scan.angle_increment = 1.91 / num_readings; //3.14 / num_readings;		
		scan.time_increment = (1 / laser_frequency) / (num_readings);
		scan.range_min = 0.0;
		scan.range_max = 1000.0;		
		

		scan.ranges.resize(num_readings);
		scan.intensities.resize(num_readings);

		for(unsigned int i = 0; i < num_readings; ++i)
		{
			scan.ranges[i] = dist2D[i]*0.001;
			//scan.ranges[i] = 5;
			scan.intensities[i] = intensities[i];
		}
		//printf("%.2f\n", dist2D[0]);
		pubScan.publish(scan);
		++count;


		//wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		if(cv::waitKey(1) == 27) 
		{
			std::cout << "esc key is pressed by user" << std::endl; 
			exit(1); 
		}

        clock_t end = clock();
        //ROS_INFO("%0.4f sec..", 1/((double)(end-start) / 100000)); 

	
        
        ros::spinOnce();
    }

	delete pTex;

	lidar_close();
	return 0;    
}

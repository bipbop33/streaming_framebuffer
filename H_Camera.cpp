#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "H_Camera.h"

using namespace cv;
using namespace std;

H_Camera::H_Camera(void* owner, int id){
	Owner = owner;
	cap_id = id;
	Active = false;
}

H_Camera::~H_Camera(){
	Active = false;
}

int H_Camera::init(int row, int cols){
	cap.open(cap_id,cv::CAP_ANY);
	//cap.open("Track.avi",cv::CAP_ANY);
	cap.set(4, row);
	cap.set(3, cols);
	if(!cap.isOpened()){
		printf("H_Camera: Error unable top open camera\n");
		return -1;
	}
	int frame_width = (int)cap.get(3);
	int frame_height = (int)cap.get(4);
	int frame_length = frame_width * frame_height;
	printf("H_Camera: Start streaming %d x %d\n", frame_height, frame_width);
	Active = true;
	return 1;
}

int H_Camera::grab_frame(Mat &dest_frame){
	cap.read(dest_frame);
	if(dest_frame.empty()){
		printf("H_Camera: Frame is empty\n");
		return -1;
	}
	return 1;
}

int H_Camera::grab_frame_imgproc(Mat &dest_frame){
	Mat frame;
	cap.read(frame);
	if(frame.empty()){
		printf("H_Camera: Frame is empty\n");
		return -1;
	}
	// Img processing algorithm
	/*
	*/
	return 1;
}
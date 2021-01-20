#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "H_Framebuffer.h"

using namespace cv;
using namespace std;

H_Framebuffer::H_Framebuffer(void* owner, int id){
	Owner = owner;
	fb_id = id;
	Active = false;
}

H_Framebuffer::~H_Framebuffer(){
	Active = false;
}

int H_Framebuffer::init(){
	int fb = 0;
	char* file_name;
	sprintf(file_name, "/dev/fb%d", fb_id);
	//fb = open("/dev/fb0", O_RDWR);
	fb = open(file_name, O_RDWR);
	if(fb==-1){
		printf("H_Framebuffer[%d]: Error cannot open framebuffer device\n", fb_id);
		return -1;
	}
	printf("H_Framebuffer[%d]: The framebuffer device was opened successfully\n", fb_id);
	if(ioctl(fb, FBIOGET_FSCREENINFO, &finfo) == -1){
		printf("H_Framebuffer[%d]: Error reading fixed information\n", fb_id);
		return -1;
	}
	if(ioctl(fb, FBIOGET_VSCREENINFO, &vinfo) == -1){
		printf("H_Framebuffer[%d]: Error reading variable information\n", fb_id);
		return -1;
	}
	printf("H_Framebuffer[%d]: Screen resolution %dx%d, %d bpp\n", fb_id, vinfo.xres, vinfo.yres, finfo.line_length);
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel/8;
	fbp = (char*)mmap(0, screensize, PROT_READ| PROT_WRITE, MAP_SHARED, fb, 0);
	printf("H_Framebuffer[%d]: The framebuffer device was mapped to memory successfully.\n", fb_id);
	printf("H_Framebuffer[%d]: Bits perpixel %d\n", fb_id, vinfo.bits_per_pixel);
	Active = true;
	return 1;
}

int H_Framebuffer::update(Mat frame, int streaming_type){
	if(streaming_type == H_FRAMEBUFFER_FULLSCREEN){
		Mat frame32, r_frame;
		//cvtColor(frame, frame32, CV_BGR2BGRA);
		cvtColor(frame, frame32, cv::COLOR_BGR2BGRA);
		//r_frame = cv::CreateMat();
		//resize(frame32, r_frame, cv::Size(vinfo.yres,vinfo.xres), 0, 0, INTER_LINEAR);
		resize(frame32, r_frame, cv::Size(vinfo.xres,vinfo.yres));
		printf("%d x %d\n", r_frame.rows, r_frame.cols);
		char* show_frame = reinterpret_cast <char*>(r_frame.data);
		memcpy(fbp, show_frame, screensize);
	}
	return 1;
}

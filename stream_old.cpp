#include <opencv2/core.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include "time.h"
#include <bits/stdc++.h>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <CL/cl.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
	// Initialize screen
	int fb = 0;
	char *fbp = 0;
	int screensize;
	long int location = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	fb = open("/dev/fb0",O_RDWR);
	if(fb==-1){
		cerr << "Error: cannot open framebuffer device";
		return -1;
	}
	printf("The framebuffer device was opened successfully.\n");
	if(ioctl(fb,FBIOGET_FSCREENINFO,&finfo) == -1){
		cerr << "Error reading fixed information";
		return -1;
	}
	if(ioctl(fb, FBIOGET_VSCREENINFO, &vinfo) == -1){
		cerr << "Error reading variable information";
		return -1;
	}
	printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, finfo.line_length);
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel/8;
	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
	//if((int)fbp == -1){
	//	cerr << "Error: failed to map framebuffer device to memory";
	//	return -1;
	//}
	printf("The framebuffer device was mapped to memory successfully.\n");
	printf("Bits perpixel: %d\n", vinfo.bits_per_pixel);

	// Initialize cam
	VideoCapture cap;
	cap.open(0,cv::CAP_ANY);
	//cap.open("Track.avi",cv::CAP_ANY);
	cap.set(4, 480.0);
	cap.set(3, 640.0);
	//cap.set(4,360);
	//cap.set(3,640);
	//cap.open("Track.avi",cv::CAP_ANY);
	if(!cap.isOpened()){
		cerr << "Error! unable top open camera\n";
		return -1;
	}
	int frame_width = (int)cap.get(3);
	int frame_height = (int)cap.get(4);
	int frame_length = frame_width * frame_height;
	printf("Start streaming: %d x %d\n", frame_height, frame_width);

	// Initialize openCL
	if(!ocl::haveOpenCL()){
		printf("OpenCL is not available...\n");
		return -1;
	}
	ocl::Context context;
	if(!context.create(ocl::Device::TYPE_GPU)){
		printf("Failed creating the context...\n");
		return -1;
	}
	ocl::Device device = context.device(0);
	cout << "Name			: " << device.name() << endl;
	cout << "Available		: " << device.available() << endl;
	cout << "ImageSupport		: " << device.imageSupport() << endl;
	cout << "OpenCL_C_Version	: " << device.OpenCL_C_Version() << endl;
	ocl::Device(0);

	//cl_context myctx = clCreateContextFromType(0, CL_DEVICE_TYPE_GPU, NULL, NULL, 0);

	// Load and compile the openCL kernel
	ifstream ifs("cl_imshow.cl");
	if(ifs.fail()){
		printf("Failed to load the kernel...\n");
		return -1;
	}
	string kernelSource((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
	ocl::ProgramSource programSource(kernelSource);
	String errmsg;
	String buildopt = cv::format("-D dstT=%s", ocl::typeToStr(3));
	ocl::Program program = context.getProg(programSource, errmsg, buildopt);
	ocl::Kernel kernel("cl_imshow", program);
	ocl::setUseOpenCL(true);
	size_t globalThreads[5] = {vinfo.yres, vinfo.xres, vinfo.xoffset, vinfo.yoffset, finfo.line_length};
	CascadeClassifier face_cascade;
	face_cascade.load("haarcascade_frontalface_alt.xml");
	if(face_cascade.empty()){
		printf("XML file is not found\n");
		return -1;
	}
	// Start streaming
	while(1){
		int increment = frame_length;
		UMat frame, frame_gray;
		//cvtColor(frame, frame_gray, CV_BGR2GRAY);
		//equalizeHist(frame_gray, frame_gray);
		UMat frame32, r_frame;
		std::vector<Rect> faces;
		cap.read(frame);
		clock_t tstart = clock();
		if(frame.empty()){
			cerr << "Error! blank frame grabbed \n";
			break;
		}
		cvtColor(frame, frame_gray, CV_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);
		//UMat uGray = frame_gray.getUMat(ACCESS_FAST);
		face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));
		//for(int i = 0; i < faces.size(); i++){
		//	Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		//	ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		//}
		cvtColor(frame, frame32, CV_BGR2BGRA);
		//resize(frame32, r_frame, cv::Size(vinfo.xres,vinfo.yres), 0, 0, CV_INTER_LINEAR);
		//char* show_frame = reinterpret_cast <char*>(r_frame.data);
		//memcpy(fbp, show_frame, screensize);
		//waitKey(30);
		printf("Time taken: %.5f\n",(double)(clock() - tstart)/CLOCKS_PER_SEC);
	}
	return 0;
}

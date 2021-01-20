#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "H_Dashboard.h"

using namespace cv;
using namespace std;


H_Dashboard::H_Dashboard(void* owner){
	Owner = owner;
	Active = false;
}

H_Dashboard::~H_Dashboard(){
	Active = false;
}

int H_Dashboard::init(int irow, int icols){
	Mat temp(3, irow*icols, CV_8UC1, cv::Scalar(0,0,0));
	Mat tmp = temp.t();
	dashboard_area = tmp.reshape(3, irow);
	row = irow; cols = icols;
	Active = true;
	return 1;
}

void dashboard_menu_update(Mat &frame){
}

void dashboard_battery_update(Mat &frame){
}

void dashboard_connection_update(Mat &frame){
}

/*
int H_Dashboard::update_dashboard(char* new_data){
	Rect black_up(0, 0, cols, (int) row/10);
	Rect black_down(0, (row - (int) row/10), cols, (int) row/10);
	rectangle(dashboard_area, black_up, cv::Scalar(0,0,0));
	rectangle(dashboard_area, black_down, cv::Scalar(0,0,0));
	return 1;
}
*/

int H_Dashboard::add_dashboard(Mat &frame, char* new_data){
	/*
			Under construction data
			Parsing char*
	*/
	/*
	float alpha = 0.2;
	Mat temp_dashboard, r_dashboard;
	temp_dashboard = dashboard_area.clone();
	resize(temp_dashboard, r_dashboard, cv::Size(1280,720));
	addWeighted(r_dashboard, alpha, frame, 1 - alpha, 0.0, frame);
	resize(temp_dashboard, r_dashboard, cv::Size(1280,720));
	*/
	
	int start_row; int start_cols;
	
	Rect black_up(0, 0, cols, row/10);
	Rect black_down(0, (row - row/10), cols, row);
	rectangle(frame, black_up, cv::Scalar(0,0,0),-1);
	rectangle(frame, black_down, cv::Scalar(0,0,0),-1);
	putText(frame, "0.00 m", Point(10, (row - row/10) + 5), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
	
	start_cols = 10; start_row = row/10 + 10;
	Rect btn_lrf(start_cols, start_row, start_cols+150, start_row+50);
	rectangle(frame, btn_lrf, cv::Scalar(0, 100, 0), -1);
	putText(frame, "LRF", Point(start_cols+10, start_row+35),cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 4);
	
	start_row = start_row + 50 + 10;
	Rect btn_zoom(start_cols, start_row, start_cols+150, start_row+50);
	rectangle(frame, btn_zoom, cv::Scalar(0, 100, 0), -1);
	putText(frame, "Zoom", Point(start_cols+10, start_row+35),cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 4);

	start_row = start_row + 50 + 10;
	Rect btn_focus(start_cols, start_row, start_cols+150, start_row+50);
	rectangle(frame, btn_focus, cv::Scalar(0, 100, 0), -1);
	putText(frame, "Fokus", Point(start_cols+10, start_row+35),cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 4);
	
	start_row = start_row + 50 + 10;
	Rect btn_iris(start_cols, start_row, start_cols+150, start_row+50);
	rectangle(frame, btn_iris, cv::Scalar(0, 100, 0), -1);
	putText(frame, "Iris", Point(start_cols+10, start_row+35),cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 4);
	
	/*
			TCP connection
	*/
	
	return 1;
}

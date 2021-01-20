#ifndef H_DASHBOARD_H
#define H_DASHBOARD_H

#include <opencv2/core.hpp>
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

class H_Dashboard{
	public:
		H_Dashboard(void* owner);
		virtual ~H_Dashboard();
		int		init(int row, int cols);
		int		update_dashboard(char* new_data);
		int 	add_dashboard(Mat &frame, char* new_data);
	
	private:
		void dashboard_menu_update();
		void dashboard_battery_update();
		void dashboard_connection_update();
	
	protected:
		void* 	Owner;
		Mat		dashboard_area;
		char*	data;
	
	private:
		bool	Active;
		int		row;
		int		cols;
};

#endif
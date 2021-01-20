#ifndef H_CAMERA_H
#define H_CAMERA_H

#include <opencv2/core.hpp>
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

class H_Camera{
	public:
		H_Camera(void* owner, int id);
		virtual ~H_Camera();
		int		init(int row, int cols);
		int		grab_frame(Mat &dest_frame);
		int 	grab_frame_imgproc(Mat &dest_frame);
		bool	isActive() {return Active; }
	
	protected:
		void* 	Owner;
	
	private:
		int 			cap_id;
		VideoCapture 	cap;
		bool			Active;
};

#endif
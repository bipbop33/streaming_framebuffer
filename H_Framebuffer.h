#ifndef H_FRAMEBUFFER_H
#define H_FRAMEBUFFER_H

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

#define H_FRAMEBUFFER_FULLSCREEN 0

using namespace cv;
using namespace std;

class H_Framebuffer{
	public:
		H_Framebuffer(void* owner, int id);
		virtual ~H_Framebuffer();
		int		init();
		int		update(Mat frame, int streaming_type);
		bool	isActive() {return Active; }
	
	protected:
		void* 	Owner;
	
	private:
		int 	fb_id;
		char*	fbp;
		bool	Active;
		int		screensize;
		struct 	fb_var_screeninfo vinfo;
		struct 	fb_fix_screeninfo finfo;
};

#endif
#include "H_Framebuffer.h"
#include "H_Camera.h"
#include "H_Dashboard.h"
//#include "H_Intf.h"

#include <stdio.h>

using namespace std;

H_Framebuffer 	*Hframebuffer=NULL;
H_Camera		*Hcamera=NULL;
H_Dashboard		*Hdashboard=NULL;

bool initAll(){

	int init_fb;
	Hframebuffer = new H_Framebuffer(NULL, 0);
	init_fb = Hframebuffer->init();
	if(init_fb==-1) return false;
	printf("H_Framebuffer: is initialized\n");

	int init_cam;
	Hcamera = new H_Camera(NULL, 0);
	init_cam = Hcamera->init(720, 1280);
	if(init_cam==-1) return false;
	printf("H_Camera: is initialized\n");
	
	int init_dboard;
	Hdashboard = new H_Dashboard(NULL);
	init_dboard = Hdashboard->init(360, 640);
	if(init_dboard==-1) return false;
	printf("H_Dashboard: is created\n");
	
	return true;
}

int main(int argc, char** argv){
	bool ret;
	ret = initAll();
	if(!ret) return -1;
	while(Hcamera->isActive()){
		Mat frame; char* data;
		Hcamera->grab_frame(frame);
		if(!frame.empty()) Hframebuffer->update(frame, H_FRAMEBUFFER_FULLSCREEN);
	}
	return 1;
}

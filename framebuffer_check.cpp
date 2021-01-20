#include "H_Framebuffer.h"

#include <stdio.h>

using namespace std;

H_Framebuffer 	*Hframebuffer=NULL;

int main(int argc, char** argv){
	for(int i=0; i<5; i++){
		Hframebuffer = new H_Framebuffer(NULL, i);
		int init_fb = Hframebuffer->init();
		printf("\n");
		if(init_fb==-1) break;
	}
	return 1;
}

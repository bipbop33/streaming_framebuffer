g++ -g -fPIC -std=c++11 `pkg-config --cflags opencv4` main.cpp libHrf.a `pkg-config --libs opencv4`
#g++ -g -fPIC -std=c++11 `pkg-config --cflags opencv4` -o fb_check framebuffer_check.cpp libHrf.a `pkg-config --libs opencv4`

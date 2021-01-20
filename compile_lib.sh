g++ -c -std=c++11 -g `pkg-config --cflags opencv4` H_Framebuffer.cpp `pkg-config --libs opencv4` -fPIC -o H_Framebuffer.o
g++ -c -std=c++11 -g `pkg-config --cflags opencv4` H_Camera.cpp `pkg-config --libs opencv4` -fPIC -o H_Camera.o
g++ -c -std=c++11 -g `pkg-config --cflags opencv4` H_Dashboard.cpp `pkg-config --libs opencv4` -fPIC -o H_Dashboard.o

ar sr libHrf.a H_Framebuffer.o H_Camera.o H_Dashboard.o

# KMeans-C-OpenGL
Basic k-means implementation for 2d data points.
Every parameter needed by the program to run correctly can be adjusted by editing the config.txt file.
The configuration file must be named "config.txt" and needs to be in the src folder.
The file that stores the points can have various names but also needs to be in the src folder and each "point" needs to be in the form x,y
as shown in the demo file "data.txt". The above limitations exist because the current program is only meant as a demo of the kmeans algorithm.

compile source: make kmeans

delete .o files: make clean

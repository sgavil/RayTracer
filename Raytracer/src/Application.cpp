#include <iostream>
#include <fstream>
#include "vec.h"

int main() {

	//Creating a PPM image file

	//Opening the file
	std::ofstream ppmImage;
	ppmImage.open("helloWorldPPM.ppm");

	//Img dimensions
	int nx = 200;
	int ny = 100;
	ppmImage << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny-1;  j >= 0;  j--)
		for (int  i = 0; i < nx; i++)
		{
			vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2f);
			int ir = int(255.99f * col[0]);
			int ig = int(255.99f * col[1]);
			int ib = int(255.99f * col[2]);

			ppmImage << ir << " " << ig << " " << ib << "\n";
		}

	ppmImage.close();

	return 0;
}
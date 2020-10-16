#include <iostream>
#include <fstream>
#include "hitable_list.h"
#include "Sphere.h"
#include "float.h"
#include <random>
#include "camera.h"


vec3 color(const ray& r, hitable* world) {
	hit_record rec;
	if (world->hit(r, 0.0f, std::numeric_limits<float>::max(), rec)) {
		return 0.5f * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	
	else {

		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}


int main() {

	//Creating a PPM image file

	//Opening the file
	std::ofstream ppmImage;
	ppmImage.open("helloWorldPPM.ppm");

	//Img dimensions
	int nx = 200;
	int ny = 100;
	//Number of samples for antialiasing for each pixel
	int ns = 100;

	//0 1 random real generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1
	
	
	ppmImage << "P3\n" << nx << " " << ny << "\n255\n";

	hitable* list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5f);
	list[1] = new sphere(vec3(0, -100.5f, -1), 100);
	hitable* world = new hitable_list(list, 2);

	camera cam;
	
	for (int j = ny-1;  j >= 0;  j--)
		for (int  i = 0; i < nx; i++)
		{
			vec3 col = vec3(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + dis(gen)) / float(nx);
				float v = float(j + dis(gen)) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0f);
				col += color(r, world);
			}
			
			col /= float(ns);
			int ir = int(255.99f * col[0]);
			int ig = int(255.99f * col[1]);
			int ib = int(255.99f * col[2]);

			ppmImage << ir << " " << ig << " " << ib << "\n";
		}

	ppmImage.close();

	return 0;
}
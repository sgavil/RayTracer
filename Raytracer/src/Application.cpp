#include <iostream>
#include <fstream>
#include "hitable_list.h"
#include "Sphere.h"
#include "float.h"
#include "material.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"

vec3 color(const ray& r, hitable* world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec)) 
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else return vec3(0, 0, 0);
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


	
	
	ppmImage << "P3\n" << nx << " " << ny << "\n255\n";

	hitable* list[4];
	list[0] = new sphere(vec3(0, 0, -1), 0.5f, new lambertian(vec3(0.8f, 0.3f, 0.3f)));
	list[1] = new sphere(vec3(0, -100.5f, -1), 100, new lambertian(vec3(0.8f, 0.8f, 0.0f)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5f, new metal(vec3(0.8f, 0.6f, 0.2f)));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5f, new metal(vec3(0.8f, 0.8f, 0.8f)));
	hitable* world = new hitable_list(list, 4);

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
				col += color(r, world,0);
			}
			
			col /= float(ns);
			//Gamma correction, gamma 2
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99f * col[0]);
			int ig = int(255.99f * col[1]);
			int ib = int(255.99f * col[2]);

			ppmImage << ir << " " << ig << " " << ib << "\n";
		}

	ppmImage.close();

	return 0;
}



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>

#include "Cube_Unity.h"
#include "bmp.h"

#define PI 3.1415

__global__ void render(Cube_Unity *Cube, Cube_Unity *Cube_Perspective){
	int Size = 100;
	int width = 2000;
	int OffSet = 3000;
   double startAngulo = 1;
   double offset = startAngulo;
   
   auto k = blockIdx.x;
   int i = int(threadIdx.x/10);
   
	  for(auto j = (threadIdx.x*10)%100; j < ((threadIdx.x*10)%100)+10; j++){
            Cube[i + Size * (j + Size * k)].z += offset;
      }
   
	double angulo = startAngulo * PI/180;

   double matrix_x[4][4] = { cos(angulo), 0, sin(angulo), 0,
                                      0, 1,           0, 0,
                           -sin(angulo), 0, cos(angulo), 0,
                                      0, 0,           0, 1};

   double new_x, new_y, new_z;

      for(auto j = (threadIdx.x*10)%100; j < ((threadIdx.x*10)%100)+10; j++){
            new_x = Cube[i + Size * (j + Size * k)].x * matrix_x[0][0] + Cube[i + Size * (j + Size * k)].y * matrix_x[0][1] + Cube[i + Size * (j + Size * k)].z * matrix_x[0][2];
            new_y = Cube[i + Size * (j + Size * k)].x * matrix_x[1][0] + Cube[i + Size * (j + Size * k)].y * matrix_x[1][1] + Cube[i + Size * (j + Size * k)].z * matrix_x[1][2];
            new_z = Cube[i + Size * (j + Size * k)].x * matrix_x[2][0] + Cube[i + Size * (j + Size * k)].y * matrix_x[2][1] + Cube[i + Size * (j + Size * k)].z * matrix_x[2][2];

            Cube[i + Size * (j + Size * k)].x = new_x;
            Cube[i + Size * (j + Size * k)].y = new_y;
            Cube[i + Size * (j + Size * k)].z = new_z;
      }
   
	angulo = startAngulo * PI/180;

   double matrix_y[4][4] = {1,           0,            0, 0,
                           0, cos(angulo), -sin(angulo), 0,
                           0, sin(angulo),  cos(angulo), 0,
                           0,           0,            0, 1};

						   
	  for(auto j = (threadIdx.x*10)%100; j < ((threadIdx.x*10)%100)+10; j++){

            new_x = Cube[i + Size * (j + Size * k)].x * matrix_y[0][0] + Cube[i + Size * (j + Size * k)].y * matrix_y[0][1] + Cube[i + Size * (j + Size * k)].z * matrix_y[0][2];
            new_y = Cube[i + Size * (j + Size * k)].x * matrix_y[1][0] + Cube[i + Size * (j + Size * k)].y * matrix_y[1][1] + Cube[i + Size * (j + Size * k)].z * matrix_y[1][2];
            new_z = Cube[i + Size * (j + Size * k)].x * matrix_y[2][0] + Cube[i + Size * (j + Size * k)].y * matrix_y[2][1] + Cube[i + Size * (j + Size * k)].z * matrix_y[2][2];

            Cube[i + Size * (j + Size * k)].x = new_x;
            Cube[i + Size * (j + Size * k)].y = new_y;
            Cube[i + Size * (j + Size * k)].z = new_z;
      }
   offset = OffSet;
	  for(auto j = (threadIdx.x*10)%100; j < ((threadIdx.x*10)%100)+10; j++){
            Cube[i + Size * (j + Size * k)].z += offset;
      }
   
   double dist_to_screen = 300;

	  for(auto j = (threadIdx.x*10)%100; j < ((threadIdx.x*10)%100)+10; j++){
            new_x = Cube[i + Size * (j + Size * k)].x*dist_to_screen/Cube[i + Size * (j + Size * k)].z+width/2;
            new_y = Cube[i + Size * (j + Size * k)].y*dist_to_screen/Cube[i + Size * (j + Size * k)].z+width/2;
			Cube_Perspective[i + Size * (j + Size * k)].x = new_x;
			Cube_Perspective[i + Size * (j + Size * k)].y = new_y;
			Cube_Perspective[i + Size * (j + Size * k)].z = 0;
			Cube_Perspective[i + Size * (j + Size * k)].cor = Cube[i + Size * (j + Size * k)].cor;
      }
   offset = -OffSet;
	  for(auto j = (threadIdx.x*10)%100; j < ((threadIdx.x*10)%100)+10; j++){
            Cube[i + Size * (j + Size * k)].z += offset;
      }
}


int main(void)
{

	

	Cube_Unity *Cube;
	Cube_Unity *Cube_Perspective;
	
	int Size = 100;
	int width = 2000;
	int frames;
	double spacing_factor = 40;
	std::cout << "Frames:" << std::endl;
	std::cin >> frames;

   double inix, iniy, iniz;
   double atualx, atualy, atualz;
   double spacing;

   inix = iniy = iniz = atualx = atualy = atualz = -double(Size)/2 * spacing_factor;
   spacing = -inix*2 / double(Size);

   cudaMallocManaged(&Cube, Size*Size*Size*sizeof(Cube_Unity));
   cudaMallocManaged(&Cube_Perspective, Size*Size*Size*sizeof(Cube_Unity));
   for(auto i = 0; i < Size; i++){
       for(auto j = 0; j < Size; j++){
           for(auto k = 0; k < Size; k++){
              Cube[i + Size * (j + Size * k)].set_pos(atualx,atualy,atualz, 255);
              atualz += spacing;
           }
           atualz = iniz;
           atualy += spacing;
       }
       atualy = iniy;
       atualx += spacing;
   }

   // allocate picture array
   /*unsigned char* pic = new unsigned char[frames * width * width];

   for (int frame = 0; frame < frames; frame++) {
      for (int row = 0; row < width; row++) {
         for (int col = 0; col < width; col++) {
            unsigned char color = (unsigned char) 255;
            pic[frame * width * width + row * width + col] = (unsigned char) color;
         }
      }
   }*/

	int max_threads, max_blocks;

	max_threads = 1000;
	max_blocks = Size;
	
// start time
	timeval start, end;
	gettimeofday(&start, NULL);
	
   for(int frame = 0; frame < frames; frame++){
	  render<<<max_blocks, max_threads>>>(Cube, Cube_Perspective);
      //render();
	  cudaDeviceSynchronize();
      /*for(auto i = 0; i < Size; i++){
         for(auto j = 0; j < Size; j++){
            for(auto k = 0; k < Size; k++){
               int row = (int)Cube_Perspective[i + Size * (j + Size * k)].x;
               int col = (int)Cube_Perspective[i + Size * (j + Size * k)].y;
               if(row >= 0 && row < width && col >= 0 && col < width){
                  unsigned char color = (unsigned char) 0;
                  pic[frame * width * width + row * width + col] = (unsigned char) color;
               }
            }
         }
      }*/
   }

	gettimeofday(&end, NULL);
	double runtime = end.tv_sec + end.tv_usec / 1000000.0 - start.tv_sec - start.tv_usec / 1000000.0;
	std::cout << "compute time: " << runtime << " s\n";

    /*for (int frame = 0; frame < frames; frame++) {
      char name[32];
      sprintf(name, "cube%d.bmp", frame + 1000);
      writeBMP(width, width, &pic[frame * width * width], name);
    }*/


}

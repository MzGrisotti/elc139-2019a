


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>

#include "Cube_Unity.h"
#include "bmp.h"

#define PI 3.1415

Cube_Unity ***Cube;
Cube_Unity ***Cube_Perspective;
int Size;
int width;

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()

void OffSet_Z(double offset){

   for(auto i = 0; i < Size; i++){
      for(auto j = 0; j < Size; j++){
         for(auto k = 0; k < Size; k++){
            Cube[i][j][k].z += offset;
         }
      }
   }

}

void Transform_3D_2D(){

   double dist_to_screen = 300;
   double new_x, new_y;

   for(auto i = 0; i < Size; i++){
      for(auto j = 0; j < Size; j++){
         for(auto k = 0; k < Size; k++){
            new_x = Cube[i][j][k].x*dist_to_screen/Cube[i][j][k].z+width/2;
            new_y = Cube[i][j][k].y*dist_to_screen/Cube[i][j][k].z+width/2;
            Cube_Perspective[i][j][k].set_pos(new_x, new_y, 0, Cube[i][j][k].cor);
         }
      }
   }

}

void Rotate_x(double angulo){

   angulo = angulo * PI/180;

   double matrix_x[4][4] = {1,           0,            0, 0,
                           0, cos(angulo), -sin(angulo), 0,
                           0, sin(angulo),  cos(angulo), 0,
                           0,           0,            0, 1};

   double new_x, new_y, new_z;

   for(auto i = 0; i < Size; i++){
      for(auto j = 0; j < Size; j++){
         for(auto k = 0; k < Size; k++){

            new_x = Cube[i][j][k].x * matrix_x[0][0] + Cube[i][j][k].y * matrix_x[0][1] + Cube[i][j][k].z * matrix_x[0][2];
            new_y = Cube[i][j][k].x * matrix_x[1][0] + Cube[i][j][k].y * matrix_x[1][1] + Cube[i][j][k].z * matrix_x[1][2];
            new_z = Cube[i][j][k].x * matrix_x[2][0] + Cube[i][j][k].y * matrix_x[2][1] + Cube[i][j][k].z * matrix_x[2][2];

            Cube[i][j][k].x = new_x;
            Cube[i][j][k].y = new_y;
            Cube[i][j][k].z = new_z;

         }
      }
   }

}

void Rotate_y(double angulo){

   angulo = angulo * PI/180;

   double matrix_x[4][4] = { cos(angulo), 0, sin(angulo), 0,
                                      0, 1,           0, 0,
                           -sin(angulo), 0, cos(angulo), 0,
                                      0, 0,           0, 1};

   double new_x, new_y, new_z;

   for(auto i = 0; i < Size; i++){
      for(auto j = 0; j < Size; j++){
         for(auto k = 0; k < Size; k++){

            new_x = Cube[i][j][k].x * matrix_x[0][0] + Cube[i][j][k].y * matrix_x[0][1] + Cube[i][j][k].z * matrix_x[0][2];
            new_y = Cube[i][j][k].x * matrix_x[1][0] + Cube[i][j][k].y * matrix_x[1][1] + Cube[i][j][k].z * matrix_x[1][2];
            new_z = Cube[i][j][k].x * matrix_x[2][0] + Cube[i][j][k].y * matrix_x[2][1] + Cube[i][j][k].z * matrix_x[2][2];

            Cube[i][j][k].x = new_x;
            Cube[i][j][k].y = new_y;
            Cube[i][j][k].z = new_z;

         }
      }
   }

}

void Rotate_z(double angulo){

   angulo = angulo * PI/180;

   double matrix_x[4][4] = {cos(angulo), -sin(angulo), 0, 0,
                           sin(angulo),  cos(angulo), 0, 0,
                                     0,            0, 1, 0,
                                     0,            0, 0, 1};

   double new_x, new_y, new_z;

   for(auto i = 0; i < Size; i++){
      for(auto j = 0; j < Size; j++){
         for(auto k = 0; k < Size; k++){

            new_x = Cube[i][j][k].x * matrix_x[0][0] + Cube[i][j][k].y * matrix_x[0][1] + Cube[i][j][k].z * matrix_x[0][2];
            new_y = Cube[i][j][k].x * matrix_x[1][0] + Cube[i][j][k].y * matrix_x[1][1] + Cube[i][j][k].z * matrix_x[1][2];
            new_z = Cube[i][j][k].x * matrix_x[2][0] + Cube[i][j][k].y * matrix_x[2][1] + Cube[i][j][k].z * matrix_x[2][2];

            Cube[i][j][k].x = new_x;
            Cube[i][j][k].y = new_y;
            Cube[i][j][k].z = new_z;

         }
      }
   }

}

void render(){
   double angulo = 1;
   Rotate_z(angulo);
   Rotate_y(angulo);
   Rotate_x(angulo);
   OffSet_Z(800);
   Transform_3D_2D();
   OffSet_Z(-800);

}


int main(void)
{

   Size = 100;
   width = 2000;
   int frames;
   double spacing_factor = 40;
   std::cout << "Frames:" << std::endl;
	std::cin >> frames;

   double inix, iniy, iniz;
   double atualx, atualy, atualz;
   double spacing;

   inix = iniy = iniz = atualx = atualy = atualz = -double(Size)/2 * spacing_factor;
   spacing = -inix*2 / double(Size);

   Cube = new Cube_Unity**[Size];
   Cube_Perspective = new Cube_Unity**[Size];
   for(auto i = 0; i < Size; i++){
       Cube[i] = new Cube_Unity*[Size];
       Cube_Perspective[i] = new Cube_Unity*[Size];
       for(auto j = 0; j < Size; j++){
           Cube[i][j] = new Cube_Unity[Size];
           Cube_Perspective[i][j] = new Cube_Unity[Size];
           for(auto k = 0; k < Size; k++){
              Cube[i][j][k].set_pos(atualx,atualy,atualz, 255);
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
// start time
	timeval start, end;
	gettimeofday(&start, NULL);

   for(int frame = 0; frame < frames; frame++){
      render();
      /*for(auto i = 0; i < Size; i++){
         for(auto j = 0; j < Size; j++){
            for(auto k = 0; k < Size; k++){
               int row = (int)Cube_Perspective[i][j][k].x;
               int col = (int)Cube_Perspective[i][j][k].y;
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

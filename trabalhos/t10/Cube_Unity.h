#ifndef CUBE_UNITY_H_INCLUDED
#define CUBE_UNITY_H_INCLUDED


class Cube_Unity{
public:
   double x;
   double y;
   double z;
   int cor;
   void set_pos(double x, double y, double z, int cor);
};

void Cube_Unity::set_pos(double x, double y, double z, int cor){
   this->x = x;
   this->y = y;
   this->z = z;
   this->cor = cor;
}


#endif // CUBE_UNITY_H_INCLUDED

#ifndef PYRAMID_H
#define PYRAMID_H
#include<memory>
#include<levelPyramid.h>
using namespace std;

class Pyramid
{
private:
   vector<LevelPyramid> octave;
   int numerOctave;
   double k;     //для очередной сигмы
public:
    Pyramid();

};

#endif

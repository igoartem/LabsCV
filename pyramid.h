#ifndef PYRAMID_H
#define PYRAMID_H
#include<memory>
#include<octave.h>
using namespace std;

class Pyramid
{
private:
   vector<Octave> octave; //вектор октав
   int numerOctave;
   int numLevels; //количество масштабов в октаве
   double k;     //для очередной сигмы ( интервал	между	масштабами	в	октаве)
   double sigma0;

public:
    Pyramid(shared_ptr<CVImage> image, double sigma0, int numLevels);
    void save();
    double L(int x, int y, double sigma);

};

#endif

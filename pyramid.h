#ifndef PYRAMID_H
#define PYRAMID_H
#include<memory>
#include<octave.h>
using namespace std;

class Pyramid
{
private:
    unique_ptr<Octave[]> octave;
    double startSigma;
    int sizeOctave;
    int sizeLevel;
public:
    Pyramid();
    Pyramid(CVImage &img, double startSigma, int sizeLevel, int sizeOctave);
};

#endif // PYRAMID_H

#ifndef LEVEL_H
#define LEVEL_H
#include<memory>
#include<cvimage.h>
using namespace std;

class Level
{
private:
    CVImage image;
    double locSigma;     //локальноая сигма для данного изображения
    double globSigma;    //глобальная сигма для данного уровня
    int nLevel;                 //номер уровня
public:
    Level();
    Level(CVImage &img, double loc, double glob);
};

#endif // LEVEL_H

#include "pyramid.h"

Pyramid::Pyramid()
{

}

Pyramid::Pyramid(CVImage &img, double startSigma, int sizeLevel, int sizeOctave)
{
    this->sizeLevel = sizeLevel;
    this->startSigma= startSigma;
    this->sizeOctave=sizeOctave;
}


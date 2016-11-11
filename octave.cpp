#include "octave.h"


Octave::Octave(double sigma, double k, int number)
{
    this->sigma = sigma;
    this->k = k;
    this->number = number;
}

vector<shared_ptr<CVImage> > Octave::getVecLayers() const
{
    return vecLayers;
}

void Octave::setVecLayers(const vector<shared_ptr<CVImage> > &value)
{
    vecLayers = value;
}

shared_ptr<CVImage> Octave::getLayer(int i)
{
    return vecLayers[i];
}

int Octave::size()
{
    return vecLayers.size();
}

double Octave::globalSigma(int i)
{
    return localSigma(i) * pow(2,number);
}

double Octave::localSigma(int i)
{
    return sigma * pow(k,i);
}

int Octave::getNumber()
{
    return number;
}
double Octave::L(int x, int y, double sigma)
{
    int level = 1;
    while(globalSigma(level) < sigma && level < vecLayers.size())
        level++;
    level--;
    int xx = x / pow(2, number);
    int yy = y / pow(2, number);

    return vecLayers[level]->getPixel(xx,yy);
}

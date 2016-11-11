#include "levelPyramid.h"


LevelPyramid::LevelPyramid(int number, double k, double sigma)
{
    this->number = number;
    this->k = k;
    this->sigma = sigma;
}

void LevelPyramid::addImage(const shared_ptr<CVImage> &_img)
{
    vec.emplace_back(_img);
}

shared_ptr<CVImage> LevelPyramid::getImage(int i)
{
    return vec[i];
}

shared_ptr<CVImage> LevelPyramid::getImageWithSigma(double sigma)
{
    int level = 1;
    while(globalSigma(level) < sigma && level < vec.size()){
        level++;
    }
    level--;
    return vec[level];
}

double LevelPyramid::globalSigma(int i)
{
    return localSigma(i) * pow(2, number);
}

double LevelPyramid::localSigma(int i)
{
    return sigma * pow(k,i);
}

int LevelPyramid::size()
{
    return vec.size();
}

int LevelPyramid::getNumber()
{
    return number;
}

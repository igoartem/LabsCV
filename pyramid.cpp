#include "pyramid.h"

Pyramid::Pyramid(shared_ptr<CVImage> image, double sigma0, int numLevels)
{
    this->sigma0 = sigma0;
    this->numLevels = numLevels;

    int minSize = min(image->getHeight(), image->getWidth());
    this->numerOctave = log2(minSize) - 5;      //строим новую октаву пока изображение не станет меньше 64

    // вычисляем значение для того чтобы досгладить, считаем что по-умолчанию 0.5
    double deltaSigma = sqrt(this->sigma0 * this->sigma0 - 0.5);
    shared_ptr<CVImage> curImg = image->separatedGauss(deltaSigma);//досглаживаем изображение до sigma0

    //начинаем вычислять октавы
    this->k = pow(2,1./this->numLevels);

    for(int i = 0; i < this->numerOctave; i++ )
    {
        //Строим пустую октаву октаву и потом заполняем её
        Octave level(this->sigma0, this->k, i);
        vector<shared_ptr<CVImage>> valueLayers;
        valueLayers.emplace_back(curImg);
        double curSigma =this->sigma0;
        for(int j = 0; j < this->numLevels; j++)
        {
            double newSigma = curSigma * this->k; //значение	очередного	масштаба
            double deltaSigma = sqrt(newSigma * newSigma - curSigma * curSigma);

            curImg = curImg->separatedGauss(deltaSigma);
            valueLayers.emplace_back(curImg);
            curSigma = newSigma;
        }
        level.setVecLayers(valueLayers);
        curImg = curImg->downScale();// уменьшаем изображение в 2 раза
        octave.emplace_back(level);
    }

}

void Pyramid::save()
{
    for(int i = 0, ei = int(this->octave.size()); i < ei; i++)
    {
        for(int j = 0; j < this->octave[i].size(); j++)
        {
            shared_ptr<CVImage> img = octave[i].getLayer(j);
            QString fileName = "pyramid\\" + QString::number(i) + "-" + QString::number(j) + "-sig-" + QString::number(octave[i].globalSigma(j)) + ".jpg";
            img-> saveImage(fileName);
        }
    }

}

double Pyramid::L(int x, int y, double sigma)
{
    int level = 1;
    while(this->octave[level].globalSigma(0) < sigma && level < this->octave.size())
        level++;
    level--;
    return octave[level].L(x, y, sigma);
}

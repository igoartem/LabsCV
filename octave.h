#ifndef LEVEL_H
#define LEVEL_H
#include<memory>
#include<cvimage.h>
using namespace std;

class Octave
{
private:
    vector<shared_ptr<CVImage>> vecLayers; //Вектор слоев октавы
    int number;     //номер октавы
    double sigma;
    double k;

public:
    Octave(double sigma, double k, int number);
//    void addLayer(shared_ptr<CVImage> layer);
    shared_ptr<CVImage> getLayer(int i);
    int size();
    double globalSigma(int i);
    double localSigma(int i);
    int getNumber();
    double L(int x, int y, double sigma);

    vector<shared_ptr<CVImage> > getVecLayers() const;
    void setVecLayers(const vector<shared_ptr<CVImage> > &value);
};

#endif // LEVEL_H

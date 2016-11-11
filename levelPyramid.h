#ifndef LEVEL_H
#define LEVEL_H
#include<memory>
#include<cvimage.h>
using namespace std;

class LevelPyramid
{
private:
    vector<shared_ptr<CVImage>> vec;
    int number;     //номер октавы
    double k;
    double sigma;
public:
    LevelPyramid(int number, double k, double sigma);

    void addImage(const shared_ptr<CVImage> &_img);

    shared_ptr<CVImage> getImage(int i);
    shared_ptr<CVImage> getImageWithSigma(double sigma);

    int size();
    double globalSigma(int i);
    double localSigma(int i);
    int getNumber();
    float L(int _x, int _y, float _sigma);
//    shared_ptr<LevelPyramid> getDOGLevel() const;
//    vector<KeyPoint> findExtemums() const;
//    bool isExtremum(int _q, int _i, int _j) const;


};

#endif // LEVEL_H

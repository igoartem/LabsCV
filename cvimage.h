#ifndef CVIMAGE_H
#define CVIMAGE_H
#include<memory>
#include <QtDebug>
#include <QImage>
#include <fstream>
#include <mykernel.h>
using namespace std;

class CVImage{
    private:
        int height,width;
        unique_ptr<double[]> image;

    public:
        CVImage();
        CVImage(int h, int w,double _image[]);
        CVImage(int h,int w);
        int getHeight();
        int getWidth();
        double* getBeginImage();
        double getPixel(int i,int j);
        double getPixelClamp(int i,int j);
        double getPixelMirror(int i, int j);
        double getPixelWrap(int i, int j);
        void setPixel(int i,int j,double pixel);
        shared_ptr<CVImage> loadImage(const QString& fileName);
        void saveImage(shared_ptr<CVImage> img, QString file);
        double intToDouble(int val);
        int doubleToInt(double val);

        shared_ptr<CVImage> convolution(shared_ptr<CVImage> img, shared_ptr<MyKernel> kernel);

        shared_ptr<CVImage> normalize(shared_ptr<CVImage> img);

        shared_ptr<CVImage> sobel(shared_ptr<CVImage> img, double sobelX[], double sobelY[]);
};

#endif // CVIMAGE_H

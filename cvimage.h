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
        static shared_ptr<CVImage> loadImage(const QString& fileName);
        void saveImage(QString file);
        static double intToDouble(int val);
        static int doubleToInt(double val);

        shared_ptr<CVImage> convolution(shared_ptr<MyKernel> kernel);

        shared_ptr<CVImage> normalize();

        shared_ptr<CVImage> sobel(shared_ptr<MyKernel> sobX, shared_ptr<MyKernel> sobY);

        shared_ptr<CVImage> separated(shared_ptr<MyKernel> kernelX, shared_ptr<MyKernel> kernelY);

        shared_ptr<CVImage> separatedGauss(double sigma);
};

#endif // CVIMAGE_H

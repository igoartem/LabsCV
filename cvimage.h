#ifndef CVIMAGE_H
#define CVIMAGE_H
#include<memory>
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
};

#endif // CVIMAGE_H

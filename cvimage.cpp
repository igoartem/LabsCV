#include "cvimage.h"
#include <memory>

using namespace std;

CVImage::CVImage(){
    this->height=0;
    this->width=0;

}

CVImage::CVImage(int h, int w,double _image[]){
    this->height = h;
    this->width=w;
    image = unique_ptr<double[]>(new double[h * w]);
    std::copy(_image,_image + height*width, image.get());
}

CVImage::CVImage(int h, int w){
    this->height =h;
    this->width = w;
    image = unique_ptr<double[]> (new double[h*w]);
}

int CVImage::getHeight(){
    return this->height;
}

int CVImage::getWidth(){
    return this->width;
}

double* CVImage::getBeginImage(){
    return this->image.get();
}


double CVImage::getPixel(int i,int j){
    if(i<0||i>height-1){
        return 0;}
    if(j<0||j>width-1){
        return 0;}

    return image[i*width + j];
}

double CVImage::getPixelClamp(int i,int j){
    if(i<0){
        return getPixelClamp(i+1,j);}
    if(i>height-1)
    {
        return getPixelClamp(i-1,j);
    }
    if(j<0){
        return getPixelClamp(i,j+1);}

    if(j>width-1){
        return getPixelClamp(i,j-1);
    }
    return image[i*width + j];
}

double CVImage::getPixelMirror(int i, int j){
    if (i < 0) {
        return getPixelMirror(-i,j);
    }
    if (i > height-1) {
        return getPixelMirror(2 * height - i - 1, j);
    }
    if (j < 0) {
        return getPixelMirror(i,-j);
    }
    if (j > width-1) {
        return  getPixelMirror(i, 2  * width - j - 1);
    }
    return image[i*width + j];
}

double CVImage::getPixelWrap(int i, int j){

    if (i < 0) {
        return getPixelWrap( height + i,j);
    }
    if (i >height-1) {
        return getPixelWrap(i - height,j);
    }


    if (j < 0) {
        return getPixelWrap(i,width + j);
    }
    if (j >width-1) {
        return getPixelWrap(i,j - width);
    }
    return image[i*width + j];
}

void CVImage::setPixel(int i, int j, double pixel){
    image[i*width + j] = pixel;
}





#include <QCoreApplication>
#include <QImage>
#include <iostream>
#include<cvimage.h>
#include <memory>
#include <fstream>
#include<cassert>
#include<string>
#include <utility>
#include<mykernel.h>
#include<pyramid.h>
using namespace std;

QString nameImage = "D:\\labs\\my\\1\\duck.jpg";

double sobelX[9] = {-1,0,1,-2,0,2,-1,0,1};
double sobelY[9] = {-1,-2,-1,0,0,0,1,2,1};

shared_ptr<CVImage> separabel(shared_ptr<CVImage> img, shared_ptr<MyKernel> kernel){

    shared_ptr<CVImage> newImgX = make_shared<CVImage>(img->getHeight(),img->getWidth());

    for(int i=0;i<img->getHeight();i++){
        for(int j=0;j<img->getWidth();j++){
            double sum =0;
            for(int _j=0;_j<kernel->getWidth();_j++){
                int posY = j+_j-kernel->getWidth()/2;
                double val = img->getPixel(i,posY);
                double ker = kernel->get(0,_j);
                sum+=val*ker;
            }
            newImgX->setPixel(i,j,sum);
        }
    }
    shared_ptr<CVImage> newImgY = make_shared<CVImage>(img->getHeight(),img->getWidth());

    for(int i=0;i<newImgX->getHeight();i++){
        for(int j=0;j<newImgX->getWidth();j++){
            double sum =0;
            for(int _i=0;_i<kernel->getHeight();_i++){
                int posX = i+_i-kernel->getHeight()/2;
                double val = newImgX->getPixel(posX,j);
                double ker = kernel->get(_i,0);
                sum+=val*ker;
            }
            newImgY->setPixel(i,j,sum);
        }
    }

    return newImgY;
}

shared_ptr<MyKernel> getGaussKernel(double sigma){

    int height = 6*sigma + 1;
    int width = 6*sigma + 1;
    shared_ptr<MyKernel> ker = make_shared<MyKernel>(height, width);
    int xc, yc;
    xc =  height / 2;
    yc =  width / 2;
    for(int i = 0;i<height;i++){
        for(int j=0;j<width;j++){
            double val = (1.0/(2.0*M_PI*pow(sigma,2.0)))*pow(M_E,-((i - xc)*(i - xc)+(j - yc)*(j - yc))/(2.0*sigma*sigma));
            ker->set(i,j,val);
        }
    }
    return ker;
}

shared_ptr<MyKernel> getSeparableGauss(double sigma){

    int height = 6*sigma + 1;
    int width = 6*sigma + 1;
    shared_ptr<MyKernel> sepKer = make_shared<MyKernel>(height, width);

    int xc =  height / 2;
    int yc =  width / 2;
    for(int i = 0;i<width;i++){
        double val = (1.0/(sqrt(2.0*M_PI)*sigma))*pow(M_E,-((i - xc)*(i - xc))/(2.0*sigma*sigma));
        sepKer->set(0,i,val);
    }

    for(int i = 0;i<height;i++){
        double val = (1.0/(sqrt(2.0*M_PI)*sigma))*pow(M_E,-((i - yc)*(i - yc))/(2.0*sigma*sigma));
        sepKer->set(i,0,val);
    }

    return sepKer;
}

//shared_ptr<Pyramid> getGaussPyramid(shared_ptr<CVImage> img){
//    shared_ptr<Pyramid> pyramid = make_shared<Pyramid>();




//    return pyramid;
//}


int main(){

    //saveImage(normalize(sobel(loadImage())),"sobel");
//    auto img = CVImage::loadImage();

//    qDebug() << "Failed to load image: " << nameImage;

     auto img = CVImage::loadImage(nameImage);

//    img->loadImage();

    //saveImage(normalize(convolution(img,getGaussKernel(3))),"gauss");
    //saveImage(normalize(separabel(img,getSeparableGauss(3))),"sepgauss");
//    saveImage(img, "norm");

    return 0;
}


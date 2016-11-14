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

QString nameImageSova = "D:\\labs\\my\\1\\sova.PNG";


int main(){

//    auto sobX = make_shared<MyKernel>(3,3,sobelX);
//    auto sobY = make_shared<MyKernel>(3,3,sobelY);
//    CVImage::loadImage(nameImage)->sobel(MyKernel::getSobelX(),MyKernel::getSobelY())->saveImage("sobel.png");

//    CVImage::loadImage(nameImageSova)->saveImage("sovaNorm.png");
//    CVImage::loadImage(nameImageSova)->convolution(MyKernel::getGaussKernel(1))->normalize()->saveImage("1gaus1.png");
//    CVImage::loadImage(nameImageSova)->convolution(MyKernel::getGaussKernel(5))->normalize()->saveImage("5gaus5.png");
//    CVImage::loadImage(nameImageSova)->convolution(MyKernel::getGaussKernel(10))->normalize()->saveImage("10gaus10.png");

    //сепарабильные гаусс
//    CVImage::loadImage(nameImageSova)->separatedGauss(1)->normalize()->saveImage("1gaus11.png");
//    CVImage::loadImage(nameImageSova)->separatedGauss(5)->normalize()->saveImage("5gaus55.png");
//    CVImage::loadImage(nameImageSova)->separatedGauss(10)->normalize()->saveImage("10gaus1010.png");

    shared_ptr<Pyramid> pyramid = make_shared<Pyramid>(CVImage::loadImage(nameImage), 1.5, 2);
    pyramid->save();
//    cout<<myIm->getPixel(1000,1000)<<endl;
//    cout<<p.L(1000,1000,3)<<endl;
//    cout<<p.L(1000,1000,6)<<endl;
//    cout<<p.L(1000,1000,15)<<endl;
//    cout<<"\ngood";

    return 0;
}


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
#define NAME_IMAGE "/home/artem/sova.png"
using namespace std;

double intToDouble(int val)
{
    return (double)val/255;
}

int doubleToInt(double val)
{
    return int(val*255);
}

shared_ptr<CVImage> loadImage(){
    QImage qimg(NAME_IMAGE);
    int width = qimg.size().width();
    int height = qimg.size().height();
    cout<<"Size image: width=" << width <<" height="<<height<<endl;

    shared_ptr<CVImage> cvimage = make_shared<CVImage>(height,width);

    for (int i=0; i<height; i++)
    {
        for(int j=0;j<width;j++)
        {
            cvimage->setPixel(i,j,intToDouble(qGray(qimg.pixel(j,i))));
            //  cvimage->setPixel(j,i,intToDouble(qimg.pixel(i,j)));
        }

    }
    return cvimage;
}

void saveImage(shared_ptr<CVImage> img, QString file){
    auto size = QSize(img->getWidth(),img->getHeight());
    QImage qimg(size,QImage::Format_RGB32);
    for(int i=0;i<img->getHeight();i++)
    {
        for(int j=0;j<img->getWidth();j++)
        {
            int pixel = doubleToInt(img->getPixel(i,j));
            // int pixel = img->getPixel(i,j);
            qimg.setPixel(j,i,qRgb(pixel,pixel,pixel));
        }
    }
    qimg.save(file,"PNG");
}

shared_ptr<CVImage> convolution(shared_ptr<CVImage> img, shared_ptr<MyKernel> kernel){

    shared_ptr<CVImage> newImg = make_shared<CVImage>(img->getHeight(),img->getWidth());

    for(int i=0;i<img->getHeight();i++){
        for(int j=0;j<img->getWidth();j++){
            double sum =0;
            for(int _i=0;_i<kernel->getHeight();_i++){
                for(int _j=0;_j<kernel->getWidth();_j++){
                    int posX = i+_i-kernel->getHeight()/2;
                    int posY = j+_j-kernel->getWidth()/2;

                    // double val = img->getPixel(posX,posY);
                    // double val = img->getPixelCopy(posX,posY);
                    // double val = img->getPixelMirror(posX,posY);
                    double val = img->getPixel(posX,posY);

                    double ker = kernel->get(kernel->getHeight()-1-_i,kernel->getWidth()-1-_j);

                    sum+=val*ker;
                }
            }
            newImg->setPixel(i,j,sum);

        }
    }
    return newImg;
}

shared_ptr<CVImage> normalize(shared_ptr<CVImage> img){
    shared_ptr<CVImage> newImg = make_shared<CVImage>(img->getHeight(),img->getWidth());
    double min=10, max=-10;

    auto result = std::minmax_element (img->getBeginImage(),img->getBeginImage() + img->getWidth()*img->getHeight());
    min= *result.first;
    max = *result.second;

    for(int i=0;i<img->getHeight();i++){
        for(int j=0;j<img->getWidth();j++){
            newImg->setPixel(i,j,((img->getPixel(i,j)-min)/(max-min)));
        }
    }
    return newImg;
}


double sobelX[9] = {-1,0,1,-2,0,2,-1,0,1};
double sobelY[9] = {-1,-2,-1,0,0,0,1,2,1};


shared_ptr<CVImage> sobel(shared_ptr<CVImage> img){
    auto sobX = make_shared<MyKernel>(3,3,sobelX);
    auto sobY = make_shared<MyKernel>(3,3,sobelY);
    auto sX = convolution(img,sobX);
    auto sY = convolution(img,sobY);
    auto newImg = make_shared<CVImage>(img->getHeight(),img->getWidth());

    for(int i=0;i<img->getHeight();i++){
        for(int j=0;j<img->getWidth();j++){
            newImg->setPixel(i,j,sqrt(sX->getPixel(i,j) * sX->getPixel(i,j) + sY->getPixel(i,j) * sY->getPixel(i,j)));
        }
    }
    return newImg;
}

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

shared_ptr<Pyramid> getGaussPyramid(shared_ptr<CVImage> img){
    shared_ptr<Pyramid> pyramid = make_shared<Pyramid>();




    return pyramid;
}


int main(){

    //saveImage(normalize(sobel(loadImage())),"sobel");
    auto img=loadImage();

    //saveImage(normalize(convolution(img,getGaussKernel(3))),"gauss");
    saveImage(normalize(separabel(img,getSeparableGauss(3))),"sepgauss");


    return 0;
}


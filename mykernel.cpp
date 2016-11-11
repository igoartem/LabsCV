#include "mykernel.h"
#include <memory>

using namespace std;

int MyKernel::getWidth(){
    return width;
}
int MyKernel::getHeight(){
    return height;
}
double MyKernel::get(int i, int j){
    return kernel[i*width + j];
}

MyKernel::MyKernel(int h,int w){
    this->height =h;
    this->width = w;
    kernel = unique_ptr<double[]> (new double[h*w]);
}
void MyKernel::set(int i, int j, double val){
    kernel[i*width + j] = val;
}

MyKernel::MyKernel(int h, int w, double ker[]){
    this->height =h;
    this->width = w;
    kernel = unique_ptr<double[]> (new double[h*w]);
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++){

            set(i,j,ker[i*width+j]);
        }
    }

}

shared_ptr<MyKernel> MyKernel::getGaussKernel(double sigma){

    //полуразмер 3 сигма
    int sigma3 = 3*sigma;
    int sigmaPow2 = sigma * sigma;

    int hKernel = 2*sigma3 + 1;
    int wKernel = 2*sigma3 + 1;
    shared_ptr<MyKernel> ker = make_shared<MyKernel>(hKernel, wKernel);
    for(int i = -sigma3;i <= sigma3; i++){
        for(int j=-sigma3;j<=sigma3;j++){
            double val = (pow(M_E, -(i*i + j*j)/(2*sigmaPow2))/(2.0*M_PI*sigmaPow2));
            ker->set(i + sigma3,j+sigma3 ,val);
        }
    }
    return ker;
}

shared_ptr<MyKernel> MyKernel::getSobelX(){
    double sobelX[9] = {-1,0,1,-2,0,2,-1,0,1};
    return make_shared<MyKernel>(3,3,sobelX);
}

shared_ptr<MyKernel> MyKernel::getSobelY(){
    double sobelY[9] = {-1,-2,-1,0,0,0,1,2,1};
    return make_shared<MyKernel>(3,3,sobelY);
}

pair<shared_ptr<MyKernel>,shared_ptr<MyKernel>> MyKernel::getGaussSeparated(double sigma)
{
    int sigma3 = 3*sigma;
    int size = 2 * sigma3 + 1;

    double sigmaPow2 = sigma*sigma;

    pair<shared_ptr<MyKernel>,shared_ptr<MyKernel>> result = make_pair(make_shared<MyKernel>(1,size), make_shared<MyKernel>(size,1));

    double value;

    for(int i=-sigma3; i<=sigma3; i++){
        value = (pow(M_E,-(i*i)/(2*sigmaPow2)))/(sqrt(2*M_PI)*sigma);
        result.first->set(0, i + sigma3, value);
        result.second->set(i + sigma3, 0, value);
    }

    return result;
}

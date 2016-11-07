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

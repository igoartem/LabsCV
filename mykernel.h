#ifndef MYKERNEL
#define MYKERNEL
#include<memory>
#include <math.h>
using namespace std;
class MyKernel
{
    private:
    int height,width;
    unique_ptr<double[]> kernel;
public:
    MyKernel(int h,int w);
    MyKernel(int h, int w, double ker[]);
    int getWidth();
    int getHeight();
    double get(int i, int j);
    void set(int i,int j, double val);
    static shared_ptr<MyKernel> getGaussKernel(double sigma);
    static shared_ptr<MyKernel> getSobelX();
    static shared_ptr<MyKernel> getSobelY();
    static pair<shared_ptr<MyKernel>,shared_ptr<MyKernel>> getGaussSeparated(double sigma);

};
#endif // MYKERNEL


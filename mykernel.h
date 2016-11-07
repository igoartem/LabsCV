#ifndef MYKERNEL
#define MYKERNEL
#include<memory>
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

};
#endif // MYKERNEL


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

shared_ptr<CVImage> CVImage::loadImage(const QString& fileName){
    QImage qimg;
    bool loaded = qimg.load(fileName);
    if(!loaded){
        qDebug() << "Failed to load image: " << fileName;
        return nullptr;
    }
    int width = qimg.size().width();
    int height = qimg.size().height();
    qDebug()<<"Size image: width=" << width <<" height="<<height;

    shared_ptr<CVImage> cvimage = make_shared<CVImage>(height,width);

    for (int i=0; i<height; i++)
    {
        for(int j=0;j<width;j++)
        {
            cvimage->setPixel(i,j, intToDouble(qGray(qimg.pixel(j,i))));
            //  cvimage->setPixel(j,i,intToDouble(qimg.pixel(i,j)));
        }

    }
    return cvimage;
}

void CVImage::saveImage(shared_ptr<CVImage> img, QString file){
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


double CVImage::intToDouble(int val)
{
    return (double)val/255;
}

int CVImage::doubleToInt(double val)
{
    return int(val*255);
}

shared_ptr<CVImage> CVImage::convolution(shared_ptr<CVImage> img, shared_ptr<MyKernel> kernel){

    shared_ptr<CVImage> newImg = make_shared<CVImage>(img->getHeight(),img->getWidth());

    for(int i=0;i<img->getHeight();i++){
        for(int j=0;j<img->getWidth();j++){
            double sum =0;
            for(int _i=0;_i<kernel->getHeight();_i++){
                for(int _j=0;_j<kernel->getWidth();_j++){
                    int posX = i+_i-kernel->getHeight()/2;
                    int posY = j+_j-kernel->getWidth()/2;

                    // double val = img->getPixel(posX,posY); //разные виды краевых значений
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

shared_ptr<CVImage> CVImage::normalize(shared_ptr<CVImage> img){
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

shared_ptr<CVImage> CVImage::sobel(shared_ptr<CVImage> img, double sobelX[9], double sobelY[9]){
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





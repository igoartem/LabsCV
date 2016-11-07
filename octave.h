#ifndef OCTAVE_H
#define OCTAVE_H
#include<memory>
#include<level.h>
using namespace std;

class Octave
{
private:
    unique_ptr<Level[]> levels;
    int sizeLevel;
public:
    Octave();

};

#endif // OCTAVE_H

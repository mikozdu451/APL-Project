#include<iostream>
#include<conio.h>

#include <fstream>

using namespace std;
struct pix {
    unsigned char b,g,r; } pixel;
unsigned char gray;
int L=255;//L is set to highest intensity per byte
char Header[54];

ifstream in;
ofstream out,out1;

int main() {
    char infile[]="sample.bmp";
    char outfile[]="out.bmp";
    char imdata[]="out1.dat";
    double options[4][3]= {{0.3, 0.59, 0.11}, {0.2126, 0.7152, 0.0722}, {0.299, 0.587, 0.113}, {0.333, 0.333, 0.333}};
    in.open(infile,ios::in|ios::binary);
    in.read((char*)(&Header),sizeof(Header));
    out.open(outfile,ios::out|ios::binary);
    out.write((char*)(&Header),sizeof(Header));
    //out1.open(imdata,ios::out);
    int choice = 0;
    while(!in.eof()) {
        in.read((char*) (&pixel),sizeof(pixel));
        //out1<<"ORIGINAL : "<<(int)pixel.r<<" , "<<(int)pixel.g<<" , "<<(int)pixel.b<<endl;
        gray = pixel.r * options[choice][0] + pixel.r * options[choice][1] + pixel.r * options[choice][2];
        pixel.r= gray;
        pixel.g= gray;
        pixel.b= gray;
        out.write((char*) (&pixel),sizeof(pixel));
        //out1<<"MODIFIED : "<<(int)pixel.r<<" "<<(int)pixel.g<<" "<<(int)pixel.b<<endl;
        }
    in.close();
    out.close();
    //out1.close();
    return 0;
}
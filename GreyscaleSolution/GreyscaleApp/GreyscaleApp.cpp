#include <iostream>
#include <random>
#include "BMP.h"

extern "C" float _stdcall MyProc3(double R, double G, double B);

//using namespace std;
//
//int random(int min, int max) //range : [min, max]
//{
//	static bool first = true;
//	if (first)
//	{
//		srand(time(NULL)); //seeding for the first time only!
//		first = false;
//	}
//	return min + rand() % ((max + 1) - min);
//}

int main() {


	/*int R = random(1, 255), G = random(1, 255), B = random(1, 255);
	float grey = MyProc3(R, G, B);

	for (int i = 0; i < 255; i++)
	{
		R = random(1, 255), G = random(1, 255), B = random(1, 255);
		float grey = MyProc3(R, G, B);
		int greInt = int(MyProc3(R, G, B));
		std::cout << "R: " << R << " G: " << G << " B: " << B << std::endl;
		cout << "Grey: " << grey << " GreInt: " << greInt << endl;
	}*/

	BMP bmp1("testing.bmp");
	bmp1.grayscale();
	bmp1.write("testinggrey.bmp");

	BMP bmp2("testing.bmp");
	bmp2.sepia();
	bmp2.write("testingsepia.bmp");

	return 0;
}
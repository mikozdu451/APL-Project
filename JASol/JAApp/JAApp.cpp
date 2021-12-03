// JAApp.cpp : Defines the entry point for the console application.
//
#include <windows.h>
#include <time.h>
#include <iostream>
#include <iomanip>


extern "C" int _stdcall Grayscale_GIMP(int*, DWORD);
extern "C" int _stdcall Grayscale_BT709(int*, DWORD);
extern "C" int _stdcall Grayscale_BT601(int*, DWORD);
extern "C" int _stdcall Grayscale_arithmetic(int*, DWORD);


int main()
{
	//typedef int(CALLBACK* TestProc)(int*, int);

	//HINSTANCE dllHandle = NULL;

	//TestProc RGBtoGrayScale = (TestProc)GetProcAddress(dllHandle, "TestProc");


	srand(time(NULL));
	int R, G, B;
	float showcase_arr_bt709[120];
	int Grayscale_GIMP_arr[120];
	int Grayscale_BT709_arr[120];
	int Grayscale_BT601_arr[120];
	int Grayscale_arithmetic_arr[120];
	
	int sizexd3 = sizeof(showcase_arr_bt709) / sizeof(showcase_arr_bt709[0]);
	int sizexd = sizeof(Grayscale_GIMP_arr) / sizeof(Grayscale_GIMP_arr[0]);
	for (int i = 0; i < sizexd3; i += 3)
	{
		std::cout << "Setting Randoms " << i << std::endl;
		R = rand() % 255 + 1;
		G = rand() % 255 + 1;
		B = rand() % 255 + 1;
		Grayscale_GIMP_arr[i] = R;
		Grayscale_GIMP_arr[i + 1] = G;
		Grayscale_GIMP_arr[i + 2] = B;

		showcase_arr_bt709[i] = R;
		showcase_arr_bt709[i + 1] = G;
		showcase_arr_bt709[i + 2] = B;

		Grayscale_BT709_arr[i] = R;
		Grayscale_BT709_arr[i + 1] = G;
		Grayscale_BT709_arr[i + 2] = B;

		Grayscale_BT601_arr[i] = R;
		Grayscale_BT601_arr[i + 1] = G;
		Grayscale_BT601_arr[i + 2] = B;

		Grayscale_arithmetic_arr[i] = R;
		Grayscale_arithmetic_arr[i + 1] = G;
		Grayscale_arithmetic_arr[i + 2] = B;

	}

	sizexd3 = sizeof(Grayscale_GIMP_arr) / sizeof(Grayscale_GIMP_arr[0]);
	sizexd = sizeof(showcase_arr_bt709) / sizeof(showcase_arr_bt709[0]);
	std::cout << sizexd3 << std::endl;
	Grayscale_GIMP(&Grayscale_GIMP_arr[0], sizexd3);
	Grayscale_BT709(&Grayscale_BT709_arr[0], sizexd3);
	Grayscale_BT601(&Grayscale_BT601_arr[0], sizexd3);
	Grayscale_arithmetic(&Grayscale_arithmetic_arr[0], sizexd3);
	int iter = 1;
	for (int j = 0; j < sizexd; j+=3)
	{
		std::cout << iter << std::endl;
		std::cout << "Default RGB values: " << showcase_arr_bt709[j] << " " << showcase_arr_bt709[j + 1] << " " << showcase_arr_bt709[j + 2] << std::endl
			<< "Grayscale_BT709_Float: " << (showcase_arr_bt709[j] * 0.2126) + (showcase_arr_bt709[j + 1] * 0.7152) + (showcase_arr_bt709[j + 2] * 0.0722) << " "
			<< (showcase_arr_bt709[j] * 0.2126) + (showcase_arr_bt709[j + 1] * 0.7152) + (showcase_arr_bt709[j + 2] * 0.0722) << " "
			<< (showcase_arr_bt709[j] * 0.2126) + (showcase_arr_bt709[j + 1] * 0.7152) + (showcase_arr_bt709[j + 2] * 0.0722) << std::endl
			<< "Grayscale_BT709_FloatCastInt: " << (int)((showcase_arr_bt709[j] * 0.2126) + (showcase_arr_bt709[j + 1] * 0.7152) + (showcase_arr_bt709[j + 2] * 0.0722)) << " "
			<< (int)((showcase_arr_bt709[j] * 0.2126) + (showcase_arr_bt709[j + 1] * 0.7152) + (showcase_arr_bt709[j + 2] * 0.0722)) << " "
			<< (int)((showcase_arr_bt709[j] * 0.2126) + (showcase_arr_bt709[j + 1] * 0.7152) + (showcase_arr_bt709[j + 2] * 0.0722)) << std::endl;
		std::cout << "ASM" << std::endl;
		std::cout << "Grayscale_GIMP_arr: " << Grayscale_GIMP_arr[j] << " " << Grayscale_GIMP_arr[j + 1] <<" " << Grayscale_GIMP_arr[j + 2] << std::endl;
		std::cout << "Grayscale_BT709_arr: " << Grayscale_BT709_arr[j] << " " << Grayscale_BT709_arr[j + 1] << " " << Grayscale_BT709_arr[j + 2] << std::endl;
		std::cout << "Grayscale_BT601_arr: " << Grayscale_BT601_arr[j] << " " << Grayscale_BT601_arr[j + 1] << " " << Grayscale_BT601_arr[j + 2] << std::endl;
		std::cout << "greyscaled_asm: " << Grayscale_arithmetic_arr[j] << " " << Grayscale_arithmetic_arr[j + 1] << " " << Grayscale_arithmetic_arr[j + 2] << std::endl;

		std::cout << std::endl;
		iter++;
	}

	return 0;

}

#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

class   CaptureScreen
{
    public: CaptureScreen()
    {   // ���������:
        ScreenDC = GetDC(0);
        MemoryDC = CreateCompatibleDC(ScreenDC);

        // ������ ������:
        screen_x = GetSystemMetrics(SM_CXSCREEN);
        screen_y = GetSystemMetrics(SM_CYSCREEN);

        // ���������� ��������� �������                         :
        BMI.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        BMI.bmiHeader.biWidth = screen_x;
        // �������������, ����� ����������� �� ���� �����������:
        BMI.bmiHeader.biHeight = -screen_y;
        BMI.bmiHeader.biSizeImage = screen_x * screen_y * 3;
        BMI.bmiHeader.biCompression = BI_RGB;
        BMI.bmiHeader.biBitCount = 24;
        BMI.bmiHeader.biPlanes = 1;

        ScreenshotSize = BMI.bmiHeader.biSizeImage;

        hBitmap = CreateDIBSection(ScreenDC, &BMI, DIB_RGB_COLORS, (void**)&buf, 0, 0);
    }
    ~CaptureScreen()
    {
        DeleteDC(MemoryDC);
        ReleaseDC(NULL, ScreenDC);
        DeleteObject(hBitmap);
    }

    HDC     ScreenDC;
    HDC     MemoryDC;
    HBITMAP  hBitmap;
    BITMAPINFO   BMI;
      
    unsigned char* buf;      
      
    int   ScreenshotSize;      
    int   screen_x;
    int   screen_y;
    int   rgb_returned[3];
      

    void get_pixel(int, int, int, int);
    int* info(int, int);
};

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<windows.h>
#include<stdio.h>
#include <QColor>
#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "wingdi.h"
#include <thread>
#include <QGuiApplication>
#include "XLAT_head.h"
#include <chrono>
#include <QMessageBox>
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib, "winmm.lib")
//#include <sstream>
using namespace std;
CaptureScreen CaptureSc;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

}

MainWindow::~MainWindow()
{
    delete ui;
}
unsigned long color[MAX_PATH];

void CaptureScreen::get_pixel(int x, int y, int width, int height)
{
    SelectObject(MemoryDC, hBitmap);
    BitBlt(MemoryDC, 0, 0, width, height, ScreenDC, x, y, SRCCOPY);
}
int* CaptureScreen::info(int x, int y)
{
    rgb_returned[0] = buf[(y * screen_x + x) * 3 + 2];
    rgb_returned[1] = buf[(y * screen_x + x) * 3 + 1];
    rgb_returned[2] = buf[(y * screen_x + x) * 3];

    return rgb_returned;
}
unsigned long get_color(int x,int y )
{
    int s = CaptureSc.rgb_returned[0] = CaptureSc.buf[(y * CaptureSc.screen_x + x) * 3 + 2];
    int ss = CaptureSc.rgb_returned[1] = CaptureSc.buf[(y * CaptureSc.screen_x + x) * 3 + 1];
    int sss = CaptureSc.rgb_returned[2] = CaptureSc.buf[(y * CaptureSc.screen_x + x) * 3];
    unsigned long rgb_hex = (s<<16)|(ss<<8)|sss;
    return rgb_hex;
}

POINT pos_mishka;
void getColorMish()
{
while(true)
{
Sleep(1);
if (GetAsyncKeyState(VK_F4)) //Действие по нажатию F12
{
GetCursorPos(&pos_mishka);
CaptureSc.get_pixel(0, 0, 1600, 900);
qDebug()<<get_color(pos_mishka.x,pos_mishka.y)<<pos_mishka.x<<pos_mishka.y;
Sleep(300);
}
}
}

void MainWindow::on_mishka_color_clicked()
{
std::thread thr(getColorMish);
thr.detach();
}


void bot_color()
{
            qDebug()<<"start";
             int y=0;
    while(true)
    {
        Sleep(1);
        if((GetKeyState(VK_RBUTTON) & 0x100) != 0)
        {
            qDebug()<<"ss";
           POINT s;
           Sleep(10);
           GetCursorPos(&s);
           s.x += 16;s.y +=10;
           CaptureSc.get_pixel(0, 0, 1600, 900);
           unsigned long  jopa = get_color(s.x,s.y);
           std::string test1 = std::to_string(jopa);
        if(jopa==16739840)MessageBoxA(NULL, test1.c_str(), "Yes", MB_OK);


           Sleep(1000);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    std::thread bot_colors(bot_color);
   bot_colors.detach();
}


int xds = 100;


int int_value_error;
const size_t sz = 512;
char buf[sz];
HWND hwnd_start;
bool predel = false;
RECT rect;
QString value_error = "0";
BOOL down_W = false,down_S = false,down_Space = false;
HWND HWND_PROVAL(HWND hwnd){return GetWindow (hwnd,GW_CHILD);}
HWND HWND_NEXT(HWND hwnd){return GetWindow (hwnd,GW_HWNDNEXT);}
HWND HWND_BACK(HWND hwnd){return GetWindow (hwnd,GW_HWNDPREV);}
bool MainWindow::reset_hwnd()
{
       HWND hwnd_iseika_start = FindWindow(NULL, L"Мониторинг ячеек");
       ShowWindow (hwnd_iseika_start, SW_SHOWMAXIMIZED);//Светим окно
       SetForegroundWindow(hwnd_iseika_start);
       hwnd_iseika_start =  HWND_PROVAL (hwnd_iseika_start);
       hwnd_iseika_start =  HWND_NEXT   (hwnd_iseika_start);
       hwnd_start =  HWND_PROVAL (hwnd_iseika_start);

       if(hwnd_start!=NULL)
       {
           statusBar()->showMessage("Успешное подключение к Мониторинг ячеек");
       }
       else
       {
       int_value_error = value_error.toInt() + 1;
       value_error = QString::number(int_value_error);
       statusBar()->showMessage("Ошибка! Мониторинг ячеек не найден! Уже x" + value_error + " раз");
       }

       if(hwnd_start==NULL)return false;else return true;
}
void goto_door_to_curso_and_click(HWND hwnd)
{
    GetWindowRect(hwnd, &rect);
    SetCursorPos(rect.left+((rect.right-rect.left)/2),rect.top+((rect.bottom-rect.top)/2));

    ShowWindow (hwnd, SW_SHOW);//Светим окно
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,rect.left+((rect.right-rect.left)/2),rect.top+((rect.bottom-rect.top)/2), 0, 0); // нажали
    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,  rect.left+((rect.right-rect.left)/2),rect.top+((rect.bottom-rect.top)/2), 0, 0); //отпустили
}
string cout_name_tilte(HWND hWnd)
{
     const auto res = ::GetWindowTextA(hWnd, buf, int(sz - 1));
     buf[res] = 0;
     std::cout << buf;
     string strbuf = " ";
     return strbuf;
}

void MainWindow::open_clik_door()
{
    if(ui->checkBox_mexanik_open_door->checkState()||ui->checkBox_avto_open_door->checkState())
    {
    goto_door_to_curso_and_click(hwnd_start);
    Sleep(1);
    keybd_event(0x5D, 0,0,0);
    keybd_event(0x5D, 0,KEYEVENTF_KEYUP,0);
    Sleep(1);
    keybd_event(0x28, 0,0,0);
    keybd_event(0x28, 0,KEYEVENTF_KEYUP,0);
    Sleep(1);
    keybd_event(0x0D, 0,0,0);
    keybd_event(0x0D, 0,KEYEVENTF_KEYUP,0);
    }
}
bool MainWindow::clik_yes_and_ok_to_open_door()
{
    if(ui->checkBox_mexanik_open_door->checkState()||ui->checkBox_avto_open_door->checkState())
    {
        for ( int counter = 0; counter < 2000; counter++)
        {
            Sleep(1);
            if(ui->checkBox_mexanik_open_door->checkState() == false && ui->checkBox_avto_open_door->checkState()==false)break;
            if(FindWindow(NULL, L"Error")!=NULL)
            {
                    statusBar()->showMessage("Ошибка открытия ячейки! Замечено окно Error");
                    return false;
                    break;
            }
            else
            {
                HWND hwnd_warning_1 = FindWindow(NULL, L"Warning");
                if(counter > 200)cout<<counter<<endl;
                if(counter > 1999){cout<<"Eror time open door"<<endl;return false;;}
                    if(FindWindow(NULL, L"Confirm")!=NULL)
                    {
                        if(ui->checkBox_mexanik_open_door->checkState() == false && ui->checkBox_avto_open_door->checkState()==false)break;
                        HWND hwnd_confirm = HWND_PROVAL(FindWindow(NULL, L"Confirm"));
                        hwnd_confirm = HWND_NEXT(hwnd_confirm);
                        Sleep(100);
                        SendMessage(hwnd_confirm, BM_CLICK,  0,  0);
                    }
                    else if(hwnd_warning_1 != NULL)
                    {
                        hwnd_warning_1 = HWND_PROVAL(hwnd_warning_1);
                        const auto res = ::GetWindowTextA(hwnd_warning_1, buf, int(sz - 1));buf[res] = 0;
                            if(strstr (buf, "&No") != NULL)
                            {
                                if(ui->checkBox_mexanik_open_door->checkState() == false && ui->checkBox_avto_open_door->checkState()==false)break;
                                hwnd_warning_1 = HWND_NEXT(hwnd_warning_1);
                                Sleep(100);
                                SendMessage(hwnd_warning_1, BM_CLICK,  0,  0);
                            }
                            else if(strstr (buf, "OK") != NULL)
                            {
                                if(ui->checkBox_mexanik_open_door->checkState() == false && ui->checkBox_avto_open_door->checkState()==false)break;
                                Sleep(100);
                                SendMessage(hwnd_warning_1, BM_CLICK,  0,  0);
                                SetWindowText(hwnd_start, L"(Open)");
                                PlaySound(L"C:\\Users\\danilov_da\\Desktop\\ЕЕ\\звуки\\stuk-s-kompyuternyim-zvuchaniem.wav", NULL, SND_ASYNC);
                                goto_door_to_curso_and_click(hwnd_start);
                                return true;
                                break;
                            }
                    }
            }
        }
    }
}


void MainWindow::potok_open_door_mexanik()
{
    if(reset_hwnd()==true)
    {
        cout<<"Mexanik open dooor aktivited |  q+w = next door | q+s = back door | q + space = open door "<<endl;
            while(ui->checkBox_mexanik_open_door->checkState())
        {
            Sleep(1);
            cout<<"2";
            if (GetAsyncKeyState((INT)KeyCodes::W) && GetAsyncKeyState((INT)KeyCodes::Q)){down_W=true;}else
            if (GetAsyncKeyState((INT)KeyCodes::S) && GetAsyncKeyState((INT)KeyCodes::Q)){down_S=true;}else
            if (GetAsyncKeyState((INT)KeyCodes::SPACE) && GetAsyncKeyState((INT)KeyCodes::Q)){down_Space=true;}

            if (GetAsyncKeyState((INT)KeyCodes::W)==false && down_W==true && GetAsyncKeyState((INT)KeyCodes::Q))
            {
                label_1:
                down_W=false;
                if(HWND_NEXT(hwnd_start)!=NULL)
                {
                    hwnd_start = HWND_NEXT(hwnd_start);
                    const auto res = ::GetWindowTextA(hwnd_start, buf, int(sz - 1));buf[res] = 0;
                     if(strstr (buf, "(")!=NULL&&strstr (buf, ")")!=NULL)
                     {
                         predel=true;
                    cout << hwnd_start << " - " <<cout_name_tilte(hwnd_start) << endl;
                    goto_door_to_curso_and_click(hwnd_start);

                     }
                     else
                     {
                         goto label_1;
                     }
                }
            else if(predel==true){cout<<"Predel VERH"<<endl;predel=false;}
            }
            if (GetAsyncKeyState((INT)KeyCodes::S)==false && down_S==true && GetAsyncKeyState((INT)KeyCodes::Q))
            {
                label_2:
                down_S=false;
                if(HWND_BACK(hwnd_start)!=NULL)
                {
                    hwnd_start = HWND_BACK(hwnd_start);
                    const auto res = ::GetWindowTextA(hwnd_start, buf, int(sz - 1));buf[res] = 0;
                     if(strstr (buf, "(")!=NULL&&strstr (buf, ")")!=NULL)
                     {

                        predel=true;
                        cout << hwnd_start << " - " <<cout_name_tilte(hwnd_start) << endl;

                        goto_door_to_curso_and_click(hwnd_start);
                     }
                     else
                     {
                         goto label_2;
                     }
                }
                else if(predel==true){cout<<"Predel NIZ privet"<<endl;predel=false;}
            }
            if (GetAsyncKeyState((INT)KeyCodes::SPACE) && down_Space==true && GetAsyncKeyState((INT)KeyCodes::Q))
            {
                down_Space = false;
                open_clik_door();
                clik_yes_and_ok_to_open_door();
            }

        }
    }
    else ui->checkBox_mexanik_open_door->setChecked(false);
}
void MainWindow::on_mexanik_open_door_button_clicked()
{
    Potok_2_run_open_door_mexanik();
}


void MainWindow::potok_open_door_avtomat()
{
    bool odin_raz=false,nagata_A=false;
    if(reset_hwnd()==true)
    {
        cout<<"avtomat open door aktivited | A = start avto open door | D = stop open door"<<endl;
            while(ui->checkBox_avto_open_door->checkState())
            {
                if(ui->checkBox_mexanik_open_door->checkState() == false && ui->checkBox_avto_open_door->checkState()==false)break;
                if (GetAsyncKeyState((INT)KeyCodes::A)&&nagata_A==false)nagata_A=true;
                if (GetAsyncKeyState((INT)KeyCodes::D)&&nagata_A==true )nagata_A=false;

                if(nagata_A)
                {
                    if(odin_raz==false)
                    {
                        open_clik_door();
                        for ( int counter = 0; counter < 200; counter++)
                        {
                            Sleep(1);
                            cout<<counter<<endl;
                            if(counter>1900){cout<<"eror 1/1";break;}
                            if(FindWindow(NULL, L"Confirm")!=NULL)
                            {
                                cout<<"ZAKRIL confrim"<<endl;
                                keybd_event(0x1B, 0,0,0);
                                keybd_event(0x1B, 0,KEYEVENTF_KEYUP,0);
                                Sleep(10);
                                break;
                            }
                        }
                    odin_raz=true;
                    }
                if(HWND_NEXT(hwnd_start)!=NULL)
                {
                    hwnd_start = HWND_NEXT(hwnd_start);
                    const auto res = ::GetWindowTextA(hwnd_start, buf, int(sz - 1));buf[res] = 0;
                    if(strstr (buf, "(")!=NULL&&strstr (buf, ")")!=NULL)
                    {
                        predel=true;
                        cout << hwnd_start << " - " <<cout_name_tilte(hwnd_start) << endl;
                        goto_door_to_curso_and_click(hwnd_start);

                        open_clik_door();
                        nagata_A = clik_yes_and_ok_to_open_door();


                    Sleep(300);
                    }
                    } else {cout<<"Finish"<<endl;break;}
                }
            Sleep(1);
            }
    }
    else ui->checkBox_avto_open_door->setChecked(false);
}


void MainWindow::on_Avto_open_door_button_clicked()
{
    Potok_1_run_open_door_avtomat();
}


HWND masiv_hwnd_door[MAX_PATH];




void MainWindow::on_avto_open_NULL_door_pushButton_clicked()
{
    RECT rect;
    HWND masiv_hwnd_pusto[MAX_PATH],masiv_hwnd_zanito[MAX_PATH];
    int value_pusto = 0,value_zanito = 0;
    unsigned long color_door = 0;
     if(reset_hwnd()==true)
     {
         CaptureSc.get_pixel(0, 0, 1600, 900);
             while(hwnd_start!=NULL)
             {
                 const auto res = ::GetWindowTextA(hwnd_start, buf, int(sz - 1));buf[res] = 0;
                 if(strstr (buf, "(")!=NULL&&strstr (buf, ")")!=NULL)
                 {
                         GetWindowRect(hwnd_start, &rect);
                         color_door = get_color(rect.left + 2,rect.top + 2);

                         if(color_door == 43008)
                         {
                            masiv_hwnd_zanito[value_zanito] = hwnd_start;
                            value_zanito++;
                            cout<<"ZANITA DOOR " << endl;
                         }
                         else if (color_door == 33023)
                         {
                             masiv_hwnd_zanito[value_zanito] = hwnd_start;
                             value_zanito++;
                             cout<<"VOZVRAT DOOR " << endl;

                         }
                         else if (color_door == 16741120)
                         {
                            masiv_hwnd_pusto[value_pusto] = hwnd_start;
                            value_pusto++;
                            cout<<"PUSTO DOOR " << endl;
                         }
                         cout<<hwnd_start<<cout_name_tilte(hwnd_start)<<" - " << color_door << endl;

                     hwnd_start = HWND_NEXT(hwnd_start);
                 }
                 else
                 {
                     hwnd_start = HWND_NEXT(hwnd_start);
                 }
             }
         cout<<"PUSTO - "<<value_pusto<<" ZANITA - "<<value_zanito<<endl;
     }

}

void Clipboard(char str[], int length)
{
    HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, length * sizeof(CHAR*));
    LPVOID gl = GlobalLock(h);

    memcpy(gl, str, length * sizeof(CHAR*));

    GlobalUnlock(gl);

    OpenClipboard(NULL); // hWnd is set to NULL
    EmptyClipboard(); // Sets clipboard ownership to someone don't know
    SetClipboardData(CF_TEXT, h);  // Successfully data to clipboard!
    CloseClipboard();
}

void MainWindow::on_pushButton_2_clicked()
{
    int value_exit_poisk_ko = -1;
    start_poisk_ko:
    value_exit_poisk_ko++;
    if(value_exit_poisk_ko >= 5)
    {
        cout<<"EROR TIME"<<endl;
        QMessageBox::warning(this, "Внимание","не существует/ошибка КО - ");
    }
    else
    {
        for ( int counter = 0; counter < 3000; counter++)
        {
            if(FindWindow(NULL, L"Ошибка")){SendMessage(FindWindow(NULL, L"Ошибка"),WM_SYSCOMMAND,SC_CLOSE,0);}
            else if(FindWindow(NULL, L"Поиск по номеру")){SendMessage(FindWindow(NULL, L"Поиск по номеру"),WM_SYSCOMMAND,SC_CLOSE,0);}
            else if(FindWindow(L"TfmInvoiceInfo", NULL)){SendMessage(FindWindow(L"TfmInvoiceInfo", NULL),WM_SYSCOMMAND,SC_CLOSE,0);}
            else if(FindWindow(NULL, L"Предупреждение")){SendMessage(FindWindow(NULL, L"Предупреждение"),WM_SYSCOMMAND,SC_CLOSE,0);}
            else break;
        }
        if(FindWindow(NULL, L"Ошибка") == NULL && FindWindow(NULL, L"Поиск по номеру") == NULL)
        {
            HWND HWND_POISK_KO = NULL,HWND_PUSH_BOTON_SHK = NULL,HWND_PUSH_BOTON_KO = NULL;
            for ( int counter = 0; counter < 1000; counter++)
            {
                if(FindWindow(NULL, L"Ошибка"))SendMessage(FindWindow(NULL, L"Ошибка"),WM_SYSCOMMAND,SC_CLOSE,0);
                cout<<"OPEN INFO - 0 "<<endl;
                HWND_PUSH_BOTON_KO = FindWindow(NULL, L"Информационное");
                HWND_PUSH_BOTON_KO = HWND_PROVAL(HWND_PUSH_BOTON_KO);
                HWND_PUSH_BOTON_KO = HWND_PROVAL(HWND_PUSH_BOTON_KO);
                HWND_PUSH_BOTON_KO = HWND_NEXT(HWND_PUSH_BOTON_KO);
                HWND_PUSH_BOTON_KO = HWND_NEXT(HWND_PUSH_BOTON_KO);
                HWND_PUSH_BOTON_KO = HWND_NEXT(HWND_PUSH_BOTON_KO);
                HWND_PUSH_BOTON_KO = HWND_NEXT(HWND_PUSH_BOTON_KO);
                HWND_PUSH_BOTON_KO = HWND_NEXT(HWND_PUSH_BOTON_KO);
                HWND_PUSH_BOTON_KO = HWND_NEXT(HWND_PUSH_BOTON_KO);
                HWND_PUSH_BOTON_KO = HWND_NEXT(HWND_PUSH_BOTON_KO);
                HWND_PUSH_BOTON_KO = HWND_NEXT(HWND_PUSH_BOTON_KO);
                HWND_PUSH_BOTON_KO = HWND_NEXT(HWND_PUSH_BOTON_KO);
                HWND_PUSH_BOTON_SHK = HWND_NEXT(HWND_PUSH_BOTON_KO);
                HWND_PUSH_BOTON_KO = HWND_NEXT(HWND_PUSH_BOTON_SHK);
                PostMessage(HWND_PUSH_BOTON_KO, BM_CLICK,  0,  0);
                HWND_PUSH_BOTON_KO = NULL;
                if(FindWindow(NULL, L"Поиск по номеру"))break;
                cout<<"clik OK INFORMASIONOE OKNO STADIA - 1 "<<endl;
            }
            for ( int counter = 0; counter < 1000; counter++)
            {
                for ( int counter = 0; counter < 1000; counter++)
                {
                    if(FindWindow(NULL, L"Предупреждение"))
                    {
                        for ( int counter = 0; counter < 1000; counter++)
                        {
                            break;
                            //SendMessage(FindWindow(NULL, L"Предупреждение"),WM_SYSCOMMAND,SC_CLOSE,0);
                            //SendMessage(FindWindow(NULL, L"Поиск по номеру"),WM_SYSCOMMAND,SC_CLOSE,0);
                            if(FindWindow(NULL, L"Предупреждение") == NULL && FindWindow(NULL, L"Поиск по номеру") == NULL)goto start_poisk_ko;
                        }
                    }

                    if(FindWindow(NULL, L"Ошибка"))SendMessage(FindWindow(NULL, L"Ошибка"),WM_SYSCOMMAND,SC_CLOSE,0);
                    else break;
                }
                cout<<"POIST PO NOMERY"<<endl;
                HWND_POISK_KO = FindWindow(NULL, L"Поиск по номеру");
                HWND_POISK_KO = HWND_PROVAL(HWND_POISK_KO);
                HWND_POISK_KO = HWND_PROVAL(HWND_POISK_KO);
                HWND_POISK_KO = HWND_NEXT(HWND_POISK_KO);
                HWND_POISK_KO = HWND_NEXT(HWND_POISK_KO);
                HWND_POISK_KO = HWND_NEXT(HWND_POISK_KO);
                HWND_POISK_KO = HWND_NEXT(HWND_POISK_KO);
                HWND_POISK_KO = HWND_NEXT(HWND_POISK_KO);
                HWND_POISK_KO = HWND_NEXT(HWND_POISK_KO);
                HWND_POISK_KO = HWND_NEXT(HWND_POISK_KO);
                HWND_POISK_KO = HWND_NEXT(HWND_POISK_KO);
                HWND HWND_TEXT_KO = HWND_NEXT(HWND_POISK_KO);//9
                HWND_POISK_KO = HWND_NEXT(HWND_TEXT_KO);
                HWND HWND_CLIK_OK_TO_KO = HWND_NEXT(HWND_POISK_KO);
                cout<<"POISK PO NOMERY VSE NASHEL"<<endl;

                QString qstr_KO_in_polzovatel = ui->lineEdit_KO->text();

                char* char_KO_in_polzovatel = qstr_KO_in_polzovatel.toUtf8().data();
                Clipboard(char_KO_in_polzovatel,50);



                cout<<char_KO_in_polzovatel<<endl;

                //SendMessage(HWND_TEXT_KO, WM_SETTEXT, 0, (LPARAM)char_KO_in_polzovatel);

                wchar_t str[] = L"15999248777";
                SendMessageW(HWND_TEXT_KO, WM_SETTEXT, 0, (LPARAM)str);


                cout<<"Pomenal text"<<endl;
                PostMessage(HWND_CLIK_OK_TO_KO, BM_CLICK,  0,  0);
                cout<<"NAGAL OK"<<endl;
                if(FindWindow(L"TfmInvoiceInfo", NULL))break;
            }
        }
    }
}



void MainWindow::on_pushButton_4_clicked()
{
    cout<<"yes and ok ? "<<endl;

}


//2 низ ,9 перед
//2 низ , 11 перед TfmInvoiceInfo

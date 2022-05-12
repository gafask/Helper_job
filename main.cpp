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
#include <QApplication>
void Console()
{
    AllocConsole();
    FILE *pFileCon = NULL;
    pFileCon = freopen("CONOUT$", "w", stdout);

    COORD coordInfo;
    coordInfo.X = 130;
    coordInfo.Y = 9000;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coordInfo);
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE),ENABLE_QUICK_EDIT_MODE| ENABLE_EXTENDED_FLAGS);
}

int main(int argc, char *argv[])
{
    Console();
    setlocale(LC_ALL, "Russian");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

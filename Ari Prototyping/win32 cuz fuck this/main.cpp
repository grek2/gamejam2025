#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "graphics.cpp"
#pragma 




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow)
{
    renderingWindow win;
    
    if (!win.Create("gamejam2025", WS_OVERLAPPEDWINDOW,0,CW_USEDEFAULT,0,336,336))
    {
        return 0;
    }


    ShowWindow(win.Window(), nCmdShow);
    // std::ofstream communicator("comunication.txt");
    // communicator << win.Window();
    // communicator.close();
    // Run the message loop.
    UINT_PTR IDT_TIMER1;
    MSG msg = { };
        SetTimer(win.Window(),             // handle to main window 
        IDT_TIMER1,            // timer identifier 
        30,                 // 10-second interval 
        (TIMERPROC) NULL);   
    // PostMessage(win.Window(),WM_USER+2,(WPARAM)(120),LPARAM(32));
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    printf("testing");
    return 0;
}
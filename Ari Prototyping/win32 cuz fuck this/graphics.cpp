#include <windows.h>
#include <windowsx.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")
#include <fstream>
#include "basewin.h"
#include "getsprites.cpp"
#include "definitions.h"
#include <iostream>
#include <stdio.h>
#include <random>
#include <vector>
#define CHANGELEVEL WM_USER+1
#define UPDATE WM_USER+2


const char *levelmapfilepaths[4] = {"Maps\\0.txt","Maps\\3.txt","Maps\\2.txt","Maps\\3.txt"};

template <class T> void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}
// class Levelmap{
//     public:
//         int level[176]={0};
//         int oldlevel[176]={0};
//         std::vector<int> typemaps[42];
//         std::vector<int> typemaps2[42];
//         // std::vector<int> collidable;
//         int iscollidable[176];

//         void updatelevel(int newlevelnum){
            
//             // collidable = getcollidable(newlevelnum);
//             std::copy(level,level+176,oldlevel);
//             std::copy(typemaps,typemaps+sizeof(typemaps)/sizeof(std::vector<int>),typemaps2);
//             std::fill_n(level,176,0);
//             std::fill_n(iscollidable,176,0);
//             for(int i = 1; i<42; i++){
//                 std::vector<int> currentmap = settomap(newlevelnum,i);
//                 typemaps[i-1] = currentmap;
//                 if(i!=41){
//                     for(int j=0;j<currentmap.size();j++){
//                         level[currentmap.at(j)-1]=i;
//                         iscollidable[currentmap.at(j)-1]=1;
//                     }
//                 }
//                 else{
//                     for(int j=0;j<currentmap.size();j++){
//                         level[currentmap.at(j)-1]=i;
//                     }
//                 }
//             }

//         }
// };

class renderingWindow : public BaseWindow<renderingWindow>{
    Level level;
    ID2D1Factory            *pFactory;
    ID2D1HwndRenderTarget   *pRenderTarget;
    ID2D1HwndRenderTarget   *pGreenTarget;
    ID2D1HwndRenderTarget   *pBlackTarget;
    ID2D1SolidColorBrush    *pBrush;
    int levelnum=0;
    double subxPos = 320.0; 
    double subyPos = 192.0;
    int direction = 2;
    int directions[4] ={-1,-1,-1,-1};
    int moving = 0;
    int screenmoving = 0;
    double offset = 0.0;
    int movesprite = 0;
    const D2D1_COLOR_F green = D2D1::ColorF(13.0/256,146.0/256,99.0/256);
    const D2D1_COLOR_F black = D2D1::ColorF(0.0f,0.0f,0.0f);
    const D2D1_COLOR_F blue = D2D1::ColorF(0.0f,0.0f,0.75f);
    const D2D1_COLOR_F map = D2D1::ColorF(0.5f,0.5f,0.5f);    
    const D2D1_COLOR_F dbrown = D2D1::ColorF(225.0/256,91.0/256,25.0/256);
    const D2D1_COLOR_F white = D2D1::ColorF(1.0f,1.0f,1.0f);
    ID2D1SolidColorBrush *pMapBrush;
    ID2D1SolidColorBrush *pGreenBrush;
    ID2D1SolidColorBrush *pBlackBrush;
    ID2D1SolidColorBrush *pBlueBrush;
    ID2D1SolidColorBrush *pDBrownBrush;
    ID2D1SolidColorBrush *pWhiteBrush;

    // Levelmap levelmap;
    
    int firstbrush(int type){
        if (type<14){
            return 3;
        }
        if (type<27){
            return 0;
        }
        if(type<40){
            return 4;
        }
        if (type ==40){
            return 2;
        }
        if (type ==41){
            return 1;
        }
        return -1;

    }
    int secondbrush(int type){
        return (type==40) ? 3 : 1; 
    }
    // void drawthemap(double offx, double offy, double off2x, double off2y){
    //     ID2D1SolidColorBrush* brushlist[5]= {pGreenBrush,pBlackBrush,pBlueBrush,pDBrownBrush,pWhiteBrush};  
    //         drawamap(level.sprites,1,offx,offy,pRenderTarget,pBlueBrush,pGreenBrush,pBlackBrush);
    //         drawamap(level.sprites,1,off2x,off2y,pRenderTarget,brushlist[firstbrush(i)],brushlist[secondbrush(i)],pBlueBrush);
    //     // for(int i = 0;i<176;i++){
    //     //     int type = levelmap.level[i];
    //     //     int type2 = levelmap.oldlevel[i];
    //     //     int y = (i)/16;
    //     //     int x = (i)%16;
    //     //     drawsprites(pRenderTarget,brushlist[firstbrush(type)],brushlist[secondbrush(type)],type,48*(x+offx),48*(y+offy)+217,pBlueBrush);
    //     //     drawsprites(pRenderTarget,brushlist[firstbrush(type2)],brushlist[secondbrush(type2)],type2,48*(x+off2x),48*(y+off2y)+217,pBlueBrush);
    //     // }
    //     pRenderTarget->FillRectangle(D2D1::RectF(0,0,783,217), pBlackBrush);
    //     pRenderTarget->FillRectangle(D2D1::RectF(48,97,240,193), pMapBrush);
            
    // }


    void addtodirection(int dir){
        for(int i = 0;i<3;i++){
            if (directions[i]==dir||directions[i]==-1){
                directions[i]=directions[i+1];
                directions[i+1]=-1;
            }
        }
        for(int i =3; i>0;i--){
            directions[i] = directions[i-1];
        }
        directions[0]=dir;
        
    }
    
    void removefromdirection(int dir){
        for(int i = 0;i<3;i++){
            if (directions[i]==dir||directions[i]==-1){
                directions[i]=directions[i+1];
                directions[i+1]=-1;
            }
        }
    }
    
    // void   CalculateLayout(){
    //     if (pRenderTarget != NULL)
    //     {
    //         D2D1_SIZE_F size = pRenderTarget->GetSize();
    //         const float x = 10;
    //         const float y = 10;
    //     }
    // }
    
    HRESULT CreateGraphicsResources(){
        HRESULT hr = S_OK;
            if (pRenderTarget == NULL)
            {
                
                RECT rc;
                GetClientRect(m_hwnd, &rc);

                D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

                hr = pFactory->CreateHwndRenderTarget(
                    D2D1::RenderTargetProperties(),
                    D2D1::HwndRenderTargetProperties(m_hwnd, size),
                    &pRenderTarget);
                

                if (SUCCEEDED(hr))
                {
                    const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
                    hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);
                    HRESULT hr2 = pRenderTarget->CreateSolidColorBrush(green, &pGreenBrush);
                    HRESULT hr3 = pRenderTarget->CreateSolidColorBrush(black, &pBlackBrush);
                    HRESULT hr4 = pRenderTarget->CreateSolidColorBrush(blue, &pBlueBrush);
                    HRESULT hr5 = pRenderTarget->CreateSolidColorBrush(dbrown, &pDBrownBrush);
                    HRESULT hr6 = pRenderTarget->CreateSolidColorBrush(map, &pMapBrush);
                    HRESULT hr7 = pRenderTarget->CreateSolidColorBrush(white, &pWhiteBrush);
                    // if (SUCCEEDED(hr))
                    // {
                    //     CalculateLayout();
                    // }
                    
                }
            }
            return hr;
        };
    
    

    void    DiscardGraphicsResources(){
        SafeRelease(&pRenderTarget);
        SafeRelease(&pBrush);
    }
    void    levelTransition(int newnum);
    void    OnPaint(){
        HRESULT hr = CreateGraphicsResources();
        if (SUCCEEDED(hr))
        {
            PAINTSTRUCT ps;
            BeginPaint(m_hwnd, &ps);
        
            pRenderTarget->BeginDraw();
            const D2D1_COLOR_F backgroundcolor = D2D1::ColorF(0.0,0.0,0.0);  
            pRenderTarget->Clear(backgroundcolor);
            // pRenderTarget->FillRectangle(greenrectangle, pBrush);
            
            
                
            drawamap(level.sprites,1,3 - subxPos/16,3 - subyPos/16,subxPos,subyPos,pRenderTarget,pGreenBrush,pBlackBrush,pBlueBrush);

            drawsub(Window(),pRenderTarget,48*3,48*3,direction,movesprite/2);

            hr = pRenderTarget->EndDraw();
            if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
            {
                DiscardGraphicsResources();
            }
            EndPaint(m_hwnd, &ps);
        }
    };
    
    void    Resize(){
        if (pRenderTarget != NULL)
        {
            RECT rc;
            GetClientRect(m_hwnd, &rc);

            D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

            pRenderTarget->Resize(size);
            // CalculateLayout();
            InvalidateRect(m_hwnd, NULL, FALSE);
        }
    }

public:
    renderingWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL)
    {
    }
    LPCSTR ClassName() const { return (LPCSTR) "New Game Button Window";}
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    boolean checkCollision(boolean movingverticle,boolean movingup=false){
        // std::vector<int> collidable = levelmap.collidable;
        int x5 = (subxPos+7)/16;
        int y5 = (subyPos+7)/16;
        
        if(level.sprites[y5][x5]==1) return true;return false;
        // for(int i = 0; i<collidable.size();i++){
        //     if(collidable[i]==pos){
        //         return false;
        //     }
        // }
        // return true;
    }

};
void renderingWindow::levelTransition(int newnum){
    levelnum = newnum;
    level = readmapfile(levelmapfilepaths[levelnum]);
    subxPos = level.startx*16;
    subyPos = level.starty*16;
}

LRESULT renderingWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
        // std::cout<<uMsg<<", ";
        switch (uMsg)
        {
        case WM_CREATE:
            if (FAILED(D2D1CreateFactory(
                    D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
            {
                return -1;  // Fail CreateWindowEx.
            }
            // PostMessage(Window(),WM_USER+2,(WPARAM)(120),LPARAM(32));
            // levelmap.updatelevel(level);
            // levelmap.updatelevel(level);
            levelTransition(3);
            return 0;
        case WM_DESTROY:
            DiscardGraphicsResources();
            SafeRelease(&pFactory);
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            // std::cout <<wParam<<"\n";
            if(screenmoving==0){
            switch(wParam){
                case(0x57):
                    direction = 1;
                    moving = 1;
                    addtodirection(1);
                    return 0;
                case(0x41):
                    direction = 3;
                    moving = 1;
                    addtodirection(3);
                    return 0;
                case(0x53):
                    direction = 2;
                    moving = 1;
                    addtodirection(2);
                    return 0;
                case(0x44):
                    direction = 4;
                    moving = 1;
                    addtodirection(4);
                    return 0;
                
            }
            }
            break;
            
        case WM_KEYUP:
            // std::cout <<wParam;
            switch(wParam){
                case(0x57):
                    removefromdirection(1);
                    break;
                case(0x41):
                    removefromdirection(3);
                    break;
                case(0x53):
                    removefromdirection(2);
                    break;
                case(0x44):
                    removefromdirection(4);
                    break;
                
            }
            if(directions[0]==-1){
                moving = 0;
                movesprite = 0;
            }
            else{
                direction=directions[0];
            }
            break;
        case WM_PAINT:
            OnPaint();
            return 0;

        // Other messages not shown...
        case CHANGELEVEL:
            levelnum = (int)wParam;
            // printf("recieved");
            // std::cout<<(int)wParam;
            return 0;
        case WM_TIMER:
            {
            clock_t begin = clock();
            // if(screenmoving!=0){
            //     switch (screenmoving){
                    
            //         case(1):
            //             subyPos+=40.0/11;
            //             offset+= 0.25;
            //             break;
            //         case(2):
            //             subyPos-=40.0/11;
            //             offset -= 0.25;
            //             break;
            //         case(3):
            //             subxPos+=3.75;
            //             offset+= 0.25;
            //             break;
            //         case(4):
            //             subxPos-=3.75;
            //             offset-= 0.25;
            //             break;
            //     }
            //     if(offset ==0){screenmoving =0;subxPos=round(subxPos);subyPos=round(subyPos);}
            // }
            if(moving){
                movesprite++;
                movesprite = movesprite%4;
                switch(direction){
                    case (1):
                        subyPos-=2;
                        if(checkCollision(true,true)){subyPos+=2;}
                        // if(subyPos<=0){level-=16;screenmoving = 1;offset =-11;levelmap.updatelevel(level);}
                        break;
                    case (2):
                        subyPos+=2;
                        if(checkCollision(true)){subyPos-=2;}
                        // if(subyPos>=160){level+=16;screenmoving = 2;offset =11;levelmap.updatelevel(level);}

                        break;
                    case (3):
                        subxPos-=2;
                        while(checkCollision(false)){
                            subxPos+=1;
                        }
                        // if(subxPos<=0){level--;screenmoving = 3;offset =-16;levelmap.updatelevel(level);}

                        break;
                    case (4):
                        subxPos+=2;
                        while(checkCollision(false)){
                            subxPos-=1;
                        }
                        // if(subxPos>=240){level++;screenmoving = 4;offset =16;levelmap.updatelevel(level);}
                        break;
                }
            }
            clock_t startpaint = clock();
            OnPaint();
                        
            clock_t end = clock();
            double rendertime = (double)(end - startpaint) / CLOCKS_PER_SEC;
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

            std::cout<<"rendering: "<<rendertime<<" total: "<<time_spent<<"\n";
            // std::cout <<subxPos<<","<<subyPos<<"\n";
            // PostMessage(Window(),UPDATE,WPARAM(1),LPARAM(1));
            return 0;
            }
        case WM_SIZE:
            Resize();
            return 0;
        }
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}
    
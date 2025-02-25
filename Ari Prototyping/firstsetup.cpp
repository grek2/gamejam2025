#include <stdio.h>
#include <string>
#include <iostream>
#include <windows.h>
#include <random>
#include <array>

const char SUBMARINE  = '#';
const char TREASURE   = '!';
const char DARKOCEAN  = '8';
const char GRAYEOCEAN  = 'O';
const char LIGHTOCEAN = ' ';

const int ASCHIIA = 65;
const int ASCHIIW = 87;
const int ASCHIIS = 83;
const int ASCHIID = 68;

const int width = 10;
const int height = 10;

const int torchsize = 3;
const int playlight = 1;



void drawOcean(char ocean[height][width]){
    for(int i = 0;i<height;i++){
        std::cout << "\033[F\r";
    }
    for(int i = 0; i<height;(std::cout<<"\r\n")){
        for(int i2 = 0;i2<width;i2++){
            std::cout<<ocean[i][i2];
        }
        i++;
    }
    

}
void drawOceanLighted(char ocean[height][width],std::array<int,2> torchmap[]){
    
}

//function to place torches. override later
void torchoverride(std::array<int,2> torchmap[],int torchmaplength){
    for(int i =1;i<torchmaplength;i++){
        torchmap[i]={rand()%10,rand()%10};
    }
}
void genmap(char map[][width]){
    for(int i = 0; i<height;i++){
        for(int i2 = 0;i2<width;i2++){
            map[i][i2] = ' ';
        }
    }
    int keyx = rand()%width;
    int keyy = rand()%height;
    map[keyx][keyy] = TREASURE;
}

int main(){
    for(int i = 0; i<height;(std::cout<<"\r\n")){
        i++;
    }
    char oceanmap[height][width];
    genmap(oceanmap);
    
    drawOcean(oceanmap);


}
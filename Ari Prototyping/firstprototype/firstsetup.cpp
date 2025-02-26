#include <stdio.h>
#include <string>
#include <ctime>
#include <iostream>
// #include <windows.h>
#include <random>
#include <array>

const char SUBMARINE  = '#';
const char TREASURE   = '!';
const char DARKOCEAN  = '8';
const char GRAYEOCEAN  = '*';
const char LIGHTOCEAN = ' ';

const int ASCHIIA = 65;
const int ASCHIIW = 87;
const int ASCHIIS = 83;
const int ASCHIID = 68;

const int width = 80;
const int height = 40;

const int torchsize = 3;
const int playlight = 1;
const int TORCHCOUNT = 5;


int x = width/2;
int y = height/2;
    
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
void drawOceanLighted(char ocean[height][width],std::array<int,2> torchmap[],int numtorches){
    for(int i = 0;i<height;i++){
        std::cout << "\033[F\r";
    }
    for(int i = 0; i<height;(std::cout<<"\r\n")){
        for(int i2 = 0;i2<width;i2++){
            int light =0;
            for(int i3=0;i3<numtorches;i3++){
                int distance = (i-torchmap[i3][0])*(i-torchmap[i3][0])+(i2-torchmap[i3][1])*(i2-torchmap[i3][1]);
                if(distance< (torchsize+1)*(torchsize+1) ){ light++;}//grey
                if(distance< torchsize*torchsize){ light++;}//bright

            }
            switch(light){
                case(0):
                    std::cout<<DARKOCEAN;
                    break;
                case(1):
                    std::cout<<GRAYEOCEAN;
                    break;
                default:                
                    char c = ocean[i][i2];
                    std::cout<< c;
                    break;
            }
        }
        i++;
    }
}

//function to place torches. override later
void torchoverride(std::array<int,2> torchmap[],int torchmaplength, char ocean[height][width]){
    for(int i =0;i<torchmaplength;i++){
        std::array<int,2> torch = {/*height*/rand()%height,/*width*/rand()%width};
        while (ocean[torch[0]][torch[1]]!=' '){
            std::cout<<"failed torch";
            torch = {/*height*/rand()%height,/*width*/rand()%width};
        }
        ocean[torch[0]][torch[1]] = 'T';
        torchmap[i]=torch;
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
    srand(time(0));
    for(int i = 0; i<height;(std::cout<<"\r\n")){
        i++;
    }
    char oceanmap[height][width];
    genmap(oceanmap);
    std::array<int,2> torchmap[TORCHCOUNT];
    torchoverride(torchmap,TORCHCOUNT,oceanmap);
    
    drawOceanLighted(oceanmap,torchmap,TORCHCOUNT);

    while(true){

    }
}

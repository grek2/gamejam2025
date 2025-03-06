#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
std::vector<int> settomap(int level,int map = 1){
    std::ifstream mapreader;
    switch(map){
        case(1):
            mapreader.open("Maps\\brownStone.txt");
            break;
        case(2):
            mapreader.open("Maps\\brownStoneDown.txt");
            break;
        case(3):
            mapreader.open("Maps\\brownStoneUp.txt");
            break;
        case(4):
            mapreader.open("Maps\\brownTree.txt");
            break;
        case(5):
            mapreader.open("Maps\\brownTreeUp.txt");
            break;
        case(6):
            mapreader.open("Maps\\brownTreeDown.txt");
            break;
        case(7):
            mapreader.open("Maps\\brownBush.txt");
            break;
        case(8):
            mapreader.open("Maps\\brownRock.txt");
            break;
        case(9):
            mapreader.open("Maps\\brownDarknut.txt");
            break;
        case(10):
            mapreader.open("Maps\\brownTree1.txt");
            break;
        case(11):
            mapreader.open("Maps\\brownTree2.txt");
            break;
        case(12):
            mapreader.open("Maps\\brownTree3.txt");
            break;
        case(13):
            mapreader.open("Maps\\brownTree4.txt");
            break;
        case(14):
            mapreader.open("Maps\\greenStone.txt");
            break;
        case(15):
            mapreader.open("Maps\\greenStoneDown.txt");
            break;
        case(16):
            mapreader.open("Maps\\greenStoneUp.txt");
            break;
        case(17):
            mapreader.open("Maps\\greenTree.txt");
            break;
        case(18):
            mapreader.open("Maps\\greenTreeUp.txt");
            break;
        case(19):
            mapreader.open("Maps\\greenTreeDown.txt");
            break;
        case(20):
            mapreader.open("Maps\\greenBush.txt");
            break;
        case(21):
            // mapreader.open("Maps\\brownRock.txt");
            break;
        case(22):
            mapreader.open("Maps\\greenDarknut.txt");
            break;
        case(23):
            mapreader.open("Maps\\greenTree1.txt");
            break;
        case(24):
            mapreader.open("Maps\\greenTree2.txt");
            break;
        case(25):
            mapreader.open("Maps\\greenTree3.txt");
            break;
        case(26):
            mapreader.open("Maps\\greenTree4.txt");
            break;
        case(27):
            mapreader.open("Maps\\whiteStone.txt");
            break;
        case(28):
            mapreader.open("Maps\\whiteStoneDown.txt");
            break;
        case(29):
            mapreader.open("Maps\\whiteStoneUp.txt");
            break;
        case(30):
            mapreader.open("Maps\\whiteTree.txt");
            break;
        case(31):
            mapreader.open("Maps\\whiteTreeUp.txt");
            break;
        case(32):
            mapreader.open("Maps\\whiteTreeDown.txt");
            break;
        case(33):
            mapreader.open("Maps\\whiteBush.txt");
            break;
        case(34):
            // mapreader.open("Maps\\brownRock.txt");
            break;
        case(35):
            mapreader.open("Maps\\whiteDarknut.txt");
            break;
        case(36):
            mapreader.open("Maps\\whiteTree1.txt");
            break;
        case(37):
            mapreader.open("Maps\\whiteTree2.txt");
            break;
        case(38):
            mapreader.open("Maps\\whiteTree3.txt");
            break;
        case(39):
            mapreader.open("Maps\\whiteTree4.txt");
            break;
        case(40):
            mapreader.open("Maps\\watermap.txt");
            break;
        case(41):
            mapreader.open("Maps\\cavemap.txt");
            break;
    }
    // if(map==1){mapreader.open("Maps\\greenStoneMap.txt");}
    // if(map==2){mapreader.open("Maps\\cavemap.txt");}
    // if(map==3){mapreader.open("Maps\\greenbushmap.txt");}
    // if(map==4){mapreader.open("Maps\\watermap.txt");}
    // if(map==5){mapreader.open("Maps\\brownStonemap.txt");}
    // if(map==7){mapreader.open("Maps\\brownBushmap.txt");}
    std::string lvl;
    for(int i =0;i<level;i++){
        getline(mapreader,lvl);
    }
    std::vector<int> stones;
    int stone = 0;
    for(int i = 0; i<lvl.size();i++){
        char atpos = lvl.at(i);
        if (isdigit(atpos)){
            stone*=10;stone+=(int)atpos-(int)(*"0");
            // printf("%d\n",(int)atpos-(int)(*"0"));
        }
        else if(atpos==*(",")){
            stones.push_back(stone);
            // printf("\n%d",stone);
            stone = 0;
        }
    }
    if(stone !=0){
        stones.push_back(stone);
    }
    return stones;

}
std::vector<int> getcollidable(int level){
    std::vector<int>collidable;
    for(int i = 1;i<41;i++){
        std::vector<int> news = settomap(level,i);
        collidable.insert(collidable.end(),news.begin(),news.end());
    }
    // std::vector<int>stones=settomap(level,1);
    // // std::vector<int>bushes=settomap(level,3);
    // // std::vector<int>waters=settomap(level,4);
    // std::vector<int>collidable=stones;
    // collidable.insert(collidable.end(),bushes.begin(),bushes.end());
    // collidable.insert(collidable.end(),waters.begin(),waters.end());
    // std::cout <<collidable.size()<<"\n";
    return collidable;
}
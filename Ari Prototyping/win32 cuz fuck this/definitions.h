
#include <string>
#include <iostream>
#include <fstream>
#include <vector> 

struct Fish {
	int x;
	int y;
	int light;
};

struct Level {
	int levelnum;
	int height;
	int width;
    int startx;
    int starty;
	// std::string issolid[height];
	std::vector<std::vector<int>> sprites;
	int numfishes;
	std::vector<Fish> fishes;
};


//level lines are made up of a string of 0's or 1's to represent the existance or absence of blocks in those squares
//fish list elements are separated by ","
//fish lists must end in comma

/*File structure
 * levelnum
 * height
 * width
 * startx
 * starty
 * level_line 0
 * level_line 1
 * level_line 2
 * level_line 3
 * ...
 * level_line ${height} 
 * num_fishes
 * fishXList
 * fishYList
 * fishLightList
 */
Level readmapfile(std::string filename){
	std::ifstream levelfile(filename);
	
	std::string line; 

	getline(levelfile, line);
	int levelnum = std::stoi( line);
	
	getline(levelfile, line);
	const int height = std::stoi( line);
	getline(levelfile, line);
	const int width = std::stoi(line);
    getline(levelfile, line);
	const int startx = std::stoi( line);
	getline(levelfile, line);
	const int starty = std::stoi(line);
    getline(levelfile, line);
	const int keyy = std::stoi( line);
	getline(levelfile, line);
	const int keyx = std::stoi(line);
	//std::string issolid[height];
	std::vector<std::vector<int>> issolid(height, std::vector<int>(width, 0));
	std::vector<std::vector<int>> sprites(height, std::vector<int>(width,0));
	for(int i =0; i<height;i++){
		getline(levelfile,line);
		//issolid[i]=line;
		for(int x = 0;x<width;x++){
            // const char* str /= (const char*)(line.at(x));
			issolid[i][x] = (int)(line.at(x*2))-48;
			sprites[i][x] = (int)(line.at(x*2))-48;
		}			
	}
		

	getline(levelfile, line);
	const int numfishes =std::stoi(line);
	std::vector<int> fishx;
	std::vector<int> fishy;
	std::vector<int> fishlight;

	std::vector<Fish> fishes;



	for(int i = 0;i<numfishes;i++){
		
		getline(levelfile,line,',');
		fishx.push_back(std::stoi(line));
	}
	for(int i = 0;i<numfishes;i++){
		
		getline(levelfile,line,',');
		fishy.push_back(std::stoi(line));
	}
	for(int i = 0;i<numfishes;i++){
		
		getline(levelfile,line,',');
		fishlight.push_back(std::stoi(line));
	}
	

	for(int i = 0;i<numfishes;i++){
		Fish fish = {fishx[i],fishy[i],fishlight[i]};
     		fishes.push_back(fish);
	}


	Level level = {levelnum, height, width,startx, starty, sprites, numfishes, fishes};

	return level;
}
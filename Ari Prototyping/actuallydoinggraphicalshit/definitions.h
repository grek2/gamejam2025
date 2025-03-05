
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector.h> 

struct Fish {
	int x;
	int y;
	int light;
};

struct Level {
	int levelnum
	int height;
	int width;
	std::string issolid[height]
	int numfishes;
	std::vector<fish> fishes;
};


//level lines are made up of a string of 0's or 1's to represent the existance or absence of blocks in those squares
//fish list elements are separated by ","
//fish lists must end in comma

/*File structure
 * levelnum
 * height
 * width
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
	ifstream levelfile(filename);
	
	std::string line; 
	Level level;

	getline(levelfile, line);
	int levelnum = std::stoi( line);
	
	getline(levelfile, line);
	int height = std::stoi( line);
	getline(levelfile, line);
	int width = std::stoi(line);

	std::string issolid[height];

	for(int i =0; i<height;i++){
		getline(levelfile,line);
		issolid[i]=line;
	
	}

	int numfishes;
	int fishx[numfishes];
	int fishy[numfishes];
	int fishlight[numfishes];

	std::vector<fish> fishes;



	for(int i = 0;i<numfishes;i++){
		
		getline(levelfile,line,',');
		fishx[i]=std::stoi(line);
	}
	for(int i = 0;i<numfishes;i++){
		
		getline(levelfile,line,',');
		fishy[i]=std::stoi(line);
	}
	for(int i = 0;i<numfishes;i++){
		
		getline(levelfile,line,',');
		fishlight[i]=std::stoi(line);
	}
	

	for(int i = 0;i<numfishes;i++){
		Fish fish = new fish{fishx[i],fishy[i],fishlight[i]};
     		fishes.add(fish);
	}


	level = {levelnum, height, width, issolid, numfishes, fishes};

	return level;

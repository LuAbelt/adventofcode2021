//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <array>

using namespace std;

using Grid = vector<vector<int>>;

struct Dir {
  int x;
  int y;
};

struct OpenNode {
  size_t cost;
  size_t x;
  size_t y;
};

void part1(){
    std::string line;
	getline(std::cin, line);
	Grid map = Grid(line.length(),vector<int>(line.length()));

	int gridSize = line.length();

	for (int y =0;y<line.length();++y) {
		map[0][y]=line[y]-'0';
	}

	int x = 1;
    while(getline(std::cin, line) && !line.empty()){
        // Read input
		for (int y =0;y<line.length();++y) {
	    	map[x][y]=line[y]-'0';
	    }
		++x;
    }

    for (const auto& line: map) {
        for (auto val:line) {
            cout << val;
        }
        cout << endl;
    }



	set<std::array<int,3>> open;

	vector<vector<bool>> closed(gridSize,vector<bool>(gridSize,false));
	vector<vector<size_t>> cost(gridSize,vector<size_t>(gridSize,std::numeric_limits<size_t>::max()));

	open.insert({0,0,0});

	vector<Dir> directions = {{-1,0},{0,1},{1,0},{0,-1}};

	while (!open.empty()){
		auto node = *open.begin();
		open.erase(open.begin());

		closed[node[1]][node[2]]=true;

		//cout << "Expanding " << node.x << "," << node.y << " with cost "<<node.cost<<endl;
		// Goal test
		if((node[1] == gridSize-1) &&(node[2] == gridSize-1)){
			cout << node[0] << endl;
			break;
		}

		for (const auto& dir:directions) {
			auto newX = node[1]+dir.x;
			auto newY = node[2]+dir.y;
			if((newX<0) || (newX>=gridSize) || (newY<0) || (newY>=gridSize)){
				continue;
			}
			auto newCost = node[0]+map[newX][newY];

			if(closed[newX][newY] || newCost > cost[newX][newY]){
				continue;
			}
			//cout << "Adding " <<newX<<","<<newY<< " with cost "<<node.first+map[newX][newY] << endl;
			open.insert({newCost,newX,newY});
		}
	}
}

void part2(){
	std::string line;
	getline(std::cin, line);
	Grid map = Grid(line.length()*5,vector<int>(line.length()*5));

	int gridSize = line.length();

	for (int y =0;y<line.length();++y) {
        int baseVal = line[y]-'0';
        for(int mapX=0;mapX<5;++mapX) {
            for (int mapY = 0; mapY < 5; ++mapY) {
                int val = baseVal+mapX+mapY;
                if(val>9){
                    val-=9;
                }
                map[mapX*gridSize][mapY*gridSize+y]=val;
            }
        }
	}

	int x = 1;
	while(getline(std::cin, line) && !line.empty()){
		// Read input
		for (int y =0;y<line.length();++y) {
			int baseVal = line[y]-'0';
            for(int mapX=0;mapX<5;++mapX) {
                for (int mapY = 0; mapY < 5; ++mapY) {
                    int val = baseVal+mapX+mapY;
                    if(val>9){
                        val-=9;
                    }
                    map[mapX*gridSize+x][mapY*gridSize+y]=val;
                }
            }
		}
		++x;
	}

    for (const auto& line: map) {
        for (auto val:line) {
            cout << val;
        }
        cout << endl;
    }

	set<std::array<int,3>> open;

	vector<vector<bool>> closed(gridSize*5,vector<bool>(gridSize*5,false));
	vector<vector<size_t>> cost(gridSize*5,vector<size_t>(gridSize*5,std::numeric_limits<size_t>::max()));

	open.insert({0,0,0});

	vector<Dir> directions = {{-1,0},{0,1},{1,0},{0,-1}};

	while (!open.empty()){
		auto node = *open.begin();
		open.erase(open.begin());

		closed[node[1]][node[2]]=true;

		//cout << "Expanding " << node.x << "," << node.y << " with cost "<<node.cost<<endl;
		// Goal test
		if((node[1] == gridSize*5-1) &&(node[2] == gridSize*5-1)){
			cout << node[0] << endl;
			break;
		}

		for (const auto& dir:directions) {
			auto newX = node[1]+dir.x;
			auto newY = node[2]+dir.y;
			if((newX<0) || (newX>=gridSize*5) || (newY<0) || (newY>=gridSize*5)){
				continue;
			}
			auto newCost = node[0]+map[newX][newY];

			if(closed[newX][newY] || newCost > cost[newX][newY]){
				continue;
			}
			//cout << "Adding " <<newX<<","<<newY<< " with cost "<<node.first+map[newX][newY] << endl;
			open.insert({newCost,newX,newY});
		}
	}
}

int main(int argc, char* argv[]){
  if(std::string(argv[1])=="--one"){
    part1();
  } else if(std::string(argv[1])=="--two"){
    part2();
  } else {
    std::cout << "Wrong usage. Allowed arguments: '--one' or '--two'";
  }
}


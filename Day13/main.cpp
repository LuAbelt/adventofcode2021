//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>

using namespace std;

using Grid = vector<vector<bool>>;

void printGrid(Grid g, int maxX,int maxY){
	for(int y = 0; y<maxY;++y){
		for (int x = 0; x < maxX; ++x) {
			cout << (g[x][y]?"#":".");
		}
		cout << endl;
	}
}

int count(Grid & g,int maxX, int maxY){
	int res = 0;
	for (int x = 0; x < maxX; ++x) {
		for (int y = 0; y < maxY; ++y) {
			if(g[x][y]){
				++res;
			}
		}
	}

	return res;
}

Grid parseGrid(){
	string line;
	int maxX = 0;
	int maxY = 0;
	vector<pair<int,int>> marks;
	while(getline(cin,line) && !line.empty()){
		auto p = line.find(",");
		int x = stoi(line.substr(0,p));
		int y = stoi(line.substr(p+1));
		marks.push_back(std::make_pair(x,y));
		maxX = max(maxX,x);
		maxY = max(maxY,y);
	}

	Grid res(maxX+1,vector<bool>(maxY+1,false));

	for (const auto& mark: marks) {
		res[mark.first][mark.second] = true;
	}

	return res;
}

void foldGrid(Grid &grid, char axis, int pos, int maxX, int maxY){
	if(axis=='y') {
		int diff = maxY - pos;
		for(int cur = 1;cur<diff;++cur){
			for (int x = 0; x < maxX; ++x) {
				grid[x][pos-cur] = grid[x][pos-cur]|grid[x][pos+cur];
			}
		}
	} else if (axis=='x') {
		int diff = maxX - pos;

		for(int cur = 1;cur<diff;++cur){
			for (int y = 0; y < maxY; ++y) {
				grid[pos-cur][y] = grid[pos-cur][y]|grid[pos+cur][y];
			}
		}
	}
}

std::vector<pair<char,int>> parseFoldInstructions(){
	std::vector<pair<char,int>> res;
	string line;
	while(getline(cin,line) && !line.empty()){
		auto p = line.find("=");
		char axis = line[p-1];
		int pos = stoi(line.substr(p+1));
		res.push_back(std::make_pair(axis,pos));
	}

	for (auto &p: res) {
		cout << p.first << "," << p.second << endl;
	}
	return res;
}

void part1(){
    auto grid = parseGrid();
	int maxX = grid.size();
	int maxY = grid[0].size();
	printGrid(grid,maxX,maxY);
	auto instr = parseFoldInstructions();

	auto firstFold = instr[0];

	foldGrid(grid,firstFold.first,firstFold.second,maxX,maxY);
	if(firstFold.first=='x'){
		maxX = firstFold.second;
	}else{
		maxY = firstFold.second;
	}
	printGrid(grid,maxX,maxY);

	cout << count(grid,maxX,maxY)<<endl;
}

void part2(){
	auto grid = parseGrid();
	int maxX = grid.size();
	int maxY = grid[0].size();
	printGrid(grid,maxX,maxY);
	auto instr = parseFoldInstructions();


	for (const auto& instruction: instr){
		foldGrid(grid,instruction.first,instruction.second,maxX,maxY);
		if(instruction.first=='x'){
			maxX = instruction.second;
		}else{
			maxY = instruction.second;
		}
	}
	printGrid(grid,maxX,maxY);

	cout << count(grid,maxX,maxY)<<endl;
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


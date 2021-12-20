//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <numeric>

using namespace std;

using Image = vector<vector<bool>>;
using Code = array<bool,512>;

Code parseCode(){
    string line;
    getline(cin,line);
    assert(line.length()==512);

    Code result = Code{false};

    for (int i = 0; i < 512; ++i) {
        result[i] = (line[i] == '#');
    }
    return result;
}

Image parseImage(int padding = 1){
    string line;
    getline(cin,line);
    if(line.empty()){
        getline(cin,line);
    }

    auto imageSize = line.length();
    Image Result(line.length()+2*padding,vector<bool>(line.length()+2*padding,false));

    for (int y = 0; y < line.length(); ++y) {
        Result[padding][y+padding] = line[y]=='#';
    }

    for (int x = 1; x < imageSize; ++x) {
        getline(cin,line);
        assert(line.length()==imageSize);
        for (int y = 0; y < imageSize; ++y) {
            Result[x+padding][y+padding] = line[y]=='#';
        }
    }

    return Result;
}

void printImage(Image &Img){
    for (const auto &line: Img) {
        for(const auto pixel : line){
            cout << (pixel?'#':'.');
        }
        cout << endl;
    }
}

bool inBounds(int x, int y, const Image &Input){
    return x>=0 && y>=0 && x<Input.size() && y<Input.size();
}

Image enhanceImage(const Image &Input, const Code& Algorithm){
    Image Result(Input.size(),vector<bool>(Input.size()));

    for (int64_t x = 1; x < Input.size()-1; ++x) {
        for (int64_t y = 1; y < Input.size()-1; ++y) {

            int codeIdx = 0;
            for (auto &xOff:{-1,0,1}) {
                for (auto& yOff : {-1,0,1}){
                    codeIdx*=2;
                    if(inBounds(x+xOff,y+yOff,Input) && Input[x+xOff][y+yOff]){
                        codeIdx++;
                    }
                }
            }
            Result[x][y] = Algorithm[codeIdx];
        }
    }

    //Fix Borders
    bool borderVal = Result[1][1];
    for (int y = 0; y < Result.size(); ++y) {
        Result[0][y]=borderVal;
        Result[y][0]=borderVal;
        Result[Result.size()-1][y]=borderVal;
        Result[y][Result.size()-1]=borderVal;

    }

    return Result;
}

void part1(){
    Code EnhancementAlgo = parseCode();
    Image Img = parseImage(10);

    printImage(Img);

    Img = enhanceImage(Img,EnhancementAlgo);
    cout << endl;
    printImage(Img);

    Img = enhanceImage(Img,EnhancementAlgo);
    cout << endl;
    printImage(Img);

    uint64_t res = 0;
    for (int x = 1; x < Img.size()-1; ++x) {
        for (int y = 1; y < Img.size()-1; ++y) {
            if(Img[x][y]){
                res++;
            }
        }
    }
    cout << res << endl;
}

void part2(){

    Code EnhancementAlgo = parseCode();
    Image Img = parseImage(60);

    printImage(Img);

    for (int i = 0; i < 50; ++i) {
        Img = enhanceImage(Img,EnhancementAlgo);
        //printImage(Img);
        cout << "Finished Iteration " << i << endl;
    }

    uint64_t res = 0;
    for (int x = 1; x < Img.size()-1; ++x) {
        for (int y = 1; y < Img.size()-1; ++y) {
            if(Img[x][y]){
                res++;
            }
        }
    }
    cout << res << endl;
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


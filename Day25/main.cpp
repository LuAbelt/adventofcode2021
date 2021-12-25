//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <iterator>

using namespace std;

struct Position{
    int x;
    int y;
};

bool operator==(Position const & Left, Position const & Right){
    return (Left.x == Right.x) && (Left.y==Right.y);
}

struct SeaCucumber{
    Position Pos;
    Position Direction;

    char charRepr() const{
        if(Direction==Position{1,0}){
            return '>';
        }
        if(Direction==Position{0,1}){
            return 'v';
        }
        return 'x';
    }
};

// custom specialization of std::hash can be injected in namespace std
template<>
struct std::hash<Position>
{
    std::size_t operator()(Position const& pos) const noexcept
    {
        uint64_t combined = (((uint64_t)pos.x)<<32)|((uint64_t)pos.y);
        return std::hash<uint64_t>{}(combined); // or use boost::hash_combine
    }
};

class SeaFloor{
    int _width;
    int _height;
    list<SeaCucumber> _cucumbers;
    unordered_set<Position> _occupied;

    Position getNext(SeaCucumber const & cucumber) const{
        return Position{(cucumber.Pos.x+cucumber.Direction.x)%_width,
                        (cucumber.Pos.y+cucumber.Direction.y)%_height};
    }
public:
    SeaFloor(int width, int height,list<SeaCucumber> cucumbers)
    :_width(width)
    ,_height(height)
    ,_cucumbers(cucumbers)
    {
        for(const auto& cucumber : cucumbers){
            _occupied.emplace(cucumber.Pos);
        }
    }

    void print() const{
        vector<string> output(_height,string(_width,'.'));

        for (const auto& cucumber : _cucumbers) {
            output[cucumber.Pos.y][cucumber.Pos.x] = cucumber.charRepr();
        }

        copy(output.begin(),output.end()
             ,ostream_iterator<string>(cout, "\n"));
    }

    bool step() {
        bool moved = false;
        auto curCucumber = _cucumbers.begin();
        unordered_set<Position> toAdd;
        unordered_set<Position> toRemove;

        while ((curCucumber!=_cucumbers.end())&&curCucumber->Direction==Position{1,0}){
            auto nextPos = getNext(*curCucumber);
            auto itr = _occupied.find(nextPos);
            if(itr==_occupied.end()){
                toAdd.emplace(nextPos);
                toRemove.emplace(curCucumber->Pos);
                curCucumber->Pos = nextPos;
                moved = true;
            }
            ++curCucumber;
        }
        for (const auto &p:toRemove) {
            _occupied.erase(p);
        }

        for(const auto& p : toAdd){
            _occupied.emplace(p);
        }

        toAdd.clear();
        toRemove.clear();

        while (curCucumber!=_cucumbers.end()){
            auto nextPos = getNext(*curCucumber);
            auto itr = _occupied.find(nextPos);
            if(itr==_occupied.end()){
                toAdd.emplace(nextPos);
                toRemove.emplace(curCucumber->Pos);
                curCucumber->Pos = nextPos;
                moved = true;
            }
            ++curCucumber;
        }
        for (const auto &p:toRemove) {
            _occupied.erase(p);
        }

        for(const auto& p : toAdd){
            _occupied.emplace(p);
        }

        toAdd.clear();
        toRemove.clear();

        return moved;
    }
};

void part1(){
    std::string line;

    list<SeaCucumber> cucs;
    int height;
    int width = 0;
    for (height = 0; getline(cin,line)&&!line.empty(); ++height) {
        width = line.length();
        for(int x = 0;x<line.length();++x){
            Position pos{x,height};
            Position dir{0,0};
            switch (line[x]) {
                case 'v':
                    dir = {0,1};
                    cucs.push_back(SeaCucumber{pos,dir});
                    break;
                case '>':
                    dir = {1,0};
                    cucs.push_front(SeaCucumber{pos,dir});
                    break;
                case '.':
                    continue;
            }
        }
    }

    SeaFloor floor(width,height,cucs);

    floor.print();
    cout << endl<<endl;
    int numSteps = 0;
    while (floor.step()){
        ++numSteps;
    }
    floor.print();
    cout << numSteps << endl;
}

void part2(){
  std::string line;

  while((std::cin >> line) && !line.empty()) {
      // Read input
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


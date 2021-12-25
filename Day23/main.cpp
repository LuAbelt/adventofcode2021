//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <cassert>

using namespace std;

struct Pos{
    int x;
    int y;
};

bool operator<(const Pos &Left, const Pos &Right){
    if(Left.x==Right.x){
        return Left.y<Right.y;
    }
    return Left.x<Right.x;
}

bool operator==(const Pos &Left, const Pos &Right){
    return Left.x==Right.x && Left.y==Right.y;
}

class State{
public:
    using PositionType = Pos;
    using LabelType = char;
    using MoveType = pair<PositionType,PositionType>;
    using MapType = map<PositionType, LabelType>;
    using MapValueType = MapType::value_type;
private:
    MapType _currentStates;

    mutable map<char,size_t> CostsPerStep = {{'A',1},
                                     {'B',10},
                                     {'C',100},
                                     {'D',1000}};

    [[nodiscard]] bool isApplicable(const MoveType &Move) const{
        if(empty(Move.first)){
            //Empty spaces cannot move
            return false;
        }

        if(!empty(Move.second)){
            // We can only move to empty spaces
            return false;
        }

        if(isInFinalPosition(Move.first)){
            return false;
        }
        if(Move.second.y==0 && (Move.second.x==2 || Move.second.x==4 ||Move.second.x==6 ||Move.second.x==8)){
            //We cannot block entries
            return false;
        }



        if(Move.first.y>0){
            if(Move.second.y!=0){
                return false;
            }
            int curX = Move.first.x;
            int curY = Move.first.y-1;
            while(curY>=0){
                if(!empty({curX,curY})){
                    return false;
                }
                --curY;
            }

            int inc = curX < Move.second.x?1:-1;
            curY=0;
            while (curX!=Move.second.x+inc){
                if(!empty({curX,curY})){
                    return false;
                }
                curX+=inc;
            }
        }else{
            if(Move.second.y==0){
                return false;
            }

            LabelType nodeLabel = at(Move.first);
            int supposedX = 2+(nodeLabel-'A')*2;
            if(supposedX!=Move.second.x){
                return false;
            }

            for(int y=Move.second.y+1;y<=(_currentStates.size() % 4);++y){
                if(at({supposedX,y})!=nodeLabel){
                    return false;
                }
            }

            int curX = Move.first.x;
            int curY = Move.first.y;
            int inc = curX < Move.second.x?1:-1;

            curX+=inc;

            while (curX!=Move.second.x+inc){
                if(!empty({curX,curY})){
                    return false;
                }
                curX+=inc;
            }
            curX=Move.second.x;
            while(curY<=Move.second.y){
                if(!empty({curX,curY})){
                    return false;
                }
                ++curY;
            }
        }
        return true;
    }

    [[nodiscard]] bool isInFinalPosition(const PositionType &Pos) const{
        if(empty(Pos)||Pos.y==0){
            // In practice, empty labels should not be passed to this
            // If we are at y-0 we cannot be in the correct pocket
            return false;
        }

        LabelType nodeLabel = at(Pos);
        int supposedX = 2+(nodeLabel-'A')*2;
        if(supposedX!=Pos.x){
            return false;
        }

        for(int y=Pos.y+1;y<=(_currentStates.size() / 4);++y){
            if(at({Pos.x,y})!=nodeLabel){
                return false;
            }
        }
        return true;
    }

public:
    bool operator<(const State &Other) const{
        return _currentStates<Other._currentStates;
    }

    bool operator==(const State &Other) const{
        return _currentStates==Other._currentStates;
    }

    explicit State(const vector<MapValueType>& initialState){
        for (const auto& entry : initialState) {
            _currentStates.emplace(entry);
        }
    }

    explicit State(MapType initialState)
    :_currentStates(std::move(initialState))
    {}

    [[nodiscard]] bool empty(const PositionType &Pos) const{
        return _currentStates.find(Pos)==_currentStates.end();
    }

    [[nodiscard]] LabelType at(const PositionType &Pos) const{
        if(empty(Pos)){
            return '.';
        }

        return _currentStates.find(Pos)->second;
    }

    [[nodiscard]] size_t costs(const MoveType &Move) const{
        if(!isApplicable(Move)){
            return -1;
        }

        auto costPerStep = CostsPerStep[at(Move.first)];

        return abs(Move.first.x-Move.second.x)*costPerStep + abs(Move.first.y-Move.second.y)*costPerStep;
    }

    bool applyMove(const MoveType& Move){
        if(!isApplicable(Move)){
            return false;
        }

        auto nodeLabel = at(Move.first);
        _currentStates.erase(Move.first);
        _currentStates.emplace(Move.second,nodeLabel);
        return true;
    }

    [[nodiscard]] vector<MoveType> applicableMoves() const{
        if(isGoalState()){
            // Nothing to be done
            return {};
        }

        vector<MoveType> applicableMoves;

        for (const auto &Node:_currentStates) {
            if(isInFinalPosition(Node.first)){
                continue;
            }

            //Distinguish two cases:
            if(Node.first.y>0){
                //Node is in initial position and moves to hallway
                for(int x=0;x<11;++x){
                    MoveType Move{Node.first,{x,0}};
                    if(isApplicable(Move)){
                        applicableMoves.emplace_back(Move);
                    }
                }
            }else{
                //Node is in hallway and needs to move to final position
                auto nodeLabel = at(Node.first);
                int supposedX = 2+(nodeLabel-'A')*2;

                for (int y = (_currentStates.size()/4); y >0 ; --y) {
                    if(empty({supposedX,y})){
                        MoveType Move{Node.first,{supposedX,y}};
                        if(isApplicable(Move)){
                            applicableMoves.emplace_back(Move);
                            // Done, only one possible moves
                            break;
                        }
                    }
                    if(!isInFinalPosition({supposedX,y})){
                        //If one in this column is not in its final position, there are no moves to add for this
                        break;
                    }
                }
            }
        }

        return applicableMoves;
    }

    [[nodiscard]] bool isGoalState() const{
        return std::all_of(_currentStates.begin(), _currentStates.end(),[this](const auto& Node){
           return isInFinalPosition(Node.first);
        });
    }

    void print() const{
        vector<string> output = {"#...........#"};
        output.emplace_back("###.#.#.#.###");
        for (int i = 1; i < (_currentStates.size() / 4); ++i) {
            output.emplace_back("  #.#.#.#.#  ");
        }

        for (const auto& entry:_currentStates) {
            output[entry.first.y][entry.first.x+1] = entry.second;
        }

        cout << "#############" << endl;

        std::copy(output.begin(),
                  output.end(),
                  ostream_iterator<string>(cout, "\n"));


        cout << "  #########  " << endl;
    }
};

class Solver{
public:
    using Path = vector<State::MoveType>;
private:
    State _initialState;
    Path _solutionPath;
    size_t _cost = -1;
    bool _isSolvable = false;
public:
    explicit Solver(State InitialState)
    : _initialState(std::move(InitialState)){}

    [[nodiscard]] bool solve(){

        multimap<size_t,pair<State,Path>> open;
        set<State> closed;
        map<State,size_t> openCosts;

        open.emplace(0, pair<State,Path>(_initialState, {}));

        while (!open.empty()){
            auto current= *open.begin();
            open.erase(open.begin());

            closed.emplace(current.second.first);
            openCosts.erase(current.second.first);

            if(current.second.first.isGoalState()){
                _isSolvable = true;
                _solutionPath = current.second.second;
                _cost = current.first;
                return true;
            }

            auto actions = current.second.first.applicableMoves();
            auto curCost = current.first;
            for (const auto& action : actions) {
                auto curPath = current.second.second;
                State currentState = current.second.first;

                auto newCost = curCost + currentState.costs(action);
                auto res = currentState.applyMove(action);
                assert(res);

                if(closed.find(currentState)!=closed.end()){
                    continue;
                }

                if(openCosts.find(currentState)!=openCosts.end()){
                    if(openCosts[currentState]<newCost){
                        continue;
                    }else{
                        for(auto itr = open.begin();itr!=open.end();++itr){
                            if(itr->second.first==currentState){
                                open.erase(itr);
                                break;
                            }
                        }
                    }
                }

                openCosts[currentState] = newCost;
                curPath.emplace_back(action);

                open.emplace(make_pair(newCost, pair<State,Path>(currentState, curPath)));
            }
        }

        _isSolvable = false;
        _solutionPath = {};
        _cost = -1;
        return false;
    }

    [[nodiscard]] Path getSolutionPath() const{
        return _solutionPath;
    }

    [[nodiscard]] size_t cost() const{
        return _cost;
    }

    [[nodiscard]] bool solvable() const{
        return _isSolvable;
    }
};

void part1(){
    string line;
    getline(cin,line);
    vector<State::MapValueType> states;
    for (int pos = 0; pos < line.length(); ++pos) {
        int x = 2+2*((pos%4));
        int y = (pos/4)+1;
        states.emplace_back(Pos{x,y},line[pos]);
    }

    State s(states);

    s.print();

    Solver solver{s};



    if(solver.solve()){
        cout << "State solvable" <<endl;
        cout << "Costs: " << solver.cost() << endl;

        auto moves = solver.getSolutionPath();
        for (const auto& m:moves) {
            auto res = s.applyMove(m);
            assert(res);
            s.print();
            cout << endl;
        }
    }
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


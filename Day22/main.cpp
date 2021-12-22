//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Coord{
    int64_t _x;
    int64_t _y;
    int64_t _z;
public:
    Coord(int64_t x, int64_t y, int64_t z)
            :_x(x),_y(y),_z(z){}

    [[nodiscard]] int64_t x() const{
        return _x;
    }

    [[nodiscard]] int64_t y() const{
        return _y;
    }

    [[nodiscard]] int64_t z() const{
        return _z;
    }

    [[nodiscard]] uint64_t manhattanLength() const{
        return abs(_x)+abs(_y)+ abs(_z);
    }

    bool operator==(Coord const & Other) const{
        return _x==Other._x && _y==Other._y&&_z==Other._z;
    }
    bool operator<(Coord const & Other) const{
        return _x<Other._x && _y<Other._y && _z<Other._z;
    }

    bool operator<=(Coord const &Other) const{
        return _x<=Other._x && _y<=Other._y&&_z<=Other._z;;
    }

    bool operator>(Coord const &Other) const{
        return _x>Other._x && _y>Other._y&&_z>Other._z;;
    }

    bool operator>=(Coord const &Other) const{
        return _x>=Other._x && _y>=Other._y&&_z>=Other._z;;
    }

    Coord & operator+=(Coord const & Other) {
        _x += Other._x;
        _y += Other._y;
        _z += Other._z;
        return *this;
    }

    Coord operator+(Coord const & Other) const{
        Coord result = *this;
        result+=Other;
        return result;
    }

    Coord & operator-=(Coord const & Other) {
        _x -= Other._x;
        _y -= Other._y;
        _z -= Other._z;
        return *this;
    }

    Coord operator-(Coord const & Other) const{
        Coord result = *this;
        result-=Other;
        return result;
    }
};

class BoundingBox{
    Coord _min;
    Coord _max;
public:
    BoundingBox(Coord min, Coord max)
    : _min(min),
      _max(max)
    {assert(min<=max);}

    [[nodiscard]] bool intersects(const BoundingBox &Other) const {
        return !(Other._min.x()>_max.x()
                ||Other._max.x()<_min.x()
                ||Other._max.y()<_min.y()
                ||Other._min.y()>_max.y()
                ||Other._max.z()<_min.z()
                ||Other._min.z()>_max.z()
                );
    }

    [[nodiscard]] BoundingBox intersection(const BoundingBox &Other) const{
        Coord intMin={::max(_min.x(),Other._min.x())
                   ,::max(_min.y(),Other._min.y())
                   ,::max(_min.z(),Other._min.z())};

        Coord intMax={::min(_max.x(),Other._max.x()),
                      ::min(_max.y(),Other._max.y()),
                      ::min(_max.z(),Other._max.z())};

        return {intMin,intMax};
    }

    [[nodiscard]] uint64_t volume() const{
        return (abs(_max.x()-_min.x())+1)*(abs(_max.y()-_min.y())+1)*(abs(_max.z()-_min.z())+1);
    }
    
    [[nodiscard]] vector<BoundingBox> dissect(const BoundingBox &Other) const{
        assert(Other._min>=_min);
        assert(Other._max<=_max);
        vector<BoundingBox> Result;
        
        // 1
        Coord min = Coord{_min.x(),_min.y(),Other._min.z()};
        Coord max = Coord{Other._min.x()-1,Other._min.y()-1,Other._max.z()};
        if(min<=max){
            Result.emplace_back(min,max);
        }
        
        // 2
        min = Coord{Other._min.x(),_min.y(),Other._min.z()};
        max = Coord{Other._max.x(),Other._min.y()-1,Other._max.z()};
        
        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 3
        min = Coord{Other._max.x()+1,_min.y(),Other._min.z()};
        max = Coord{_max.x(),Other._min.y()-1,Other._max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 4
        min = Coord{_min.x(),Other._min.y(),Other._min.z()};
        max = Coord{Other._min.x()-1,Other._max.y(),Other._max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 5
        min = Coord{Other._max.x()+1,Other._min.y(),Other._min.z()};
        max = Coord{_max.x(),Other._max.y(),Other._max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 6
        min = Coord{_min.x(),Other._max.y()+1,Other._min.z()};
        max = Coord{Other._min.x()-1,_max.y(),Other._max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 7
        min = Coord{Other._min.x(),Other._max.y()+1,Other._min.z()};
        max = Coord{Other._max.x(),_max.y(),Other._max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 8
        min = Coord{Other._max.x()+1,Other._max.y()+1,Other._min.z()};
        max = Coord{_max.x(),_max.y(),Other._max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 1
        min = Coord{_min.x(),_min.y(),_min.z()};
        max = Coord{Other._min.x()-1,Other._min.y()-1,Other._min.z()-1};
        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 2
        min = Coord{Other._min.x(),_min.y(),_min.z()};
        max = Coord{Other._max.x(),Other._min.y()-1,Other._min.z()-1};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 3
        min = Coord{Other._max.x()+1,_min.y(),_min.z()};
        max = Coord{_max.x(),Other._min.y()-1,Other._min.z()-1};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 4
        min = Coord{_min.x(),Other._min.y(),_min.z()};
        max = Coord{Other._min.x()-1,Other._max.y(),Other._min.z()-1};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // Middle
        min = Coord{Other._min.x(),Other._min.y(),_min.z()};
        max = Coord{Other._max.x(),Other._max.y(),Other._min.z()-1};

        if(min<=max){
            Result.emplace_back(min,max);
        }
        
        // 5
        min = Coord{Other._max.x()+1,Other._min.y(),_min.z()};
        max = Coord{_max.x(),Other._max.y(),Other._min.z()-1};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 6
        min = Coord{_min.x(),Other._max.y()+1,_min.z()};
        max = Coord{Other._min.x()-1,_max.y(),Other._min.z()-1};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 7
        min = Coord{Other._min.x(),Other._max.y()+1,_min.z()};
        max = Coord{Other._max.x(),_max.y(),Other._min.z()-1};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 8
        min = Coord{Other._max.x()+1,Other._max.y()+1,_min.z()};
        max = Coord{_max.x(),_max.y(),Other._min.z()-1};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 1
        min = Coord{_min.x(),_min.y(),Other._max.z()+1};
        max = Coord{Other._min.x()-1,Other._min.y()-1,_max.z()};
        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 2
        min = Coord{Other._min.x(),_min.y(),Other._max.z()+1};
        max = Coord{Other._max.x(),Other._min.y()-1,_max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 3
        min = Coord{Other._max.x()+1,_min.y(),Other._max.z()+1};
        max = Coord{_max.x(),Other._min.y()-1,_max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 4
        min = Coord{_min.x(),Other._min.y(),Other._max.z()+1};
        max = Coord{Other._min.x()-1,Other._max.y(),_max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // Middle
        min = Coord{Other._min.x(),Other._min.y(),Other._max.z()+1};
        max = Coord{Other._max.x(),Other._max.y(),_max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 5
        min = Coord{Other._max.x()+1,Other._min.y(),Other._max.z()+1};
        max = Coord{_max.x(),Other._max.y(),_max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 6
        min = Coord{_min.x(),Other._max.y()+1,Other._max.z()+1};
        max = Coord{Other._min.x()-1,_max.y(),_max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 7
        min = Coord{Other._min.x(),Other._max.y()+1,Other._max.z()+1};
        max = Coord{Other._max.x(),_max.y(),_max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }

        // 8
        min = Coord{Other._max.x()+1,Other._max.y()+1,Other._max.z()+1};
        max = Coord{_max.x(),_max.y(),_max.z()};

        if(min<=max){
            Result.emplace_back(min,max);
        }
        
        return Result;
    }

    [[nodiscard]] Coord min() const{
        return _min;
    }

    [[nodiscard]] Coord max() const{
        return _max;
    }
};

BoundingBox parseLine(const string& line, bool &on){
    on = line.starts_with("on");

    size_t xStart = line.find("x=")+2;
    size_t yStart = line.find("y=")+2;
    size_t zStart = line.find("z=")+2;
    int64_t minX = stoi(line.substr(xStart,line.find("..")-xStart));
    int64_t maxX = stoi(line.substr(line.find("..")+2,line.find(',')-line.find("..")-2));
    int64_t minY = stoi(line.substr(yStart,line.find("..",yStart)-yStart));
    int64_t maxY = stoi(line.substr(line.find("..",yStart)+2,line.find(',',yStart)-line.find("..",yStart)-2));
    int64_t minZ = stoi(line.substr(zStart,line.find("..",zStart)-zStart));
    int64_t maxZ = stoi(line.substr(line.find("..",zStart)+2,line.find(',',zStart)-line.find("..",zStart)-2));

    assert(minX<=maxX);
    assert(minY<=maxY);
    assert(minZ<=maxZ);

    return BoundingBox{{minX,minY,minZ},{maxX,maxY,maxZ}};
}

ostream& operator<<(ostream& os, const Coord& c)
{
    os << "(" << c.x()<<"|"<<c.y()<<"|"<<c.z()<<")";
    return os;
}

ostream& operator<<(ostream& os, const BoundingBox& bb)
{
    os << bb.min() << "-" << bb.max() << " (Volume: "<<bb.volume() << ")";
    return os;
}



void part1(){
    string line;
    std::vector<BoundingBox> turnedOnLights;

    while (getline(cin,line)&&!line.empty()){
        cout << line<<endl;
        bool on = false;
        auto currentBox = parseLine(line,on);
        //18719358303783
        BoundingBox bounds{{-50,-50,-50},{50,50,50}};

        if(!bounds.intersects(currentBox)){
            continue;
        }

        if(on){
            std::vector<BoundingBox> lightsToTurnOn{currentBox};
            for (const auto turnedOnLight:turnedOnLights) {

                vector<BoundingBox> newLightsToTurnOn;

                for (const auto& lightToTurnOn:lightsToTurnOn) {
                    if(turnedOnLight.intersects(lightToTurnOn)){
                        auto intersection = lightToTurnOn.intersection(turnedOnLight);
                        auto dissection = lightToTurnOn.dissect(intersection);
                        newLightsToTurnOn.insert(newLightsToTurnOn.end()
                                                 ,dissection.begin()
                                                 ,dissection.end());
                    }else{
                        newLightsToTurnOn.emplace_back(lightToTurnOn);
                    }
                }
                lightsToTurnOn = newLightsToTurnOn;
            }

            turnedOnLights.insert(turnedOnLights.end()
                                  ,lightsToTurnOn.begin()
                                  , lightsToTurnOn.end());
        }else{
            vector<BoundingBox> newTurnedOnLights;
            for (const auto turnedOnLight:turnedOnLights) {
                if(turnedOnLight.intersects(currentBox)){
                    auto intersection = turnedOnLight.intersection(currentBox);
                    auto dissection = turnedOnLight.dissect(intersection);

                    newTurnedOnLights.insert(newTurnedOnLights.end(),
                                             dissection.begin(),
                                             dissection.end());
                }else{
                    newTurnedOnLights.emplace_back(turnedOnLight);
                }
            }

            turnedOnLights = newTurnedOnLights;
        }


        /*uint64_t totalVol = 0;
        for (const auto& light:turnedOnLights) {
            cout << light << endl;
            totalVol+=light.volume();
        }
        cout << totalVol << endl << endl;*/
    }

    uint64_t totalVol = 0;
    for (const auto& light:turnedOnLights) {
        //cout << light << endl;
        totalVol+=light.volume();
    }

    cout << totalVol << endl;
}

void part2(){
    string line;
    std::vector<BoundingBox> turnedOnLights;

    while (getline(cin,line)&&!line.empty()){
        cout << line<<endl;
        bool on = false;
        auto currentBox = parseLine(line,on);
        //18719358303783
        /*BoundingBox bounds{{-50,-50,-50},{50,50,50}};

        if(!bounds.intersects(currentBox)){
            continue;
        }
*/
        if(on){
            std::vector<BoundingBox> lightsToTurnOn{currentBox};
            for (const auto turnedOnLight:turnedOnLights) {

                vector<BoundingBox> newLightsToTurnOn;

                for (const auto& lightToTurnOn:lightsToTurnOn) {
                    if(turnedOnLight.intersects(lightToTurnOn)){
                        auto intersection = lightToTurnOn.intersection(turnedOnLight);
                        auto dissection = lightToTurnOn.dissect(intersection);
                        newLightsToTurnOn.insert(newLightsToTurnOn.end()
                                ,dissection.begin()
                                ,dissection.end());
                    }else{
                        newLightsToTurnOn.emplace_back(lightToTurnOn);
                    }
                }
                lightsToTurnOn = newLightsToTurnOn;
            }

            turnedOnLights.insert(turnedOnLights.end()
                    ,lightsToTurnOn.begin()
                    , lightsToTurnOn.end());
        }else{
            vector<BoundingBox> newTurnedOnLights;
            for (const auto turnedOnLight:turnedOnLights) {
                if(turnedOnLight.intersects(currentBox)){
                    auto intersection = turnedOnLight.intersection(currentBox);
                    auto dissection = turnedOnLight.dissect(intersection);

                    newTurnedOnLights.insert(newTurnedOnLights.end(),
                                             dissection.begin(),
                                             dissection.end());
                }else{
                    newTurnedOnLights.emplace_back(turnedOnLight);
                }
            }

            turnedOnLights = newTurnedOnLights;
        }


        /*uint64_t totalVol = 0;
        for (const auto& light:turnedOnLights) {
            cout << light << endl;
            totalVol+=light.volume();
        }
        cout << totalVol << endl << endl;*/
    }

    uint64_t totalVol = 0;
    for (const auto& light:turnedOnLights) {
        //cout << light << endl;
        totalVol+=light.volume();
    }

    cout << totalVol << endl;
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


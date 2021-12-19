//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <cassert>
#include <set>

using namespace std;

class Coord{
    int _x;
    int _y;
    int _z;
public:
    Coord(int x, int y, int z)
    :_x(x),_y(y),_z(z){}

    [[nodiscard]] int x() const{
        return _x;
    }

    [[nodiscard]] int y() const{
        return _y;
    }

    [[nodiscard]] int z() const{
        return _z;
    }

    [[nodiscard]] uint64_t manhattanLength() const{
        return abs(_x)+abs(_y)+ abs(_z);
    }

    bool operator==(Coord const & Other) const{
        return _x==Other._x && _y==Other._y&&_z==Other._z;
    }
    bool operator<(Coord const & Other) const{
        if(_x==Other._x){
            if(_y==Other._y){
                return _z<Other._z;
            }else{
                return _y<Other._y;
            }
        }else{
            return _x<Other._x;
        }
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

class Sensor{
    bool _fixed = false;
    size_t _id;

    Coord _pos{0,0,0};

    vector<Coord> _beacons;
public:
    explicit Sensor(size_t id, vector<Coord> &relativePositions)
    :_id(id),_beacons(std::move(relativePositions)){}

    void fixSensor(Coord position, vector<Coord> absolutePositions){
        _pos = std::move(position);
        _beacons = std::move(absolutePositions);
        fixSensor();
    }

    void fixSensor(){
        _fixed = true;
    }

    [[nodiscard]] const vector<Coord> &getBeacons() const {
        return _beacons;
    }

    [[nodiscard]] size_t id() const{
        return _id;
    }

    [[nodiscard]] Coord pos() const{
        return _pos;
    }
};

namespace transform{
    Coord rotateCoord(const Coord& coord, size_t rotation){
        assert(rotation<24);


        // We rotate in two steps
        // Imagine the 24 possibilities as the following:
        // The sensor can face 6 different directions (Like on a dice)
        // For each side, there are four possible "roll" values
        // We first determine the side to turn to
        // Then we apply the roll
        Coord result=coord;
        switch (rotation/4) {
            // case 0: Omitted, no change in rotation
            case 1:
                // Face "right"
                result = {result.y(),-result.x(),result.z()};
                break;
            case 2:
                // Face "back"
                result = {-result.x(),-result.y(),result.z()};
                break;
            case 3:
                // Face "left"
                result = {-result.y(),result.x(),result.z()};
                break;
            case 4:
                // Face "up"
                result = {result.z(),result.y(),-result.x()};
                break;
            case 5:
                // Face "down"
                result = {-result.z(),result.y(),result.x()};
                break;
        }

        switch(rotation%4){
            //case 0: Omitted, no roll
            case 1:
                //Roll 90 degree
                result = {result.x(),result.z(),-result.y()};
                break;
            case 2:
                //Roll 180 degree
                result = {result.x(),-result.y(),-result.z()};
                break;
            case 3:
                //Roll 270 Degree
                result = {result.x(),-result.z(),result.y()};
                break;
        }

        return result;
    }

    std::vector<Coord> rotateCoords(const vector<Coord> &Coords, size_t rotation){
        vector<Coord> result;
        result.reserve(Coords.size());
        for (const auto& coord:Coords) {
            result.push_back(rotateCoord(coord,rotation));
        }

        sort(result.begin(),result.end());
        return result;
    }

    void applyTranslation(Coord &Pos, vector<Coord> &Coords){
        for (auto &coord:Coords) {
            coord+=Pos;
        }
    }
}

bool parseSensor(queue<Sensor> &SensorList){
    string line;
    getline(cin, line);
    if(line.empty()){
        return false;
    }
    int id = stoi(line.substr(12,line.length()-16));

    vector<Coord> readings;

    while (getline(cin,line) && !line.empty()){
        size_t separator1 = line.find_first_of(",");
        size_t separator2 = line.find_last_of(",");

        int x = stoi(line.substr(0,separator1));
        int y = stoi(line.substr(separator1+1,separator2-separator1));
        int z = stoi(line.substr(separator2+1));

        readings.emplace_back(x,y,z);
    }

    std::sort(readings.begin(),readings.end());

    SensorList.emplace(id,readings);
    return true;
}

void part1(){
    queue<Sensor> sensors;
    vector<Sensor> fixedSensors;

    while (parseSensor(sensors)){
    }

    Sensor sensor0 = std::move(sensors.front());
    sensors.pop();

    sensor0.fixSensor();

    fixedSensors.push_back(std::move(sensor0));

    while (!sensors.empty()){
        Sensor currentSensor = std::move(sensors.front());
        sensors.pop();

        bool sensorFixed = false;
        for (const auto& fixedSensor : fixedSensors) {
            auto &Beacons = fixedSensor.getBeacons();

            auto &Offsets = currentSensor.getBeacons();

            for (const auto& offset : Offsets) {

                for (auto& knownBeacon : Beacons) {

                    for (int rotation = 0; rotation < 24; ++rotation) {
                        auto rotatedOffset = transform::rotateCoord(offset,rotation);
                        auto rotatedOffsets = transform::rotateCoords(Offsets,rotation);

                        auto suspectedPosition = knownBeacon-rotatedOffset;
                        transform::applyTranslation(suspectedPosition,rotatedOffsets);

                        vector<Coord> intersection;
                        std::set_intersection(Beacons.begin(),Beacons.end(),rotatedOffsets.begin(),rotatedOffsets.end(),
                                              back_inserter(intersection));

                        if(intersection.size()>=12){
                            // Found overlap, fix this sensor
                            cout << "Sensor #" << currentSensor.id() << " fixed (Matches against Sensor #" << fixedSensor.id() << ")"<<endl;
                            sensorFixed = true;
                            currentSensor.fixSensor(suspectedPosition,rotatedOffsets);
                            fixedSensors.push_back(std::move(currentSensor));
                            break;
                        }
                    }
                    if(sensorFixed){
                        break;
                    }
                }
                if(sensorFixed){
                    break;
                }
            }
            if(sensorFixed){
                break;
            }
        }

        if(!sensorFixed) {
            sensors.emplace(std::move(currentSensor));
        }
    }

    std::set<Coord> beacons;

    for (const auto& fixedSensor:fixedSensors) {
        for (const auto& beacon:fixedSensor.getBeacons()) {
            beacons.emplace(beacon);
        }
    }

    cout << beacons.size() << endl;
}

void part2(){
    queue<Sensor> sensors;
    vector<Sensor> fixedSensors;

    while (parseSensor(sensors)){
    }

    vector<vector<bool>> checkedOverlap(sensors.size(),vector<bool>(sensors.size(),false));

    Sensor sensor0 = std::move(sensors.front());
    sensors.pop();

    sensor0.fixSensor();

    fixedSensors.push_back(std::move(sensor0));

    while (!sensors.empty()){
        Sensor currentSensor = std::move(sensors.front());
        sensors.pop();

        bool sensorFixed = false;
        for (const auto& fixedSensor : fixedSensors) {
            if(checkedOverlap[currentSensor.id()][fixedSensor.id()]){
                continue;
            }

            auto &Beacons = fixedSensor.getBeacons();

            auto &Offsets = currentSensor.getBeacons();

            for (const auto& offset : Offsets) {

                for (auto& knownBeacon : Beacons) {

                    for (int rotation = 0; rotation < 24; ++rotation) {
                        auto rotatedOffset = transform::rotateCoord(offset,rotation);
                        auto rotatedOffsets = transform::rotateCoords(Offsets,rotation);

                        auto suspectedPosition = knownBeacon-rotatedOffset;
                        transform::applyTranslation(suspectedPosition,rotatedOffsets);

                        vector<Coord> intersection;
                        std::set_intersection(Beacons.begin(),Beacons.end(),rotatedOffsets.begin(),rotatedOffsets.end(),
                                              back_inserter(intersection));

                        if(intersection.size()>=12){
                            // Found overlap, fix this sensor
                            cout << "Sensor #" << currentSensor.id() << " fixed (Matches against Sensor #" << fixedSensor.id() << ")"<<endl;
                            sensorFixed = true;
                            currentSensor.fixSensor(suspectedPosition,rotatedOffsets);
                            fixedSensors.push_back(std::move(currentSensor));
                            break;
                        }
                    }
                    if(sensorFixed){
                        break;
                    }
                }
                if(sensorFixed){
                    break;
                }
            }
            if(sensorFixed){
                break;
            }else{
                checkedOverlap[currentSensor.id()][fixedSensor.id()] = true;
            }
        }

        if(!sensorFixed) {
            sensors.emplace(std::move(currentSensor));
        }
    }

    std::set<Coord> beacons;

    for (const auto& fixedSensor:fixedSensors) {
        for (const auto& beacon:fixedSensor.getBeacons()) {
            beacons.emplace(beacon);
        }
    }

    cout << beacons.size() << endl;
    uint64_t maxManhattan = 0;

    for (int first = 0; first < fixedSensors.size(); ++first) {
        for (int second = first+1; second < fixedSensors.size(); ++second) {
            auto diff = fixedSensors[first].pos()-fixedSensors[second].pos();
            maxManhattan = max(maxManhattan,diff.manhattanLength());
        }
    }

    cout << maxManhattan << endl;
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


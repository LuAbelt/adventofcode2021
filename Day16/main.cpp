//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <numeric>
#include <memory>
#include <cassert>

using namespace std;

class Packet{
protected:
    uint64_t version;
    uint64_t typeID;
public:
    Packet(uint64_t version, uint64_t typeID)
    :version(version)
    ,typeID(typeID){}

    virtual uint64_t sumVersions() const {return 0;};
    virtual uint64_t evaluate() const { return 0; };
};

class Literal
 : public Packet
{
    uint64_t literal_value;
public:
    Literal(uint64_t version,uint64_t value)
    : Packet(version,4)
    ,literal_value(value)
    {}

    virtual uint64_t evaluate() const override{
        return literal_value;
    }

    virtual uint64_t sumVersions() const override{
        return version;
    }
};

class Operator
    :public Packet
{
    std::vector<std::shared_ptr<Packet>> _subPackets;
public:
    using Packets = std::vector<std::shared_ptr<Packet>>;
    Operator(uint64_t version, uint64_t typeId, Packets subPackets)
    : Packet(version,typeId)
    ,_subPackets(subPackets){}

    virtual uint64_t sumVersions() const override{
        return std::accumulate(_subPackets.begin(),_subPackets.end(),version,[](uint64_t current, const auto& packet){
            return current+packet->sumVersions();
        });
    }

    virtual uint64_t evaluate() const override{
        switch(typeID){
            case 0:
                return std::accumulate(_subPackets.begin(), _subPackets.end(),(uint64_t)0LL,[](uint64_t current, auto& pack){
                   return current+pack->evaluate();
                });
            case 1:
                return std::accumulate(_subPackets.begin(), _subPackets.end(),(uint64_t)1LL,[](uint64_t current, auto& pack){
                    return current*pack->evaluate();
                });
            case 2:
                return std::accumulate(_subPackets.begin(), _subPackets.end(),std::numeric_limits<uint64_t>::max(),[](uint64_t current, auto& pack){
                    return min(current,pack->evaluate());
                });
            case 3:
                return std::accumulate(_subPackets.begin(), _subPackets.end(),0LL,[](uint64_t current, auto& pack){
                    return max(current,pack->evaluate());
                });
            case 5:
                assert(_subPackets.size()==2);
                if(_subPackets[0]->evaluate()>_subPackets[1]->evaluate()){
                    return 1;
                }else{
                    return 0;
                }
            case 6:
                assert(_subPackets.size()==2);
                if(_subPackets[0]->evaluate()<_subPackets[1]->evaluate()){
                    return 1;
                }else{
                    return 0;
                }
            case 7:
                assert(_subPackets.size()==2);
                if(_subPackets[0]->evaluate()==_subPackets[1]->evaluate()){
                    return 1;
                }else{
                    return 0;
                }
            default:
                cout << "Should not happen" << endl;
                return -1;
        }
    }
};

std::shared_ptr<Operator> parseOperator(uint64_t ,uint64_t ,const string&,size_t&);

uint64_t binaryStringToInt(const string &input){
    return std::accumulate(input.begin(), input.end(),0LL,[](size_t current, char next){
        return (current*2)+(next-'0');
    });
}

std::shared_ptr<Literal> parseLiteral(uint64_t version, const string &input, size_t &position){
    string binString;
    while (input[position]=='1'){
        binString += input.substr(position + 1, 4);
        position+=5;
    }
    binString += input.substr(position + 1, 4);
    position+=5;

    uint64_t value = binaryStringToInt(binString);
    return make_shared<Literal>(version,value);
}

std::shared_ptr<Packet> parsePacket(const string &input, size_t &position){
    int version = binaryStringToInt(input.substr(position,3));
    int typeId = binaryStringToInt(input.substr(position+3,3));
    position+=6;
    if(typeId==4){
        return parseLiteral(version, input, position);
    }else{
        return parseOperator(version, typeId, input, position);
    }
}

std::shared_ptr<Operator> parseOperator(uint64_t version, uint64_t typeId, const string& input, size_t &position){
    Operator::Packets subPackets;
    if (input[position]=='0'){
        uint64_t subPacketLength = binaryStringToInt(input.substr(position+1,15));
        position += 16;

        size_t endPosition = position+subPacketLength;
        while (position<endPosition){
            subPackets.push_back(parsePacket(input,position));
        }
        position=endPosition;
    } else {
        uint64_t numSubPackets = binaryStringToInt(input.substr(position+1,11));
        position += 12;
        for(int i = 0;i<numSubPackets;++i) {
            subPackets.push_back(parsePacket(input, position));
        }
    }

    return make_shared<Operator>(version,typeId,subPackets);
}

string hexToBinary(const string &input){
    string result = "";

    for (auto character : input) {
        switch (character) {
            case '0':
                result.append("0000");
                break;
            case '1':
                result.append("0001");
                break;
            case '2':
                result.append("0010");
                break;
            case '3':
                result.append("0011");
                break;
            case '4':
                result.append("0100");
                break;
            case '5':
                result.append("0101");
                break;
            case '6':
                result.append("0110");
                break;
            case '7':
                result.append("0111");
                break;
            case '8':
                result.append("1000");
                break;
            case '9':
                result.append("1001");
                break;
            case 'A':
                result.append("1010");
                break;
            case 'B':
                result.append("1011");
                break;
            case 'C':
                result.append("1100");
                break;
            case 'D':
                result.append("1101");
                break;
            case 'E':
                result.append("1110");
                break;
            case 'F':
                result.append("1111");
                break;
            default:
                cout << "Unexpected character! "<<character<<endl;
        }
    }
    return result;
}

void part1(){
  std::string line;
  while(getline(std::cin, line) && !line.empty()){
    // Read input
    string binary_repr = hexToBinary(line);

    size_t pos = 0;
    auto Packet = parsePacket(binary_repr,pos);
    cout << Packet->sumVersions() << endl;
  }
}

void part2(){
    std::string line;
    while(getline(std::cin, line) && !line.empty()){
        // Read input
        string binary_repr = hexToBinary(line);

        size_t pos = 0;
        auto Packet = parsePacket(binary_repr,pos);
        cout << Packet->evaluate() << endl;
        cout << binary_repr.substr(pos) << endl;
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


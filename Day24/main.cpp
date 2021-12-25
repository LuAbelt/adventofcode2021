//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <array>
#include <iterator>

using namespace std;

int64_t StupidMONAD(array<int,14> inputs){
    int64_t x = 0;
    int64_t y = 0;
    int64_t z = 0;
    int64_t w = 0;

    w = inputs[0];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 12;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 15;
    y *= x;
    z += y;
    w = inputs[1];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 14;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 12;
    y *= x;
    z += y;
    w = inputs[2];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 11;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 15;
    y *= x;
    z += y;
    w=inputs[3];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -9;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 12;
    y *= x;
    z += y;
    w=inputs[4];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -7;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 15;
    y *= x;
    z += y;
    w=inputs[5];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 11;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 2;
    y *= x;
    z += y;
    w=inputs[6];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -1;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 11;
    y *= x;
    z += y;
    w=inputs[7];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -16;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 15;
    y *= x;
    z += y;
    w=inputs[8];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 11;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 10;
    y *= x;
    z += y;
    w=inputs[9];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -15;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 2;
    y *= x;
    z += y;
    w=inputs[10];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 10;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 0;
    y *= x;
    z += y;
    w = inputs[11];
    x *= 0;
    x += z;
    x %= 26;
    z /= 1;
    x += 12;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 0;
    y *= x;
    z += y;
    w = inputs[12];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += -4;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 15;
    y *= x;
    z += y;
    w = inputs[13];
    x *= 0;
    x += z;
    x %= 26;
    z /= 26;
    x += 0;
    x = (x==w)?1:0;
    x = (x==0)?1:0;
    y *= 0;
    y += 25;
    y *= x;
    y += 1;
    z *= y;
    y *= 0;
    y += w;
    y += 15;
    y *= x;
    z += y;
    return z;
}

void part1(){

    vector<int> w1Candidates = {2,3,4,5,6,7,8,9};
    vector<int> w2Candidates = {1,2,3,4};
    vector<int> w3Candidates = {1,2,3};
    vector<int> w6Candidates = {1,2,3,4,5,6,7,8};
    vector<int> w9Candidates = {6,7,8,9};
    vector<int> w11Candidates = {1,2,3,4,5,6,7,8,9};
    vector<int> w12Candidates = {5,6,7,8,9};

    std::reverse(w1Candidates.begin(), w1Candidates.end());
    std::reverse(w2Candidates.begin(), w2Candidates.end());
    std::reverse(w3Candidates.begin(), w3Candidates.end());
    std::reverse(w6Candidates.begin(), w6Candidates.end());
    std::reverse(w9Candidates.begin(), w9Candidates.end());
    std::reverse(w11Candidates.begin(), w11Candidates.end());
    std::reverse(w12Candidates.begin(), w12Candidates.end());

    cout << "Checking " << w1Candidates.size()*w2Candidates.size()*w3Candidates.size()
    *w6Candidates.size()*w9Candidates.size()*w11Candidates.size()*w12Candidates.size() << " candidates" << endl;

    for (auto w1 : w1Candidates) {
        int w8=w1-1;
        for (auto w2 : w2Candidates) {
            int w5 = w2+5;
            for (auto w3 : w3Candidates) {
                int w4 = w3+6;
                for (auto w6 : w6Candidates) {
                    int w7 = w6+1;
                    for (auto w9 : w9Candidates) {
                        int w10 = w9-5;
                        for (auto w11 : w11Candidates) {
                            int w14=w11;
                            for (auto w12 : w12Candidates) {
                                int w13 = w12-4;

                                array<int,14> input = {w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14};

                                if(StupidMONAD(input)==0){
                                    for (auto v:input) {
                                        cout << v;
                                    }
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void part2(){

    vector<int> w1Candidates = {2,3,4,5,6,7,8,9};
    vector<int> w2Candidates = {1,2,3,4};
    vector<int> w3Candidates = {1,2,3};
    vector<int> w6Candidates = {1,2,3,4,5,6,7,8};
    vector<int> w9Candidates = {6,7,8,9};
    vector<int> w11Candidates = {1,2,3,4,5,6,7,8,9};
    vector<int> w12Candidates = {5,6,7,8,9};

    cout << "Checking " << w1Candidates.size()*w2Candidates.size()*w3Candidates.size()
                           *w6Candidates.size()*w9Candidates.size()*w11Candidates.size()*w12Candidates.size() << " candidates" << endl;

    for (auto w1 : w1Candidates) {
        int w8=w1-1;
        for (auto w2 : w2Candidates) {
            int w5 = w2+5;
            for (auto w3 : w3Candidates) {
                int w4 = w3+6;
                for (auto w6 : w6Candidates) {
                    int w7 = w6+1;
                    for (auto w9 : w9Candidates) {
                        int w10 = w9-5;
                        for (auto w11 : w11Candidates) {
                            int w14=w11;
                            for (auto w12 : w12Candidates) {
                                int w13 = w12-4;

                                array<int,14> input = {w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w13,w14};

                                if(StupidMONAD(input)==0){
                                    for (auto v:input) {
                                        cout << v;
                                    }
                                    return;
                                }
                            }
                        }
                    }
                }
            }
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


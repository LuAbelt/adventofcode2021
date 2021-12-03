#include <iostream>

int main() {
    int cnt = 0;
    int curIdx = 0;

    int sliding[3] = {0,0,0};

    int cur;

    std::cin >> cur;
    sliding[0]+=cur;

    std::cin >> cur;
    sliding[0]+=cur;
    sliding[1]+=cur;

    std::cin >> cur;
    sliding[0]+=cur;
    sliding[1]+=cur;
    sliding[2]+=cur;

    int lastSum = sliding[0];
    curIdx = 1;
    sliding[0]=0;
    for(int i=0;i<1997;++i) {
        std::cin >> cur;
        sliding[0]+=cur;
        sliding[1]+=cur;
        sliding[2]+=cur;

        //std::cout << lastSum <<std::endl;
        if(sliding[curIdx]>lastSum){
            ++cnt;
        }

        lastSum=sliding[curIdx];
        sliding[curIdx]=0;
        curIdx= (curIdx+1)%3;
    }

    std::cout << cnt << std::endl;

    return cnt;
}

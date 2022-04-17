/*************************************************************************
    > File Name: test.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include<iostream>
#include <stdlib.h>
#include <celero/Celero.h>
#include <vector>
#include <memory>
#include <utility>

using ptr=std::shared_ptr<int>;
using wptr=std::weak_ptr<int>;
static std::vector<int> valgroup;
static std::vector<ptr> sharedgroup;
static std::vector<wptr> weakgroup;
static std::vector<int*> cptrgroup;
static std::vector<double> values;

int main(int argc, char *argv[]) {
    for (int i=0; i < 100000; ++i) {
        valgroup.push_back(i);
        auto p = std::make_shared<int>(i);
        sharedgroup.push_back(p);
        weakgroup.push_back(p);
        cptrgroup.push_back(p.get());
    }
    
    celero::Run(argc, argv);
    std::cout << values.size() << std::endl;

    return 0;
}

BASELINE(Ptr, Baseline, 600, 3) {
    double val = 0;
    for (auto v: valgroup) {
        val += v;
    }
    values.push_back(val);
}

BENCHMARK(Ptr, SharedPtr, 600, 3) {
    double val = 0;
    for (auto &v: sharedgroup) {
        if (v) val += *v;
    }
    values.push_back(val);
}

BENCHMARK(Ptr, Ptr, 600, 3) {
    double val = 0;
    for (auto &v: cptrgroup) {
        if (v) val += *v;
    }
    values.push_back(val);
}

BENCHMARK(Ptr, wptr, 600, 3) {
    double val = 0;
    for (auto &v: weakgroup) {
        auto pp = v.lock();
        if (pp) val += *pp;
    }
    values.push_back(val);
}


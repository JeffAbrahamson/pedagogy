// for_each example
#include <iostream>
#include <algorithm>
#include <vector>


void myfunction (int i) {
        std::cout << " " << i;
}

class myclass {
public:
        void operator() (int i) {std::cout << " " << i;}
};
myclass myobject;

int main () {
        std::vector<int> myvector;
        myvector.push_back(10);
        myvector.push_back(20);
        myvector.push_back(30);

        std::cout << "myvector contains:";
        for_each (myvector.begin(), myvector.end(), myfunction);

        // or:
        std::cout << "\nmyvector contains:";
        for_each (myvector.begin(), myvector.end(), myobject);

        std::cout << std::endl;

        return 0;
}

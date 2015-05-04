// dictionary: how many times words appear in input stream

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>



int main( int argc, char *argv[] )
{
        std::map<std::string, int> dict;

        std::string word;
        while(std::cin>>word) {
                dict[word]++;
        }

        class printer {
        public:
                void operator()(std::map<std::string, int>::value_type pr) {
                        std::cout << pr.first << " " << pr.second << std::endl;
                }
        };

        std::cout << std::endl;
        /*
          Why doesn't for_each() work here?
         */
        //std::for_each(dict.begin(), dict.end(), printer());
        std::map<std::string, int>::const_iterator it = dict.begin();
        for(; it != dict.end(); ++it) {
                std::cout << it->first << " " << it->second << std::endl;
        }
}

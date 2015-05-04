// Find the first non-repeating character in a string.

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>




std::string::value_type first_non_repeat(std::string s)
{
        std::map<std::string::value_type, int> chars;

        class no_uniques {};
        class counter {
                //std::map<std::string::value_type, int> chars;
        public:
                void operator() (char i) {}
                //void operator()(std::string::value_type c) { chars[c]++; }
                //int operator[](std::string::value_type c) { return chars[c]; }
        };

        counter count;

        // Why doesn't for_each() work here?
        //std::for_each(s.begin(), s.end(), count);

        std::string::const_iterator it = s.begin();
        for(; it != s.end(); ++it) {
                chars[*it]++;
        }

        it = s.begin();
        for(; it != s.end(); ++it) {
                if(1 == chars[*it])
                        return(*it);
        }
        throw(no_uniques());
}



int main( int argc, char *argv[] )
{
        std::string s1 = "abca"; // Answer = 'b'
        std::string::value_type c1 = first_non_repeat(s1);
        std::cout << s1 << std::endl << c1 << std::endl;

        // Answer = 'A'
        std::string s2 = "All happy families are all alike, every unhappy family is unhappy in its own way.";
        std::string::value_type c2 = first_non_repeat(s2);
        std::cout << s2 << std::endl << c2 << std::endl;


        // Answer = 'k'
        std::string s3 = "all happy families are all alike, every unhappy family is unhappy in its own way.";
        std::string::value_type c3 = first_non_repeat(s3);
        std::cout << s3 << std::endl << c3 << std::endl;
}


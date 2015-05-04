
#include <list>
#include <iostream>


template<class T>
void populate_collection(T &collection, int num = 6)
{
        int a = 1;
        int b = 1;

        for(int i = 0; i < num; i++) {
                collection.push_back(a);
                int tmp = a;
                a = b;
                b += tmp;
        }
}


template<class T>
void print_collection( const T &collection)
{
        for( typename T::const_iterator pos = collection.begin(); pos != collection.end(); pos++ ) {
                std::cout << *pos << " ";
        }
        std::cout << std::endl;        
}



template<class T>
void reverse_list(T &collection)
{
        typename T::iterator begin = collection.begin();
        typename T::iterator end = collection.end();
        if(begin == end)
                return;
        end--;
        while(true) {
                typename T::value_type tmp;
                tmp = *begin;
                *begin = *end;
                *end = tmp;
                begin++;
                if(begin == end)
                        return;
                end--;
                if(begin == end)
                        return;
        }
        return;
}



int main( int argc, char *argv[] )
{
        std::list< int > L;
        populate_collection(L, 9);
        
        print_collection(L);
        reverse_list(L);
        print_collection(L);
}





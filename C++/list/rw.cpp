
#include <list>
#include <iostream>



void advance_to_space(std::string::iterator &iter, const std::string::const_iterator end)
{
        while(end != iter && isalpha(*iter))
                iter++;
}



void advance_to_nonspace(std::string::iterator &iter, const std::string::const_iterator end)
{
        while(end != iter && !isalpha(*iter))
                iter++;
}


void reverse_word(const std::string::iterator from_iter, const std::string::iterator to_iter)
{
        if(from_iter == to_iter)
                return;
        std::string::iterator from = from_iter;
        std::string::iterator to = to_iter;

        to--;                   // Don't copy the space
        while(from != to) {
                std::string::value_type c = *from;
                *from = *to;
                *to = c;
                to--;
                if(from == to)
                        return;
                from++;
        }
}


void reverse_words(std::string &s)
{
        std::string::iterator begin_word = s.begin();
        std::string::iterator end_word = s.begin();

        while(begin_word != s.end() ) {
                advance_to_space(end_word, s.end());
                reverse_word(begin_word, end_word);
                begin_word = end_word;
                advance_to_nonspace(begin_word, s.end());
                end_word = begin_word;
        }
                        
}


int main( int argc, char *argv[] )
{
        std::string s = "All happy families are all alike, every unhappy family is unhappy in its own way.";

        std::cout << s << std::endl;
        reverse_words(s);        
        std::cout << s << std::endl;        
        reverse_words(s);        
        std::cout << s << std::endl;        
}





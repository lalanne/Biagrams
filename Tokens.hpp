
#include <vector>
#include <string>
#include <sstream>

class TokensIterator{
    public:
        TokensIterator(std::vector<std::string>::iterator it) : it(it){}
        TokensIterator& operator++(){
            ++it;
            return *this;
        }

        TokensIterator operator++(int){
            TokensIterator tmp(*this);
            operator++();
            return tmp;
        }

        bool operator>(const TokensIterator& rhs){
            return it>rhs.it;
        }

        bool operator<( const TokensIterator& rhs){
            return it<rhs.it;
        }

        std::string& operator*(){
            return *it;
        }

        TokensIterator operator+(const unsigned int i){
            return TokensIterator(it+i);
        }

    private:
        std::vector<std::string>::iterator it; 
};

class Tokens{
    public:
        Tokens(std::istringstream& iss):tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}}{}

        TokensIterator begin(){
            return TokensIterator(tokens.begin());
        }

        TokensIterator end(){
            return TokensIterator(tokens.end());
        }

    private:
        std::vector<std::string> tokens;
};




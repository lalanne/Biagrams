
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Tokens{
    public:
        Tokens(istringstream& iss):tokens{istream_iterator<string>{iss}, istream_iterator<string>{}}{}

        vector<string>::iterator begin(){
            return tokens.begin();
        }

        vector<string>::iterator end(){
            return tokens.end();
        }

    private:
        vector<string> tokens;

};

struct StreamImporter{
    Tokens operator()(string file_name){
        ifstream in(file_name);
        string contents((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        istringstream iss(contents);
        Tokens tokens(iss);
        return tokens;
    }
};

map<pair<string, string>, unsigned int> store_biagrams(Tokens& tokens){
    map<pair<string, string>, unsigned int> biagrams;
    pair<map<pair<string, string>, unsigned int>::iterator, bool> ret;

    for(auto i = tokens.begin(); i < tokens.end(); ++i){
        ret = biagrams.insert(pair<pair<string, string>,unsigned int>(pair<string, string>(*i, *(i+1)), 1));
        if(!ret.second){
            ++(ret.first->second);
        }
    }

    return biagrams;
}

void show_in_order(map<pair<string, string>, unsigned int> biagrams){
    vector<pair<pair<string, string>, unsigned int>> map_copy(biagrams.begin(), biagrams.end());

    sort(map_copy.begin(), map_copy.end(),
    [](pair<pair<string, string>, unsigned int>& i, pair<pair<string, string>, unsigned int>& j)->bool{
            return i.second > j.second;
        });

    for(auto &i : map_copy) cout<<i.second<<"  <"<<i.first.first<<","<<i.first.second<<">"<<endl; 
}

void show_biagram_numbers(map<pair<string, string>, unsigned int>& biagrams){
    cout<<"Number of biagrams: "<<biagrams.size()<<endl;
}

int main(int argc, const char *argv[]){
    string file_name(argv[1]);

    StreamImporter import_file;
    Tokens tokens =  import_file(file_name);
    auto biagrams = store_biagrams(tokens);
    show_in_order(biagrams);
    show_biagram_numbers(biagrams);

    return 0;
}



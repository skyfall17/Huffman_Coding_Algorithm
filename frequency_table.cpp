#include "frequency_table.h"
#include <fstream>
using namespace std;
frequency_table::frequency_table(const std::string &file_name) {    // constructs object. Read file, store freq. throw runtime_error if file isn't found or can't be open
    for(int c = 0; c < 128; c++){
        map.insert({char(c), 0});
    }
    ifstream inFile(file_name);
    char c;
    if(inFile.good()){
        while(inFile.get(c)){
            map.at(c)++;
        }
    }else{
        throw runtime_error("File not found");
    }
}

frequency_table::~frequency_table() {   // destructs object, frees dynamic memory
    map.erase(map.begin(), map.end());
}

int frequency_table::get_frequency(char c) const {  // returns frequency of character c in the file
    return map.at(c);
}

int frequency_table::getSize() const{
    return map.size();
}
#pragma once

#include <iostream>
//#include <string>
#include <unordered_map>
using namespace std;
class frequency_table {
    // Something to store the frequency of each character

public:
    unordered_map<char, int> map;

    frequency_table(const std::string &file_name);
    ~frequency_table();

    int get_frequency(char c) const;
    int getSize() const;
};
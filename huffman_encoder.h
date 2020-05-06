#pragma once

#include "frequency_table.h"
#include <queue>
#include <unordered_map>
// struct for the nodes of the tree?
struct HuffmanTreeNode{
    char character;
    int frequency;
    HuffmanTreeNode* left; //0
    HuffmanTreeNode* right; //1
    HuffmanTreeNode(char character, int frequency){
        this->character = character;
        this->frequency = frequency;
        left = nullptr;
        right = nullptr;
    }
};
class compareFreq{
public:
    bool operator() (HuffmanTreeNode* first, HuffmanTreeNode* second){
        return first->frequency > second->frequency;
    }
};
class huffman_encoder {
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, compareFreq> queue;
    unordered_map<char, std::string> binaryStrings;
    public:
        huffman_encoder(const frequency_table &table);
        ~huffman_encoder();

        std::string get_character_code(char c) const;
        std::string encode(const std::string &file_name) const;
        std::string decode(const std::string &string_to_decode) const;

        void erase(HuffmanTreeNode* nodeToDelete);
        void clear(HuffmanTreeNode* nodeToDelete);

        void traverse(HuffmanTreeNode* node, string code);
};

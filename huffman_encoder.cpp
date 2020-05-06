#include "huffman_encoder.h"
#include <fstream>
void huffman_encoder::traverse(HuffmanTreeNode* node, string code){
    if(node == nullptr){
        return;
    }
    if(node->character != (char) 128) {
        binaryStrings[node->character] = code;
    }
    traverse(node->left, code + "0");
    traverse(node->right, code + "1");
}
huffman_encoder::huffman_encoder(const frequency_table &table){
    //creates object w/ characters of nonzero entries
    for(auto pair : table.map){
        if(pair.second > 0){
            HuffmanTreeNode* ins = new HuffmanTreeNode(pair.first, pair.second);
            queue.push(ins);
        }
    }
    if(queue.size() == 1){
        HuffmanTreeNode* left = queue.top();
        queue.pop();
        HuffmanTreeNode* root = new HuffmanTreeNode((char) 128, left->frequency);
        root->left = left;
        root->right = nullptr;
        queue.push(root);
    }
    while(queue.size() != 1){
        HuffmanTreeNode* left = queue.top();
        queue.pop();
        HuffmanTreeNode* right = queue.top();
        queue.pop();
        int parent = left->frequency + right->frequency;
        HuffmanTreeNode* ins = new HuffmanTreeNode((char) 128, parent);
        ins->left = left;
        ins->right = right;
        queue.push(ins);
    }
    traverse(queue.top(), "");
}
void huffman_encoder::erase(HuffmanTreeNode* nodeToDelete){
    if(nodeToDelete->left == nullptr && nodeToDelete->right == nullptr){
        delete nodeToDelete;
        nodeToDelete = nullptr;
    }
}
void huffman_encoder::clear(HuffmanTreeNode* nodeToDelete){    // recursive function to delete every node from bottom up
    if(nodeToDelete != nullptr){
        clear(nodeToDelete->left);
        clear(nodeToDelete->right);
        erase(nodeToDelete);   // delete node, set parent's pointer to nullptr
    }
}
huffman_encoder::~huffman_encoder(){
    //destructs object; free dynamic memory
    if(queue.size() > 0){
        clear(queue.top());
    }
}

std::string huffman_encoder::get_character_code(char character) const {
    //returns binary code for char; returns empty string if not present
    if(binaryStrings.find(character) == binaryStrings.end()){
        return "";
    }else{
        return binaryStrings.at(character);
    }
}

std::string huffman_encoder::encode(const std::string &file_name) const {
    //encodes the string to binary and concatenates
    //if file contains a letter not present, return empty string
    string result = "";
    ifstream inFile(file_name);
    char c;
    if(inFile.good()){
        while(inFile.get(c)){
            if(binaryStrings.find(c) == binaryStrings.end()){
                return "";
            }else{
                result += binaryStrings.at(c);
            }
        }
        return result;
    }else{
        throw runtime_error("File not found");
    }
}

std::string huffman_encoder::decode(const std::string &string_to_decode) const {
    //decodes binary to characters
    //if encoding is not valid, return empty string
    string result = "";
    HuffmanTreeNode* test = queue.top();
    if(test != nullptr) {
        for (unsigned int i = 0; i < string_to_decode.length(); i++) {
            if (string_to_decode[i] == '0') {
                test = test->left;
            }else if(string_to_decode[i] == '1') {
                test = test->right;
            }else {
                return "";
            }
            if(test->left == nullptr && test->right == nullptr) {
                result += test->character;
                test = queue.top();
            }
        }
        return result;
    }else{
        throw "No nodes in tree";
    }
}
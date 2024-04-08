/* Name: Sadman Sakib 
   Name: Khoa Le 
    This file contains the prototype of our Huffman class (compress, serializeTree and decompress)*/

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <map>
#include <deque> 
#include <climits>
#include <algorithm>
#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"


class HuffmanTree : public HuffmanTreeBase {
public:
   HuffmanTree() {}; //construction
   ~HuffmanTree(); //destruction
   void postOrderDelete(HuffmanNode* node); // post order delete function
   std::string compress(const std::string str_input); //compress function
   std::string serializeTree() const; //serializeTree function
   std::string decompress(const std::string inputCode, const std::string serializedTree); //decompress function

private:
   HuffmanNode* _node; // root node
   
protected:
   std::map<char, std::string> codeTable; // map for code table
   HeapQueue<HuffmanNode*, HuffmanNode::Compare> huffQueue; // a heap queue implementation of priority queue
   std::string serialize_string; // serialized string
   std::map <char, int> freqTable; // a map containing the frequency for each characters 
   std::string compressedString = ""; // compressed string 
   std::string decompressedString = ""; // decompressed string
   void encode(HuffmanNode* node, std::string code); // encode the string by going left or right in the tree 
   void create_freqTable(std::string str_input); // create the frequency table function 
   void traverse_postOrder(HuffmanNode* node); // traverse post order function
   void create_priorityQueue(std::map<char, int> x); // create priority queue function
   void string_to_compress(std::string str_input, std::map<char, std::string> map_); // turn into compressed string function //TODO change t const std::
};

#endif /* HUFFMANTREE_H */
/* Name: Sadman Sakib 
   Name: Khoa Le 
   This file contains the function definitions of our Huffman class (compress, serializeTree and decompress).*/


#include "HuffmanTree.hpp"

using namespace std;

// Destructor
HuffmanTree::~HuffmanTree() {
    if (!huffQueue.empty()) {
        postOrderDelete(_node);
    }
    _node = nullptr;
}

// Post order delete
void HuffmanTree::postOrderDelete(HuffmanNode* node) {
    if (node == nullptr) {
        return;
    }
    if (node->left != nullptr) {
        postOrderDelete(node->left);
    }
    if (node->right != nullptr) {
        postOrderDelete(node->right);
    }

    delete node;
}

// encoding the tree to a string 
void HuffmanTree::encode(HuffmanNode* node, std::string code) {
    if (node != nullptr) {
        if (node->isLeaf()) {
            codeTable.insert(std::pair<char, std::string>(node->getCharacter(), code));
    }
    encode(node->left, code + "0"); // left is 0
    encode(node->right, code + "1"); // right is 1
    }
    else 
        return;
}

// creating the frequency table for the characters
void HuffmanTree::create_freqTable(std::string str_input) {
    if (str_input == "") {
        return;
    }
    for (char c : str_input) {
        if (freqTable.find(c) != freqTable.end()) { 
            freqTable.at(c)++; // increment the frequency
        }
        else 
            freqTable.insert(std::pair<char, int>(c, 1)); // insert the character and frequency
    }
}

// traversing the tree in post order
void HuffmanTree::traverse_postOrder(HuffmanNode* node) {
    if (node == nullptr) {
        return;
    }
    else {
        traverse_postOrder(node->left);
        traverse_postOrder(node->right);
        if (node->isBranch()) {
            serialize_string += "B";
        } else if (node->isLeaf()) {
            serialize_string += "L";
            serialize_string += node->getCharacter();
        }
    }
}

// creates the priority queue for the characters according to their frequency and lexigraphical order
void HuffmanTree::create_priorityQueue(std::map<char, int> x) {
    for (const auto& entry : x) {
        huffQueue.insert(new HuffmanNode(entry.first, entry.second));
    }

    while (huffQueue.size() > 1) {
        HuffmanNode* left = huffQueue.min();
        huffQueue.removeMin();
        
        HuffmanNode* right = huffQueue.min();
        huffQueue.removeMin();

        int total_freq = left->getFrequency() + right->getFrequency();

        HuffmanNode* parent = new HuffmanNode('\0', total_freq, nullptr, left, right);

        huffQueue.insert(parent);
    }

        _node = huffQueue.min();
}

// turn into a compressed string using the frequency table 
void HuffmanTree::string_to_compress(std::string str_input, std::map<char, std::string> map_) {
    for (char c : str_input) {
        compressedString += map_[c];
    } 
}

/* ___________________________________________________________________________________________________________________________________ */

// compress function
std::string HuffmanTree::compress(const std::string str_input) {
    std::string s = "";
    create_freqTable(str_input);
    create_priorityQueue(freqTable);
    encode(huffQueue.min(), s);
    string_to_compress(str_input, codeTable);
    traverse_postOrder(huffQueue.min());

    return compressedString;
}

// serializeTree function
std::string HuffmanTree::serializeTree() const {
    return serialize_string;
}

// decompress function
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {
    std::deque<HuffmanNode*> deque_char;
    HuffmanNode *deque_left, *deque_right, *deque_root;

    // recreate the tree from the serialized string
    for (unsigned int x = 1; x < serializedTree.length(); x++) {
        char current = serializedTree.at(x);

        if (current != '\\') {

            if ((serializedTree.at(x) == 'B' && (serializedTree.at(x - 1) != 'L' || 
                    (serializedTree.at(x - 1) == 'L' && serializedTree.at(x - 2) == 'L')))) {
                deque_right = deque_char.back();
                deque_char.pop_back();
                deque_left = deque_char.back();
                deque_char.pop_back();

                deque_root = new HuffmanNode('#', 1, nullptr, deque_left, deque_right);
                deque_char.push_back(deque_root);
            }
            // If a leaf node is found
            else if (serializedTree.at(x - 1) == 'L') {
                deque_char.push_back(new HuffmanNode(current, 1));
            }
        }
    }

    // decompression process 
    HuffmanNode *root = deque_char.back();
    HuffmanNode *current = root;

    std::string decompressed = "";

    for (unsigned int c = 0; c < inputCode.length(); c++) {
        char bit = inputCode.at(c);

        current = (bit == '1') ? current->right : current->left; // if bit is 1, go right, else go left

        // if leaf node 
        if (current->isLeaf()) {
            decompressed += current->getCharacter();
            current = root;
        }
    }

    return decompressed;
}
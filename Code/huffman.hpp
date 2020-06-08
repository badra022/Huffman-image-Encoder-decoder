#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include "helpers.hpp"
#include "priority_queue.cpp"
#include "queue.cpp"

uint8_t buffer;
//#define ENDLINE_DETECTOR (uint8_t)243

queue<char> bits;

namespace huffman{

/* the tree node */
struct node
{
    uint8_t pixelValue;
    int frq;
    node* left;
    node* right;
};

/* function to allocate a new tree node */
node* getNode(uint8_t pixel_val , int frq , node* left , node* right)
{
    node* newNode = new node{pixel_val , frq , left , right};
    return newNode;
}

/* function to traverse the huffman tree (not the priority queue cause this is for frq table)
 * and storing haffmanCodes in the map */
void encode(node* root , string str , map<uint8_t , std::vector<char> >& huffmanCode)
{
    if(root == nullptr)return;

    /* if the root is a leaf node while recursing */
    if(!root->left && !root->right)
    {
        uint64_t idx = 0;
        while(idx != str.size())
        {
            huffmanCode[root->pixelValue].push_back(str[idx]);
        }
    }

    /* recursively traversing left nodes and right nodes of the current node */
    encode(root->left , str + '0' , huffmanCode);
    encode(root->right , str + '1' , huffmanCode);
}

/* function to traverse the huffman tree (not the priority queue cause this is for frq table)
 * and storing pixelvalues in the map according to the huffmanCodes */
int decode(node* root , char distination , uint8_t& pixel)
{
    if(root == nullptr || bits.isEmpty())return 0;

    /* if the root is a leaf node while recursing */
    if(!root->left && !root->right)
    {
        pixel = root->pixelValue;
    }
    /* recursively traversing left nodes of the current character of the huffmanCode is 0 , otherwise,
     *  traversing right nodes */
    if(distination == 0)
    {
        decode(root->left ,bits.dequeue(), pixel);
    }
    else
    {
        decode(root->right ,bits.dequeue(), pixel);
    }
    return 1;
}
}

//static void printElementInHeap(huffman::node* element)
//{
//    cout << (int)element->frq << "\n";
//}

void encodeImage(const char *imagePath , const char *encodedFilePath , const char *frequencyFilePath , const char *testPath)
{
    map< uint8_t , int >* frequencyTable;

    frequencyTable = help::getFrequencyTable(imagePath); /* ../data/NORMAL2-IM-1427-0001.pgm */
//    help::printFrequencyTable(frequencyTable);

    /* writing the frequency file to the destincted path */
    help::writeFrequencyTable(frequencyFilePath , frequencyTable);

    //Debug
    //help::printFrequencyTable(frequencyTable);

    /* creating the priority queue to store the nodes (leafs) of the frequency table
      * to construct the huffman tree */
    pQueue <huffman::node* > pq;

    for(auto pair : *frequencyTable)
    {
        pq.insert(huffman::getNode(pair.first , pair.second , nullptr , nullptr));
    }

//    // Debug
//    int sz = 0;
//    while(pq.size())
//    {
//        cout << (int)pq.extract()->frq << "\n";
//        sz++;
//    }
//    cout << "size: " << sz;

//    pq.traverseHeap(&printElementInHeap);

    /* while I have more than one node in the priority queue */
    while(pq.size() != 1)
    {
        /* making the lowest frequency pixelvalue is the left of a bigger node */
        huffman::node* left = pq.extract();

        /* making the second lowest frequency pixelvalue ( which is now the lowest after extracting the last one)
         *  is the left of a bigger node */
        huffman::node* right = pq.extract();

        int sum = left->frq + right->frq;
        /* making one big parent for both nodes and adding it to the priority queue */
        pq.insert(huffman::getNode('\0', sum , left , right ));
    }

    /* now the only node in the pq is the root of all the big (but smaller) nodes w.r.t it */
    huffman::node* root = pq.extract();

    /* traverse the huffman Tree and storing huffmanCodes into the map */
    map<uint8_t , string> huffmanCode;
    huffman::encode(root , "" , huffmanCode);

    // Debug
//    for(auto pair : huffmanCode)
//    {
//        cout << pair.first << "   " <<pair.second << "\n";
//    }

    /* creating the file that we will print pixelvalue and it's huffman code on it */
    std::ofstream encodedfile(encodedFilePath, std::ios::binary | std::ios::out);

    /* opening the image file to print for each pixevalue it's corresponding huffman code
     * but in the same order of the image file ot be able to decode it back */
    std::ifstream Imagefile(imagePath);

    std::ofstream testfile(testPath);
    /* First line : version */
    Imagefile >> version;
    testfile << version << "\n";

    /* third line is the width and height */
    Imagefile >> width >> height >> maxValue;
    testfile << width << "\t" << height << "\n" << maxValue << "\n";
//    /*write them to the encodedfile */
//    encodedfile << version << "\n" << width << "\t" << height << "\n" << maxValue <<"\n";

    // continues with the pixels input (character by character )
    while(Imagefile)
    {
        /* read the pixel (uint8_t) and print the corresponding huffmanCode in the encodedfile */
        Imagefile >> std::noskipws >> buffer;
        testfile << (uint8_t)buffer;
        encodedfile << huffmanCode[buffer];
//        help::writeBinaryCode(huffmanCode[buffer] , encodedfile);
//        encodedfile << " ";
    }
}


void decodeCompressedData(const char *imagePath , const char *encodedFilePath , const char *frequencyFilePath)
{
    map< uint8_t , int >* frequencyTable = new map< uint8_t , int >;

    for(uint8_t i = 0 ; i < (uint8_t)256 ; i++)
    {
        (*frequencyTable)[i] = 0;
    }

    /* reading the frequency file from the destincted path */
    help::readFrequencyTable(frequencyFilePath , frequencyTable);

    // Debug
    //    help::printFrequencyTable(frequencyTable);

    /* creating the priority queue to store the nodes (leafs) of the frequency table
      * to construct the huffman tree */
    pQueue <huffman::node* > pq;

    for(auto pair : *frequencyTable)
    {
        pq.insert(huffman::getNode(pair.first , pair.second , nullptr , nullptr));
    }

//    /* the frequency table no longer needed */
//    delete [] frequencyTable;
//    // Debug
//    int sz = 0;
//    while(pq.size())
//    {
//        cout << (int)pq.extract()->frq << "\n";
//        sz++;
//    }
//    cout << "size: " << sz;

//    pq.traverseHeap(&printElementInHeap);

    /* while I have more than one node in the priority queue */
    while(pq.size() != 1)
    {
        /* making the lowest frequency pixelvalue is the left of a bigger node */
        huffman::node* left = pq.extract();

        /* making the second lowest frequency pixelvalue ( which is now the lowest after extracting the last one)
         *  is the left of a bigger node */
        huffman::node* right = pq.extract();

        /* making one big parent for both nodes and adding it to the priority queue */
        pq.insert(huffman::getNode('\0', left->frq + right->frq , left , right ));
    }

    /* now the only node in the pq is the root of all the big (but smaller) nodes w.r.t it */
    huffman::node* root = pq.extract();

    /* traverse the huffman Tree and storing huffmanCodes into the map */
    map<uint8_t , string> huffmanCode;
    huffman::encode(root , "" , huffmanCode);

    // Debug
//    for(auto pair : huffmanCode)
//    {
//        cout << pair.first << "   " <<pair.second << "\n";
//    }

    /* opening the file that we will read pixelvalue and it's huffman code on it */
    std::ifstream encodedfile(encodedFilePath);

    /* creating the file that we will print the original data in it */
    std::ofstream Image(imagePath);

    /* First line : version */
    encodedfile >> version;


    /* third line is the width and height */
    encodedfile >> width >> height >> maxValue;

    /*write them to the encodedfile */
    Image << version << "\n" << width << "\t" << height << "\n" << maxValue <<"\n";

    /* string variable to hold the huffman code input from the encoded file */
    string code;
    // continues with the pixels input (character by character )
//    while(encodedfile)
//    {
//        /* read the pixel (uint8_t) and print the corresponding huffmanCode in the encodedfile */
//        encodedfile >> std::skipws >> code;
//        if((uint8_t)code[0] == ENDLINE_DETECTOR)
//        {
//            Image << "\n";
//        }
//        else
//        {
//            //Debug
////           cout << code << "\n";
//            uint8_t pixel;
//            int index = 0;
//            huffman::decode(root , index , code , pixel);
//            Image << (uint8_t)pixel;
//        }
//    }
  }

#endif // HUFFMAN_HPP

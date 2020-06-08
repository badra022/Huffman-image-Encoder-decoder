#ifndef HELPERS_HPP
#define HELPERS_HPP


#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include<bits/stdc++.h>

using std::cin;
using std::cout;
using std::map;
using std::string;

int width = 0 , height = 0 , maxValue = 0;
string version;
//string buffer;
uint8_t pixel;
string comment;
typedef map< uint8_t , int >::iterator it_t;
#define M 16

namespace help{
map< uint8_t , int >* getFrequencyTable(const char *filePath)
{
    std::ifstream file(filePath);
    map < uint8_t , int >* pTable = new map < uint8_t , int >;

    /* init the map */
    for(uint8_t i = 0 ; i < (uint8_t)256 ; i++)
    {
        (*pTable)[i] = 0;
    }

    // First line : version
    file >> version;
    if(version.compare("P5") != 0) std::cerr << "Version error" << "\n";
    else cout << "Version : " << version << "\n";

//    // comment
//    getline(file , comment);
//    cout << "comment: " << comment << "\n";

    // third line is the width and height
    file >> width >> height >> maxValue;
    cout << "width: " << width << "\theight: " << height << "\tmax value: " << maxValue << "\n";
    long long size = 0;
    // continues with the pixels input (character by character )
    while(file)
    {
        file >> std::noskipws >> pixel;
        (*pTable)[pixel]++;
        //cout << (int)pixel << "\nrep: " << (*pTable)[pixel] << "\n";
        size++;
    }
    //cout << size;

    // closing the file
    file.close();
    return pTable;
}

void printFrequencyTable(map< uint8_t , int >* table)
{
    int size = 0;
    for(auto pair : *table)
    {
        cout << "character: " << (int)pair.first << "\t" << "frequency: " << pair.second << "\n";
        size++;
    }
    cout << size;
}

int writeFrequencyTable(const char *filePath , map< uint8_t , int >* table)
{
    std::ofstream file(filePath);

    // If we couldn't open the output file stream for writing
      if (!file)
      {
          // Print an error and exit
          std::cerr << "Uh oh, could not create frequency table file!" << std::endl;
          return 0;
      }
      for(auto pair : *table)
      {
          file << (uint8_t)pair.first << "\t" << pair.second << "\n";
      }
      return 1;
}

int readFrequencyTable(const char *filePath , map< uint8_t , int >* table)
{

    uint8_t pixel;
    int frq;
    std::ifstream file(filePath);
    while(file)
    {
        file >> pixel >> frq;
        (*table)[pixel] = frq;
    }
    return 1;
}

int writeBinaryCode(string code , std::ofstream& outputfile)
{
    std::bitset<M> binarycode(code);
    for(uint64_t i = 0 ; i < code.size() ; i++)
    {
        outputfile << binarycode[i];
    }
    return 1;
}

std::vector<uint8_t> convertCodesStrToBin(string &strcode)
{
//    std::vector<uint8_t> *pcode = new std::vector<uint8_t>;
//    int idx = 0;
//    while(strcode[index] != '/0')
//    {
//        if(strcode[index] == '1')
//        {
//            pcode->push_back(1);
//        }
//        else
//        {
//            pcode->push_back(0);
//        }
//    }
}

std::vector<uint8_t> readByteCode(std::ifstream& encodedfile)
{

}

}


#endif // HELPERS_HPP

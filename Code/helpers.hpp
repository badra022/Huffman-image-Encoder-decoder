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

namespace help{
map< uint8_t , int >* getFrequencyTable(const char *filePath)
{
    std::ifstream file(filePath);
    map < uint8_t , int >* pTable = new map < uint8_t , int >;

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
        file >> pixel;
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
        cout << "character: " << (uint8_t)pair.first << "\t" << "frequency: " << pair.second << "\n";
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
          std::cerr << "Uh oh, could not create compressed file!" << std::endl;
          return 0;
      }
      for(auto pair : *table)
      {
          file << (uint8_t)pair.first << " " << pair.second << "\n";
      }
      return 1;
}

}


#endif // HELPERS_HPP

#include "huffman.cpp"

int main(int argc, char ** argv)
{
    if( argc != 3 )
        {
            std::cout << "Invalid usage!" << std::endl;
            return 1;
        }
    map< uint8_t , int >* frequencyTable;

    frequencyTable = help::getFrequencyTable(argv[1]); /* ../data/NORMAL2-IM-1427-0001.pgm */
//    help::printFrequencyTable(frequencyTable);
    help::writeFrequencyTable(argv[2] , frequencyTable);


//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
}

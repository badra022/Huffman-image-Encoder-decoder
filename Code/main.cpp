#include "huffman.hpp"

int main(/*int argc, char ** argv*/)
{
//    if( argc != 5 )
//        {
//            std::cout << "Invalid usage!" << std::endl;
//            return 1;
//        }

    /* imagepath , encodedpath , frequencyTablepath , testpath */
    encodeImage("../data/NORMAL2-IM-1430-0001.pgm","../encoded.enc","../frequency.frq" ,"../originalback.pgm");

    //decodeCompressedData("../decodedImage.pgm" , "../encoded.enc","../frequency.frq");

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
}

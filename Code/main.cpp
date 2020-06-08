#include "huffman.hpp"

int main(int argc, char ** argv)
{
    if( argc != 5 )
        {
            std::cout << "Invalid usage!" << std::endl;
            return 1;
        }

    /* imagepath , encodedpath , frequencyTablepath */
    encodeImage(argv[1],argv[2],argv[3] , argv[4]);


//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
}

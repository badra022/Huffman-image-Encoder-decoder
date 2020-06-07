/***************************************
 * [file name]: heap
 *
 * [type]:	header file
 *
 * [PROJECT]:	huffman encoding
 *
 * [CREATOR]:	Ahmed mohamed mohamed mohamed
 * *************************************/

/*************************************************************************
 * 			              	GUARDFILE
 * **********************************************************************/
#ifndef HEAP_HPP
#define HEAP_HPP
/*************************************************************************
 *                              INCLUDES
 * **********************************************************************/
#include <vector>
#include <iostream>
/*************************************************************************
 *                              DECLARATIONS
 * **********************************************************************/
template< typename T >
class pQueue
{
public:
    void traverseHeap(void(*pf)(T value));
    size_t size() const;
    void insert(T value);
    T extract();
private:
    void siftUp( size_t child );
    void siftDown( size_t parent);
    static size_t leftChildIdx(size_t parent);
    static size_t rightChildIdx(size_t parent);
    static size_t parentIdx(size_t child);
    std::vector<T> data;
};

#endif // HEAP_HPP

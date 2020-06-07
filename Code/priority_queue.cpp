/***************************************
 * [file name]: heap
 *
 * [type]:	source file
 *
 * [PROJECT]:	huffman encoding
 *
 * [CREATOR]:	Ahmed mohamed mohamed mohamed
 * *************************************/

 /*************************************************************************
  *                              INCLUDES
  * **********************************************************************/
#include "priority_queue.hpp"
/*************************************************************************
 *                              DEFINITIONS
 * **********************************************************************/
template< typename T >
void pQueue<T>::traverseHeap(void(*pf)(T value))
{
    for(int i = data.begin() ; i != data.end() ; i++)
    {
        pf(data[i]);
    }
}

template< typename T >
size_t pQueue < T >::size() const
{
    return data.size();
}

template< typename T >
void pQueue < T >::insert(T value)
{
    data.push_back(value);
    size_t childIdx = size() - 1;
    siftUp( childIdx );
}

template< typename T >
T pQueue < T >::extract()
{
    if( data.empty())
    {
        std::cout << "Empty Heap!\n";
        exit( 1 ); // Crash
    }
    size_t child = size() - 1;
    std::swap(data[child], data[0]);
    T value = data.back();
    data.pop_back();
    siftDown(0);
    return value;
}

template< typename T >
void pQueue < T >::siftUp( size_t child )
{
    auto parent = parentIdx(child);
    if( child > 0  && data[child]->frq < data[parent]->frq)
    {
        std::swap(data[child], data[parent]);
        siftUp( parent );
    }
}

template< typename T >
void pQueue < T >::siftDown( size_t parent)
{
    size_t left = leftChildIdx(parent);
    size_t right = rightChildIdx(parent);
    size_t length = size();
    size_t minimum = parent;

    if (left < length && data[left]->frq < data[minimum]->frq)
        minimum = left;

    if (right < length && data[right]->frq < data[minimum]->frq)
        minimum = right;

    if (minimum != parent)
    {
        std::swap(data[minimum], data[parent]);
        siftDown( minimum);
    }
}

template< typename T >
size_t pQueue < T >::leftChildIdx(size_t parent)
{
    return parent * 2 + 1;
}

template< typename T >
size_t pQueue < T >::rightChildIdx(size_t parent)
{
    return parent * 2 + 2;
}

template< typename T >
size_t pQueue < T >::parentIdx(size_t child)
{
    if (child % 2 == 1)
        return (child - 1) / 2;
    else
        return (child - 2) / 2;
}

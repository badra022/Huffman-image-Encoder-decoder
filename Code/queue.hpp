/***************************************
 * [file name]: queue
 *
 * [type]:	header file
 *
 * [LAYER]:	First Layer
 *
 * [PROJECT]:	hospital information system
 *
 * [CREATOR]	Ahmed mohamed mohamed mohamed
 * *************************************/
 /*************************************************************************
 * 				GUARDFILE
 * **********************************************************************/
#ifndef _STACK_HPP_
#define _STACK_HPP_
/*************************************************************************
 *                              INCLUDES
 * **********************************************************************/
#include<iostream>
#include <vector>
/*************************************************************************
 *                              DECLARATIONS
 * **********************************************************************/
#define MAX_SIZE 500

template< typename T  >
class queue
{
public:
    void TraverseQueue(void (*pf)(T var));
    bool find(long long Id);
    bool isEmpty() const;
    T front() const;
    T dequeue();
    void enqueue( T value );
private:
    bool isFull() const;
    std::vector<T> data;
    int front_ = 0, rear_ = 0;
};

#endif

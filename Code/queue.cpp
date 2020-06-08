/***************************************
 * [file name]: queue
 *
 * [type]:	source file
 *
 * [LAYER]:	First Layer
 *
 * [PROJECT]:	hospital information system
 *
 * [CREATOR]:   Ahmed mohamed mohamed mohamed
 * *************************************/
/*************************************************************************
 *                              INCLUDES
 * **********************************************************************/
#include"queue.hpp"
/*************************************************************************
 *                              DEFINITIONS
 * **********************************************************************/
template< typename T>
void queue<T>::TraverseQueue(void (*pf)(T var))
{
    for(int i = this->front_; i != this->rear_  ;i = (i + 1) % MAX_SIZE){
    (*pf)(this->data[i]);
    }
}
template<typename T>
bool queue<T>::find(long long Id)
{
     for(int i = this->front_; i != this->rear_  ;i = (i + 1) % MAX_SIZE)
     {
          if(this->data[i]->ID == Id)return true;
     }
     return false;
}
template< typename T>
    bool queue<T>::isEmpty() const
    {
        return front_ == rear_;
    }
template< typename T>
T queue<T>::front() const
{
   if( isEmpty()) exit( 1 ); // Crash
   return data[front_];
}
template< typename T>
T queue<T>::dequeue()
{
   if( isEmpty()) exit( 1 ); // Crash
   return data[front_];
   front_ =(front_ + 1) % MAX_SIZE;
}
template< typename T>
void queue<T>::enqueue( T value ){
   if( isFull()) exit( 1 ); // Crash.
   data[rear_] = value;
   rear_ = (rear_+1) % MAX_SIZE;
}
template< typename T>
bool queue<T>::isFull() const
{
   return (rear_ + 1) % MAX_SIZE == front_;
}

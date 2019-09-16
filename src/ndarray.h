


#ifndef NDARRAY_H
#define NDARRAY_H


#include "data.h"
#include <cassert>
#include <iostream>



namespace np{
  
  template <typename T>
  class ndarray : public data
  {
    public :
      typedef T* iterator;
      ndarray():_start(nullptr),_finish(nullptr),_end_of_storage(nullptr)
      {}
      ndarray(size_t size,T data=T()){
        _start = new T [size*sizeof(T)];
        for(size_t i =0;i<size;i++){
          _start[i]=data;
        }
        _finish=_start+size;
        _end_of_storage=_start+size;
      }
      ndarray(const ndarray<T>& array){
        _start = new T[sizeof(T)*array.capacity()];
        for(size_t i=0;i<array.size();i++){
          _start[i]=array._start[i];
        }
        _finish=_start+array.size();
        _end_of_storage=_start+array.capacity();
      }
      ~ndarray(){
        if(_start != nullptr){
          delete [] _start;
        }
      }

      ndarray<T> & operator=(const ndarray<T> & array){
        if(*this != array){
          if(_start != nullptr){
            delete[] _start;
          }
          _start = new T[sizeof(T)*array.capacity()];
          for(size_t i=0;i<array.size();i++){
            _start[i]=array._start[i];
          }
          _finish=_start+array.size();
          _end_of_storage=_start+array.capacity();
        }
        return *this;
      }

      void print(){
        for(size_t i=0;i<size();i++){
          std::cout<<*(_start+i)<<" ";
        }
        std::cout<<std::endl;
      }

    protected:
      size_t size()const{
        return _finish - _start;
      }

      size_t capacity()const{
        return _end_of_storage - _start;
      }

      bool isempty()const{
        return _start == _finish;
      }

      void clear()const{
        _finish = _start;
      }

      iterator begin(){
        return _start;
      }

      iterator end(){
        return _finish;
      }

      T & front(){
        assert(_start != nullptr);
        return *_start;
      }

      T & back(){
        assert(_finish != nullptr);
        return *(_finish-1);
      }

      void swap(ndarray<T> & array){
        iterator _tmp;
        _tmp=array._start;array._start=_start;_start=_tmp;
        _tmp=array._finish;array._finish=_finish;_finish=_tmp;
        _tmp=array._end_of_storage;array._end_of_storage=_end_of_storage;_end_of_storage=_tmp;
      }


    private:
      iterator _start;
      iterator _finish;
      iterator _end_of_storage;

      
  };
}


#endif




#ifndef NDARRAY_H
#define NDARRAY_H


#include "data.h"
#include <cassert>
#include <iostream>
#include <vector>



namespace np{
  
  template <typename T>
  class ndarray : public data
  {
    public :
      typedef T* iterator;
      ndarray():_start(nullptr),_finish(nullptr),_end_of_storage(nullptr),_ndim(0)
      {}
      ndarray(size_t size,T data=T()){
        _start = new T [size*sizeof(T)];
        for(size_t i =0;i<size;i++){
          _start[i]=data;
        }
        _finish=_start+size;
        _end_of_storage=_start+size;
        _ndim=1;
        _shape.push_back(size);

      }
      ndarray(const ndarray<T>& array){
        _start = new T[sizeof(T)*array.capacity()];
        for(size_t i=0;i<array.size();i++){
          _start[i]=array._start[i];
        }
        _finish=_start+array.size();
        _end_of_storage=_start+array.capacity();
        _ndim=array._ndim;
        _shape=array._shape;
      }
      ~ndarray(){
        if(_start != nullptr){
          delete [] _start;
        }
      }

      ndarray<T> & operator=(const ndarray<T> & array){
        if(this != &array){
          std::cout<<"*this != array"<<std::endl;
          if(_start != nullptr){
            delete[] _start;
          }
          _start = new T[sizeof(T)*array.capacity()];
          for(size_t i=0;i<array.size();i++){
            _start[i]=array._start[i];
          }
          _finish=_start+array.size();
          _end_of_storage=_start+array.capacity();
          _ndim=array._ndim;
          _shape=array._shape;
        }
        else{
          std::cout<<"*this == array"<<std::endl;
        }
        return *this;
      }

      size_t ndim()const;
      std::vector<size_t> shape()const{
        return _shape;
      }
      size_t size()const{
        return _finish - _start;
      }
      size_t itemsize()const{
        return sizeof(T);
      }
      iterator data(){
        return _start;
      }

      void print_data(){
        std::cout<<"data:[ ";
        for(size_t i=0;i<size();i++){
          std::cout<<*(_start+i)<<", ";
        }
        std::cout<<"]"<<std::endl;
      }
      void print_shape(){
        std::cout<<"shape:[ ";
        for(size_t i=0;i<_shape.size();i++){
          std::cout<<_shape[i]<<", ";
        }
        std::cout<<"]"<<std::endl;
      }

    protected:

      size_t capacity()const{
        return _end_of_storage - _start;
      }

      bool isempty()const{
        return _start == _finish;
      }

      void clear()const{
        _finish = _start;
        _ndim=0;
        _shape.clear();
        _shape.push_back(0);
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
        size_t dim;
        dim=array._ndim;array._ndim=_ndim;_ndim=dim;
        std::vector<T> sha;
        sha=array._shape;array._shape=_shape;_shape=sha;

      }


    private:
      iterator _start;
      iterator _finish;
      iterator _end_of_storage;
      size_t _ndim;
      std::vector<size_t> _shape;
      

      
  };


  template<typename T>
  size_t ndarray<T>:: ndim()const{
    return _ndim;
  }



}


#endif

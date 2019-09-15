
#ifndef NDARRAY_H
#define NDARRAY_H

#include <>

namespace std{
  
  template <typename T>
  class ndarray{
    public :
      typedef T* iterator;
      ndarray():_begin(nullptr),_end(nullptr),_finish(nullptr)
      {}
      ndarray(size_t size,T data=T()){
        _begin = new T [size*sizeof(T)];
        for(size_t i =0;i<size;i++){
          _begin[i]=data;
        }
        _end=_begin+size;
        _finish=_begin+size;
      }
      ndarray(){
        
      }

    private:
      iterator _begin;
      iterator _end;
      iterator _finish;
      
  }
}


#endif

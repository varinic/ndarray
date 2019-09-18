


#ifndef NDARRAY_H
#define NDARRAY_H


#include "data.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>



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
        _suffix_product=array._suffix_product;
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
          _suffix_product=array._suffix_product;
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

      void empty(std::vector<size_t> &Shape);
      void zeros(std::vector<size_t> &Shape);
      void ones(std::vector<size_t> &Shape);
      void asarray(std::vector<size_t> &Shape){
        empty(Shape);
      }
      void arange(size_t st,size_t ed,size_t step);
      void arange(size_t stop);
      //void T();
      void reshape(std::vector<size_t> &Shape);
      T & at(size_t x0)const;
      T & at(size_t x0,size_t x1)const;
      T & at(size_t x0,size_t x1,size_t x2)const;
      T & at(size_t x0,size_t x1,size_t x2,size_t x3)const;
      T & at(size_t x0,size_t x1,size_t x2,size_t x3,size_t x4)const;
      T & at(size_t x0,size_t x1,size_t x2,size_t x3,size_t x4,size_t x5)const;
      T & at(size_t x0,size_t x1,size_t x2,size_t x3,size_t x4,size_t x5,size_t x6)const;

      void _print_data(size_t depth,size_t count,size_t cnt,size_t tot,std::string str){
        if(depth+1==_ndim){
          if(cnt==0)
            std::cout<<"[";
          else
            std::cout<<str<<"[";
          for(size_t i=0;i<_shape[depth];i++){
            std::cout<<_start[count+i]<<", ";
          }
          if(cnt+1==tot)
            std::cout<<"]";
          else
            std::cout<<"]"<<std::endl;
        }
        else{
          if(cnt==0)
            std::cout<<"[";
          else
            std::cout<<str<<"[";
          size_t sum=1;
          for(size_t i=depth+1;i<_shape.size();i++){
            sum*=_shape[i];
          }
          for(size_t i=0;i<_shape[depth];i++){
            _print_data(depth+1,count+sum*i,i,_shape[depth],str+" ");
          }
          if(cnt+1==tot)
            std::cout<<"]";
          else
            std::cout<<"]"<<std::endl;
        }

      }
      void print_data(){
        if(_shape.size()==0){
          std::cout<<"no data"<<std::endl;
          return ;
        }
        std::cout<<"data:"<<std::endl;
        _print_data(0,0,0,0,"");
      }
      void print_rawdata(){
        std::cout<<"rawdata:[ ";
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
      void print_all(){
        std::cout<<std::endl;
        std::cout<<"{"<<std::endl;
        print_shape();
        print_data();
        std::cout<<"ndim: "<<_ndim<<std::endl;
        std::cout<<"size: "<<size()<<std::endl;
        std::cout<<"dtype: "<<dtype()<<std::endl;
        std::cout<<"itemsize: "<<itemsize()<<std::endl;
        std::cout<<"}"<<std::endl;
        std::cout<<std::endl;

      }

    protected:

      size_t capacity()const{
        return _end_of_storage - _start;
      }

      bool isempty()const{
        return _start == _finish;
      }

      void clear(){
        _finish = _start;
        _ndim=0;
        _shape.clear();
        _suffix_product.clear();
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
        std::vector<size_t> sha;
        sha=array._shape;array._shape=_shape;_shape=sha;
        std::vector<size_t> suf;
        suf=array._suffix_product;array._suffix_product=_suffix_product;_suffix_product=suf;

      }


    private:
      iterator _start;
      iterator _finish;
      iterator _end_of_storage;
      size_t _ndim;
      std::vector<size_t> _shape;
      std::vector<size_t> _suffix_product;
      

      
  };


  template<typename T>
  size_t ndarray<T>:: ndim()const{
    return _ndim;
  }

  template<typename T>
  void ndarray<T>:: empty(std::vector<size_t> &Shape){
    _ndim = Shape.size();
    _shape=Shape;
    
    size_t product=1;
    for(size_t i=_ndim-1;i>0;i--){
      product*=Shape[i];
      _suffix_product.push_back(product);
    }
    std::reverse(_suffix_product.begin(),_suffix_product.end());

    size_t size_ndarray=1;
    for(size_t i=0;i<_ndim;i++){
      size_ndarray*=Shape[i];
    }
    if(_start != nullptr){
      delete[] _start;
    }
    _start = new T[sizeof(T)*size_ndarray];
    srand(233);
    for(size_t i=0;i<size_ndarray;i++){
      _start[i]=(T)((rand()%10000)*1.0/100.0);
    }
    _finish=_start+size_ndarray;
    _end_of_storage=_start+size_ndarray;

  }
  template<typename T>
  void ndarray<T>:: ones(std::vector<size_t> &Shape){
    _ndim = Shape.size();
    _shape=Shape;
    
    size_t product=1;
    for(size_t i=_ndim-1;i>0;i--){
      product*=Shape[i];
      _suffix_product.push_back(product);
    }
    std::reverse(_suffix_product.begin(),_suffix_product.end());

    size_t size_ndarray=1;
    for(size_t i=0;i<_ndim;i++){
      size_ndarray*=Shape[i];
    }
    if(_start != nullptr){
      delete[] _start;
    }
    _start = new T[sizeof(T)*size_ndarray];
    for(size_t i=0;i<size_ndarray;i++){
      _start[i]=1;
    }
    _finish=_start+size_ndarray;
    _end_of_storage=_start+size_ndarray;

  }
  template<typename T>
  void ndarray<T>:: zeros(std::vector<size_t> &Shape){
    _ndim = Shape.size();
    _shape=Shape;
    
    size_t product=1;
    for(size_t i=_ndim-1;i>0;i--){
      product*=Shape[i];
      _suffix_product.push_back(product);
    }
    std::reverse(_suffix_product.begin(),_suffix_product.end());

    size_t size_ndarray=1;
    for(size_t i=0;i<_ndim;i++){
      size_ndarray*=Shape[i];
    }
    if(_start != nullptr){
      delete[] _start;
    }
    _start = new T[sizeof(T)*size_ndarray];
    for(size_t i=0;i<size_ndarray;i++){
      _start[i]=0;
    }
    _finish=_start+size_ndarray;
    _end_of_storage=_start+size_ndarray;

  }

  template<typename T>
  void ndarray<T>:: arange(size_t st,size_t ed,size_t step){
    assert(st<=ed && 1<=step);
    _ndim=1;
    size_t size_ndarray=0;
    if( (ed-st)%step ==0){
      size_ndarray=(ed-st)/step;
    }
    else{
      size_ndarray=(ed-st)/step+1;
    }
    _shape.clear();
    _shape.push_back(size_ndarray);
    if(_start != nullptr){
      delete[] _start;
    }
    _start = new T[sizeof(T)*size_ndarray];
    size_t cnt=0;
    for(size_t i=st;i<ed;i+=step){
      _start[cnt++]=(T)(i);
    }
    assert(cnt==size_ndarray);
    _finish=_start+size_ndarray;
    _end_of_storage=_start+size_ndarray;

  }
  template<typename T>
  void ndarray<T>:: arange(size_t stop){
    assert( 1<=stop);
    _ndim=1;
    _shape.clear();
    _shape.push_back(stop);
    if(_start != nullptr){
      delete[] _start;
    }
    _start = new T[sizeof(T)*stop];
    for(size_t i=0;i<stop;i++){
      _start[i]=(T)(i);
    }
    _finish=_start+stop;
    _end_of_storage=_start+stop;
  }

  /*
  template<typename T>
  void ndarray<T>:: T(){
    assert(_ndim==2);
  }
  */
  template<typename T>
  void ndarray<T>:: reshape(std::vector<size_t> &Shape){
    size_t size_ndarray=1;
    for(size_t i=0;i<Shape.size();i++){
      size_ndarray*=Shape[i];
    }
    assert(size()==size_ndarray);
    _ndim = Shape.size();
    _shape=Shape;
    
    size_t product=1;
    for(size_t i=_ndim-1;i>0;i--){
      product*=Shape[i];
      _suffix_product.push_back(product);
    }
    std::reverse(_suffix_product.begin(),_suffix_product.end());

    
    //if(_start != nullptr){
    //  delete[] _start;
    //}
    //_start = new T[sizeof(T)*size_ndarray];
    //for(size_t i=0;i<size_ndarray;i++){
    //  _start[i]=0;
    //}
    //_finish=_start+size_ndarray;
    //_end_of_storage=_start+size_ndarray;

  }

  template<typename T>
  T & ndarray<T>:: at(size_t x0)const{
    assert(_ndim==1 && 0<=x0 && x0<size());
    return _start[x0];
  }
  template<typename T>
  T & ndarray<T>:: at(size_t x0,size_t x1)const{
    assert(_ndim==2 && 0<=x0 && x0<_shape[0] && 0<=x1 && x1<_shape[1]);
    return _start[x0*_suffix_product[0]+x1];
  }
  template<typename T>
  T & ndarray<T>:: at(size_t x0,size_t x1,size_t x2)const{
    assert(_ndim==3 && 0<=x0 && x0<_shape[0] && 0<=x1 && x1<_shape[1] && 0<=x2 && x2<_shape[2]);
    return _start[x0*_suffix_product[0]+x1*_suffix_product[1]+x2];
  }
  template<typename T>
  T & ndarray<T>:: at(size_t x0,size_t x1,size_t x2,size_t x3)const{
    assert(_ndim==4 && 0<=x0 && x0<_shape[0] && 0<=x1 && x1<_shape[1] && 0<=x2 && x2<_shape[2] 
                    && 0<=x3 && x3<_shape[3]);
    return _start[x0*_suffix_product[0]+x1*_suffix_product[1]+x2*_suffix_product[2]+x3];
  }
  template<typename T>
  T & ndarray<T>:: at(size_t x0,size_t x1,size_t x2,size_t x3,size_t x4)const{
    assert(_ndim==5 && 0<=x0 && x0<_shape[0] && 0<=x1 && x1<_shape[1] && 0<=x2 && x2<_shape[2] 
                    && 0<=x3 && x3<_shape[3] && 0<=x4 && x4<_shape[4]);
    return _start[x0*_suffix_product[0]+x1*_suffix_product[1]+x2*_suffix_product[2]+x3*_suffix_product[3]+x4];
  }
  template<typename T>
  T & ndarray<T>:: at(size_t x0,size_t x1,size_t x2,size_t x3,size_t x4,size_t x5)const{
    assert(_ndim==6 && 0<=x0 && x0<_shape[0] && 0<=x1 && x1<_shape[1] && 0<=x2 && x2<_shape[2] 
                    && 0<=x3 && x3<_shape[3] && 0<=x4 && x4<_shape[4] && 0<=x5 && x5<_shape[5]);
    return _start[x0*_suffix_product[0]+x1*_suffix_product[1]+x2*_suffix_product[2]+x3*_suffix_product[3]
                 +x4*_suffix_product[4]+x5];
  }
  template<typename T>
  T & ndarray<T>:: at(size_t x0,size_t x1,size_t x2,size_t x3,size_t x4,size_t x5,size_t x6)const{
    assert(_ndim==7 && 0<=x0 && x0<_shape[0] && 0<=x1 && x1<_shape[1] && 0<=x2 && x2<_shape[2] 
                    && 0<=x3 && x3<_shape[3] && 0<=x4 && x4<_shape[4] && 0<=x5 && x5<_shape[5]
                    && 0<=x6 && x6<_shape[6]);
    return _start[x0*_suffix_product[0]+x1*_suffix_product[1]+x2*_suffix_product[2]+x3*_suffix_product[3]
                 +x4*_suffix_product[4]+x5*_suffix_product[5]+x6];
  }


}


#endif

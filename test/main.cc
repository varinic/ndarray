
#include "../ndarray"
#include "../src/debug.h"


int main(){

  using np::ndarray;

  static ndarray<np::int64> a(5,4);
  a.print_data();
  std::cout<<a.name()<<std::endl;
  std::cout<<a.dtype()<<std::endl;
  
  ndarray<np::int64> b(a);
  b.print_data();

  using np::data;
  std::cout<<data::int32()<<std::endl;

  a.dtype(data::int64());
  std::cout<<a.dtype()<<std::endl;

  ndarray<np::int64> c;
  c=b;
  c=c;

  a.print_data();
  ndarray<np::int64> d(4,3);
  d.print_data();
  

  ndarray<np::int32> e;
  print(e.size());
  print(e.ndim());

  ndarray<np::float64> f(10,9.9);
  print(f.ndim());
  print(f.size());
  print(f.dtype());
  print(f.itemsize());
  f.print_data();
  np::float64* buffer=f.data();
  for(size_t i=0;i<f.size();i++){
    print(buffer[i]);
  }
  f.print_shape();



  return 0;

}

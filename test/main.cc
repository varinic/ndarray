
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

  std::vector<size_t> shape {3,4};

  ndarray <np::float64> g;
  g.empty(shape);
  g.print_all();
  g.ones(shape);
  g.print_all();
  g.zeros(shape);
  g.print_all();
  g.arange(10);
  g.print_all();
  g.arange(1,10,2);
  g.print_all();
  for(size_t i=0;i<5;i++){
    printcm(g.at(i));
  }
  println();

  ndarray <np::float64> h;
  h.arange(72);
  std::vector<size_t> shape1 {2,3,4,3};
  h.reshape(shape1);
  h.print_all();
  for(size_t i=0;i<2;i++){
    for(size_t j=0;j<3;j++){
      for(size_t k=0;k<4;k++){
        for(size_t l=0;l<3;l++){
          printcm(h.at(i,j,k,l));
        }
    println();
      }
    println();
    }
    println();
  }
  std::vector<size_t> shape11 {8,9};
  h.reshape(shape11);
  h.print_all();

  ndarray <np::float64> p;
  p.arange(6);
  std::vector<size_t> shape2 {2,3};
  p.reshape(shape2);
  p.print_all();
  for(size_t i=0;i<2;i++){
    for(size_t j=0;j<3;j++){
      printcm(p.at(i,j));
    }
    println();
  }



  return 0;

}

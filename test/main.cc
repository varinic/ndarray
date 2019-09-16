
#include "../ndarray"


int main(){

  //np::ndarray<np::float64> a();
  //std::cout<<np::ndarray.int64()<<std::endl;
  //std::cout<<a.int64()<<std::endl;
  using np::ndarray;

  static ndarray<np::int64> a(5,4);

  
  using np::data;
  std::cout<<data::int32()<<std::endl;
  a.print();

  return 0;

}

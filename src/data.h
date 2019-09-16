
#ifndef DATA_H
#define DATA_H


#include <string>
#include "Type.h"

namespace np{

  //template<typename T>
  class data {
    private :
      std::string _dtype;
      std::string _name;

    public:
      data(){
        _dtype="unknown";
        _name="unnamed";
      }
      ~data(){}
      void name(std::string t_name){
        _name=t_name;
      }
      std::string name(){
        return _name;
      }
      void dtype(std::string t_dtype){
        _dtype=t_dtype;
      }
      std::string dtype(){
        return _dtype;
      }
      void asdata(std::string t_dtype,std::string t_name){
        _dtype=t_dtype;
        _name=t_name;
      }
      
      static std::string int64(){
        return "int64";
      }
      static std::string int32(){
        return "int32";
      }
      static std::string uint64(){
        return "uint64";
      }
      static std::string uint32(){
        return "uint32";
      }
      static std::string float64(){
        return "float64";
      }
      static std::string float32(){
        return "float32";
      }
      /*
      string float16(){
        return "float16";
      }
      */

  };


}

#endif

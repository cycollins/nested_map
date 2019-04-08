//
//  main.cpp
//  nested_map
//
//  Created by David Collins on 4/7/19.
//
//  MIT License
//
//  Copyright (c) 2019 David Collins
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//
//  Just a toy data structure, but I thought it was a useful example of recursive variadic
//  template metaprogramming of containers.
//

#include <iostream>
#include <unordered_map>

template<typename T, typename K, typename ... KS> struct nested_map_base : std::unordered_map<K, T>
{
  T &operator[](const K &key)
  {
    return this->std::unordered_map<K, T>::operator[](key);
  }
};

template<typename T, typename New_K, typename K, typename ... KS>
struct nested_map_base<T, New_K, K, KS ...>
: std::unordered_map<New_K, nested_map_base<T, K, KS...>>
{
  nested_map_base<T, K, KS...> &operator[](const New_K &new_key)
  {
    return this->std::unordered_map<New_K, nested_map_base<T, K, KS...>>::operator[](new_key);
  }
};

template<typename datum_type, typename ... keys> class nested_map
{
private:
  nested_map_base<datum_type, keys ...> backing_store;
  
public:
  template<typename Base_key, typename ... KS> auto &operator[](const Base_key &key)
  {
    return backing_store[key];
  }
};

void method1()
{
  std::cout << "Method1:" << std::endl << std::endl;
  nested_map<int, std::string, double, int> test_nest;
  std::cout << "insert" << std::endl;
  test_nest["leonard"][4.8][45] = 111;
  std::cout << "retrieve" << std::endl;
  int &answer = test_nest["leonard"][4.8][45];
  std::cout << "Answer should be 111. Answer is " << answer << std::endl << std::endl;
}

void method2()
{
  std::cout << "Method2:" << std::endl << std::endl;
  nested_map_base<int, std::string, double, int> test_nest;
  std::cout << "insert" << std::endl;
  test_nest["leonard"][4.8][45] = 111;
  std::cout << "retrieve" << std::endl;
  int &answer = test_nest["leonard"][4.8][45];
  std::cout << "Aanswer should be 111. Answer is " << answer << std::endl << std::endl;
}

int main(int argc, const char * argv[]) {
  method1();
  method2();
  
  return 0;
}

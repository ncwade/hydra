#include <iostream>
#include "hydra.hpp"

using namespace std::literals;

bool print_str(std::string data) 
{
    std::cout << data << std::endl;
    return true;
}

bool print_str1(std::string data)
{
    std::cout << "1 "<< data << std::endl;
    return true;
}

bool publishData(std::atomic<bool> &exit, Hydra<std::string> &parent)
{
    while(!exit) {
        parent.push_data("/hello/world","test from thread 1");
        std::this_thread::sleep_for(2s);
    }
    return true;
}

int main() 
{
  Hydra<std::string> vonStrucker(2);
  vonStrucker.subscribe("/hello/world", print_str);
  vonStrucker.subscribe("/hello/world", print_str1);
  vonStrucker.push_data("/hello/world","test");
  vonStrucker.enlist(publishData);
  std::this_thread::sleep_for(5s);
  return 0;
}

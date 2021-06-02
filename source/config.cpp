/*
*   config.cpp
*
*   @author Ryan Morehouse
*   @date June 2, 2021
*
*/

#include "config.h"

// open config file and parse config options as strings
Config::Config(std::string url) {
  std::ifstream file(url);

  if(file.is_open()) {
    for(std::string text; getline(file, text); ) {
      int position = text.find(" = ");
      std::string name = text.substr(0, position);
      std::string value = text.substr(position+3);

      this->options[name] = value;
    }
  }

}

// access config option by name
std::string Config::getOption(std::string name) {
  return this->options[name];
}

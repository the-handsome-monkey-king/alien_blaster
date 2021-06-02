/*
*   config.h
*
*   @author Ryan Morehouse
*   @date June 2, 2021
*
*   @purpose a class to encapsulate the loading, storing, and accessing
*   config options.
*
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>
#include <fstream>

class Config {
  private:
    std::map<std::string, std::string> options;
  public:
    Config(std::string url);

    std::string getOption(std::string name);
};

#endif

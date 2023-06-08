#include "Config.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <stdexcept>

Config::Config(std::string path)
{
  std::ifstream file{ path };
  if (!file.good()) {
    std::cout << "not good\n";
    throw std::runtime_error{"No config file provided!"};
  }
  nlohmann::json data;
  file >> data;
  file.close();
  speed = data.value("speed", -1) == -1 ? 0.f : data.at("speed").get<float>();
}

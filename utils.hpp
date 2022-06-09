#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "BinarySearchTree.hpp"

bool doesVectorContains(const std::vector< std::string >& vector, const std::string& element);
bool readFiles(std::vector< std::string >& files, std::vector < std::string >& dictNames,
  std::map< std::string, BinarySearchTree< std::string, std::size_t > >& dictOfDicts);
bool makeSubstring(std::string& temp);
std::vector< std::string > splitString(const std::string& str);
void makeFreqDict(BinarySearchTree< std::string, std::size_t >& dict, const std::vector < std::string >& words);
void help();
bool find(const std::string& word, const BinarySearchTree< std::string, std::size_t >& dict);
void search(const std::string& word, std::map< std::string, BinarySearchTree< std::string, std::size_t > >& dictOfDicts);
bool insert(std::string& word, const std::size_t& freq, BinarySearchTree< std::string, std::size_t >& dict);
bool isNumber(const std::string& word);
void deleteFunc(const std::string& word, BinarySearchTree< std::string, std::size_t >& dict);
void deleteFunc(BinarySearchTree< std::string, std::size_t >& dict,
  std::map< std::string, BinarySearchTree< std::string, std::size_t > >& dictOfDicts);
void clear(std::vector< std::string >& files, std::vector < std::string >& dictNames,
  std::map< std::string, BinarySearchTree< std::string, std::size_t > >& dictOfDicts);
void print(const BinarySearchTree< std::string, std::size_t >& dict);
void list(const std::map< std::string, BinarySearchTree< std::string, std::size_t > >& dictOfDicts);
bool compare(const std::string& word, const BinarySearchTree< std::string, std::size_t >& dict1,
  const BinarySearchTree< std::string, std::size_t >& dict2);
void top(BinarySearchTree< std::string, std::size_t > dict, int pos);
void showFreq(const std::string& word, const BinarySearchTree< std::string, std::size_t >& dict);

#endif

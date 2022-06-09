#include "utils.hpp"

bool doesVectorContains(const std::vector< std::string >& vector, const std::string& element)
{
  for (std::size_t i = 0; i < vector.size(); i++)
  {
    if (vector[i] == element)
    {
      return true;
    }
  }

  return false;
}

bool readFiles(std::vector< std::string >& files, std::vector < std::string >& dictNames,
  std::map< std::string, BinarySearchTree< std::string, std::size_t > >& dictOfDicts)
{
  for (std::size_t i = 0; i < files.size(); i++)
  {
    if (dictOfDicts.find(dictNames[i]) != dictOfDicts.end())
    {
      continue;
    }
    std::ifstream text(files[i]);
    if (text.is_open() == false)
    {
      std::cerr << "File \"" << files[i] << "\" is not open!\n";
      return false;
    }
    std::string str = "";
    std::getline(text, str);
    for (std::string i; std::getline(text, i); )
    {
      str = str + " " + i;
    }
    text.close();
    BinarySearchTree< std::string, std::size_t > dict;
    makeFreqDict(dict, splitString(str));
    dictOfDicts.insert_or_assign(dictNames[i], dict);
  }

  return true;
}

bool makeSubstring(std::string& temp)
{
  if (temp[0] == '.' || temp[0] == ',' || temp[0] == '!' || temp[0] == '?')
  {
    return false;
  }

  if (temp[0] == '(' || temp[0] == '[' || temp[0] == '{' || temp[0] == '"')
  {
    temp = temp.substr(1, temp.size());

    if (temp[temp.size()] == ')' || temp[temp.size()] == ']' ||
      temp[temp.size()] == '}' || temp[temp.size()] == '"')
    {
      temp = temp.substr(1, temp.size() - 1);
    }
    else if (temp[temp.size() - 1] == '.' || temp[temp.size() - 1] == ',' ||
      temp[temp.size() - 1] == '!' || temp[temp.size() - 1] == '?')
    {
      temp = temp.substr(1, temp.size() - 2);
    }
  }
  else if (temp[temp.size()] == ')' || temp[temp.size()] == ']' ||
    temp[temp.size()] == '}' || temp[temp.size()] == '"')
  {
    if (temp[temp.size() - 1] == '.' || temp[temp.size() - 1] == ',' ||
      temp[temp.size() - 1] == '!' || temp[temp.size() - 1] == '?')
    {
      temp = temp.substr(0, temp.size() - 2);
    }
    else
    {
      temp = temp.substr(0, temp.size() - 1);
    }
  }
  else if (temp[temp.size()] == '.' || temp[temp.size()] == ',' ||
    temp[temp.size()] == '!' || temp[temp.size()] == '?')
  {
    temp = temp.substr(0, temp.size() - 1);
  }

  return true;
}

std::vector< std::string > splitString(const std::string& str)
{
  std::vector< std::string > words;

  std::size_t begin = 0;
  std::size_t end = str.find(' ', begin);
  std::string temp = "";
  while (end != -1)
  {
    temp = str.substr(begin, end - begin);
    if (makeSubstring(temp) == false)
    {
      continue;
    }

    words.push_back(temp);

    begin = end + 1;
    end = str.find(' ', begin);
  }

  temp = str.substr(begin);
  if (makeSubstring(temp) == true)
  {
    words.push_back(temp);
  }

  return words;
}

void makeFreqDict(BinarySearchTree< std::string, std::size_t >& dict, const std::vector < std::string >& words)
{
  std::size_t freq = 1;
  for (std::size_t i = 0; i < words.size(); i++)
  {
    if (dict.searchKey(words[i]) == false)
    {
      for (std::size_t j = i + 1; j < words.size(); j++)
      {
        if (words[i] == words[j])
        {
          freq += 1;
        }
      }
      dict.insert(words[i], freq);
      freq = 1;
    }
  }
}

void help()
{
  std::cout << "Available commands:\n";
  std::cout << "help\nfind [word] [dict] - search a word in one dict\nsearch [word] - search a word in all dicts\n";
  std::cout << "insert [word] [freq] [dict] - insert a word with its freq in dict if the word is unique\n";
  std::cout << "delete [word] [dict]- delete a word from a dict\ndelete [dict] - clear a dict\n";
  std::cout << "clear - clear all dicts\n";
  std::cout << "print [dict] - print a dict\nlist - print a list of dicts\n";
  std::cout << "compare [word] [dict1] [dict2] - compare freq of a word in two dicts\n";
  std::cout << "topThree [dict] - print 3 words with the biggest freqs\n";
  std::cout << "showFreq [word] [dict] - show freq of the word in the dict\n";
  std::cout << "makeFreqTable [file] [name_of_dict] - make freq dict\n";
}

bool find(const std::string& word, const BinarySearchTree< std::string, std::size_t >& dict)
{
  return dict.searchKey(word);
}

void search(const std::string& word, std::map< std::string, BinarySearchTree< std::string, std::size_t > >& dictOfDicts)
{
  BinarySearchTree< std::string, std::size_t > tempDict;

  bool check = false;
  for (std::map< std::string, BinarySearchTree< std::string, std::size_t > >::const_iterator
    dictsIterator = dictOfDicts.cbegin(); dictsIterator != dictOfDicts.cend(); dictsIterator++)
  {
    tempDict = dictsIterator->second;
    if (find(word, tempDict) == true)
    {
      if (check == false)
      {
        std::cout << "\"" << word << "\" is found in " << dictsIterator->first;
        check = true;
      }
      else
      {
        std::cout << ", " << dictsIterator->first;
      }
    }
  }
  if (check == false)
  {
    std::cout << "No \"" << word << "\" in all dicts\n";
  }
  else
  {
    std::cout << "\n";
  }
}

bool insert(std::string& word, const std::size_t& freq, BinarySearchTree< std::string, std::size_t >& dict)
{
  if (dict.insert(word, freq) == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool isNumber(const std::string& word)
{
  for (std::size_t i = 0; i < word.size(); i++)
  {
    if (word[i] < '0' || word[i] > '9')
    {
      return false;
    }
  }

  return true;
}

void deleteFunc(const std::string& word, BinarySearchTree< std::string, std::size_t >& dict)
{
  dict.erase(word);
}

void deleteFunc(BinarySearchTree< std::string, std::size_t >& dict,
  std::map< std::string, BinarySearchTree< std::string, std::size_t > >& dictOfDicts)
{
  for (std::map< std::string, BinarySearchTree< std::string, std::size_t > >::iterator
    dictsIterator = dictOfDicts.begin(); dictsIterator != dictOfDicts.end(); dictsIterator++)
  {
    if (dictsIterator->second == dict)
    {
      dictOfDicts.erase(dictsIterator->first);
      break;
    }
  }
}

void clear(std::vector< std::string >& files, std::vector < std::string >& dictNames,
  std::map< std::string, BinarySearchTree< std::string, std::size_t > >& dictOfDicts)
{
  dictOfDicts.clear();
  while (files.empty() == false)
  {
    files.pop_back();
    dictNames.pop_back();
  }
}

void print(const BinarySearchTree< std::string, std::size_t >& dict)
{
  dict.inorderWalk();
}

void list(const std::map< std::string, BinarySearchTree< std::string, std::size_t > >& dictOfDicts)
{
  bool check = false;
  for (std::map< std::string, BinarySearchTree< std::string, std::size_t > >::const_iterator
    dictsIterator = dictOfDicts.cbegin(); dictsIterator != dictOfDicts.cend(); dictsIterator++)
  {
    std::cout << "Name of dict: " << dictsIterator->first << "\nDict: ";
    print(dictsIterator->second);
    std::cout << "\n";
    check = true;
  }
  if (check == false)
  {
    std::cout << "There is not any dict\n";
  }
}

bool compare(const std::string& word, const BinarySearchTree< std::string, std::size_t >& dict1,
  const BinarySearchTree< std::string, std::size_t >& dict2)
{
  if (dict1.findKey(word)->value_ >= dict2.findKey(word)->value_)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void top(BinarySearchTree< std::string, std::size_t > dict, int pos)
{
  dict.remake().top(pos);
}

void showFreq(const std::string& word, const BinarySearchTree< std::string, std::size_t >& dict)
{
  std::cout << "Freq of word \"" << dict.findKey(word)->key_ << "\" is " << dict.findKey(word)->value_ << "\n";
}

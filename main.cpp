#include "utils.hpp"

int main()
{
  std::vector< std::string > files;
  files.push_back("Test-First.txt");
  files.push_back("Test-Second.txt");
  files.push_back("Test-Third.txt");

  std::vector< std::string > dictNames;
  dictNames.push_back("first");
  dictNames.push_back("second");
  dictNames.push_back("third");

  std::map< std::string, BinarySearchTree< std::string, std::size_t > > dictOfDicts;
  if (readFiles(files, dictNames, dictOfDicts) == false)
  {
    std::cout << "Exit...\n";
    return -1;
  }

  std::string strOfArgs = "";
  std::vector< std::string > args;
  std::string cmd = "";
  std::string word = "";
  std::size_t freq = 0;
  std::string nameOfDict1 = "";
  std::string nameOfDict2 = "";

  while (std::getline(std::cin, strOfArgs))
  {
    args = splitString(strOfArgs);
    if (args.empty() == true)
    {
      continue;
    }
    cmd = args[0];

    if (cmd == "help")
    {
      if (args.size() != 1)
      {
        continue;
      }
      help();
    }
    else if (cmd == "find")
    {
      if (args.size() != 3)
      {
        continue;
      }
      word = args[1];
      nameOfDict1 = args[2];
      if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end())
      {
        if (find(word, dictOfDicts.find(nameOfDict1)->second))
        {
          std::cout << "\"" << word << "\" is found\n";
        }
        else
        {
          std::cout << "No \"" << word << "\" in dict \"" << nameOfDict1 << "\"\n";
        }
      }
      else
      {
        std::cerr << "Dict \"" << nameOfDict1 << "\" is not found\n";
      }
    }
    else if (cmd == "search")
    {
      if (args.size() != 2)
      {
        continue;
      }
      word = args[1];
      search(word, dictOfDicts);
    }
    else if (cmd == "insert")
    {
      if (args.size() != 4)
      {
        continue;
      }
      else if (isNumber(args[2]) == false)
      {
        std::cerr << "Invalid freq\n";
      }
      else if (makeSubstring(word) == false)
      {
        std::cerr << "Invalid word\n";
      }
      else
      {
        word = args[1];
        freq = std::stoull(args[2]);
        nameOfDict1 = args[3];
        if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end())
        {
          if (insert(word, freq, dictOfDicts.find(nameOfDict1)->second) == true)
          {
            std::cout << "Insertion completed successfully\n";
          }
          else
          {
            std::cerr << "Insertion failed\n";
          }
        }
        else
        {
          std::cerr << "Dict \"" << nameOfDict1 << "\" is not found\n";
        }
      }
    }
    else if (cmd == "delete")
    {
      if (args.size() == 3)
      {
        word = args[1];
        nameOfDict1 = args[2];
        if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end())
        {
          if (find(word, dictOfDicts.find(nameOfDict1)->second))
          {
            deleteFunc(word, dictOfDicts.find(nameOfDict1)->second);
            std::cout << "Word \"" << word << "\" was deleted\n";
          }
          else
          {
            std::cerr << "There is not \"" << word << "\" in dict \"" << nameOfDict1 << "\"\n";
          }
        }
        else
        {
          std::cerr << "There is not dict \"" << nameOfDict1 << "\"\n";
        }
      }
      else if (args.size() == 2)
      {
        nameOfDict1 = args[1];
        if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end())
        {
          deleteFunc(dictOfDicts.find(nameOfDict1)->second, dictOfDicts);
          std::cout << "\"" << nameOfDict1 << "\" dict was deleted\n";
        }
        else
        {
          std::cerr << "There is not dict \"" << nameOfDict1 << "\"\n";
        }
      }
      else
      {
        continue;
      }
    }
    else if (cmd == "clear")
    {
      if (args.size() != 1)
      {
        continue;
      }
      clear(files, dictNames, dictOfDicts);
      std::cout << "All dicts were deleted\n";
    }
    else if (cmd == "print")
    {
      if (args.size() != 2)
      {
        continue;
      }
      nameOfDict1 = args[1];
      if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end())
      {
        print(dictOfDicts.find(nameOfDict1)->second);
      }
      else
      {
        std::cerr << "There is not dict \"" << nameOfDict1 << "\"\n";
      }
    }
    else if (cmd == "list")
    {
      if (args.size() != 1)
      {
        continue;
      }
      list(dictOfDicts);
    }
    else if (cmd == "compare")
    {
      if (args.size() != 4)
      {
        continue;
      }
      word = args[1];
      nameOfDict1 = args[2];
      nameOfDict2 = args[3];
      if (dictOfDicts.find(nameOfDict1) == dictOfDicts.end())
      {
        std::cerr << "There is not dict \"" << nameOfDict1 << "\"\n";
      }
      else if (dictOfDicts.find(nameOfDict2) == dictOfDicts.end())
      {
        std::cerr << "There is not dict \"" << nameOfDict2 << "\"\n";
      }
      else if (dictOfDicts.find(nameOfDict1)->second.findKey(word) == nullptr &&
        dictOfDicts.find(nameOfDict2)->second.findKey(word) == nullptr)
      {
        std::cerr << "There is not \"" << word << "\" in both dicts\n";
      }
      else if (dictOfDicts.find(nameOfDict1)->second.findKey(word) == nullptr)
      {
        std::cerr << "There is not \"" << word << "\" in dict \"" << nameOfDict1 << "\"\n";
      }
      else if (dictOfDicts.find(nameOfDict2)->second.findKey(word) == nullptr)
      {
        std::cerr << "There is not \"" << word << "\" in dict \"" << nameOfDict2 << "\"\n";
      }
      else if (compare(word, dictOfDicts.find(nameOfDict1)->second, dictOfDicts.find(nameOfDict2)->second))
      {
        if (compare(word, dictOfDicts.find(nameOfDict2)->second, dictOfDicts.find(nameOfDict1)->second))
        {
          std::cout << "Freq of word \"" << word << "\" in dict \"" << nameOfDict1
            << "\" and in dict \"" << nameOfDict2 << "\" is equal\n";
        }
        else
        {
          std::cout << "Freq of word \"" << word << "\" in dict \"" << nameOfDict1
            << "\" is bigger than in dict \"" << nameOfDict2 << "\"\n";
        }
      }
      else
      {
        std::cout << "Freq of word \"" << word << "\" in dict \"" << nameOfDict1
          << "\" is smaller than in dict \"" << nameOfDict2 << "\"\n";
      }
    }
    else if (cmd == "topThree")
    {
      if (args.size() != 2)
      {
        continue;
      }
      nameOfDict1 = args[1];
      if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end())
      {
        int pos = 3;
        top(dictOfDicts.find(nameOfDict1)->second, pos);
      }
      else
      {
        std::cerr << "There is not dict \"" << nameOfDict1 << "\"\n";
      }
    }
    else if (cmd == "showFreq")
    {
      if (args.size() != 3)
      {
        continue;
      }
      word = args[1];
      nameOfDict1 = args[2];
      if (dictOfDicts.find(nameOfDict1) != dictOfDicts.end())
      {
        if (dictOfDicts.find(nameOfDict1)->second.findKey(word) != nullptr)
        {
          showFreq(word, dictOfDicts.find(nameOfDict1)->second);
        }
        else
        {
          std::cerr << "There is not word \"" << word << "\" in dict \"" << nameOfDict1 << "\"\n";
        }
      }
      else
      {
        std::cerr << "There is not dict \"" << nameOfDict1 << "\"\n";
      }
    }
    else if (cmd == "makeFreqTable")
    {
      if (args.size() != 3)
      {
        continue;
      }
      word = args[1];
      nameOfDict1 = args[2];
      if (doesVectorContains(files, word) == true)
      {
        std::cerr << "File \"" << word << "\" was opened before\n";
      }
      else if (doesVectorContains(dictNames, nameOfDict1) == true)
      {
        std::cerr << "Dict with name \"" << nameOfDict1 << "\" is already exists. Enter other name\n";
      }
      else
      {
        files.push_back(word);
        dictNames.push_back(nameOfDict1);
        if (readFiles(files, dictNames, dictOfDicts) == true)
        {
          std::cout << "Freq dict with name \"" << nameOfDict1 << "\" has been made\n";
        }
        else
        {
          files.pop_back();
          dictNames.pop_back();
        }
      }
    }
    else if (cmd == "exit")
    {
      break;
    }
  }

  return 0;
}

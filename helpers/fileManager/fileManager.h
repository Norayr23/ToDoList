#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "../taskClass/taskClass.h"

#include <string>
#include <fstream>
#include <iostream>

class FileManager {
public:
  explicit FileManager(const std::string& fileName) : m_fileName(fileName), separator(" ,./,./ ") {}
  template <template<typename...> class Container>
  void saveToFile(const Container<Task>& cont) const;
  template <template<typename...> class Container>
  void loadFromFile(Container<Task>& cont) const;
  void setFileName(const std::string& fileName);
  const std::string& getFileName() const;
private:
  std::string m_fileName;
  const std::string separator;
};
inline void FileManager::setFileName(const std::string& name) { m_fileName = name; }
inline const std::string& FileManager::getFileName() const { return m_fileName; }
template <template<typename...> class Container>
inline void FileManager::saveToFile(const Container<Task>& cont) const {
   std::ofstream file;
   file.open(getFileName());
   if (!file.is_open()) {
    throw std::ios_base::failure("Failed to open the file.");
   }
   for (const Task& task : cont) {
    file << task.toString(separator)  << " " << std::to_string(task.isDone()) << '\n';  
   }
   file.close();
}
template <template<typename...> class Container>
inline void FileManager::loadFromFile(Container<Task>& cont) const {
   std::ifstream file(getFileName());
   if (!file.is_open()) {
    throw std::ios_base::failure("Failed to open the file.");
   }
   std::string line; 
   for (int i = 0; !file.eof() ; ) {
     Task tmp;
     getline(file, line);
     int firstSepIndex = line.find(separator);
     if (firstSepIndex == std::string::npos) {
        continue;
     }
     tmp.setTitle(line.substr(0, firstSepIndex));
     int secondSepIndex = line.find(separator, firstSepIndex + 1);
     if (secondSepIndex == std::string::npos) {
        continue;
     }
     tmp.setMessage(line.substr(firstSepIndex  + separator.length(), secondSepIndex - firstSepIndex - separator.length()));
     int lastSpaceIndex = line.find_first_of("\t ", secondSepIndex  + separator.length());
     if (lastSpaceIndex == std::string::npos) {
        cont.push_back(tmp);
     }
     tmp.setDedline(line.substr(secondSepIndex  + separator.length(), lastSpaceIndex - secondSepIndex - separator.length()));
     if (line.back() == '1') {
        tmp.makeDone();
     }
     cont.push_back(tmp);
     line.clear();
   }
   file.close();
}

#endif

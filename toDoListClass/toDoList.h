#ifndef TO_DO_LIST_H
#define TO_DO_LIST_H

#include "../helpers/fileManager/fileManager.h"

#include <deque>
#include <map>

class ToDoList {
public:
  ToDoList();
  void run();
  ~ToDoList();
private:
  enum class Keyword;
  std::deque<Task> m_tasks;
  void addTask(const Task&);
  void removeTask(const int index);
  int findTask(const std::string& title, const int startIndex);
  const Task& getTask(const int index);
  void print();
  const std::string fileName;
  FileManager m_fm;
  std::map<Keyword, void (ToDoList::*)()> m_keyWords;
  //Working with User
  void addUs();
  void removeUs();
  void searchUs();
  void changeUs();
  void makeDoneUs();
  void makeUndoneUs();
  int findFromInputUs();  
};

#endif

#include "toDoList.h"

#include <iostream>
#include <map>
#include <limits>
#include <thread>



bool getNum(const std::string str, int& dest) {
	dest = 0;				
	int d = 1;
    int start = str[0] == '-' ? 1 : 0;
	for (int i = str.length() - 1; i >= start; i --) {
		if (str[i] < '0' || str[i] > '9') {
            dest = 0;
		    return false;
	    }								
		dest += d * (str[i] - '0');
		d *= 10;
	}
    dest *= start ? -1 : 1;								
	return true;
}    
enum class ToDoList::Keyword {
  Add = 1,
  Delete = 2,
  Find = 3,
  Change = 4,
  MakeDone = 5,
  MakeUndone = 6,
  Exit = 7,
};
ToDoList::ToDoList() : fileName("tasks.txt"), m_fm(fileName) {
  m_tasks.clear();
  m_fm.loadFromFile(m_tasks);
  m_keyWords[Keyword::Add] = &ToDoList::addUs;
  m_keyWords[Keyword::Delete] = &ToDoList::removeUs;
  m_keyWords[Keyword::Find] = &ToDoList::searchUs;
  m_keyWords[Keyword::Change] = &ToDoList::changeUs;
  m_keyWords[Keyword::MakeDone] = &ToDoList::makeDoneUs;
  m_keyWords[Keyword::MakeUndone] = &ToDoList::makeUndoneUs;
}
ToDoList::~ToDoList() { m_fm.saveToFile(m_tasks); }
void ToDoList::addTask(const Task& task) { m_tasks.push_back(task); }
void ToDoList::removeTask(const int index) { m_tasks.erase(m_tasks.begin() + index); }
int ToDoList::findTask(const std::string& title, const int startIndex) {
  for (int i = startIndex; i < m_tasks.size(); ++i) {
      if (getTask(i).getTitle() == title) {
        return i;
      }
  }
  return -1;
}
int ToDoList::findFromInputUs() {
   std::cout << "Please enter task number or title: ";
   std::string answer;
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   getline(std::cin, answer);
   int num;
   if (getNum(answer, num) && num >= 0 && num < m_tasks.size()) {
    return num;
   }
   num = findTask(answer, 0);
   if (num != -1) {
    return num; 
   }
   return -1;
}
const Task& ToDoList::getTask(const int index) { return m_tasks[index]; }
void ToDoList::print() {
  system("clear");
  std::cout << "To Do List:\n\n"  << std::endl;
  std::cout << "\n1: Add task  2: Delete task 3: Search task 4: Change task 5: MakeDone 6: MakeUndone 7: Exit\n\n" << std::endl;
  for (size_t i = 0; i < m_tasks.size(); ++i) {
    const Task& cur = getTask(i);
    std::string doneMessage = cur.isDone() ? "Finished" : "Unfinished";
    std::cout << i << ": " << "Title: " << cur.getTitle() << "  Message: " << 
    cur.getMessage() << "  Dedline: " << cur.getDedline() << "   " << doneMessage << "\n" << std::endl;
  }
}
void ToDoList::run() {
  while(true) {
    print();
    int input = 0;
    std::cin.clear();
    std::cin >> input;
    if (m_keyWords[(Keyword)input]) {
       (this->*m_keyWords[(Keyword)input])();
    }
    else if (input == (int)Keyword::Exit) {
      std::cout << "Do you want exit the programm? (y/n): ";
      std::string ans;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      getline(std::cin, ans);
      if (ans == "y") {
        return;
      }
    }
    else {
      std::cout << "ivailid input" << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
   
  }
}  
void ToDoList::addUs() {
  Task task;
  std::cout << "For canceling enter cancel" << std::endl;
  std::cout << "Please enter task title: ";
  std::string tmp;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  getline(std::cin, tmp);
  if (tmp == "cancel") {
     return;
  }
  task.setTitle(tmp);
  std::cout << "Please enter task message: ";
  tmp.clear();
  getline(std::cin, tmp);
   if (tmp == "cancel") {
     return;
  }
  task.setMessage(tmp);
  std::cout << "Please enter task dedline: ";
  tmp.clear();
  getline(std::cin, tmp);
   if (tmp == "cancel") {
     return;
  }
  task.setDedline(tmp);
  m_tasks.push_back(task);

}
void ToDoList::removeUs() {
  const int index = findFromInputUs();
  if ( index != -1) {
    std::cout << "Do you want remove  " << getTask(index).toString(" ") << "  ? (y/n): ";
    std::string ans;
    std::cin.clear();
    getline(std::cin, ans);
    if (ans == "y") {
      removeTask(index); 
    }  
  }
  else {
    std::cout << "task not found" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

}
void ToDoList::searchUs() {
  const int index = findFromInputUs();
  if (index != -1) {
    std::cout << index << ": " << getTask(index).toString(" ") << std::endl;
    std::cin.get();
  }
  else {
    std::cout << "task not found" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

}
void ToDoList::changeUs() {
  const int index = findFromInputUs();
  if (index != -1) {
    std::cout << "Please enter new properties for Task: " << getTask(index).toString(" ") << std::endl;
    const size_t initSize = m_tasks.size();
    addUs();
    if (initSize < m_tasks.size()) {
      removeTask(index);
    }

  }
  else {
    std::cout << "task not found" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  } 
}
void ToDoList::makeDoneUs() {
  int index = findFromInputUs();
  if (index != -1) {
    getTask(index).makeDone();
  }
  else {
    std::cout << "task not found" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
void ToDoList::makeUndoneUs() {
  int index = findFromInputUs();
  if (index != -1) {
    getTask(index).makeUnDone();
  }
  else {
    std::cout << "task not found" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}


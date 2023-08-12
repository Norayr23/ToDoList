#ifndef TASK_CLASS_H
#define TASK_CLASS_H

#include <string>

class Task {
public:
  Task();
  Task(const std::string& title, const std::string& message, std::string dedline);
  bool isTitleExist() const;
  bool isMessageExist() const;
  bool isDedlineExist() const;
  void setMessage(std::string message);
  const std::string& getMessage() const;
  void setTitle(std::string title);
  const std::string& getTitle() const;
  bool setDedline(std::string dedline);
  const std::string& getDedline() const;
  std::string toString(const std::string& separator) const;
  void makeDone() const;
  void makeUnDone() const;
  bool isDone() const;
private:
  bool m_isDedline;
  bool m_isTitle;
  bool m_isMessage;
  mutable bool m_done;
  static bool isDedlineValid(const std::string& dedline);
  std::string m_dedline;
  std::string m_message;
  std::string m_title;
  static void trim(std::string& str);
};

#endif


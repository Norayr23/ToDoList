#include "taskClass.h"

#include <string>
#include <algorithm>

Task::Task() : m_done(false) {
   setMessage("None");
   setTitle("None");
   setDedline("None");
}
Task::Task(const std::string& title, const std::string& message, std::string dedline) : m_done(false) {
    setMessage(message);
    setTitle(title);
    if (!setDedline(dedline)) {
        setDedline("None");
    }
} 
                                                                   
void Task::setMessage(std::string ms) {
    trim(ms);
    if (ms == "" || ms == "None") {
       m_message = "None";
       m_isMessage = false;
       return;
    }
    m_isMessage = true; 
    m_message = ms; 
}
const std::string& Task::getMessage() const { return m_message; }
void Task::setTitle(std::string tl) {
    trim(tl);
    if (tl == "" || tl == "None") {
        m_title = "None";
        m_isTitle = false;
        return;
    }
    m_isTitle = true; 
    m_title = tl; 
}
const std::string& Task::getTitle() const { return m_title; }
bool Task::setDedline(std::string dedline) {
    dedline.erase(std::remove_if(dedline.begin(), dedline.end(), [](char c) {
        return c == ' ' || c == '\t';
    }), dedline.end());
    if (dedline == "" || dedline == "None") {
        m_dedline = "None";
        m_isDedline = false;
        return true;
    }
    if (isDedlineValid(dedline)) {
        m_dedline = dedline;
        m_isDedline = true;
        return true;
    }
    return false;
}
const std::string& Task::getDedline() const { return m_dedline; }
std::string Task::toString(const std::string& sep) const {
    return getTitle() + sep + getMessage() + sep + getDedline();
}
void Task::makeDone() const { m_done = true; }
void Task::makeUnDone() const { m_done = false; }
bool Task::isDone() const { return m_done;}
bool Task::isMessageExist() const { return m_isMessage; }
bool Task::isTitleExist() const { return m_isTitle; }
bool Task::isDedlineExist() const { return m_isDedline; }
//Helper Function getNumber()
bool getNumber(const std::string str, int& dest) {
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
bool Task::isDedlineValid(const std::string& date) {
    int firstSlash = date.find_first_of('/');
    if (firstSlash == std::string::npos) {
        return false;
    }
    std::string dayStr = date.substr(0, firstSlash);
    int day;
    if (!getNumber(dayStr, day) || (day > 31 || day < 1)) {
        return false;
    }
    int secondSlash = date.find_first_of('/', firstSlash) + firstSlash + 1;
    if (secondSlash == std::string::npos) {
        return false;
    }
    std::string monthStr = date.substr(firstSlash + 1, secondSlash - firstSlash - 1);
    int month = 0;
    if (!getNumber(monthStr, month) || (month < 1 || month > 12)) {
        return false;
    }
    std::string yearStr = date.substr(secondSlash + 1);
    int year;
    if (!getNumber(yearStr, year) || year < 0 || year > 2100) {
        return false;
    } 
    return true;

}
void Task::trim(std::string& str) {
   int start = str.find_first_not_of(" \t");
   if (start == std::string::npos) {
    str = "";
    return;
   }
   int end = str.find_last_not_of("\t ");
   str = str.substr(start, (end - start + 1));
}



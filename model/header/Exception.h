#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <QString>

class Exception  {
  private:
    QString error_msg;
  public:
    Exception() {};
    Exception(const QString& err_msg) : error_msg(err_msg) {}
    virtual const QString what() const throw() { return error_msg; };
};

class Data_Exception : public Exception {
  public:
    Data_Exception() : Exception() {};
    Data_Exception(const QString& err_msg) : Exception(err_msg) {}
};

class Err_File_Handling : public Exception {
  public:
    Err_File_Handling() : Exception() {};
    Err_File_Handling(const QString& s) : Exception(s) {}
};

class Queue_Exception : public Exception {
  public:
    Queue_Exception() : Exception() {}
    Queue_Exception(const QString& s) : Exception(s) {}
};

class Err_Empty_Queue : public Queue_Exception {
  public:
    Err_Empty_Queue() : Queue_Exception() {};
    Err_Empty_Queue(const QString& s) : Queue_Exception(s) {}
};

class Err_Bad_Iterator : public Queue_Exception {
  public:
    Err_Bad_Iterator() : Queue_Exception() {};
    Err_Bad_Iterator(const QString& s) : Queue_Exception(s) {}
};

#endif // EXCEPTION_H

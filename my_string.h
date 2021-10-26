#ifndef MY_STRING_H_
#define MY_STRING_H_

#include "string"

class String {
 public:
  String();
  explicit String(const char *c_str);
  String(int count, char ch);
  String(const String &other_str);
  String(String &&other_str) noexcept;
  String &operator=(const String &other_str);
  String &operator=(String &&other_str) noexcept ;
  ~String();

  [[nodiscard]] int length() const;
  [[nodiscard]] bool empty() const;
  [[nodiscard]] char *c_str() const;

  char &operator[](int i);
  const char &operator[](int i) const;

  char &front();
  [[nodiscard]] const char &front() const;
  char &back();
  [[nodiscard]] const char &back() const;

  void reserve(int capacity);
  void push_back(char ch);
  void pop_back();
  void clear();

  void insert(int index, const String &str);
  void insert(int index, const char *str, int count);
  void erase(int index, int count = 1);

  [[nodiscard]] int compare(const String &str) const;
  int compare(const char *str) const;

  String operator+(const String &other_str) const;
  String &operator+=(const String &other_str);

  bool operator<(const String &rhs) const;
  bool operator>(const String &rhs) const;
  bool operator<=(const String &rhs) const;
  bool operator>=(const String &rhs) const;
  bool operator==(const String &rhs) const;
  bool operator!=(const String &rhs) const;

  bool operator<(const char *rhs) const;
  bool operator>(const char *rhs) const;
  bool operator<=(const char *rhs) const;
  bool operator>=(const char *rhs) const;
  bool operator==(const char *rhs) const;
  bool operator!=(const char *rhs) const;

  friend bool operator<(const char *lhs, const String &rhs);
  friend bool operator>(const char *lhs, const String &rhs);
  friend bool operator<=(const char *lhs, const String &rhs);
  friend bool operator>=(const char *lhs, const String &rhs);
  friend bool operator==(const char *lhs, const String &rhs);
  friend bool operator!=(const char *lhs, const String &rhs);

 private:
  int size_;
  int capacity_;
  char *str_;
};

#endif  // MY_STRING_H_

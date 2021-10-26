#ifndef MY_STRING_VIEW_H_
#define MY_STRING_VIEW_H_

#include <iostream>
#include <limits>
#include <numeric>

class StringView {
 public:
  static constexpr int npos = std::numeric_limits<int>::max();

  StringView() = default;
  explicit StringView(const char *str, int count = npos);

  int length() const;
  bool empty() const;
  const char *data() const;
  const char &operator[](int index) const;
  const char &at(int index) const;

  bool starts_with(StringView v) const;
  bool ends_with(StringView v) const;

  void remove_prefix(int count);
  void remove_suffix(int count);

  StringView substr(int pos, int count = npos);

  int find(StringView v, int pos = 0);
  int find(char ch, int pos = 0);

  int compare(const StringView &str) const;
  int compare(const char *str) const;

  bool operator<(const StringView &rhs) const;
  bool operator>(const StringView &rhs) const;
  bool operator<=(const StringView &rhs) const;
  bool operator>=(const StringView &rhs) const;
  bool operator==(const StringView &rhs) const;
  bool operator!=(const StringView &rhs) const;

 private:
  const char *str_ = nullptr;
  int size_ = 0;
};

#endif  // MY_STRING_VIEW_H_

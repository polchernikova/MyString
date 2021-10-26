#include "my_string_view.h"
#include <algorithm>
#include <string>
#include <cstring>

StringView::StringView(const char *str, int count) {
  size_t actual = std::min(static_cast<size_t>(count), strlen(str));
  size_ = actual;
  str_ = str;
}

int StringView::length() const {
  return size_;
}
bool StringView::empty() const {
  return (size_ == 0);
}
const char *StringView::data() const {
  return str_;
}

const char &StringView::operator[](int index) const {
  return str_[index];
}
const char &StringView::at(int index) const {
  if ((index >= size_) || (index < 0)) {
    throw std::out_of_range("Invalid index");
  }
  return str_[index];
}

bool StringView::starts_with(StringView v) const {
  if (v.length() > size_) {
    return false;
  }
  for (int i = 0; i < v.length(); i++) {
    if (v[i] != str_[i]) {
      return false;
    }
  }
  return true;
}
bool StringView::ends_with(StringView v) const {
  if (v.length() > size_) {
    return false;
  }
  for (int i = 0; i < v.length(); i++) {
    if (str_[size_ - i - 1] != v[v.length() - i - 1]) {
      return false;
    }
  }
  return true;
}

void StringView::remove_prefix(int count) {
  str_ = str_ + count;
  size_ = size_ - count;
}

void StringView::remove_suffix(int count) {
  size_ = size_ - count;
}

StringView StringView::substr(int pos, int count) {
  int actual = std::min(count, size_ - pos);
  StringView new_string_view = *this;
  new_string_view.remove_prefix(pos);
  new_string_view.size_ = actual;
  return new_string_view;
}

int StringView::find(StringView v, int pos) {
  for (int i = pos; i <= size_ - v.size_; i++) {
    int right_str = true;
    for (int j = 0; j < v.size_; j++) {
      if (str_[i + j] != v[j]) {
        right_str = false;
        break;
      }
    }
    if (right_str) {
      return i;
    }
  }
  return npos;
}

int StringView::find(char ch, int pos) {
  for (int i = pos; i < size_; i++) {
    if (str_[i] == ch) {
      return i;
    }
  }
  return npos;
}

int StringView::compare(const StringView &str) const {
  int lhs_size = size_;
  int rhs_size = str.size_;
  for (int i = 0; i < std::min(lhs_size, rhs_size); i++) {
    if (str_[i] < str[i]) {
      return -1;
    } else if (str_[i] > str[i]) {
      return 1;
    }
  }
  if (lhs_size < rhs_size) {
    return -1;
  }
  if (lhs_size > rhs_size) {
    return 1;
  }
  return 0;
}
int StringView::compare(const char *str) const {
  StringView temp(str);
  return compare(temp);
}


bool StringView::operator<(const StringView &rhs) const {
  return (compare(rhs) == -1);
}
bool StringView::operator>(const StringView &rhs) const {
  return (compare(rhs) == 1);
}
bool StringView::operator<=(const StringView &rhs) const {
  return (compare(rhs) != 1);
}
bool StringView::operator>=(const StringView &rhs) const {
  return (compare(rhs) != -1);
}
bool StringView::operator==(const StringView &rhs) const {
  return (compare(rhs) == 0);
}
bool StringView::operator!=(const StringView &rhs) const {
  return (compare(rhs) != 0);
}

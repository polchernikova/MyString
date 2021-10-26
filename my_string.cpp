#include <utility>
#include <algorithm>
#include <cstring>

#include "my_string.h"

String::String() : size_(1), capacity_(1) {
    str_ = new char[1];
    str_[0] = '\0';
}

String::String(const char *c_str) : String() {
    for (int i = 0; c_str[i] != '\0'; i++) {
        this->push_back(c_str[i]);
    }
}

String::String(int count, char ch) : size_(count + 1), capacity_(size_ * 2) {
    str_ = new char[capacity_];
    while (count--) {
        str_[size_ - count - 2] = ch;
    }
    str_[size_ - 1] = '\0';
}

String::String(const String &other_str) : size_(other_str.size_), capacity_
        (other_str.capacity_) {
    str_ = new char[capacity_];
    strncpy(str_, other_str.str_, other_str.size_);
    str_[size_ - 1] = '\0';
}

String::String(String &&other_str)  noexcept : size_(other_str.size_), capacity_
        (other_str.capacity_), str_(other_str.str_) {
    other_str.str_ = new char[1];
    other_str[0] = '\0';
    other_str.size_ = 1;
    other_str.capacity_ = 1;
}

String &String::operator=(const String &other_str) {
    if (this->str_ == other_str.str_) {
        return *this;
    }
    delete[] str_;
    size_ = other_str.size_;
    capacity_ = other_str.capacity_;
    str_ = new char[capacity_];
    strncpy(str_, other_str.str_, capacity_);
    return *this;
}

String &String::operator=(String &&other_str) noexcept {
    if (this->str_ == other_str.str_) {
        return *this;
    }
    delete[] str_;
    size_ = other_str.size_;
    capacity_ = other_str.capacity_;
    str_ = other_str.str_;
    other_str.str_ = new char[1];
    other_str.str_[0] = '\0';
    other_str.size_ = 1;
    other_str.capacity_ = 1;
    return *this;
}

String::~String() {
    delete[] str_;
}

int String::length() const {
    return (size_ - 1);
}

bool String::empty() const {
    return (size_ == 1);
}

char *String::c_str() const {
    return str_;
}

char &String::operator[](int i) {
    return str_[i];
}

const char &String::operator[](int i) const {
    return str_[i];
}

char &String::front() {
    return str_[0];
}

const char &String::front() const {
    return str_[0];
}

char &String::back() {
    return str_[size_ - 2];
}

const char &String::back() const {
    return str_[size_ - 2];
}

void String::reserve(int capacity) {
    if (this->capacity_ >= capacity) {
        return;
    }
    capacity_ = capacity;
    char *new_str = new char[capacity_];
    strncpy(new_str, str_, size_);
    new_str[size_ - 1] = '\0';
    std::swap(new_str, str_);
    delete[] new_str;
}

void String::push_back(char ch) {
    reserve(size_ + 1);
    size_++;
    str_[size_ - 2] = ch;
    str_[size_ - 1] = '\0';
}

void String::pop_back() {
    size_ = size_ - 1;
    str_[size_ - 1] = '\0';
}

void String::clear() {
    erase(0, size_ - 1);
}

void String::insert(int index, const String &str) {
    reserve(size_ + str.length());
    for (int i = size_ - 2; i >= index; i--) {
        str_[i + str.length()] = str_[i];
    }
    for (int i = index; i < index + str.length(); i++) {
        str_[i] = str[i - index];
    }
    size_ = size_ + str.length();
    str_[size_ - 1] = '\0';
}

void String::insert(int index, const char *str, int count) {
    String in_str(str);
    in_str.size_ = count + 1;
    in_str.str_[count] = '\0';
    insert(index, in_str);
}

void String::erase(int index, int count) {
    int actual = std::min(count, length() - index);
    for (int i = index; i < size_ - actual; i++) {
        str_[i] = str_[i + actual];
    }
    size_ = size_ - actual;
}

int String::compare(const String &str) const {
    return strcmp(str_, str.str_);
}

int String::compare(const char *str) const {
    return strcmp(str_, str);
}

String String::operator+(const String &other_str) const {
    String result;
    result.reserve(size_ + other_str.length());
    strncpy(result.str_, str_, size_);
    strncpy(result.str_ + size_ - 1, other_str.str_, other_str.size_);
    result.size_ = size_ + other_str.length();
    return result;
}

String &String::operator+=(const String &other_str) {
    reserve(size_ + other_str.length());
    strncpy(str_ + size_ - 1, other_str.str_, other_str.size_);
    size_ = size_ + other_str.length();
    return *this;
}

bool String::operator<(const String &rhs) const {
    return (compare(rhs) < 0);
}

bool String::operator>(const String &rhs) const {
    return (compare(rhs) > 0);
}

bool String::operator<=(const String &rhs) const {
    return (compare(rhs) <= 0);
}

bool String::operator>=(const String &rhs) const {
    return (compare(rhs) >= 0);
}

bool String::operator==(const String &rhs) const {
    return (compare(rhs) == 0);
}

bool String::operator!=(const String &rhs) const {
    return (compare(rhs) != 0);
}

bool String::operator<(const char *rhs) const {
    return (compare(rhs) < 0);
}

bool String::operator>(const char *rhs) const {
    return (compare(rhs) > 0);
}

bool String::operator<=(const char *rhs) const {
    return (compare(rhs) <= 0);
}

bool String::operator>=(const char *rhs) const {
    return (compare(rhs) >= 0);
}

bool String::operator==(const char *rhs) const {
    return (compare(rhs) == 0);
}

bool String::operator!=(const char *rhs) const {
    return (compare(rhs) != 0);
}

bool operator<(const char *lhs, const String &rhs) {
    return (rhs > lhs);
}

bool operator>(const char *lhs, const String &rhs) {
    return (rhs < lhs);
}

bool operator<=(const char *lhs, const String &rhs) {
    return (rhs >= lhs);
}

bool operator>=(const char *lhs, const String &rhs) {
    return (rhs <= lhs);
}

bool operator==(const char *lhs, const String &rhs) {
    return (rhs == lhs);
}

bool operator!=(const char *lhs, const String &rhs) {
    return (rhs != lhs);
}

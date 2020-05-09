#include "vnpch.h"
#include "Core/String/String.h"

namespace Vein
{

    String::String()
    {
        _length = 0;
        _data = new char('\0');
    }

    String::String(char c)
    {
        _length = 1;
        _data = new char[_length + 1];
        _data[0] = c;
        _data[1] = '\0';
    }

    String::String(const char* c)
    {
        if (c)
        {
            size_t n = 0;
            while (c[n] != '\0') n++;
            _length = n;
            _data = new char[n + 1];
            strcpy(_data, c);
        }
        else
        {
            _length = 0;
            _data = new char[0];
        }
    }

    String::String(const String& s)
    {
        _length = s.length();
        _data = new char[_length + 1];
        strcpy(_data, s._data);
    }

    String::String(char* s, size_t l)
    {
        _length = l;
        _data = s;
    }

    String::~String()
    {
        delete[] _data;
    }


    const char* String::c_str() const
    {
        return _data;
    }

    const size_t String::begin() const {
        return 0;
    }
    const size_t String::end() const {
        return _length;
    }

    size_t String::length() const
    {
        return _length;
    }

    String String::replace(const String& str, const String& with)
    {
        char* old_data = _data;
        char* new_data;
        char* ins;
        char* tmp;
        size_t len_front;
        size_t count;
        size_t result_length;

        if (_length == 0 || str._length == 0) return String();

        ins = old_data;
        for (count = 0; tmp = strstr(ins, str.c_str()); count++) {
            ins = tmp + str._length;
        }
        result_length = _length + (with._length - str._length) * count;
        tmp = new_data = new char[result_length + 1];

        while (count--) {
            ins = strstr(old_data, str.c_str());
            len_front = ins - old_data;
            tmp = strncpy(tmp, old_data, len_front) + len_front;
            tmp = strcpy(tmp, with.c_str()) + with._length;
            old_data += len_front + str._length;
        }
        strcpy(tmp, old_data);

        return String(new_data, result_length);
    }

    String String::remove(size_t beg, size_t end, char c)
    {
        char* sub_data = &_data[beg];
        char* new_data;
        char* ins;
        char* tmp;
        size_t len_front;
        size_t count;
        size_t result_length;
        
        if (_length == 0) return String();
        
        ins = &_data[beg];
        tmp = strstr(ins, &c);
        for (count = 0; tmp = strstr(ins, &c); count++) {
            if (tmp > &_data[end]) break;
            ins = tmp + 1;
        }
        result_length = _length - count;
        tmp = new_data = new char[result_length + 1];
        
        //tmp = strncpy(tmp, _data, &_data[beg] - _data + 1) + (&_data[beg] - _data + 1);
        while (count--) {
            ins = strstr(sub_data, &c);
            len_front = ins - sub_data;
            tmp = strncpy(tmp, sub_data, len_front) + len_front;
            sub_data += len_front + 1;
        }
        strcpy(tmp, &_data[end] + 1);
        
        return String(new_data, result_length);
    }

    String String::substr(size_t pos, size_t len)
    {
        size_t length = len - pos;
        char* str = new char[length + (size_t)1];

        str = strncpy(str, &_data[pos], length);
        str[length] = '\0';
        return String(str);
    }



    char String::operator[] (size_t pos) const
    {
        if (pos >= _length) throw 1;
        return _data[pos];
    }

    char& String::operator[] (size_t pos)
    {
        if (pos >= _length) throw 1;
        return _data[pos];
    }



    String& String::operator=(char c)
    {
        delete[] _data;
        _length = 1;
        _data = new char[_length + 1];

        _data[0] = c;
        return *this;
    }

    String& String::operator=(const char* c)
    {
        String s(c);

        delete[] _data;
        _length = s.length();
        _data = new char[_length + 1];

        strcpy(_data, s._data);
        return *this;
    }

    String& String::operator=(const String& s)
    {
        if (this == &s) return *this;

        delete[] _data;
        _length = s.length();
        _data = new char[_length + 1];

        strcpy(_data, s._data);
        return *this;
    }

    String& String::operator+=(const String& s)
    {
        size_t len = _length + s.length();
        char* str = new char[len + 1];

        strcpy(str, _data);
        strcat(str, s._data);

        delete[] _data;
        _length = len;
        _data = str;
        return *this;
    }



    String operator+(const String& lhs, const String& rhs) {
        return String(lhs) += rhs;
    }
    String operator+(const String& lhs, char rhs) {
        return String(lhs) += String(rhs);
    }
    String operator+(const String& lhs, const char* rhs) {
        return String(lhs) += String(rhs);
    }
    String operator+(char lhs, const String& rhs) {
        return String(lhs) += rhs;
    }
    String operator+(const char* lhs, const String& rhs) {
        return String(lhs) += rhs;
    }



    std::ostream& operator<<(std::ostream& os, const String& s)
    {
        if (s.length() > 0)
        {
            for (size_t j = 0; j < s.length(); j++)
                os << s[j];
        }
        else os << "";

        return os;
    }

    std::istream& operator>>(std::istream& is, String& s)
    {
        char* c = new char[1024];
        is >> c;
        s = String(c);
        delete[] c;

        return is;
    }



    bool operator==(const String& lhs, const String& rhs) {
        if (lhs.length() != rhs.length()) return false;

        size_t cap = lhs.length();
        size_t n = 0;
        while ((n < cap) && (lhs[n] == rhs[n])) n++;
        return (n == cap);
    }
    bool operator==(const String& lhs, char rhs) {
        return (lhs == String(rhs));
    }
    bool operator==(const String& lhs, const char* rhs) {
        return (lhs == String(rhs));
    }
    bool operator==(char lhs, const String& rhs) {
        return (String(lhs) == rhs);
    }
    bool operator==(const char* lhs, const String& rhs) {
        return (String(lhs) == rhs);
    }



    bool operator!=(const String& lhs, const String& rhs) {
        return !(lhs == rhs);
    }
    bool operator!=(const String& lhs, char rhs) {
        return !(lhs == rhs);
    }
    bool operator!=(const String& lhs, const char* rhs) {
        return !(lhs == rhs);
    }
    bool operator!=(char lhs, const String& rhs) {
        return !(lhs == rhs);
    }
    bool operator!=(const char* lhs, const String& rhs) {
        return !(lhs == rhs);
    }



    bool operator>(const String& lhs, const String& rhs) {
        size_t cap = (lhs.length() < rhs.length()) ? lhs.length() : rhs.length();
        size_t n = 0;
        while ((n < cap) && (lhs[n] == rhs[n])) n++;
        if (n == cap) return (lhs.length() > rhs.length());

        if ((('A' <= lhs[n] && lhs[n] <= 'Z') || ('a' <= lhs[n] && lhs[n] <= 'z')) &&
            (('A' <= rhs[n] && rhs[n] <= 'Z') || ('a' <= rhs[n] && rhs[n] <= 'z')))
        {
            char A = (lhs[n] & ~32);
            char B = (rhs[n] & ~32);
            if (A != B) return (A > B);
        }
        return lhs[n] > rhs[n];
    }
    bool operator>(const String& lhs, char rhs) {
        return (lhs > String(rhs));
    }
    bool operator>(const String& lhs, const char* rhs) {
        return (lhs > String(rhs));
    }
    bool operator>(char lhs, const String& rhs) {
        return (String(lhs) > rhs);
    }
    bool operator>(const char* lhs, const String& rhs) {
        return (String(lhs) > rhs);
    }



    bool operator<(const String& lhs, const String& rhs) {
        return !(lhs == rhs) && !(lhs > rhs);
    }
    bool operator<(const String& lhs, char rhs) {
        return !(lhs == rhs) && !(lhs > rhs);
    }
    bool operator<(const String& lhs, const char* rhs) {
        return !(lhs == rhs) && !(lhs > rhs);
    }
    bool operator<(char lhs, const String& rhs) {
        return !(lhs == rhs) && !(lhs > rhs);
    }
    bool operator<(const char* lhs, const String& rhs) {
        return !(lhs == rhs) && !(lhs > rhs);
    }



    bool operator>=(const String& lhs, const String& rhs) {
        return (lhs == rhs) || (lhs > rhs);
    }
    bool operator>=(const String& lhs, char rhs) {
        return (lhs == rhs) || (lhs > rhs);
    }
    bool operator>=(const String& lhs, const char* rhs) {
        return (lhs == rhs) || (lhs > rhs);
    }
    bool operator>=(char lhs, const String& rhs) {
        return (lhs == rhs) || (lhs > rhs);
    }
    bool operator>=(const char* lhs, const String& rhs) {
        return (lhs == rhs) || (lhs > rhs);
    }



    bool operator<=(const String& lhs, const String& rhs) {
        return !(lhs > rhs);
    }
    bool operator<=(const String& lhs, char rhs) {
        return !(lhs > rhs);
    }
    bool operator<=(const String& lhs, const char* rhs) {
        return !(lhs > rhs);
    }
    bool operator<=(char lhs, const String& rhs) {
        return !(lhs > rhs);
    }
    bool operator<=(const char* lhs, const String& rhs) {
        return !(lhs > rhs);
    }

}
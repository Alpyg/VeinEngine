#include "vnpch.h"
#include "Core/String/String.h"

namespace Vein
{

    String::String()
    {
        m_length = 0;
        m_data = new char('\0');
    }

    String::String(char c)
    {
        m_length = 1;
        m_data = new char[m_length + 1];
        m_data[0] = c;
        m_data[1] = '\0';
    }

    String::String(const char* c)
    {
        if (c)
        {
            size_t n = 0;
            while (c[n] != '\0') n++;
            m_length = n;
            m_data = new char[n + 1];
            strcpy(m_data, c);
        }
        else
        {
            m_length = 0;
            m_data = new char[0];
        }
    }

    String::String(const String& s)
    {
        m_length = s.length();
        m_data = new char[m_length + 1];
        strcpy(m_data, s.m_data);
    }

    String::String(char* s, size_t l)
    {
        m_length = l;
        m_data = s;
    }

    String::~String()
    {
        delete[] m_data;
    }


    const char* String::c_str() const {
        return m_data;
    }
    const char* String::begin() const {
        return m_data;
    }
    const char* String::end() const {
        return m_data + m_length;
    }

    size_t String::length() const
    {
        return m_length;
    }

    String String::replace(const String& str, const String& with)
    {
        char* old_data = m_data;
        char* new_data;
        char* ins;
        char* tmp;
        size_t len_front;
        size_t count;
        size_t result_length;

        if (m_length == 0 || str.m_length == 0) return String();

        ins = old_data;
        for (count = 0; tmp = strstr(ins, str.c_str()); count++) {
            ins = tmp + str.m_length;
        }
        result_length = m_length + (with.m_length - str.m_length) * count;
        tmp = new_data = new char[result_length + 1];

        while (count--) {
            ins = strstr(old_data, str.c_str());
            len_front = ins - old_data;
            tmp = strncpy(tmp, old_data, len_front) + len_front;
            tmp = strcpy(tmp, with.c_str()) + with.m_length;
            old_data += len_front + str.m_length;
        }
        strcpy(tmp, old_data);

        return String(new_data, result_length);
    }

    String String::remove(size_t beg, size_t end, char c)
    {
        char* sub_data = &m_data[beg];
        char* new_data;
        char* ins;
        char* tmp;
        size_t len_front;
        size_t count;
        size_t result_length;
        
        if (m_length == 0) return String();
        
        ins = &m_data[beg];
        tmp = strstr(ins, &c);
        if (tmp == NULL) return *this;

        for (count = 0; tmp = strstr(ins, &c); count++) {
            if (tmp > &m_data[end]) break;
            ins = tmp + 1;
        }
        result_length = m_length - count;
        tmp = new_data = new char[result_length + 1];
        
        while (count--) {
            ins = strstr(sub_data, &c);
            len_front = ins - sub_data;
            tmp = strncpy(tmp, sub_data, len_front) + len_front;
            sub_data += len_front + 1;
        }
        strcpy(tmp, sub_data);
        
        return String(new_data, result_length);
    }

    String String::substr(size_t pos, size_t len)
    {
        size_t length = len - pos;
        char* str = new char[length + (size_t)1];

        str = strncpy(str, &m_data[pos], length);
        str[length] = '\0';
        return String(str);
    }



    char String::operator[] (size_t pos) const
    {
        if (pos >= m_length) throw 1;
        return m_data[pos];
    }

    char& String::operator[] (size_t pos)
    {
        if (pos >= m_length) throw 1;
        return m_data[pos];
    }



    String& String::operator=(char c)
    {
        delete[] m_data;
        m_length = 1;
        m_data = new char[m_length + 1];

        m_data[0] = c;
        return *this;
    }

    String& String::operator=(const char* c)
    {
        String s(c);

        delete[] m_data;
        m_length = s.length();
        m_data = new char[m_length + 1];

        strcpy(m_data, s.m_data);
        return *this;
    }

    String& String::operator=(const String& s)
    {
        if (this == &s) return *this;

        delete[] m_data;
        m_length = s.length();
        m_data = new char[m_length + 1];

        strcpy(m_data, s.m_data);
        return *this;
    }

    String& String::operator+=(const String& s)
    {
        size_t len = m_length + s.length();
        char* str = new char[len + 1];

        strcpy(str, m_data);
        strcat(str, s.m_data);

        delete[] m_data;
        m_length = len;
        m_data = str;
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
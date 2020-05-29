#pragma once

namespace Vein
{

    class String
    {
    public:
        VN_API String();
        VN_API String(char c);
        VN_API String(const char* c);
        VN_API String(const String& s);
        VN_API ~String();

        VN_API const char* c_str() const;

        VN_API const char* begin() const;
        VN_API const char* end() const;
        VN_API size_t length() const;

        VN_API String replace(const String& str, const String& with);
        VN_API String remove(size_t beg, size_t end, char c);
        VN_API String substr(size_t beg, size_t end);

        VN_API char  operator[] (size_t pos) const;
        VN_API char& operator[] (size_t pos);

        VN_API String& operator=(char c);
        VN_API String& operator=(const char* c);
        VN_API String& operator=(const String& s);
        VN_API String& operator+=(const String& s);

        VN_API friend std::ostream& operator<< (std::ostream& so, const String& s);
        VN_API friend std::istream& operator>> (std::istream& so, String& s);

        VN_API friend String operator+(const String& lhs, const String& rhs);
        VN_API friend String operator+(const String& lhs, char          rhs);
        VN_API friend String operator+(const String& lhs, const char*   rhs);
        VN_API friend String operator+(char          lhs, const String& rhs);
        VN_API friend String operator+(const char*   lhs, const String& rhs);

        VN_API friend bool operator==(const String& lhs, const String& rhs);
        VN_API friend bool operator==(const String& lhs, char          rhs);
        VN_API friend bool operator==(const String& lhs, const char*   rhs);
        VN_API friend bool operator==(char          lhs, const String& rhs);
        VN_API friend bool operator==(const char*   lhs, const String& rhs);

        VN_API friend bool operator!=(const String& lhs, const String& rhs);
        VN_API friend bool operator!=(const String& lhs, char          rhs);
        VN_API friend bool operator!=(const String& lhs, const char*   rhs);
        VN_API friend bool operator!=(char          lhs, const String& rhs);
        VN_API friend bool operator!=(const char*   lhs, const String& rhs);

        VN_API friend bool operator>(const String& lhs, const String& rhs);
        VN_API friend bool operator>(const String& lhs, char          rhs);
        VN_API friend bool operator>(const String& lhs, const char*   rhs);
        VN_API friend bool operator>(char          lhs, const String& rhs);
        VN_API friend bool operator>(const char*   lhs, const String& rhs);

        VN_API friend bool operator<(const String& lhs, const String& rhs);
        VN_API friend bool operator<(const String& lhs, char          rhs);
        VN_API friend bool operator<(const String& lhs, const char*   rhs);
        VN_API friend bool operator<(char          lhs, const String& rhs);
        VN_API friend bool operator<(const char*   lhs, const String& rhs);

        VN_API friend bool operator>=(const String& lhs, const String& rhs);
        VN_API friend bool operator>=(const String& lhs, char          rhs);
        VN_API friend bool operator>=(const String& lhs, const char*   rhs);
        VN_API friend bool operator>=(char          lhs, const String& rhs);
        VN_API friend bool operator>=(const char*   lhs, const String& rhs);

        VN_API friend bool operator<=(const String& lhs, const String& rhs);
        VN_API friend bool operator<=(const String& lhs, char          rhs);
        VN_API friend bool operator<=(const String& lhs, const char*   rhs);
        VN_API friend bool operator<=(char          lhs, const String& rhs);
        VN_API friend bool operator<=(const char*   lhs, const String& rhs);
    private:
        VN_API String(char* c, size_t l);

        char* m_data;
        size_t m_length;
    };

}

namespace std {
    template<>
    struct hash<Vein::String> {
    public:
        // hash functor: hash uuid to size_t value by pseudorandomizing transform
        size_t operator()(const Vein::String& s) const noexcept
        {
            size_t hash = 0;
            for (size_t i = 0; i < s.length(); i++)
            {
                hash += s[i] * (i + 1);
            }
            return hash;
        }
    };
}
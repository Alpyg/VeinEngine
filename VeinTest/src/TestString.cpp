#include <catch.hpp>

#include "Core/Core.h"
#include "Core/String/String.h"

using namespace Vein;

TEST_CASE("String Operators", "[string_operators]")
{
    REQUIRE(String("ABZBC")[2] == 'Z');

    REQUIRE((String() = 'C')                == 'C');
    REQUIRE((String() = "C")                == 'C');
    REQUIRE((String() = String("C"))        == 'C');
    REQUIRE((String("AB") += String("C"))   == "ABC");

    REQUIRE((String("AB") + String("C"))   == String("ABC"));
    REQUIRE((String("AB") + 'C')           == String("ABC"));
    REQUIRE((String("AB") + "C")           == String("ABC"));
    REQUIRE(('A' + String("BC"))           == String("ABC"));
    REQUIRE(("A" + String("BC"))           == String("ABC"));

    REQUIRE(String("ABC")   == String("ABC"));
    REQUIRE(String("A")     == 'A');
    REQUIRE(String("A")     == "A");
    REQUIRE('A'             == String("A")); 
    REQUIRE("A"             == String("A"));
    
    REQUIRE(String("ABC")   != String("abc"));
    REQUIRE(String("A")     != 'a');
    REQUIRE(String("A")     != "a");
    REQUIRE('A'             != String("a"));
    REQUIRE("A"             != String("a"));

    REQUIRE(String("abc")   > String("ABC"));
    REQUIRE(String("a")     > 'A');
    REQUIRE(String("a")     > "A");
    REQUIRE('a'             > String("A"));
    REQUIRE("a"             > String("A"));

    REQUIRE(String("ABC")   < String("abc"));
    REQUIRE(String("A")     < 'a');
    REQUIRE(String("A")     < "a");
    REQUIRE('A'             < String("a"));
    REQUIRE("A"             < String("a"));

    REQUIRE(String("abc")   >= String("ABC"));
    REQUIRE(String("a")     >= 'A');
    REQUIRE(String("a")     >= "A");
    REQUIRE('a'             >= String("A"));
    REQUIRE("a"             >= String("A"));

    REQUIRE(String("ABC")   <= String("abc"));
    REQUIRE(String("A")     <= 'a');
    REQUIRE(String("A")     <= "a");
    REQUIRE('A'             <= String("a"));
    REQUIRE("A"             <= String("a"));
}

TEST_CASE("String Methods", "[string_methods]")
{
    String str("ABBBC");

    REQUIRE(str.begin() == str.c_str());
    REQUIRE(str.end() == str.c_str() + str.length());
    REQUIRE(str.length() == 5);

    REQUIRE(str.replace("BBB", "B") == "ABC");
    REQUIRE(str.substr(0, 2) == "AB");

    REQUIRE(str.remove(0, 5, 'B') == "AC");
    REQUIRE(str.remove(0, 4, 'B') == "AC");
    REQUIRE(str.remove(0, 3, 'B') == "AC");
    REQUIRE(str.remove(0, 2, 'B') == "ABC");
    REQUIRE(str.remove(0, 1, 'B') == "ABBC");
    REQUIRE(str.remove(0, 0, 'B') == "ABBBC");
}
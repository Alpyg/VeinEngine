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

    REQUIRE(String("ABBBC").begin() == 0);
    REQUIRE(String("ABBBC").end() == 5);
    REQUIRE(String("ABBBC").length() == 5);

    REQUIRE(String("ABBBC").replace("BBB", "B") == "ABC");
    REQUIRE(String("ABBBC").remove(0, 1, 'B') == "ABBC");
    REQUIRE(String("ABBBC").substr(0, 2) == "AB");
}
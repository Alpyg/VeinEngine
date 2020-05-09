#include <catch.hpp>

#include "Core/Core.h"
#include "Core/UUID/UUID.h"

using namespace Vein;

TEST_CASE("UUID Methods", "[uuid_methods]")
{
    REQUIRE((UUID() = UUID("123e4567-e89b-12d3-a456-426614174000")) == UUID("123e4567-e89b-12d3-a456-426614174000"));
    REQUIRE(UUID("123e4567-e89b-12d3-a456-426614174000").GetMost() == 1314564453825188563);
    REQUIRE(UUID("123e4567-e89b-12d3-a456-426614174000").GetLeast() == 11841725276408463360);

    REQUIRE(UUID("123e4567-e89b-12d3-a456-426614174000") == UUID("123e4567-e89b-12d3-a456-426614174000"));
    REQUIRE(UUID("123e4567-e89b-12d3-a456-426614174000") != UUID("123e4567-e89b-12d3-a456-426614174001"));
    REQUIRE(UUID("123e4567-e89b-12d3-a456-426614174001") > UUID("123e4567-e89b-12d3-a456-426614174000"));
    REQUIRE(UUID("123e4567-e89b-12d3-a456-426614174000") < UUID("123e4567-e89b-12d3-a456-426614174001"));
    REQUIRE(UUID("123e4567-e89b-12d3-a456-426614174001") >= UUID("123e4567-e89b-12d3-a456-426614174000"));
    REQUIRE(UUID("123e4567-e89b-12d3-a456-426614174000") <= UUID("123e4567-e89b-12d3-a456-426614174001"));
}
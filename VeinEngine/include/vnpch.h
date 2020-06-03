#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Core/Core.h"
#include "Core/Assert/Assert.h"
#include "Core/Memory/Pointers.h"
#include "Core/Math/Math.h"

#ifdef VN_PLATFORM_WINDOWS
    #include <Windows.h>
#endif
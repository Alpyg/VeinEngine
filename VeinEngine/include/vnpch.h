#pragma once

#include <algorithm>
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
#include "Core/String/String.h"

#ifdef VEIN_PLATFORM_WINDOWS
    #include <Windows.h>
#endif
#pragma once

#include "Core/Application.h"
#include "Core/EntryPoint.h"

#define BIND_FN(x) std::bind(x, this, std::placeholders::_1)
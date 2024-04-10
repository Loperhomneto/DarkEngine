#pragma once

#include "Core/Renderer.h"
#include "Core/Application.h"
#include "Core/EntryPoint.h"
#include "Core/SoundEngine.h"
#include "Core/Input.h"

#define BIND_FN(x) std::bind(x, this, std::placeholders::_1)
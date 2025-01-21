#pragma once

#include "Dark/Renderer/Renderer.h"
#include "Dark/Application.h"
#include "Dark/EntryPoint.h"
#include "Dark/SoundEngine.h"
#include "Dark/Input.h"
//#include "Dark/Logger.h"

#define BIND_FN(x) std::bind(x, this, std::placeholders::_1)
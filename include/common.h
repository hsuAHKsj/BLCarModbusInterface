#pragma once
#include <string>
#include <atomic>
#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"  // support for loading levels from the environment variable
#include "spdlog/fmt/ostr.h" // support for user defined types


static const std::atomic<bool> ENALBE(true); 


static const std::string Version = "0.0.1";
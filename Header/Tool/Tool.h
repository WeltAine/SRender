#pragma once

#include <windows.h>
#include <string>

std::wstring StringToWideString(const std::string& str, UINT codePage = CP_UTF8);
#pragma once
#include <tchar.h>
#include <iostream>
#include <Windows.h>

void print_error_message(int);
bool parse_args(int, _TCHAR**, int&, _TCHAR*&, _TCHAR*&, _TCHAR*&);

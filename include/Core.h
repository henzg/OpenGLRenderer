#pragma once

/*General includes*/
#include "glad/glad.h"

#include <string.h>
#include <iostream>
#include <cstdlib>

#ifdef _DBUG
#define ASSERT(x) if (!(x)) std::abort();
#define GLCALL(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__));
#else
#define GLCall(x) x
#endif

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

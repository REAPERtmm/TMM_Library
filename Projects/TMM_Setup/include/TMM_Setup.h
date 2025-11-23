#pragma once

#ifndef NDEBUG

#define _CRTDBG_MAP_ALLOC
#define D3D_DEBUG_INFO
#include <crtdbg.h>

#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__ , __LINE__)
#define new DEBUG_NEW

#endif // !NDEBUG

#include <stdint.h>

namespace TMM {
	class Utils {
	public:
		static bool CheckMaskLt(uint64_t mask1, uint64_t mask2);
		static bool CheckMaskGt(uint64_t mask1, uint64_t mask2);
	};
}

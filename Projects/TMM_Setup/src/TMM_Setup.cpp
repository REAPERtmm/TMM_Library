#include "TMM_Setup.h"

namespace TMM {
	bool Utils::CheckMaskLt(uint64_t mask1, uint64_t mask2)
	{
		return (mask1 & mask2) == mask1;
	}

	bool Utils::CheckMaskGt(uint64_t mask1, uint64_t mask2)
	{
		return (mask1 & mask2) == mask2;
	}
}

#include <TMM_Setup.h>
#include <TMM_Debugger.h>
#include <TMM_BitMask.h>

TMM_START_BITMASK(BitMaskTest)
TMM_ADD_MASK(1, MASK1)
TMM_ADD_MASK(2, MASK2)
TMM_ADD_MASK(3, MASK3)
TMM_END_BITMASK()

int main(int argc, char* argv[]) 
{
#ifndef NDEBUG
	auto tmp = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmp |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(tmp);
	DBG_INIT(DBG_ALL, OUTPUT_CONSOLE);
#else
	DBG_INIT(DBG_ERROR, OUTPUT_DEBUGGER);
#endif // !NDEBUG

	TMM::BitMask<BitMaskTest> mask(MASK1);
	mask |= MASK2;

	if (mask.Contain(MASK3)) {
		LOG_INFO << "ERROR" << ENDL;
	}
	else if (mask.Contain(MASK1 | MASK2)) {
		LOG_INFO << "GOOD" << ENDL;
	}

	DBG_UNINIT();

	return 0;
}

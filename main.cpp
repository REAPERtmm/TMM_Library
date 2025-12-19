#include <TMM_Debugger.h>
#include <TMM_Vectors.h>
#include <TMM_SSEMath.h>
#include <intrin.h>

#pragma comment(lib, "Winmm.lib")

int main(int argc, char* argv[]) 
{
#ifndef NDEBUG
	auto tmp = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmp |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(tmp);

	TMM::BitMask<TMM::DEBUGGER_FLAGS> flags = TMM::DEBUGGER_FLAGS::ALL;
	TMM::BitMask<TMM::DEBUGGER_OUTPUT> outputs;
	outputs |= TMM::DEBUGGER_OUTPUT::OUTPUT_CONSOLE;
	outputs |= TMM::DEBUGGER_OUTPUT::OUTPUT_LOGS;
	DBG_INIT(flags, outputs, true);
#else
	TMM::BitMask<TMM::DEBUGGER_FLAGS> flags = TMM::DEBUGGER_FLAGS::ALL;
	TMM::BitMask<TMM::DEBUGGER_OUTPUT> outputs = TMM::DEBUGGER_OUTPUT::OUTPUT_CONSOLE;
	outputs |= TMM::DEBUGGER_OUTPUT::OUTPUT_LOGS;
	DBG_INIT(flags, outputs, true);
#endif // !NDEBUG

	TMM::Vec4f matOut[4];

	uint64_t t1 = __rdtsc();

	TMM::MATRIX_OPP mat0(2.0f);
	TMM::MATRIX_OPP mat1(
		1, 2, 3, 4,
		5, 6, 7, 8,
		1, 2, 3, 4,
		5, 6, 7, 8
	);

	// 800-900 ticks
	//for (int i = 0; i < 5; ++i) {
	//	TMM_OPP_MUL_MAT_Accumulate(mat1, mat0);
	//}

	//mat1.Out(matOut);

	// 45 ticks
	TMM_OPP_MUL_MAT(mat2, mat1, mat0);
	TMM_OPP_MUL_MAT(mat3, mat2, mat0);
	TMM_OPP_MUL_MAT(mat4, mat3, mat0);
	TMM_OPP_MUL_MAT(mat5, mat4, mat0);
	TMM_OPP_MUL_MAT(mat6, mat5, mat0);

	mat6.Out(matOut);

	uint64_t t2 = __rdtsc();

	LOG_INFO << "Enlapsed time SIMD : " << t2 - t1 << " ticks output : " << ENDL;
	LOG_INFO << matOut[0].x << ", " << matOut[0].y << ", " << matOut[0].z << ", " << matOut[0].w << ENDL;
	LOG_INFO << matOut[1].x << ", " << matOut[1].y << ", " << matOut[1].z << ", " << matOut[1].w << ENDL;
	LOG_INFO << matOut[2].x << ", " << matOut[2].y << ", " << matOut[2].z << ", " << matOut[2].w << ENDL;
	LOG_INFO << matOut[3].x << ", " << matOut[3].y << ", " << matOut[3].z << ", " << matOut[3].w << ENDL;

	DBG_UNINIT();

	return 0;
}

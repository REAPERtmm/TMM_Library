#include "TMM_AudioParser.h"

namespace TMM
{
	template<typename T_IN, typename T_OUT>
	inline void FileContent_WAV::CopySampleGroupTo(T_OUT* pDest, T_IN* pSrc, unsigned int channel_count, T_OUT(*convert)(T_IN& value))
	{
		TMM_ITER(i, channel_count)
		{
			pDest[i] = convert(pSrc[i]);
		}
	}

	template<typename T_IN, typename T_OUT>
	inline T_OUT FileContent_WAV::Convert(T_IN& src)
	{
		if constexpr (TMM::OneOf<T_IN, float, double>)
		{
			if constexpr (TMM::OneOf<T_OUT, float, double>)
			{
				// FLOATING => FLOATING
				return (T_OUT)src;
			}
			else
			{
				// FLOATING => INTEGER
				return (T_OUT)((src > 0 ? src * TMM::MAX_INTEGER<T_OUT>::VALUE : src * -TMM::MIN_INTEGER<T_OUT>::VALUE));
			}
		}
		else
		{
			if constexpr (TMM::OneOf<T_OUT, float, double>)
			{
				// INTEGER => FLOATING
				const double RCP_MAX_VALUE = 1.0 / static_cast<double>(TMM::MAX_INTEGER<T_IN>::VALUE);
				const double RCP_MIN_VALUE = -1.0 / static_cast<double>(TMM::MIN_INTEGER<T_IN>::VALUE);
				return (T_OUT)((src > 0 ? static_cast<double>(src) * RCP_MAX_VALUE : static_cast<double>(src) * RCP_MIN_VALUE));
			}
			else
			{
				// INTEGER => INTEGER
				const double RATIO_MAX = static_cast<double>(TMM::MAX_INTEGER<T_OUT>::VALUE) / static_cast<double>(TMM::MAX_INTEGER<T_IN>::VALUE);
				const double RATIO_MIN = -static_cast<double>(TMM::MIN_INTEGER<T_OUT>::VALUE) / static_cast<double>(TMM::MIN_INTEGER<T_IN>::VALUE);
				return (T_OUT)((src > 0 ? src * RATIO_MAX : src * RATIO_MIN));
			}
		}
	}

	template<typename T_OUT>
	inline FileContent_WAV* FileContent_WAV::Translate()

	{
		BASE_TYPE type = GetEncodedType();
		unsigned char in_size = GetSampleByteSize();
		FileContent_WAV_DESCRIPTOR desc = GetDescriptor();
		TMM::FileContent_WAV* pOut = nullptr;

		desc.sampleByteSize = sizeof(T_OUT);
		if constexpr (TMM::OneOf<T_OUT, float, double>)
		{
			desc.format = WAV_TYPE_FORMAT::IEEE_FLOATING;
		}
		else {
			desc.format = WAV_TYPE_FORMAT::PCM_INTEGER;
		}

		pOut = CreateEmpty(desc);

		switch (type)
		{
		case TMM::BASE_TYPE::FLOAT:
		{
			TMM_ITER(i, GetTotalSampleCount()) {
				FileContent_WAV::CopySampleGroupTo<float, T_OUT>((T_OUT*)pOut->At(i), (float*)At(i), desc.channelCount, Convert<float, T_OUT>);
			}
			return pOut;
		}
		case TMM::BASE_TYPE::DOUBLE:
		{
			TMM_ITER(i, GetTotalSampleCount()) {
				FileContent_WAV::CopySampleGroupTo<double, T_OUT>((T_OUT*)pOut->At(i), (double*)At(i), desc.channelCount, Convert<double, T_OUT>);
			}
			return pOut;
		}
		case TMM::BASE_TYPE::INT8:
		{
			TMM_ITER(i, GetTotalSampleCount()) {
				FileContent_WAV::CopySampleGroupTo<signed char, T_OUT>((T_OUT*)pOut->At(i), (signed char*)At(i), desc.channelCount, Convert<signed char, T_OUT>);
			}
			return pOut;
		}
		case TMM::BASE_TYPE::INT16:
		{
			TMM_ITER(i, GetTotalSampleCount()) {
				FileContent_WAV::CopySampleGroupTo<signed short, T_OUT>((T_OUT*)pOut->At(i), (signed short*)At(i), desc.channelCount, Convert<signed short, T_OUT>);
			}
			return pOut;
		}
		case TMM::BASE_TYPE::INT32:
		{
			TMM_ITER(i, GetTotalSampleCount()) {
				FileContent_WAV::CopySampleGroupTo<signed int, T_OUT>((T_OUT*)pOut->At(i), (signed int*)At(i), desc.channelCount, Convert<signed int, T_OUT>);
			}
			return pOut;
		}
		case TMM::BASE_TYPE::INT64:
		{
			TMM_ITER(i, GetTotalSampleCount()) {
				FileContent_WAV::CopySampleGroupTo<signed long long, T_OUT>((T_OUT*)pOut->At(i), (signed long long*)At(i), desc.channelCount, Convert<signed long long, T_OUT>);
			}
			return pOut;
		}
		default: return nullptr;
		}
	}

	template<typename T>
	inline void FileContent_WAV::ChangeSignal(T(*transformation)(const T*), Second_f start, Second_f end)
	{
		unsigned int i_start = start * mHeader.SampleRate;
		unsigned int i_end = (end > start ? end * mHeader.SampleRate : GetTotalSampleCount());
		for (unsigned int i = i_start; i < i_end; ++i)
		{
			*((T*)At(i)) = transformation(At(i));
		}
	}

	template<typename T>
	inline void FileContent_WAV::ChangeSignal(T(*transformation)(Second_f, const T*), Second_f start, Second_f end)
	{
		unsigned int i_start = start * mHeader.SampleRate;
		unsigned int i_end = (end > start ? end * mHeader.SampleRate : GetTotalSampleCount());
		for (unsigned int i = i_start; i < i_end; ++i)
		{
			*((T*)At(i)) = transformation(i * mHeader.SampleRate, At(i));
		}
	}

	template<typename T>
	inline void FileContent_WAV::ChangeSignal(T(*transformation)(Second_f, const T*, FileContent_WAV*), Second_f start, Second_f end)
	{
		unsigned int i_start = start * mHeader.SampleRate;
		unsigned int i_end = (end > start ? end * mHeader.SampleRate : GetTotalSampleCount());
		for (unsigned int i = i_start; i < i_end; ++i)
		{
			*((T*)At(i)) = transformation(i * mHeader.SampleRate, At(i), this);
		}
	}

	template<typename T>
	inline void FileContent_WAV::ChangeSignal(T(*transformation)(unsigned int, const T*), Second_f start, Second_f end)
	{
		unsigned int i_start = start * mHeader.SampleRate;
		unsigned int i_end = (end > start ? end * mHeader.SampleRate : GetTotalSampleCount());
		for (unsigned int i = i_start; i < i_end; ++i)
		{
			*((T*)At(i)) = transformation(i, At(i));
		}
	}

	template<typename T>
	inline void FileContent_WAV::ChangeSignal(T(*transformation)(unsigned int, const T*, FileContent_WAV*), Second_f start, Second_f end)
	{
		unsigned int i_start = start * mHeader.SampleRate;
		unsigned int i_end = (end > start ? end * mHeader.SampleRate : GetTotalSampleCount());
		for (unsigned int i = i_start; i < i_end; ++i)
		{
			*((T*)At(i)) = transformation(i, At(i), this);
		}
	}

	template<typename T, float FACTOR>
	inline void FileContent_WAV::Amplify()
	{
		ChangeSignal(+[](Second_f t, const T* pValue) -> T { return FACTOR * *pValue; });
	}

}
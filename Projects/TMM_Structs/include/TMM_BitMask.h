#pragma once
#include <TMM_Setup.h>

#define TMM_START_BITMASK(name) enum class name : uint64_t { NONE = 0,

#define TMM_ADD_MASK(index, name) name = 1 << index,

#define TMM_END_BITMASK() ALL = UINT64_MAX };

namespace TMM
{
	template<typename Enum> requires( __is_enum(Enum))
	class BitMask {
		uint64_t mValue;
	public:
		BitMask() : mValue(0) {}
		BitMask(uint64_t value) : mValue(value) {}
		BitMask(Enum value) : mValue((uint64_t)value) {}

		BitMask operator | (const BitMask& other) const {
			return { mValue | other.mValue };
		}

		BitMask operator | (const Enum& other) const {
			return { mValue | static_cast<uint64_t>(other) };
		}

		BitMask& operator |= (const BitMask& other) {
			mValue |= other.mValue;
			return *this;
		}

		BitMask& operator |= (const Enum& other) {
			mValue |= static_cast<uint64_t>(other);
			return *this;
		}

		BitMask operator & (const BitMask& other) const {
			return { mValue & other.mValue };
		}

		BitMask operator & (const Enum& other) const {
			return { mValue & static_cast<uint64_t>(other) };
		}

		BitMask& operator &= (const BitMask& other) {
			mValue &= other.mValue;
			return *this;
		}

		BitMask& operator &= (const Enum& other) {
			mValue &= static_cast<uint64_t>(other);
			return *this;
		}

		BitMask operator ^ (const BitMask& other) const {
			return { mValue ^ other.mValue };
		}

		BitMask operator ^ (const Enum& other) const {
			return { mValue ^ static_cast<uint64_t>(other) };
		}

		BitMask& operator ^= (const BitMask& other) {
			mValue ^= other.mValue;
			return *this;
		}

		BitMask& operator ^= (const Enum& other) {
			mValue ^= static_cast<uint64_t>(other);
			return *this;
		}

		bool operator == (const BitMask& other) const {
			return mValue == other.mValue;
		}

		bool operator == (const Enum& other) const {
			return mValue == static_cast<uint64_t>(other);
		}

		bool operator != (const BitMask& other) const {
			return mValue != other.mValue;
		}

		bool operator != (const Enum& other) const {
			return mValue != static_cast<uint64_t>(other);
		}

		bool operator >= (const BitMask& other) const {
			return (mValue & other.mValue) == other.mValue; 
		}

		bool operator >= (const Enum& other) const {
			return (mValue & static_cast<uint64_t>(other)) == static_cast<uint64_t>(other);
		}

		bool operator <= (const BitMask& other) const {
			return (mValue & other.mValue) == mValue;
		}

		bool operator <= (const Enum& other) const {
			return (mValue & static_cast<uint64_t>(other)) == mValue;
		}

		bool operator > (const BitMask& other) const {
			return operator >= (other) && operator != (other);
		}

		bool operator > (const Enum& other) const {
			return operator >= (other) && operator != (other);
		}

		bool operator < (const BitMask& other) const {
			return operator <= (other) && operator != (other);
		}

		bool operator < (const Enum& other) const {
			return operator <= (other) && operator != (other);
		}

		bool Contain(const BitMask& other) const {
			return operator >= (other);
		}

		bool Contain(const Enum& other) const {
			return operator >= (other);
		}
	};

}

#include "TMM_Bitmask.hpp"
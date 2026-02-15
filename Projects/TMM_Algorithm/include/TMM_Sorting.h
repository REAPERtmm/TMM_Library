#pragma once

#include <TMM_Setup.h>
#include <queue>

namespace TMM
{

	namespace SORTING {


		template<typename T>
		void InsertionSort(T* buffer, uint64_t buffer_size, bool(*compare)(T& before, T& after) = +[](T& before, T& after) { return before < after; })
		{

			for (uint64_t i = 1; i < buffer_size; ++i)
			{

				for (uint64_t j = i; j > 0; --j)
				{
					if (compare(buffer[j - 1], buffer[j])) {
						break;
					}

					TMM_SWAP(buffer[j - 1], buffer[j]);
				}

			}

		}

		template<typename T>
		void SelectionSort(T* buffer, uint64_t buffer_size, bool(*compare)(T& before, T& after) = +[](T& before, T& after) { return before < after; })
		{
			for (uint64_t i = 0; i < buffer_size - 1; ++i)
			{
				uint64_t next = i;
				for (uint64_t j = i + 1; j < buffer_size; ++j)
				{
					if (compare(buffer[j], buffer[next]))
					{
						next = j;
					}
				}
				TMM_SWAP(buffer[i], buffer[next]);
			}

		}

		template<typename T>
		void BubbleSort(T* buffer, uint64_t buffer_size, bool(*compare)(T& before, T& after) = +[](T& before, T& after) { return before < after; })
		{
			for (uint64_t i = 1; i < buffer_size; ++i)
			{
				for (uint64_t j = i; j < buffer_size; ++j)
				{
					if (compare(buffer[j], buffer[j - 1]))
					{
						TMM_SWAP(buffer[j], buffer[j - 1]);
					}
				}
			}
		}

		template<typename T, unsigned BITS> 
		requires(
			TMM::OneOf<T, uint8_t, uint16_t, uint32_t, uint64_t> &&
			(BITS == 8 || BITS == 16)
			)
		void RandixSort(T* buffer, uint64_t buffer_size, bool(*compare)(uint32_t& before, uint32_t& after) = +[](uint32_t& before, uint32_t& after) { return before < after; })
		{
			static std::queue<T> buckets[1 << BITS];

			auto ProcessMask = [&](T mask, uint8_t offset)
			{
				TMM_ITER(i, buffer_size)
				{
					T v = (buffer[i] & mask) >> offset;
					buckets[v].push(buffer[i]);
				}
				uint64_t index = 0;
				TMM_ITER(i, 256)
				{
					while (buckets[i].size() > 0)
					{
						buffer[index++] = buckets[i].front();
						buckets[i].pop();
					}
				}
			};

			uint64_t mask = (1 << BITS) - 1;
			uint64_t offset = 0;
			while (offset < (sizeof(T) * 8))
			{
				ProcessMask(mask, offset);
				mask <<= BITS;
				offset += BITS;
			}
		}
	
		template<typename T>
		void _QuickSort(T* buffer, uint64_t first, uint64_t last, bool(*compare)(T& before, T& after))
		{
			static auto Partitionner = [&](uint64_t first, uint64_t last, uint64_t pivot)
				{
					T& temp = buffer[last];
					buffer[last] = buffer[pivot];
					buffer[pivot] = temp;

					uint64_t j = first;
					for (uint64_t i = first; i < last; ++i)
					{
						if (compare(buffer[i], buffer[last])) {
							temp = buffer[i];
							buffer[i] = buffer[j];
							buffer[j] = temp;
							++j;
						}
					}

					temp = buffer[last];
					buffer[last] = buffer[j];
					buffer[j] = temp;

					return j;
				};

			if (first < last)
			{
				uint64_t pivot = first;
				pivot = Partitionner(first, last, pivot);
				if(pivot > 0)
					_QuickSort(buffer, first, pivot - 1, compare);
				_QuickSort(buffer, pivot + 1, last, compare);
			}
		};

		template<typename T>
		void QuickSort(T* buffer, uint64_t buffer_size, bool(*compare)(T& before, T& after) = +[](T& before, T& after) { return before < after; })
		{
			TMM::SORTING::_QuickSort(buffer, 0, buffer_size - 1, compare);
		}

	}

}
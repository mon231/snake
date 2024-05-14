#include "Random.hpp"

#include <ctime>
#include <cstdlib>

uint32_t randint(const uint32_t min_inclusive, const uint32_t max_exclusive)
{
	static bool is_random_seed_initialized = false;

	if (!is_random_seed_initialized)
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		is_random_seed_initialized = true;
	}

	return min_inclusive + (std::rand() % (max_exclusive - min_inclusive));
}

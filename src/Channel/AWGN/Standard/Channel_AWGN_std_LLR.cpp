#include "Channel_AWGN_std_LLR.hpp"

#include <algorithm>
#include <cassert>

template <typename R>
Channel_AWGN_std_LLR<R>
::Channel_AWGN_std_LLR(const R& sigma, const int seed, const R scaling_factor)
: sigma(sigma),
  scaling_factor(scaling_factor),
  rd(),
  rd_engine(this->rd()),
  normal_dist(0, sigma)
{
	assert(scaling_factor != 0);
	assert(sigma          != 0);

	rd_engine.seed(seed);
}

template <typename R>
Channel_AWGN_std_LLR<R>
::~Channel_AWGN_std_LLR()
{
}

template <typename R>
void Channel_AWGN_std_LLR<R>
::add_noise(const mipp::vector<R>& X_N, mipp::vector<R>& Y_N)
{
	assert(X_N.size() == Y_N.size());

	for (unsigned i = 0; i < X_N.size(); i++)
		Y_N[i] = (X_N[i] + this->normal_dist(this->rd_engine)) * scaling_factor;
}

// ==================================================================================== explicit template instantiation 
#include "../../../Tools/types.h"
#ifdef MULTI_PREC
template class Channel_AWGN_std_LLR<R_32>;
template class Channel_AWGN_std_LLR<R_64>;
#else
template class Channel_AWGN_std_LLR<R>;
#endif
// ==================================================================================== explicit template instantiation
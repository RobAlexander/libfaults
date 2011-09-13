/*
 * Copyright (c) 2011, The University of York
 * All rights reserved.
 * Author(s):
 *   James Arnold <jarnie@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the The University of York nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * ANY ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY OF YORK BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>

#include "Noise.h"

template <typename T>
NoiseFaultModel<T>::NoiseFaultModel(T min, T max, noise_type type)
   : _min(min), _max(max), _type(type), _seed(time(NULL))
{
   init();
}

template <typename T>
NoiseFaultModel<T>::NoiseFaultModel(T min, T max, noise_type type, unsigned int seed)
   : _min(min), _max(max), _type(type), _seed(seed)
{
   init();
}

template <typename T>
T NoiseFaultModel<T>::GetFaulty(const T value)
{
   // Get the randomly generated noise
   T noise = (*random)();

   // No noise, return original value
   if (noise == 0)
      return value;

   if (_type == Offset)
      return (*coin)() ? value + noise : value - noise; // Randomly add or subtract noise
   else // (_type == Scaled)
      return value * noise; // Random scaled noise
}

template <typename T>
void NoiseFaultModel<T>::SetMin(T value)
{
   _min = value;
   dist.reset(new distribution_type(_min, _max));
}

template <typename T>
void NoiseFaultModel<T>::SetMax(T value)
{
   _max = value;
   dist.reset(new distribution_type(_min, _max));
}

template <typename T>
void NoiseFaultModel<T>::SetSeed(unsigned int value)
{
   _seed = value;
   gen.seed(_seed);
}

template <typename T>
void NoiseFaultModel<T>::init()
{
   // Instantiate the Mersenne Twister
   gen.seed(_seed);

   // Instantiate the noise distribution and variate generator
   dist.reset(new distribution_type(_min, _max));
   random.reset(new boost::variate_generator<boost::mt19937&, distribution_type>(gen, *dist));

   // Instantiate the coin used to decice whether to add or subtract noise
   bdist.reset(new boost::bernoulli_distribution<>(0.5));
   coin.reset(new boost::variate_generator<boost::mt19937&, boost::bernoulli_distribution<> >(gen, *bdist));
}


// Explicit declarations needed to compile type support into the library
template class NoiseFaultModel<int8_t>;
template class NoiseFaultModel<uint8_t>;
template class NoiseFaultModel<int16_t>;
template class NoiseFaultModel<uint16_t>;
template class NoiseFaultModel<int32_t>;
template class NoiseFaultModel<uint32_t>;
template class NoiseFaultModel<int64_t>;
template class NoiseFaultModel<uint64_t>;
template class NoiseFaultModel<float>;
template class NoiseFaultModel<double>;
template class NoiseFaultModel<long double>;

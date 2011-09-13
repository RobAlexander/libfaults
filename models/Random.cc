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
 *     * Neither the name of the <organization> nor the
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

#include <algorithm>
#include <stdint.h>

#include "Random.h"

template <typename T>
RandomFaultModel<T>::RandomFaultModel(T values[], int len)
   : _min(0), _max(len - 1), _seed(time(NULL)), _len(len)
{
   init_array(values);
   init_prng();
}

template <typename T>
RandomFaultModel<T>::RandomFaultModel(T values[], int len, unsigned int seed)
   : _min(0), _max(len - 1), _seed(seed), _len(len)
{
   init_array(values);
   init_prng();
}

template <typename T>
RandomFaultModel<T>::RandomFaultModel(T min, T max)
   : _min(min), _max(max), _seed(time(NULL)), _len(0)
{
   init_prng();
}

template <typename T>
RandomFaultModel<T>::RandomFaultModel(T min, T max, unsigned int seed)
   : _min(min), _max(max), _seed(seed), _len(0)
{
   init_prng();
}

template <typename T>
T RandomFaultModel<T>::GetFaulty(const T value)
{
   // If we have a list of values, randomly choose one from it.
   // Otherwise we can simply return a random number.
   return (_len > 0) ? _values[(*choice)()] : (*ranged)();
}

template <typename T>
void RandomFaultModel<T>::SetMin(T value)
{
   _min = value;
   ranged_dist.reset(new distribution_type(_min, _max));
}

template <typename T>
void RandomFaultModel<T>::SetMax(T value)
{
   _max = value;
   ranged_dist.reset(new distribution_type(_min, _max));
}

template <typename T>
void RandomFaultModel<T>::SetSeed(unsigned int value)
{
   _seed = value;
   gen.seed(_seed);
}

template <typename T>
void RandomFaultModel<T>::init_array(T values[])
{
   // TODO: Sanity check for:
   //         len <= 0

   // Copy the value list
   _values.reset(new T[_len]);
   std::copy(values, values + _len, _values.get());
}

template <typename T>
void RandomFaultModel<T>::init_prng()
{
   // TODO: Sanity check for:
   //         min > max

   // Instantiate the PRNG
   gen.seed(_seed);
   if (_len > 0)
   {
      // Generate index into array
      choice_dist.reset(new uniform_int(_min, _max));
      choice.reset(new boost::variate_generator<boost::mt19937&, uniform_int>(gen, *choice_dist));
   }
   else
   {
      // Generate number within range
      ranged_dist.reset(new distribution_type(_min, _max));
      ranged.reset(new boost::variate_generator<boost::mt19937&, distribution_type>(gen, *ranged_dist));
   }
}


// Explicit declarations needed to compile type support into the library
template class RandomFaultModel<int8_t>;
template class RandomFaultModel<uint8_t>;
template class RandomFaultModel<int16_t>;
template class RandomFaultModel<uint16_t>;
template class RandomFaultModel<int32_t>;
template class RandomFaultModel<uint32_t>;
template class RandomFaultModel<int64_t>;
template class RandomFaultModel<uint64_t>;
template class RandomFaultModel<float>;
template class RandomFaultModel<double>;
template class RandomFaultModel<long double>;

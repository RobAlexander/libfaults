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

#include <algorithm>
#include <stdint.h>

#include "Cycle.h"

template <typename T>
CycleFaultModel<T>::CycleFaultModel(T values[], int len)
{
   init(values, len, 0);
}

template <typename T>
CycleFaultModel<T>::CycleFaultModel(T values[], int len, int initialOffset)
{
   init(values, len, initialOffset);
}

template <typename T>
T CycleFaultModel<T>::GetFaulty(const T value)
{
   T faultyValue = _values[_index++];
   if (_index >= _len)
      _index = 0;
   return faultyValue;
}

template <typename T>
void CycleFaultModel<T>::init(T values[], int len, int initialOffset)
{
   // TODO: Sanity check for:
   //         len <= 0
   //         initialOffset >= len

   // Remember configuration values
   _len = len;
   _index = initialOffset;

   // Copy the value list
   _values.reset(new T[len]);
   std::copy(values, values + len, _values.get());
}


// Explicit declarations needed to compile type support into the library
template class CycleFaultModel<int8_t>;
template class CycleFaultModel<uint8_t>;
template class CycleFaultModel<int16_t>;
template class CycleFaultModel<uint16_t>;
template class CycleFaultModel<int32_t>;
template class CycleFaultModel<uint32_t>;
template class CycleFaultModel<int64_t>;
template class CycleFaultModel<uint64_t>;
template class CycleFaultModel<float>;
template class CycleFaultModel<double>;
template class CycleFaultModel<long double>;

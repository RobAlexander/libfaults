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

#include "../FaultModel.h"
#include "../models/Noise.h"

#include <stdint.h>

#include <boost/test/minimal.hpp>

template<typename T> void testNoise(T parameterValue, T min, T max, noise_type type, unsigned int seed);

int test_main(int argc, char* argv[])
{
   unsigned int seed = time(NULL);

   // Test offset noise
   testNoise<double>(1.0, 0.0, 0.1, Offset, seed);
   testNoise<float>(1.0f, 0.0f, 0.1f, Offset, seed);
   testNoise<uint32_t>(10, 0, 2, Offset, seed);

   // Test scaled noise
   testNoise<double>(1.0, 0.0, 2.0, Scaled, seed);
   testNoise<float>(1.0f, 0.0f, 2.0f, Scaled, seed);
   testNoise<uint32_t>(1, 1, 2, Scaled, seed);

   // Yey!
   return EXIT_SUCCESS;
}

template<typename T>
void testNoise(T parameterValue, T min, T max, noise_type type, unsigned int seed)
{
   // Remember the original value
   T originalValue = parameterValue;

   // Instantiate the model
   NoiseFaultModel<T> *fm = new NoiseFaultModel<T>(min, max, type, seed);

   // Pick random items and ensure they're in the original value list
   for (int i = 0; i < 100000; i++)
   {
      T faultyValue = fm->GetFaulty(parameterValue);

      if (type == Offset)
      {
         BOOST_CHECK(faultyValue >= parameterValue - max && faultyValue <= parameterValue + max);
         BOOST_CHECK(faultyValue <= parameterValue - min || faultyValue >= parameterValue + min);
      }
      else
         BOOST_CHECK(faultyValue >= parameterValue * min && faultyValue <= parameterValue * max);
   }

   // Try changing the seed
   fm->SetSeed(1u);
   BOOST_CHECK(fm->GetSeed() == 1u);

   // Check the range
   BOOST_CHECK(fm->GetMin() == min);
   BOOST_CHECK(fm->GetMax() == max);

   // Make our original value faulty
   // and ensure it was applied correctly
   fm->MakeFaulty(parameterValue);

   if (type == Offset)
   {
      BOOST_CHECK(parameterValue >= originalValue - max && parameterValue <= originalValue + max);
      BOOST_CHECK(parameterValue <= originalValue - min || parameterValue >= originalValue + min);
   }
   else
      BOOST_CHECK(parameterValue >= originalValue * min && parameterValue <= originalValue * max);

   delete fm;
}

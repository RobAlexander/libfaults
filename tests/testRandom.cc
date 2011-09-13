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
#include "../models/Random.h"

#include <stdint.h>

#include <boost/test/minimal.hpp>

template<typename T> bool contains(T value, T array[], int len);
template<typename T> void testChoice(T parameterValue, T values[], int len, unsigned int seed);
template<typename T> void testRange(T parameterValue, T min, T max, unsigned int seed);

int test_main(int argc, char* argv[])
{
   unsigned int seed = time(NULL);
   double   values_d[] = {0.0, 5.0, 10.0, 15.0, 20.0};
   float    values_f[] = {0.0f, 5.0f, 10.0f, 15.0f, 20.0f};
   uint32_t values_i[] = {0, 5, 10, 15, 20};

   // Test the random choice model for all supported types
   testChoice<double>(1.0, values_d, sizeof(values_d) / sizeof(double), seed);
   testChoice<float>(1.0f, values_f, sizeof(values_f) / sizeof(float), seed);
   testChoice<uint32_t>(1, values_i, sizeof(values_i) / sizeof(uint32_t), seed);

   // Test the random value model for all supported types
   testRange<double>(1.0, -100.0, 100.0, seed);
   testRange<float>(1.0f, -100.0f, 100.0f, seed);
   testRange<uint32_t>(1, 0, 100, seed);

   // Yey!
   return EXIT_SUCCESS;
}

template<typename T>
inline bool contains(T value, T array[], int len)
{
   // See if the array contains the specified value
   for (int i = 0; i < len; i++)
      if (array[i] == value)
         return true;

   // It didn't contain it :(
   return false;
}

template<typename T>
void testChoice(T parameterValue, T values[], int len, unsigned int seed)
{
   // Instantiate the model
   RandomFaultModel<T> *fm = new RandomFaultModel<T>(values, len, seed);

   // Pick random items and ensure they're in the original value list
   for (int i = 0; i < 100000; i++)
   {
      T faultyValue = fm->GetFaulty(parameterValue);
      BOOST_CHECK(contains<T>(faultyValue, values, len));
   }

   // Try changing the seed
   fm->SetSeed(1u);
   BOOST_CHECK(fm->GetSeed() == 1u);

   // Make our original value faulty
   // and ensure it was applied correctly
   fm->MakeFaulty(parameterValue);
   BOOST_CHECK(contains<T>(parameterValue, values, len));

   delete fm;
}

template<typename T>
void testRange(T parameterValue, T min, T max, unsigned int seed)
{
   // Instantiate the model
   RandomFaultModel<T> *fm = new RandomFaultModel<T>(min, max, seed);

   // Generate random numbers and ensure they're within range
   for (int i = 0; i < 100000; i++)
   {
      T faultyValue = fm->GetFaulty(parameterValue);
      BOOST_CHECK(faultyValue >= min && faultyValue <= max);
   }

   // Try changing the seed
   fm->SetSeed(1u);
   BOOST_CHECK(fm->GetSeed() == 1u);

   // Make our original value faulty
   // and ensure it was applied correctly
   fm->MakeFaulty(parameterValue);
   BOOST_CHECK(parameterValue >= min && parameterValue <= max);

   delete fm;
}

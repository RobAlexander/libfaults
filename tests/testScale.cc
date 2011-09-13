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
#include "../models/Scale.h"

#include <stdint.h>

#include <boost/test/minimal.hpp>

template<typename T>
void testScaleFaultModel(T parameterValue, T multiplier1, T multiplier2);

int test_main(int argc, char* argv[])
{
   // Test the model for all supported types
   testScaleFaultModel<double>(15.0, 0.01, 2.0);
   testScaleFaultModel<float>(15.0f, 0.01f, 2.0f);
   testScaleFaultModel<uint32_t>(15, 1, 2);

   // Yey!
   return EXIT_SUCCESS;
}

template<typename T>
void testScaleFaultModel(T parameterValue, T multiplier1, T multiplier2)
{
   // Keep a copy of the original value
   T original_value = parameterValue;

   // Instantiate the model
   ScaleFaultModel<T> fm(multiplier1);

   // Pass the value through the fault model
   // and ensure it was applied correctly.
   T faultyValue = fm.GetFaulty(parameterValue);
   BOOST_CHECK(faultyValue == (original_value * multiplier1));

   // Make our original value faulty
   // and ensure it was applied correctly
   fm.MakeFaulty(parameterValue);
   BOOST_CHECK(parameterValue == (original_value * multiplier1));

   // Try changing the multiplier
   fm.SetMultiplier(multiplier2);
   BOOST_CHECK(fm.GetMultiplier() == multiplier2);

   // Pass the value through the fault model
   // and ensure it was applied correctly.
   parameterValue = original_value;
   faultyValue = fm.GetFaulty(parameterValue);
   BOOST_CHECK(faultyValue == (original_value * multiplier2));

   // Make our original value faulty
   // and ensure it was applied correctly.
   fm.MakeFaulty(parameterValue);
   BOOST_CHECK(parameterValue == (original_value * multiplier2));
}

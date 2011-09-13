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
#include "../models/Cycle.h"

#include <stdint.h>

#include <boost/test/minimal.hpp>

template<typename T>
void testCycleFaultModel(T parameterValue, T values[], int len);

int test_main(int argc, char* argv[])
{
   double   values_d[] = {15.0, 10.0, -25.0};
   float    values_f[] = {15.0f, 10.0f, -25.0f};
   uint32_t values_i[] = {15, 10, -25};

   // Test the model for all supported types
   testCycleFaultModel<double>(1.0, values_d, sizeof(values_d) / sizeof(double));
   testCycleFaultModel<float>(1.0f, values_f, sizeof(values_f) / sizeof(float));
   testCycleFaultModel<uint32_t>(1, values_i, sizeof(values_i) / sizeof(uint32_t));

   // Yey!
   return EXIT_SUCCESS;
}

template<typename T>
void testCycleFaultModel(T parameterValue, T values[], int len)
{
   // Instantiate the model
   CycleFaultModel<T> *fm = new CycleFaultModel<T>(values, len);

   // Loop through the cycle list twice
   for (int i = 0; i < (len * 2); i++)
   {
      // Pass the value through the fault model and
      // ensure the items are cycled through.
      T faultyValue = fm->GetFaulty(parameterValue);
      BOOST_CHECK(faultyValue == values[i % len]);
   }

   // Instantiate the model
   delete fm;
   fm = new CycleFaultModel<T>(values, len, 2);

   // Loop through the cycle list twice
   for (int i = 0; i < (len * 2); i++)
   {
      // Pass the value through the fault model and
      // ensure the items are cycled through.
      T faultyValue = fm->GetFaulty(parameterValue);
      BOOST_CHECK(faultyValue == values[(2 + i) % len]);
   }

   // Try changing the index
   fm->SetIndex(1);
   BOOST_CHECK(fm->GetIndex() == 1);

   // Ensure the correctly indexed value is returned
   BOOST_CHECK(fm->GetFaulty(parameterValue) == values[1]);

   // Make our original value faulty
   // and ensure it was applied correctly
   fm->MakeFaulty(parameterValue);
   BOOST_CHECK(parameterValue == values[2]);

   delete fm;
}

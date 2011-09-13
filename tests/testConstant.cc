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
#include "../models/Constant.h"

#include <stdint.h>

#include <boost/test/minimal.hpp>

template<typename T>
void testConstantFaultModel(T parameterValue, T constant1, T constant2);

int test_main(int argc, char* argv[])
{
   // Test the model for all supported types
   testConstantFaultModel<double>(15.0, 10.0, 25.0);
   testConstantFaultModel<float>(15.0f, 10.0f, 25.0f);
   testConstantFaultModel<uint32_t>(15, 10, 25);

   // Yey!
   return EXIT_SUCCESS;
}

template<typename T>
void testConstantFaultModel(T parameterValue, T constant1, T constant2)
{
   // Instantiate the model
   ConstantFaultModel<T> fm(constant1);

   // Pass the value through the fault model
   // and ensure it was applied correctly.
   T faultyValue = fm.GetFaulty(parameterValue);
   BOOST_CHECK(faultyValue == constant1);

   // Make our original value faulty
   // and ensure it was applied correctly
   fm.MakeFaulty(parameterValue);
   BOOST_CHECK(parameterValue == constant1);

   // Try changing the constant
   fm.SetConstant(constant2);
   BOOST_CHECK(fm.GetConstant() == constant2);

   // Pass the value through the fault model
   // and ensure it was applied correctly.
   faultyValue = fm.GetFaulty(parameterValue);
   BOOST_CHECK(faultyValue == constant2);

   // Make our original value faulty
   // and ensure it was applied correctly.
   fm.MakeFaulty(parameterValue);
   BOOST_CHECK(parameterValue == constant2);
}

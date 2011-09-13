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

#ifndef RANDOMFAULTMODEL_H
#define RANDOMFAULTMODEL_H

#include "../FaultModel.h"

#include <boost/random.hpp>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/type_traits/is_floating_point.hpp>

template <class T>
class RandomFaultModel : public FaultModel<T>
{
   public:

      // A random item from the specified array
      RandomFaultModel(T values[], int len);
      RandomFaultModel(T values[], int len, unsigned int seed);

      // Random numbers in the range [min, max]
      RandomFaultModel(T min, T max);
      RandomFaultModel(T min, T max, unsigned int seed);

      T GetFaulty(const T value);

      T GetMin() { return _min; }
      void SetMin(T value);

      T GetMax() { return _max; }
      void SetMax(T value);

      unsigned int GetSeed() { return _seed; }
      void SetSeed(unsigned int value);

   private:

      T _min, _max;
      unsigned int _seed;

      boost::scoped_array<T> _values;
      int _len;

      typedef typename boost::mpl::if_
      <
         boost::is_floating_point<T>,
         boost::uniform_real<>,
         boost::uniform_int<>
      >::type distribution_type;

      typedef typename boost::uniform_int<> uniform_int;

      boost::mt19937 gen;
      boost::scoped_ptr<distribution_type> ranged_dist;
      boost::scoped_ptr<boost::variate_generator<boost::mt19937&, distribution_type> > ranged;

      boost::scoped_ptr<uniform_int> choice_dist;
      boost::scoped_ptr<boost::variate_generator<boost::mt19937&, uniform_int> > choice;

      void init_array(T values[]);
      void init_prng();

};

#endif

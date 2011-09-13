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

#ifndef NOISEFAULTMODEL_H
#define NOISEFAULTMODEL_H

#include "../FaultModel.h"

#include <boost/random.hpp>
#include <boost/random/bernoulli_distribution.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/type_traits/is_floating_point.hpp>

enum noise_type
{
   Offset,
   Scaled
};

template <class T>
class NoiseFaultModel : public FaultModel<T>
{
   public:

      NoiseFaultModel(T min, T max, noise_type type);
      NoiseFaultModel(T min, T max, noise_type type, unsigned int seed);

      T GetFaulty(const T value);

      T GetMin() { return _min; }
      void SetMin(T value);

      T GetMax() { return _max; }
      void SetMax(T value);

      unsigned int GetSeed() { return _seed; }
      void SetSeed(unsigned int value);

      noise_type GetNoiseType() { return _type; }
      void SetNoiseType(noise_type value);

   private:

      T _min, _max;
      noise_type _type;
      unsigned int _seed;

      typedef typename boost::mpl::if_
      <
         boost::is_floating_point<T>,
         boost::uniform_real<>,
         boost::uniform_int<>
      >::type distribution_type;

      boost::mt19937 gen;
      boost::scoped_ptr<distribution_type> dist;
      boost::scoped_ptr<boost::variate_generator<boost::mt19937&, distribution_type> > random;

      boost::scoped_ptr<boost::bernoulli_distribution<> > bdist;
      boost::scoped_ptr<boost::variate_generator<boost::mt19937&, boost::bernoulli_distribution<> > > coin;

      void init();

};

#endif

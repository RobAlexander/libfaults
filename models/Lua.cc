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

#include <stdint.h>
#include <string.h>

#include "Lua.h"
//#include "luajit/lua.hpp"

template <typename T>
LuaFaultModel<T>::LuaFaultModel(const char *file)
{
   // Load the Lua script into the LuaJIT VM
   LoadScript(file);

   return;
}

template <typename T>
T LuaFaultModel<T>::GetFaulty(const T value)
{
   T faultyValue = 0;

   // TODO: Call Lua function and fetch value

   return faultyValue;
}

template <typename T>
bool LuaFaultModel<T>::LoadScript(const char *file)
{
   // TODO

   // All done; take a copy of the file
   _loadedFile = strdup(file);
   return true;
}


// Explicit declarations needed to compile type support into the library
template class LuaFaultModel<int8_t>;
template class LuaFaultModel<uint8_t>;
template class LuaFaultModel<int16_t>;
template class LuaFaultModel<uint16_t>;
template class LuaFaultModel<int32_t>;
template class LuaFaultModel<uint32_t>;
template class LuaFaultModel<int64_t>;
template class LuaFaultModel<uint64_t>;
template class LuaFaultModel<float>;
template class LuaFaultModel<double>;
template class LuaFaultModel<long double>;

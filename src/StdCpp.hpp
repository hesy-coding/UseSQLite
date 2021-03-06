/**
 Copyright (c) 2015, 2coding
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **/

#ifndef StdCpp_hpp
#define StdCpp_hpp

#if _MSC_VER > 1900 //Visual Studio 2015 (14.0)
#define _USQL_MEMBER_FUNCTION_DELETE_ENABLE 1
#define _USQL_ENUM_CLASS_DEF(name) enum class name
#define _USQL_ENUM_VALUE(type, value) type::value

#else
#define _USQL_MEMBER_FUNCTION_DELETE_ENABLE 0
#define _USQL_ENUM_CLASS_DEF(name) enum name
#define _USQL_ENUM_VALUE(type, value) value
#endif


#include <string>
#include <sstream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

#ifdef USQL_STD_TR1
#include <tr1/functional>
#include <tr1/type_traits>
#include <tr1/memory>
namespace tr1 = std::tr1;

#else
#include <functional>
#include <type_traits>
#include <memory>
namespace tr1 = std;

#endif

#include <stdint.h>
#include <cassert>
#include <ctime>
#include <cstdio>

#include <sqlite3.h>
#define _USQL_SQLITE_CREATE_FUNCTION_V2_ENABLE 1
#define _USQL_SQLITE_ERRSTR(c) sqlite3_errstr((c)) 

#endif /* StdCpp_hpp */

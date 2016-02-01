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

#ifndef USQLDefs_hpp
#define USQLDefs_hpp

#include "USQLStdCpp.hpp"

#define USQL_OK(code) ((code) == SQLITE_OK)
#define USQL_STEP_OK(code) ((code) == SQLITE_DONE || (code) == SQLITE_ROW)
#define USQL_QUERY_OK(code) ((code) == SQLITE_ROW)

#define USQL_LOCK
#define USQL_START_LOCK { USQL_LOCK
#define USQL_UNLOCK }

//defines
#define USQL_ERROR_INTEGER 0
#define USQL_ERROR_TEXT ""
#define USQL_ERROR_FLOAT (double)0.0f
#define USQL_ERROR_BLOB ""

#define USQL_INVALID_COLUMN_INDEX -1

typedef enum {
    USQLInvalidType = -1,
    USQLInteger,
    USQLText,
    USQLFloat,
    USQLBlob,
    USQLNull,
}USQLColumnType;

#endif /* USQLDefs_hpp */

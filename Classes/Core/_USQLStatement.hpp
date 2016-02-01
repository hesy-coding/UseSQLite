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

#ifndef _USQLSatement_hpp
#define _USQLSatement_hpp

#include "USQLDefs.hpp"
#include "USQLObject.hpp"

namespace usqlite {
    class _USQLDatabase;
    class _USQLStatement : public USQLShareObject
    {
    public:
        static _USQLStatement *create(const std::string &cmd, _USQLDatabase *db);
        
        bool reset();
        bool step();
        bool query();
        void finilize();
        
        inline sqlite3_stmt *statement() {
            return _stmt;
        }
        
        inline int columnCount() const {
            return static_cast<int>(_columns.size());
        }
        int columnIndexForName(const std::string &name) const;
        USQLColumnType typeForColumnIndex(int i) const;
        
        template<class Type>
        Type staticValueForColumnIndex(int idx, USQLColumnType expect, Type (*fn)(sqlite3_stmt *, int), Type err) {
            if (!_USQLStatement::safeTypeCast(typeForColumnIndex(idx), expect)) {
                return err;
            }
            
            if (!fn) {
                return err;
            }
            
            return fn(_stmt, idx);
        }
        
    private:
        void initColumnInfo();
        void clearColumnInfo() {
            _columns.clear();
            _columnTypes.clear();
        }
        
        USQLColumnType typeForColumn(int i);
        
        static bool safeTypeCast(USQLColumnType actual, USQLColumnType expect) {
            return actual == expect;
        }
        
    private:
        _USQLStatement(const std::string &cmd, _USQLDatabase *db);
        _USQLStatement();
        
        bool prepare();
        
    private:
        const std::string _command;
        sqlite3_stmt *_stmt;
        _USQLDatabase *_db;
        
        std::map<std::string, int> _columns;
        std::vector<USQLColumnType> _columnTypes;
    };
}

#endif /* _USQLSatement_hpp */
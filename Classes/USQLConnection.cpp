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

#include "USQLConnection.hpp"
#include "USQLDefs.hpp"
#include "_USQLStatement.hpp"
#include "_USQLDatabase.hpp"

#define _USQL_CONNECTION_FIELD (dynamic_cast<_USQLDatabase *>(_field))

namespace usqlite {
    USQLConnection::USQLConnection(const std::string &fn) {
        _field = new _USQLDatabase(fn);
    }
    
    USQLConnection::~USQLConnection() {
        delete _USQL_CONNECTION_FIELD;
    }
    
    sqlite3 *USQLConnection::db() {
        return _USQL_CONNECTION_FIELD->db();
    }
    
    bool USQLConnection::open() {
        return open(SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    }
    
    bool USQLConnection::open(int flags) {
        USQL_START_LOCK;
        return _USQL_CONNECTION_FIELD->open(flags);
        USQL_UNLOCK;
    }
    
    bool USQLConnection::isOpenning() const {
        USQL_START_LOCK;
        return _USQL_CONNECTION_FIELD->isOpenning();
        USQL_UNLOCK;
    }
    
    bool USQLConnection::closeSync() {
        USQL_START_LOCK;
        return _USQL_CONNECTION_FIELD->closeSync();
        USQL_UNLOCK;
    }
    
    void USQLConnection::close() {
        USQL_START_LOCK;
        _USQL_CONNECTION_FIELD->close();
        USQL_UNLOCK;
    }
    
    void USQLConnection::setLastErrorCode(int code) {
        USQL_START_LOCK;
        _USQL_CONNECTION_FIELD->setLastErrorCode(code);
        USQL_UNLOCK;
    }
    
    int USQLConnection::lastErrorCode() const {
        USQL_START_LOCK;
        return _USQL_CONNECTION_FIELD->lastErrorCode();
        USQL_UNLOCK;
    }
    
    std::string USQLConnection::lastErrorMessage() {
        USQL_START_LOCK;
        return _USQL_CONNECTION_FIELD->lastErrorMessage();
        USQL_UNLOCK;
    }
    
    bool USQLConnection::exec(const std::string &cmd) {
        if (cmd.empty()) {
            return false;
        }
        
        return exec(USQLCommand(cmd));
    }
    
    bool USQLConnection::exec(const usqlite::USQLCommand &cmd) {
        if (!isOpenning()) {
            return false;
        }
        
        USQL_START_LOCK;
        _USQLStatement *stmt = _USQLStatement::create(cmd.command(), _USQL_CONNECTION_FIELD);
        bool ret = stmt->step();
        stmt->finilize();
        stmt->release();
        
        return ret;
        USQL_UNLOCK;
    }
    
    USQLQuery USQLConnection::query(const std::string &cmd) {
        return query(USQLCommand(cmd));
    }
    
    USQLQuery USQLConnection::query(const usqlite::USQLCommand &cmd) {
        USQL_START_LOCK;
        _USQLStatement *stmt = _USQLStatement::create(cmd.command(), _USQL_CONNECTION_FIELD);
        USQLQuery query(stmt);
        stmt->release();
        
        return query;
        USQL_UNLOCK;
    }
}
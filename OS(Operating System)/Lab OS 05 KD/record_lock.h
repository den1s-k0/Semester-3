#pragma once

#include <windows.h>

struct RecordLock {
    CRITICAL_SECTION cs;
    int readerCount;
    bool writerActive;
};

bool initLocks(RecordLock* locks, int count);
void cleanupLocks(RecordLock* locks, int count);
void enterReadLock(RecordLock& lock);
void exitReadLock(RecordLock& lock);
void enterWriteLock(RecordLock& lock);
void exitWriteLock(RecordLock& lock);
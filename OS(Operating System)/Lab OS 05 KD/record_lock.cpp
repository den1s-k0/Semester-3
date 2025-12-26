#include "record_lock.h"

bool initLocks(RecordLock* locks, int count) {
    for (int i = 0; i < count; i++) {
        InitializeCriticalSection(&locks[i].cs);
        locks[i].readerCount = 0;
        locks[i].writerActive = false;
    }
    return true;
}

void cleanupLocks(RecordLock* locks, int count) {
    for (int i = 0; i < count; i++) {
        DeleteCriticalSection(&locks[i].cs);
    }
}

void enterReadLock(RecordLock& lock) {
    while (true) {
        EnterCriticalSection(&lock.cs);
        if (!lock.writerActive) {
            lock.readerCount++;
            LeaveCriticalSection(&lock.cs);
            break;
        }
        LeaveCriticalSection(&lock.cs);
        Sleep(1);
    }
}

void exitReadLock(RecordLock& lock) {
    EnterCriticalSection(&lock.cs);
    lock.readerCount--;
    LeaveCriticalSection(&lock.cs);
}

void enterWriteLock(RecordLock& lock) {
    while (true) {
        EnterCriticalSection(&lock.cs);
        if (!lock.writerActive && lock.readerCount == 0) {
            lock.writerActive = true;
            LeaveCriticalSection(&lock.cs);
            break;
        }
        LeaveCriticalSection(&lock.cs);
        Sleep(1);
    }
}

void exitWriteLock(RecordLock& lock) {
    EnterCriticalSection(&lock.cs);
    lock.writerActive = false;
    LeaveCriticalSection(&lock.cs);
}
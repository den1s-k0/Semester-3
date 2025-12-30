#include "test_record_lock.h"

TEST(RecordLockTest, InitLocks) {
    RecordLock locks[3];

    EXPECT_TRUE(initLocks(locks, 3));

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(locks[i].readerCount, 0);
        EXPECT_FALSE(locks[i].writerActive);
    }

    cleanupLocks(locks, 3);
}

TEST(RecordLockTest, ReadLockSingleThread) {
    RecordLock lock;
    initLocks(&lock, 1);

    enterReadLock(lock);
    EXPECT_EQ(lock.readerCount, 1);
    EXPECT_FALSE(lock.writerActive);

    exitReadLock(lock);
    EXPECT_EQ(lock.readerCount, 0);

    cleanupLocks(&lock, 1);
}

TEST(RecordLockTest, WriteLockSingleThread) {
    RecordLock lock;
    initLocks(&lock, 1);

    enterWriteLock(lock);
    EXPECT_TRUE(lock.writerActive);
    EXPECT_EQ(lock.readerCount, 0);

    exitWriteLock(lock);
    EXPECT_FALSE(lock.writerActive);

    cleanupLocks(&lock, 1);
}

TEST(RecordLockTest, ReadWriteExclusion) {
    RecordLock lock;
    initLocks(&lock, 1);

    enterReadLock(lock);
    EXPECT_EQ(lock.readerCount, 1);

    EXPECT_FALSE(lock.writerActive);

    exitReadLock(lock);

    enterWriteLock(lock);
    EXPECT_TRUE(lock.writerActive);
    EXPECT_EQ(lock.readerCount, 0);

    exitWriteLock(lock);

    cleanupLocks(&lock, 1);
}

TEST(RecordLockTest, MultipleReaders) {
    RecordLock lock;
    initLocks(&lock, 1);

    enterReadLock(lock);
    enterReadLock(lock);

    EXPECT_EQ(lock.readerCount, 2);
    EXPECT_FALSE(lock.writerActive);

    exitReadLock(lock);
    EXPECT_EQ(lock.readerCount, 1);

    exitReadLock(lock);
    EXPECT_EQ(lock.readerCount, 0);

    cleanupLocks(&lock, 1);
}

TEST(RecordLockTest, CleanupLocks) {
    RecordLock locks[2];

    EXPECT_TRUE(initLocks(locks, 2));

    EXPECT_NO_THROW(cleanupLocks(locks, 2));
}
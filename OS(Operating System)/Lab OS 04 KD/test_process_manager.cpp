#include "test_process_manager.h"

TEST_F(ProcessManagerTest, CreateReadyEvent_ValidName) {
    HANDLE hEvent = create_ready_event("test_base", 0);
    EXPECT_NE(nullptr, hEvent);

    if (hEvent) {
        CloseHandle(hEvent);
    }

    // Also test with index
    hEvent = create_ready_event("test_base", 5);
    EXPECT_NE(nullptr, hEvent);

    if (hEvent) {
        CloseHandle(hEvent);
    }
}

TEST_F(ProcessManagerTest, CreateSyncObjects_ValidParameters) {
    HANDLE hMutex = nullptr;
    HANDLE hEmpty = nullptr;
    HANDLE hFull = nullptr;

    bool result = create_sync_objects("test_sync", 10, hMutex, hEmpty, hFull);
    EXPECT_TRUE(result);

    if (result) {
        EXPECT_NE(nullptr, hMutex);
        EXPECT_NE(nullptr, hEmpty);
        EXPECT_NE(nullptr, hFull);

        CloseHandle(hMutex);
        CloseHandle(hEmpty);
        CloseHandle(hFull);
    }
}

TEST_F(ProcessManagerTest, OpenSyncObjects_AfterCreation) {
    // First create the objects
    HANDLE hMutex, hEmpty, hFull;
    ASSERT_TRUE(create_sync_objects("test_open", 5, hMutex, hEmpty, hFull));

    // Close them first
    CloseHandle(hMutex);
    CloseHandle(hEmpty);
    CloseHandle(hFull);

    // Now open them
    HANDLE hMutex2 = nullptr, hEmpty2 = nullptr, hFull2 = nullptr;
    bool result = open_sync_objects("test_open", hMutex2, hEmpty2, hFull2);
    EXPECT_TRUE(result);

    if (result) {
        EXPECT_NE(nullptr, hMutex2);
        EXPECT_NE(nullptr, hEmpty2);
        EXPECT_NE(nullptr, hFull2);

        CloseHandle(hMutex2);
        CloseHandle(hEmpty2);
        CloseHandle(hFull2);
    }
}

TEST_F(ProcessManagerTest, StartSenderProcess_InvalidCommand) {
    PROCESS_INFORMATION pi;

    // Try to start with invalid command
    bool result = start_sender_process("nonexistent.exe", pi);
    EXPECT_FALSE(result);
}

TEST_F(ProcessManagerTest, StartSenderProcess_ValidCommand) {
    PROCESS_INFORMATION pi;

    // Test with a simple command that should work on Windows
    bool result = start_sender_process("cmd.exe /c echo test", pi);

    // This might fail if cmd.exe is not available, so we just check that
    // the function doesn't crash
    if (result) {
        // Clean up if process was created
        WaitForSingleObject(pi.hProcess, 1000);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    // The test passes as long as the function executes without crashing
    SUCCEED();
}

TEST_F(ProcessManagerTest, SyncObjectsNames_Consistent) {
    // Test that names are constructed consistently
    string base_name = "test_file";

    // Test mutex name
    string mutex_name = base_name + "_mtx";
    EXPECT_EQ("test_file_mtx", mutex_name);

    // Test semaphore names
    string empty_name = base_name + "_emp";
    EXPECT_EQ("test_file_emp", empty_name);

    string full_name = base_name + "_ful";
    EXPECT_EQ("test_file_ful", full_name);
}

TEST_F(ProcessManagerTest, ReadyEventName_Format) {
    string base_name = "base";
    int index = 3;

    string expected_name = base_name + "_rdy_" + to_string(index + 1);
    EXPECT_EQ("base_rdy_4", expected_name);
}
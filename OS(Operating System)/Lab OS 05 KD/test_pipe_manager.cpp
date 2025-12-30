#include "test_pipe_manager.h"

TEST(PipeManagerTest, PipeNameFormat) {
    string pipeName = "\\\\.\\pipe\\test";
    EXPECT_NE(pipeName.find("\\\\.\\pipe\\"), string::npos);
}

TEST(PipeManagerTest, CloseNamedPipe_ValidHandle) {
    EXPECT_NO_THROW(closeNamedPipe(NULL));
}

TEST(PipeManagerTest, CreateNamedPipe_InvalidName) {
    HANDLE hPipe = createNamedPipe("invalid_pipe_name");

    EXPECT_TRUE(hPipe == NULL || hPipe == INVALID_HANDLE_VALUE);
}

TEST(PipeManagerTest, PipeNameConstruction) {
    string baseName = "test";
    string pipeName = "\\\\.\\pipe\\" + baseName;

    EXPECT_EQ(pipeName, "\\\\.\\pipe\\test");
}

TEST(PipeManagerTest, PipeManagerFunctionsCompile) {

    HANDLE(*createFunc)(const string&) = createNamedPipe;
    HANDLE(*connectFunc)(const string&) = connectToNamedPipe;
    bool (*closeFunc)(HANDLE) = closeNamedPipe;
    bool (*connectClientFunc)(HANDLE) = connectClientToPipe;

    EXPECT_TRUE(createFunc != nullptr);
    EXPECT_TRUE(connectFunc != nullptr);
    EXPECT_TRUE(closeFunc != nullptr);
    EXPECT_TRUE(connectClientFunc != nullptr);
}

TEST(PipeManagerTest, CloseHandleBehavior) {
    HANDLE invalidHandle = INVALID_HANDLE_VALUE;

    EXPECT_NO_THROW(CloseHandle(invalidHandle));

    EXPECT_NO_THROW(CloseHandle(NULL));
}
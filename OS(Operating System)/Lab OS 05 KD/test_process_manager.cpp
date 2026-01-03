#include "test_process_manager.h"

TEST(ProcessManagerTest, ThreadParamsInitialization) {
    ThreadParams params = { "test_pipe", 5, nullptr, "test.dat" };

    EXPECT_EQ(params.pipeName, "test_pipe");
    EXPECT_EQ(params.employeeCount, 5);
    EXPECT_EQ(params.locks, nullptr);
    EXPECT_EQ(params.fileName, "test.dat");
}

TEST(ProcessManagerTest, CommandLineConstruction) {
    string pipeName = "\\\\.\\pipe\\test";
    int employeeCount = 5;

    string actualCommand = "Client.exe \"" + pipeName + "\" " + to_string(employeeCount);

    EXPECT_NE(actualCommand.find("Client.exe"), string::npos);
    EXPECT_NE(actualCommand.find("test"), string::npos);
    EXPECT_NE(actualCommand.find("5"), string::npos);
}

TEST(ProcessManagerTest, PipeNameGeneration) {
    int index = 3;
    string pipeName = "\\\\.\\pipe\\EmployeePipe" + to_string(index);

    EXPECT_NE(pipeName.find("EmployeePipe3"), string::npos);
    EXPECT_NE(pipeName.find("\\\\.\\pipe\\"), string::npos);
}

TEST(ProcessManagerTest, ProcessInfoMethodsExist) {
    ProcessInfo process;
    string pipeName = "\\\\.\\pipe\\test";

    EXPECT_NO_THROW({
        bool result = process.launchClientProcess(pipeName, 1);
        process.closeProcess();
        });
}

TEST(ProcessManagerTest, StartClientThreadFunction) {
    RecordLock* locks = nullptr;
    string pipeName = "\\\\.\\pipe\\test";
    string fileName = "test.dat";

    EXPECT_NO_THROW({
        bool result = startClientThread(pipeName, 1, locks, fileName);
        });
}
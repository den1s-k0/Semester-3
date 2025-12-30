#include "test_constants.h"

TEST(ConstantsTest, ServerConstantsValues) {
    EXPECT_EQ(ServerConstants::MIN_EMPLOYEES, 1);
    EXPECT_EQ(ServerConstants::MAX_EMPLOYEES, 1000);
    EXPECT_EQ(ServerConstants::MIN_CLIENTS, 1);
    EXPECT_EQ(ServerConstants::MAX_CLIENTS, 100);

    EXPECT_GT(ServerConstants::MAX_EMPLOYEES, ServerConstants::MIN_EMPLOYEES);
    EXPECT_GT(ServerConstants::MAX_CLIENTS, ServerConstants::MIN_CLIENTS);
}

TEST(ConstantsTest, ClientConstantsValues) {
    EXPECT_EQ(ClientConstants::MODIFY_CHOICE, 1);
    EXPECT_EQ(ClientConstants::READ_CHOICE, 2);
    EXPECT_EQ(ClientConstants::EXIT_CHOICE, 3);

    EXPECT_NE(ClientConstants::MODIFY_CHOICE, ClientConstants::READ_CHOICE);
    EXPECT_NE(ClientConstants::READ_CHOICE, ClientConstants::EXIT_CHOICE);
    EXPECT_NE(ClientConstants::MODIFY_CHOICE, ClientConstants::EXIT_CHOICE);
}

TEST(ConstantsTest, OperationTypeValues) {
    EXPECT_EQ(OperationType::READ_OPERATION, 1);
    EXPECT_EQ(OperationType::WRITE_OPERATION, 2);
    EXPECT_EQ(OperationType::END_OPERATION, 3);

    EXPECT_NE(OperationType::READ_OPERATION, OperationType::WRITE_OPERATION);
    EXPECT_NE(OperationType::WRITE_OPERATION, OperationType::END_OPERATION);
    EXPECT_NE(OperationType::READ_OPERATION, OperationType::END_OPERATION);
}
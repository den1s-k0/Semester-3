#pragma once

namespace ServerConstants {
    const int MIN_EMPLOYEES = 1;
    const int MAX_EMPLOYEES = 1000;
    const int MIN_CLIENTS = 1;
    const int MAX_CLIENTS = 100;
}

namespace ClientConstants {
    const int MODIFY_CHOICE = 1;
    const int READ_CHOICE = 2;
    const int EXIT_CHOICE = 3;
}

namespace OperationType {
    const int READ_OPERATION = 1;
    const int WRITE_OPERATION = 2;
    const int END_OPERATION = 3;
}
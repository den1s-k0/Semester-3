#include "main.h"

int main()
{
	vector<int> mas = createVectorOfZeros();
	int thread_count = cinThreadCount();
	HANDLE* hThread = new HANDLE[thread_count];
	DWORD* dwThread = new DWORD[thread_count];

	for (int i = 0; i < thread_count; i++) {
		hThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread,
			NULL, 0, &dwThread[i]);
		if (hThread[i] == NULL)
			return GetLastError();
	}

	if (WaitForMultipleObjects(thread_count, hThread, TRUE, INFINITE) == WAIT_FAILED)
	{
		cout << "Wait for multiple objects failed." << endl;
		cout << "Press any key to exit." << endl;
	}
	
	for (int i = 0; i < thread_count; i++) {
		CloseHandle(hThread[i]);
	}


	return 0;
}

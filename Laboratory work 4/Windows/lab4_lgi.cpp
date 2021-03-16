#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
using namespace std;

int main()
{
    int number_pides = 2;
    int status;
    STARTUPINFO si;
	PROCESS_INFORMATION piCom;

    for (int i = 0; i < number_pides; i++) {
    	sleep(1);
        ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(STARTUPINFO);
		CreateProcess("C:\\Users\\G L\\Desktop\\systemProgramming\\7171_lgi_thirdLab\\lab4process\\bin\\Release\\lab4process.exe", NULL,
			NULL, NULL, FALSE, 0, NULL, NULL, &si, &piCom);
		_getch();
    }
	CloseHandle(piCom.hThread);
	CloseHandle(piCom.hProcess);

return 0;
}

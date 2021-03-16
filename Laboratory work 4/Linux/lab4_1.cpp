#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

int main()
{
    int number_pides = 2;
    pid_t* pides = (pid_t*)malloc(sizeof(pid_t));
    int status;

    for (int i = 0; i < number_pides; i++)
    {
        sleep(1);
        pid_t pid = fork();
        switch (pid)
        {
            case -1:
                exit(-1);
            case 0:
                cout << "My PID is " << getpid() << endl;
                execl("lab4_2", "", NULL);
            default:
                wait(&status);
        }
    }
    for (int i = 0; i < number_pides; ++i)
    {
        waitpid(pides[i], NULL, {});
    }
    return 0;
}



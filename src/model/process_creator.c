#include <process_creator.h>
#include <stdio.h>
#include <string.h>
#include <utils.h>

#if _WIN32 || _WIN64

#include <windows.h>
int call_prog(char* prog,char *argv[], int argc) {
    printf("windows\n");
    PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
    STARTUPINFO StartupInfo; //This is an [in] parameter
    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
    StartupInfo.cb = sizeof StartupInfo ; //Only compulsory field
    DWORD exit_code;
    _string str;
    str.value = (char *) malloc(100* sizeof(char));
    str.size=100;
    if(str==NULL){
        return -1;
    }
    copy_string(str,prog);
    for(int i=0;i<argc;i++){
        append_string(str," ");
        append_string(str,argv[i]);
    }
    printf("%s\n",str);
    printf("%s\n",prog);
    if(CreateProcess(prog, str,NULL,NULL,FALSE,0,NULL,NULL,&StartupInfo,&ProcessInfo)) {
        WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
        GetExitCodeProcess(ProcessInfo.hProcess, &exit_code);
        printf("returns: %d\n", exit_code);
        CloseHandle(ProcessInfo.hThread);
        CloseHandle(ProcessInfo.hProcess);
    } else {
        printf("The process could not be started...");
    }
    return exit_code;
}
#elif __linux__
//define it for a Linux machine
#include  <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <unistd.h>

int call_prog( char *prog,char *argv[], int argc)  {
    pid_t pid;
    int status;
	printf("\n%s\n",prog);
    pid = fork();

    if (pid == 0) { //child process
        execv(prog,argv);
    }
    waitpid(pid,&status,0);
    int es = WEXITSTATUS(status);
    printf("Exit status was %d\n", es);
    return es;
}

#endif

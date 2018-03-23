#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

extern char **environ;

int main(int argc, char *argv[]){

    char **new_argv;
    char command[] = "ls";
    int idx;
    int link[2];
    char foo[4096];

    new_argv = (char**)malloc(sizeof(char*) *(argc + 1));
    new_argv[0] = command;

    for (idx = 1; idx < argc; idx++) new_argv[idx] = argv[idx];
    new_argv[argc] = NULL;

    pipe(link);
    int pid = fork();
    
    if(pid == 0){
        dup2(link[1], STDOUT_FILENO);
        close(link[0]);
        close(link[1]);

//        execve("/bin/ls", new_argv, environ);

        execl("/usr/bin/gpg", "gpg", "--version", (char*)0);
    }    
    else{
        close(link[1]);
        printf("After execve\n");
        int nbytes = read(link[0], foo, sizeof(foo));
        printf("Output : (%.*s)\n", nbytes, foo);
        //wait();
    }
    return 0;
    


}

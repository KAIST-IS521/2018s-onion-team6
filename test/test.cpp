#include <iostream>
#include <errno.h>
#include <stdio.h>

using namespace std;
#define MAX 256

#define command "gpg2 --version"



int main(){

    FILE *fp;
    int state;

    char buff[MAX];

    fp  = popen(command, "r");
    cout << "Display command result" << endl;
    if(fp!=NULL){
        while(fgets(buff, MAX, fp) != NULL)
            printf("%s", buff);
    }

    state = pclose(fp);
    printf("State is %d\n", state);

    return 0;

}

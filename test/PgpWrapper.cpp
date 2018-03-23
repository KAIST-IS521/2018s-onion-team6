#include "PgpWrapper.h"
#include <iostream>
using namespace std;


enum{
    GET_GPG_VERSION=0,
    IMPORT_PRIVATE_KEY,



};

const char* MY_GPG_OPTION[]={
    "--version",
    "--import",

};

PgpWrapper::~PgpWrapper(){}


PgpWrapper::PgpWrapper(){
    if(CheckProperGPG()) cout << "PROPER_GPG" << endl;              // proper handling needed
    else cout << "INVALID_GPG" << endl;

}

PgpWrapper::PgpWrapper(const string PubKey){
   PgpWrapper();
}

int
PgpWrapper::ImportMyPrivateKey(string privKey){
   
}


void 
PgpWrapper::CleanDisplayedBuf(){
    for(int i = 0; i<MAX_DISPLAY_BUF; i++)DisPlayedBuf[i] = '\0';
}

void
PgpWrapper::CallLocalGPG(string msg, string mOption)
{
    DEBUG cout << msg + "start!!" << endl;
    int link[2];
    CleanDisplayedBuf();
    //int pid;
    pid_t pid ;

    string cmd_option = mOption;

    pipe(link);                 // error handling needed
    pid = fork();               // error hadnling needed
    
    if( pid ==0){
       dup2(link[1], STDOUT_FILENO);
       close(link[0]);
       close(link[1]);
        
        execl(GPG_PATH, GPG_COMMAND, cmd_option ,(char*) 0);
    }

    else{
        close(link[1]);
        DEBUG{  
        cout << "GPG_PATH : " << GPG_PATH << endl;
        cout << "GPG_COMMAND : " << GPG_COMMAND << endl;
        cout << "cmd_option : " << cmd_option <<endl;
        
        }
      
       
      int nbytes = read(link[0], DisPlayedBuf, sizeof(DisPlayedBuf));

    DEBUG  printf("Output : (%.*s)\n", nbytes, DisPlayedBuf); 
    }

}

int 
PgpWrapper::CheckProperGPG(){

    CallLocalGPG("CheckerProperGPG", MY_GPG_OPTION[GET_GPG_VERSION])
    /*

    DEBUG cout << "CheckProperGPG start!!" << endl;
    int link[2];
    CleanDisplayedBuf();
    //int pid;
    pid_t pid ;


    pipe(link);                 // error handling needed
    pid = fork();               // error hadnling needed
    
    if( pid ==0){
       dup2(link[1], STDOUT_FILENO);
       close(link[0]);
       close(link[1]);
        
        execl(GPG_PATH, GPG_COMMAND, MY_GPG_OPTION[GET_GPG_VERSION],(char*) 0);
    }

    else{
        close(link[1]);
        DEBUG{  
        cout << "GPG_PATH : " << GPG_PATH << endl;
        cout << "GPG_COMMAND : " << GPG_COMMAND << endl;
        cout << "MY_GPG_OPTION[GET_GPG_VERSION] : " << MY_GPG_OPTION[GET_GPG_VERSION] <<endl;
        
        }
      
       
      int nbytes = read(link[0], DisPlayedBuf, sizeof(MAX_DISPLAY_BUF));
      */
      char sig[11];
      for(int i = 0; i<10 ; i++) sig[i] = DisPlayedBuf[i];
      sig[10] = '\0';
      string mSig = sig;
      if(mSig.find("(GnuPG") != string::npos){

          return PROPER_GPG;
      }
      //printf("output : %.*s\n",10, foo );  
        // printf("Output : (%.*s)\n", nbytes, foo); 
    }


    return INVALID_GPG;
}



/*


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

        execl("/bin/ls", "ls", "-1", (char*)0);
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
*/

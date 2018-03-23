#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

const char* buf[]={
    "gpg --veirsion",
};


int main(){

    cout << buf[0] << endl;
   printf("%s",buf[0] );
    return 0;
}

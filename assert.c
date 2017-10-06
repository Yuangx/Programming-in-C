#include<assert.h>

//learning

int main(int argc ,char *argv[]){
    assert(argc >= 2);
    assert(isalnum(argv[1][0]));
    return 0;
}

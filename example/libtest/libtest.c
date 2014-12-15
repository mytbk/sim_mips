#include "libs.h"
#include "printf.h"

int main(int argc, char *argv[])
{
    char mystr[100];
    int (*scmp)(const char*, const char*);
    
    fprintf(stdout, "argc=%d\n");
    
    if (argc>=0) {
        scmp = strcmp;
    } else {
        exit(1);
    }
        
    strcpy(mystr, "This is a program.");
    if (scmp(mystr, "This is a program.")!=0) {
        fprintf(stderr, "string test failed.\n");
    } else {
        fprintf(stderr, "string test ok.\n");
    }
        
    return 0;
}

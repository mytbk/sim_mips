#include "libs.h"
#include "printf.h"

typedef int Enumeration;

typedef struct record
{
    struct record *Ptr_Comp;
    Enumeration    Discr;
    union {
        struct
        {
            Enumeration Enum_Comp;
            int         Int_Comp;
            char        Str_Comp [31];
        } var_1;
        struct
        {
            Enumeration E_Comp_2;
            char        Str_2_Comp [31];
        } var_2;
        struct
        {
            char        Ch_1_Comp;
            char        Ch_2_Comp;
        } var_3;
    } variant;
} Rec_Type, *Rec_Pointer;

int main(int argc, char *argv[])
{
    char mystr[100];
    int (*scmp)(const char*, const char*);
    
    Rec_Type *Ptr_Glob = (Rec_Type*) malloc (sizeof (Rec_Type));
    strcpy (Ptr_Glob->variant.var_1.Str_Comp, 
            "DHRY");
    printf("%s\n", Ptr_Glob->variant.var_1.Str_Comp);

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

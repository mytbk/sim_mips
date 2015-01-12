#define MSIZE 1000
int A[MSIZE][MSIZE], B[MSIZE][MSIZE];

int main()
{
    int i, j, k;
#ifdef TRANS01    
    for (i=0; i<MSIZE; i++) {
        for (j=0; j<MSIZE; j++) {
            B[i][j] = A[j][i];
        }
    }
#endif
#ifdef TRANS02
    for (i=0; i<MSIZE; i+=2) {
        for (j=0; j<MSIZE; j+=2) {
            B[i][j] = A[j][i];
            B[i][j+1] = A[j+1][i];
            B[i+1][j] = A[j][i+1];
            B[i+1][j+1] = A[j+1][i+1];
        }
    }
#endif
    return 0;
}











#define MSIZE 100
int A[MSIZE][MSIZE], B[MSIZE][MSIZE], C[MSIZE][MSIZE];

int main()
{
    int i, j, k, nTimes;

    for (nTimes=0; nTimes<4; nTimes++) {
#ifdef MATRIX01
        for (i=0; i<MSIZE; i++) {
            for (j=0; j<MSIZE; j++) {
                int sum = 0;
                for (k=0; k<MSIZE; k++) {
                    sum += A[i][k]*B[k][j];
                }
                C[i][j] = sum;
            }
        }
#endif
#ifdef MATRIX02
        for (j=0; j<MSIZE; j++) {
            for (i=0; i<MSIZE; i++) {
                int sum = 0;
                for (k=0; k<MSIZE; k++) {
                    sum += A[i][k]*B[k][j];
                }
                C[i][j] = sum;
            }
        }
#endif
    }
    
}

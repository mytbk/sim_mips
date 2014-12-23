#define MSIZE 100
static int A[MSIZE][MSIZE], B[MSIZE][MSIZE], C[MSIZE][MSIZE];

int main()
{
    int i, j, k, nTimes;

    for (nTimes=0; nTimes<4; nTimes++) {
        for (i=0; i<MSIZE; i++) {
            for (j=0; j<MSIZE; j++) {
                int sum = 0;
                for (k=0; k<MSIZE; k++) {
                    sum += A[i][k]*B[k][j];
                }
                C[i][j] = sum;
            }
        }
    }
    
}

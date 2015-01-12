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
        for (i=0; i<MSIZE; i++) {
            for (j=0; j<MSIZE; j++) {
                int aij = A[i][j];
                for (k=0; k<MSIZE; k++) {
                    C[i][k] += aij*B[j][k];
                }
            }
        }
#endif
#ifdef MATRIX03
        for (i=0; i<MSIZE; i+=2) {
            for (j=0; j<MSIZE; j+=2) {
                int a=0,b=0,c=0,d=0;
                for (k=0; k<MSIZE; k+=2) {
                    a += A[i][k]*B[k][j] + A[i][k+1]*B[k+1][j];
                    b += A[i][k]*B[k][j+1] + A[i][k+1]*B[k+1][j+1];
                    c += A[i+1][k]*B[k][j] + A[i+1][k+1]*B[k+1][j];
                    d += A[i+1][k]*B[k][j+1] + A[i+1][k+1]*B[k+1][j+1];
                }
                C[i][j] = a;
                C[i][j+1] = b;
                C[i+1][j] = c;
                C[i+1][j+1] = d;
            }
        }
#endif
    }
    return 0;
}

#include "printf.h"
#include "data.h"

void quick_sort(int s[], int l, int r)
{
    int i;
    
    while (r-l>20){
        int x = s[l];
        
        int i = l, j = r;
        while (i<j){
            while (i<j && s[j]>x){
                j--;
            }
            if (i<j){
                s[i] = s[j];
                i++;
            }
                        
            while (i<j && s[i]<x){
                i++;
            }
            if (i<j){
                s[j] = s[i];
                j--;
            }
        }
        s[i] = x;

        if (i*2>l+r){
            quick_sort(s, i+1, r);
            r = i-1;
        }else{
            quick_sort(s, l, i-1);
            l = i+1;
        }
    }
    // do insertion sort
    for (i=l+1; i<=r; i++){
        int tmp = s[i];
        int j;
        for (j=i; j>l; j--){
            if (s[j-1]>tmp){
                s[j] = s[j-1];
            }else{
                break;
            }
        }
        s[j] = tmp;
    }
}

int main()
{
    int i;
    quick_sort(array, 0, NUM);
#ifdef PRINT
    for (i=0; i<NUM; i++) {
        printf("%d\n", array[i]);
    }
#endif
    return 0;
}


# include "lab_1.h"
# include <iostream>
using namespace std;

int main(){
    data_t A[3] = {190,62,53};
    data_t B[3] = {56,6,3};
    data_t C[3] = {49,82,23};
    data_t grnd_truth[3] = {0};
    for(int i=0;i<3;i++){
        grnd_truth[i] = 2*A[i] +B[i]-C[i];
    }
    data_t output[3] = {0};
    for(int i=0;i<3;i++){
        lab_1(A[i] ,B[i],C[i], output[i]);
    }
    
    int ret_val = 0;
    for(int i =0; i<3;i++){
        if(grnd_truth[i]!=output[i]){
            ret_val++;
        }
    }


    cout<< "There were "<<ret_val<<"Errors";
    return 0;
}
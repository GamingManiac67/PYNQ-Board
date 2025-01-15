#include "demapping.h"

void demapping(int A, int B, int &I, int &Q){
    #pragma HLS INTERFACE mode=s_axilite port=A
    #pragma HLS INTERFACE mode=s_axilite port=B
    #pragma HLS INTERFACE mode=s_axilite port=I
    #pragma HLS INTERFACE mode=s_axilite port=Q
    #pragma HLS INTERFACE mode=ap_ctrl_none port=return
    int mappingTable[16][2] = {
        {-3, -3}, {-3, -1}, {-3, 3}, {-3, 1},
        {-1, -3}, {-1, -1}, {-1, 3}, {-1, 1},
        {3, -3}, {3, -1}, {3, 3}, {3, 1},
        {1, -3}, {1, -1}, {1, 3}, {1, 1}
    };
    float dist = 0;
    float min_dist = 10000;
    int min_index = 0;

    for (int i =0; i<16;i++){
        dist = (A  - mappingTable[i][0]*100) * (A  - mappingTable[i][0]*100) +(B - mappingTable[i][1]*100) * (B - mappingTable[i][1]*100);

        if(min_dist>dist){
            min_dist = dist;
            min_index = i;            
        }
    }

    I = mappingTable[min_index][0];
    Q = mappingTable[min_index][1];

}
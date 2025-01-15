# include "simple_func.h"

void lab_1(data_t A,data_t B,data_t C, data_t &Y){
#pragma HLS INTERFACE mode=s_axilite port=A
#pragma HLS INTERFACE mode=s_axilite port=B
#pragma HLS INTERFACE mode=s_axilite port=C
#pragma HLS INTERFACE mode=s_axilite port=Y
#pragma HLS INTERFACE mode=ap_ctrl_none port=return
    Y = 2*A+B-C;
}
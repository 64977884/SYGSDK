#ifndef FILTER_NOISE_DOT_RUNTIME_ADDAPTER_H
#define FILTER_NOISE_DOT_RUNTIME_ADDAPTER_H

//此处实现，主要将之前和笔画数据结构转换成实际滤噪的结构，方案测试与集成兼容之前旧的数据结构

#include "filter_noise_dot_runtime.h"
#include "stroke_struct.h"

//定义一个中转的数据结构，封装成实时过滤的输入点集
typedef struct _S_ENCAP_RUNTIME_INPUT_DOT_SET{
    //输入点集
    vector<OID_DOT_VAL> input_v_dot;

    //是否是新的一个笔画
    bool b_new_stroke;

    //如果是新的笔画，需要设置笔画时间
    S_STROKE_TIME stroke_time;
}S_ENCAP_RUNTIME_INPUT_DOT_SET;

//将单个笔画数据，拆分成若干个实时滤噪接口的输入点集，方便模拟实时滤噪场景
void split_stroke_into_runtime_input_dot_v(const STROKE_ITEM &stroke, vector<S_ENCAP_RUNTIME_INPUT_DOT_SET> &output_v_dot_set);

//根据封装的中转结构，调用实时滤噪接口，返回滤噪结果点集
void encap_runtime_noisedot_interface(const S_ENCAP_RUNTIME_INPUT_DOT_SET &input_v_dot,
                                      S_STROKE_STRUCT pre_stroke,
                                      vector<OID_DOT_VAL> &output_v_dot,
                                      PRE_STROKE_USEFUL_DOT_SET &pre_stroke_set);

//兼容之前整个笔画滤噪接口，底层实现根据实时滤噪接口实现，输入为整个笔画，输出为整个笔画滤噪结构，滤噪过程拆分成实时滤噪包进行滤噪
//此封装接口可能返回两个笔画，一个为正常滤噪笔画，一个为上一笔画点数过少产生的笔画
void encap_filter_algorithm_interface(const STROKE_ITEM &stroke, const STROKE_ITEM &pre_stroke, STROKE_ITEM &no_noise_stroke);

//定义每多少个点拆成一个实时滤噪输入点集
//#define DOT_NUMER_PER_RUNTIME_INPUT_DOT_V       1

bool encap_reconstruct_stroke_dot_imageidx(const STROKE_ITEM &stroke, STROKE_ITEM &reconstruct_stroke);

#endif // FILTER_NOISE_DOT_RUNTIME_ADDAPTER_H

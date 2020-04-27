#ifndef FILTER_NOISE_DOT_RUNTIME_ADDAPTER_H
#define FILTER_NOISE_DOT_RUNTIME_ADDAPTER_H

//�˴�ʵ�֣���Ҫ��֮ǰ�ͱʻ����ݽṹת����ʵ������Ľṹ�����������뼯�ɼ���֮ǰ�ɵ����ݽṹ

#include "filter_noise_dot_runtime.h"
#include "stroke_struct.h"

//����һ����ת�����ݽṹ����װ��ʵʱ���˵�����㼯
typedef struct _S_ENCAP_RUNTIME_INPUT_DOT_SET{
    //����㼯
    vector<OID_DOT_VAL> input_v_dot;

    //�Ƿ����µ�һ���ʻ�
    bool b_new_stroke;

    //������µıʻ�����Ҫ���ñʻ�ʱ��
    S_STROKE_TIME stroke_time;
}S_ENCAP_RUNTIME_INPUT_DOT_SET;

//�������ʻ����ݣ���ֳ����ɸ�ʵʱ����ӿڵ�����㼯������ģ��ʵʱ���볡��
void split_stroke_into_runtime_input_dot_v(const STROKE_ITEM &stroke, vector<S_ENCAP_RUNTIME_INPUT_DOT_SET> &output_v_dot_set);

//���ݷ�װ����ת�ṹ������ʵʱ����ӿڣ������������㼯
void encap_runtime_noisedot_interface(const S_ENCAP_RUNTIME_INPUT_DOT_SET &input_v_dot,
                                      S_STROKE_STRUCT pre_stroke,
                                      vector<OID_DOT_VAL> &output_v_dot,
                                      PRE_STROKE_USEFUL_DOT_SET &pre_stroke_set);

//����֮ǰ�����ʻ�����ӿڣ��ײ�ʵ�ָ���ʵʱ����ӿ�ʵ�֣�����Ϊ�����ʻ������Ϊ�����ʻ�����ṹ��������̲�ֳ�ʵʱ�������������
//�˷�װ�ӿڿ��ܷ��������ʻ���һ��Ϊ��������ʻ���һ��Ϊ��һ�ʻ��������ٲ����ıʻ�
void encap_filter_algorithm_interface(const STROKE_ITEM &stroke, const STROKE_ITEM &pre_stroke, STROKE_ITEM &no_noise_stroke);

//����ÿ���ٸ�����һ��ʵʱ��������㼯
//#define DOT_NUMER_PER_RUNTIME_INPUT_DOT_V       1

bool encap_reconstruct_stroke_dot_imageidx(const STROKE_ITEM &stroke, STROKE_ITEM &reconstruct_stroke);

#endif // FILTER_NOISE_DOT_RUNTIME_ADDAPTER_H

#ifndef FILTER_NOISE_DOT_RUNTIME_H
#define FILTER_NOISE_DOT_RUNTIME_H

#include "vector"
#include "stroke_struct.h"
#include <math.h>
#include <map>

using namespace std;

#define DEBUG_RUNTIME_FILETER_ENABLE    0

//����ʵʱ���뷵�ص�״̬����
typedef enum _E_FILETER_RUNTIME_RET_STATUS{
    //����״̬���أ���ʾ�˴δ���������ɹ��˳����ɸ������㣬�����ĵ�����Ϊ0
    RUNTIME_FILTER_RET_NORMAL,

    //��ʾ�˴�����û�п��õ�������,ȫ��Ϊ���
    RUNTIME_FILTER_RET_NO_USE_DOT,

    //��ʾ�����㷨����ȷ�ϱʻ��ɿ���,��ʱû�п��õ㷵��
    RUNTIME_FILTER_RET_FIND_RELIABLE_DOT,

//    //��ʾ��һ�ʻ����ڴ����ݶ���Ч��״̬���µıʻ�������ֱ�ӽ���һ�ʻ��ݶ���Ч����Ϊ��һ�ʻ����������ݵ�
//    RUNTIME_FILTER_RET_PRE_STROKE_DATA_RETURN,

    //�쳣״̬���µıʻ���������һ�ʻ�����ȷ�Ͽɿ��㣬�����һ�ʻ���ʧ
    RUNTIME_FILTER_RET_RRE_STROKE_LOST,

    //�쳣״̬������ĵ㼯Ϊ��
    RUNTIME_FILTER_RET_INPUT_DOT_EMPYT,

    //δ���壬Ĭ�ϳ�ʼ����״̬
    RUNTIME_FILETER_RET_DEFAULT

}E_FILETER_RUNTIME_RET_STATUS;

//����ʻ�ʱ�����ݽṹ
typedef struct _S_STROKE_TIME{
    unsigned int stroke_s;
    unsigned int stroke_ms;
}S_STROKE_TIME;

//����ʵʱ����ӿ�����״̬
typedef enum _E_FILTER_STATE{
    //Ѱ�ҿɿ���
    FILTER_STATE_FIND_RELIABLE_DOT,

    //�Ѿ��ҵ��ɿ��㣬ʵʱ����
    FILTER_STATE_FILTERING,

    //δ����״̬
    FILTER_STATE_DEFAULT
}E_FILTER_STATE;

//ʵʱ�����ʼ���ӿ�
bool filter_noise_runtime_init();

//����һ���ʻ��������Ϣ,��Ҫ���ڴ洢��һ�ʻ�����Ϣ���ɵ��������
typedef struct _S_STROKE_STRUCT{
    S_STROKE_TIME stroke_time;

	vector <OID_DOT_VAL> stroke_dot_array;

    //�ʻ���ҳ��
    int code_val;
}S_STROKE_STRUCT;

//�����µıʻ���ʼ������һ�ʻ����һ���ɿ����ʱ�䣬���ھ����Ƿ�����һ�ʻ����һ�������ɿ���������룬���ص�λ��
float cal_stroke_interval_time_s(const S_STROKE_TIME &pre_stroke_time, const S_STROKE_TIME &cur_stroke_time);

//��һ�ʻ��Ƿ������ݷ��أ���Ҫ����ʵʱ����ӿ��׳���һ�ʻ��㼯�����ڴ�ȷ�Ͽɿ��㼯��Ȼ���µıʻ��㼯����������
typedef struct _PRE_STROKE_USEFUL_DOT_SET{
    //�Ƿ���Ч�����Ϊtrue������ĵ㼯Ϊ��һ�ʻ����õ㼯
    bool b_valid;

    //���õ�㼯
    vector<OID_DOT_VAL> output_v_dot;
}PRE_STROKE_USEFUL_DOT_SET;

//ʵʱ����ӿڣ�������ӿ�
E_FILETER_RUNTIME_RET_STATUS filter_noise_runtime_interface(
	//���룺��Ҫ���˵�����㼯�ϣ�ʵʱ���յ����ٵ�ͽ���Ӧ�ĵ�ȫ���Ž�ȥ
	vector<OID_DOT_VAL> &input_v_dot,

	//���룺�Ƿ����µ�һ���ʻ�
	bool b_new_stroke,

	//���룺������µ�һ���ʻ�����Ҫ���´�ʱ��ṹ��������Ҫ
	S_STROKE_TIME &stroke_time,

	//���룺��һ�ʻ�����Ϣ�������ϵͳ��һ���ʻ�����Ӧ�ıʻ�ʱ������Ϊ0��ҳ������Ϊ0����Ҫ���������ʻ�����ֻ��������ʱ���������������Ҫ�󣬵�ҳ���˲���ʱ������ҳ����
	S_STROKE_STRUCT pre_stroke,

    //������������㼯
	vector<OID_DOT_VAL> &output_v_dot,

    //�������һ�ʻ��㼯�������һ�ʻ�����̫�٣����ж��ݶ���Ч��׶ξ����µ�
	//�ʻ�������ͨ���˲������ݶ���Ч����Ϊ��һ�ʻ��ĵ㼯���
    PRE_STROKE_USEFUL_DOT_SET &pre_stroke_dot_set
    );

//״̬��������������״̬����������
E_FILETER_RUNTIME_RET_STATUS filter_normal_state(vector<OID_DOT_VAL> &input_v_dot, vector<OID_DOT_VAL> &output_v_dot);

//�����������ڵ�ļ��ٶ���ֵ,��ȷ�ϼ��ٶ��Ƿ����
bool cal_acc(const OID_DOT_VAL &pre, const OID_DOT_VAL &mid, const OID_DOT_VAL &aft);

//����ǰһ���ɿ��㼯
void update_pre_reliable_dot_set(const OID_DOT_VAL &aft);

//�ڴ˱ʻ�������Ѱ�ҿɿ���,��״̬�£�����ҵ�����Ч�㣬����㼯��Ϊ�գ��ҵ㼯remain_hanle_v_dot��Ҫ���������̽������룩������û������㷵��
E_FILETER_RUNTIME_RET_STATUS filter_find_reilable_state(vector<OID_DOT_VAL> &input_v_dot, vector<OID_DOT_VAL> &output_v_dot, vector<OID_DOT_VAL> &remain_hanle_v_dot);

//���ּ��ٶ��������쳣����ֵ
#define ACC_NORMAL_THRESHOLD     0.15

//��ȷ�ϵ㼯������Ҫ���ٸ�����ܽ��в�Ѱ��Ч��
#define WAIT_CONFIRM_DOT_SET_MIN_NUM    3

//�ݶ���Ч�����ﵽȷ��Ϊ��Ч����ٽ���ֵ
#define MAKE_SURE_DOT_T_CONFIRM_DOT_NUM    12

//������������ʱ����
#define SAMPLE_INTERVAL_MS      7

//���������ݶ���׼����
bool find_three_tempoary_reliable_dot(int &find_start_offset,
                                      OID_DOT_VAL &pre, OID_DOT_VAL &mid, OID_DOT_VAL &aft,
                                      int &pre_idx, int &mid_idx, int &aft_idx);

//������µıʻ���������һ�ʻ�ʱ�䰤�úܽ�����Ҫ���ڹ���ҳ��
#define TIME_STROKE_INTERVAL_THRESHOLD  1.5 //unit s

//�����������������ֵ������Ҫ��״̬����ΪѰ�ҿɿ���״̬������Ѱ�ҿɿ���
#define CONTINUE_NOISE_DOT_NUM      12

//�������֮��������
#define MAX_INTERVAL_IMAGE_IDX_ACC_DOT		7

//��������㹹�ɵļнǣ����жϼн�Сʱ���ٶ��Ƿ����
bool verify_mid_dot_useful(const OID_DOT_VAL &pre, const OID_DOT_VAL &mid, const OID_DOT_VAL &aft);

//���ݴ˱ʻ����ݶ���Ч�㼯������˱ʻ���ҳ��
bool solve_pagecode_in_t_useful_dot_set(const vector<OID_DOT_VAL> &t_set, const S_STROKE_STRUCT &pre_stroke, int &page_code);

//����Ӧ������㼯����ֵ��Ӧ��ҳ��
void assign_pagecode_to_output_vector(vector<OID_DOT_VAL> &dot_set, int page_code);

float cal_stroke_interval_time_s(const S_STROKE_TIME &pre_stroke_time, const S_STROKE_TIME &cur_stroke_time);

//�˳����������úܽ������
//�����������ڵ�֮��ľ��룬������úܽ����򷵻�true
int cal_neighbor_dot_distance(const OID_DOT_VAL &pre, const OID_DOT_VAL &cur);

//�������ڵ����1����������Ϊ���úܽ�
#define NEIGHBOR_DOT_DISTANCE_THRESHOLD     (32/8.0)

#define ANGLE_A_THRESHOLD	(-0.5)//120��// (-0.93) //�н�160�� //��ʱѡȡ��ֵ,��Ӧ�н�45�ȣ�TODO:������Ҫ����
#define ANGLE_A_VELOCITY_THRESHOLD	2.0

//������������ʧ�ܣ���ǰ���ж������ǰһ�ɿ���ľ��룬С�ڴ���ֵ������Ϊ�˵�ɿ�
#define NEIGHBOR_DOT_DISTANCE_THRESHOLD_RELIABLE    (32*2)//������������

//�յ��þ����ж�
#define ANGLE_A_DISTANCE_THRESHOLD	(32.0 * 1.5) //�����������

#endif // FILTER_NOISE_DOT_RUNTIME_H

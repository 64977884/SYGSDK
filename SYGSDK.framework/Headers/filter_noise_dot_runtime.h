#ifndef FILTER_NOISE_DOT_RUNTIME_H
#define FILTER_NOISE_DOT_RUNTIME_H

#include "vector"
#include "stroke_struct.h"
#include <math.h>
#include <map>

using namespace std;

#define DEBUG_RUNTIME_FILETER_ENABLE    0

//定义实时滤噪返回的状态类型
typedef enum _E_FILETER_RUNTIME_RET_STATUS{
    //正常状态返回，表示此次传入的坐标点成功滤出若干个正常点，正常的点数不为0
    RUNTIME_FILTER_RET_NORMAL,

    //表示此次滤噪没有可用的正常点,全部为噪点
    RUNTIME_FILTER_RET_NO_USE_DOT,

    //表示滤噪算法还在确认笔画可靠点,此时没有可用点返回
    RUNTIME_FILTER_RET_FIND_RELIABLE_DOT,

//    //表示上一笔画还在处于暂定有效点状态，新的笔画进来，直接将上一笔画暂定有效点作为上一笔画的有用数据点
//    RUNTIME_FILTER_RET_PRE_STROKE_DATA_RETURN,

    //异常状态，新的笔画进来，上一笔画还在确认可靠点，造成上一笔画丢失
    RUNTIME_FILTER_RET_RRE_STROKE_LOST,

    //异常状态，传入的点集为空
    RUNTIME_FILTER_RET_INPUT_DOT_EMPYT,

    //未定义，默认初始返回状态
    RUNTIME_FILETER_RET_DEFAULT

}E_FILETER_RUNTIME_RET_STATUS;

//定义笔画时间数据结构
typedef struct _S_STROKE_TIME{
    unsigned int stroke_s;
    unsigned int stroke_ms;
}S_STROKE_TIME;

//定义实时滤噪接口所处状态
typedef enum _E_FILTER_STATE{
    //寻找可靠点
    FILTER_STATE_FIND_RELIABLE_DOT,

    //已经找到可靠点，实时滤噪
    FILTER_STATE_FILTERING,

    //未定义状态
    FILTER_STATE_DEFAULT
}E_FILTER_STATE;

//实时滤噪初始化接口
bool filter_noise_runtime_init();

//定义一个笔画的相关信息,主要用于存储上一笔画的信息，由调用者填充
typedef struct _S_STROKE_STRUCT{
    S_STROKE_TIME stroke_time;

	vector <OID_DOT_VAL> stroke_dot_array;

    //笔画的页码
    int code_val;
}S_STROKE_STRUCT;

//计算新的笔画起始点与上一笔画最后一个可靠点的时间，用于决定是否拿上一笔画最后一个点做可靠点进行滤噪，返回单位秒
float cal_stroke_interval_time_s(const S_STROKE_TIME &pre_stroke_time, const S_STROKE_TIME &cur_stroke_time);

//上一笔画是否有数据返回，主要用于实时滤噪接口抛出上一笔画点集还处于待确认可靠点集，然后新的笔画点集进来的情形
typedef struct _PRE_STROKE_USEFUL_DOT_SET{
    //是否有效，如果为true，后面的点集为上一笔画有用点集
    bool b_valid;

    //有用点点集
    vector<OID_DOT_VAL> output_v_dot;
}PRE_STROKE_USEFUL_DOT_SET;

//实时滤噪接口，主处理接口
E_FILETER_RUNTIME_RET_STATUS filter_noise_runtime_interface(
	//输入：需要过滤的坐标点集合，实时接收到多少点就将对应的点全部放进去
	vector<OID_DOT_VAL> &input_v_dot,

	//输入：是否是新的一个笔画
	bool b_new_stroke,

	//输入：如果是新的一个笔画，需要更新此时间结构，否则不需要
	S_STROKE_TIME &stroke_time,

	//输入：上一笔画的信息，如果是系统第一个笔画，对应的笔画时间设置为0、页码设置为0，主要用于整个笔画点数只有三两个时，且坐标满足过滤要求，但页码滤不出时，设置页码用
	S_STROKE_STRUCT pre_stroke,

    //输出：滤噪结果点集
	vector<OID_DOT_VAL> &output_v_dot,

    //输出：上一笔画点集，如果上一笔画点数太少，在判定暂定有效点阶段就有新的
	//笔画进来，通过此参数将暂定有效点作为上一笔画的点集输出
    PRE_STROKE_USEFUL_DOT_SET &pre_stroke_dot_set
    );

//状态机处理正常滤噪状态，进行滤噪
E_FILETER_RUNTIME_RET_STATUS filter_normal_state(vector<OID_DOT_VAL> &input_v_dot, vector<OID_DOT_VAL> &output_v_dot);

//计算三个相邻点的加速度域值,并确认加速度是否合理
bool cal_acc(const OID_DOT_VAL &pre, const OID_DOT_VAL &mid, const OID_DOT_VAL &aft);

//更新前一个可靠点集
void update_pre_reliable_dot_set(const OID_DOT_VAL &aft);

//在此笔画数据中寻找可靠点,此状态下，如果找到了有效点，结果点集不为空（且点集remain_hanle_v_dot需要经正常流程进行滤噪），否则，没有坐标点返回
E_FILETER_RUNTIME_RET_STATUS filter_find_reilable_state(vector<OID_DOT_VAL> &input_v_dot, vector<OID_DOT_VAL> &output_v_dot, vector<OID_DOT_VAL> &remain_hanle_v_dot);

//划分加速度正常与异常的域值
#define ACC_NORMAL_THRESHOLD     0.15

//待确认点集至少需要多少个点才能进行查寻有效点
#define WAIT_CONFIRM_DOT_SET_MIN_NUM    3

//暂定有效点数达到确认为有效点的临界域值
#define MAKE_SURE_DOT_T_CONFIRM_DOT_NUM    12

//定义坐标点采样时间间隔
#define SAMPLE_INTERVAL_MS      7

//查找三个暂定有准备点
bool find_three_tempoary_reliable_dot(int &find_start_offset,
                                      OID_DOT_VAL &pre, OID_DOT_VAL &mid, OID_DOT_VAL &aft,
                                      int &pre_idx, int &mid_idx, int &aft_idx);

//如果是新的笔画，且与上一笔画时间挨得很近，主要用于过滤页码
#define TIME_STROKE_INTERVAL_THRESHOLD  1.5 //unit s

//连续噪点数超过此阈值，则需要将状态机置为寻找可靠点状态，重新寻找可靠点
#define CONTINUE_NOISE_DOT_NUM      12

//计算加速之间的最大间隔
#define MAX_INTERVAL_IMAGE_IDX_ACC_DOT		7

//求得三个点构成的夹角，并判断夹角小时，速度是否合理
bool verify_mid_dot_useful(const OID_DOT_VAL &pre, const OID_DOT_VAL &mid, const OID_DOT_VAL &aft);

//根据此笔画的暂定有效点集，求出此笔画的页码
bool solve_pagecode_in_t_useful_dot_set(const vector<OID_DOT_VAL> &t_set, const S_STROKE_STRUCT &pre_stroke, int &page_code);

//将对应的输出点集都赋值对应的页码
void assign_pagecode_to_output_vector(vector<OID_DOT_VAL> &dot_set, int page_code);

float cal_stroke_interval_time_s(const S_STROKE_TIME &pre_stroke_time, const S_STROKE_TIME &cur_stroke_time);

//滤除掉连续挨得很近的噪点
//计算两个相邻点之间的距离，如果挨得很近，则返回true
int cal_neighbor_dot_distance(const OID_DOT_VAL &pre, const OID_DOT_VAL &cur);

//定义相邻点距离1个码区，则为挨得很近
#define NEIGHBOR_DOT_DISTANCE_THRESHOLD     (32/8.0)

#define ANGLE_A_THRESHOLD	(-0.5)//120度// (-0.93) //夹角160度 //临时选取阈值,对应夹角45度，TODO:持续需要调整
#define ANGLE_A_VELOCITY_THRESHOLD	2.0

//定义连续解码失败，当前待判定码点与前一可靠点的距离，小于此域值，则认为此点可靠
#define NEIGHBOR_DOT_DISTANCE_THRESHOLD_RELIABLE    (32*2)//两倍码区长度

//拐点用距离判断
#define ANGLE_A_DISTANCE_THRESHOLD	(32.0 * 1.5) //半个码区长度

#endif // FILTER_NOISE_DOT_RUNTIME_H

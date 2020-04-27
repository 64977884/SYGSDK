#ifndef  _STROKE_STRUCT_H_
#define  _STROKE_STRUCT_H_

#include <vector>

using namespace std; 

//是否采用整个笔画进行传输，而不是实时传输 
//0: 实时传输   
//1: 整笔传输
#define  ENBALE_STROKE_DATA_ENTIRE_SEND		1

typedef struct _OID_DOT_VAL{
    unsigned int code_val;//点读码的码值 或 手写码的页码
    unsigned short x_val;//x坐标 8bit最大长度（2.2MM码区宽度）小数点右移两位得到的整数值
    unsigned short y_val;
    unsigned int imageIndex;
    unsigned int type; //0:落笔 1:移动 2:起笔
    bool isTmp;
    
    long time;
    long pressure_val;
    
#if DEBUG_JSON_FILE_ALGORITHM
    DOT_DEC_DETAIL_INFO _dbg_detail_info;
#endif
    
#if DEBUG_FILTER_ALGORITHM_IN_PC_ENV
    QString image_name;
    
    friend QDataStream &operator >>(QDataStream &in, _OID_DOT_VAL &code_val)
    {
        in >> code_val.code_val >> code_val.x_val >> code_val.y_val >> code_val.imageIndex
        >>code_val.cur_pressure_val >> code_val.image_name;
        return in;
    }
    
    friend QDataStream &operator <<(QDataStream &out, _OID_DOT_VAL &code_val){
        out << code_val.code_val << code_val.x_val << code_val.y_val << code_val.imageIndex
        <<code_val.cur_pressure_val << code_val.image_name;
        return out;
    }
#endif
    
}OID_DOT_VAL;

//笔画的数据需要分为笔画开头、笔画中间、笔画结尾，另外兼容之前的整个笔画
typedef enum _stroke_item_e
{
    //整个笔画，在实时传输下，表示离线存储的笔画， 在非实时传输实现下，表示整个笔画处理
    E_STROKE_ITEM_ENTIRE,

    //笔画开头,笔画开头包含坐标点,实际底层组包，笔画头不包含坐标点
    E_STROKE_ITEM_START,

    //笔画中间
    E_STROKE_ITEM_MIDDLE,

    //笔画结尾，不包含坐标点
    E_STROKE_ITEM_END
}stroke_item_e;

//每个笔画包最多包含的坐标个数,此主要用于（笔画开头、笔画中间、笔画结尾），不适用于整个笔画的情况
#define DOT_NUM_PER_STROKE_PACKET_ITEM		8*2 //单位：1个坐标点

typedef struct _STROKE_ITEM{
    //用于表征此笔画数据包的笔画类型
    stroke_item_e e_stroke_item_type;

    vector<OID_DOT_VAL> stroke_dot_array;
    unsigned int stroke_start_times_ms;
    unsigned int stroke_start_times_s;
    unsigned int page_code;

	//根据码区空间划分规则，折算后的笔画信息，逻辑页类型、逻辑页ID，且坐标已经根据逻辑页调整过来
	//logical_page_type_e e_page_type;
    int logical_page_id;

#if DEBUG_FILTER_ALGORITHM_IN_PC_ENV
    //序列化
    friend QDataStream &operator <<(QDataStream &out, _STROKE_ITEM &obj){
        int dot_num = obj.stroke_dot_array.size();
        out << dot_num;
        for(int i=0; i<dot_num; i++){
            out << obj.stroke_dot_array[i];
        }
        out << obj.page_code;
        return out;
    }

    //反序列化
    friend QDataStream &operator >>(QDataStream &in, _STROKE_ITEM &obj){
        int dot_num;
        in >> dot_num;
        for(int i=0; i<dot_num; i++){
            OID_DOT_VAL tmp_dot_val;
            in >> tmp_dot_val;
            obj.stroke_dot_array.push_back(tmp_dot_val);
        }
        in >> obj.page_code;
        return in;
    }
#endif

    //PC端需要用到的变量
    //TODO: 0 ~ 3，2bit长度， 主要用于调试，后续应该拿掉
    unsigned int stroke_sequence;

    //是否是离线笔画数据
    bool b_history_stroke;

    //离线笔画数据计数器，每传输一笔画，减1
    int number_history_stroke;

}STROKE_ITEM;

#endif

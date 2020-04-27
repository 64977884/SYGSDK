#ifndef  _STROKE_STRUCT_H_
#define  _STROKE_STRUCT_H_

#include <vector>

using namespace std; 

//�Ƿ���������ʻ����д��䣬������ʵʱ���� 
//0: ʵʱ����   
//1: ���ʴ���
#define  ENBALE_STROKE_DATA_ENTIRE_SEND		1

typedef struct _OID_DOT_VAL{
    unsigned int code_val;//��������ֵ �� ��д���ҳ��
    unsigned short x_val;//x���� 8bit��󳤶ȣ�2.2MM������ȣ�С����������λ�õ�������ֵ
    unsigned short y_val;
    unsigned int imageIndex;
    unsigned int type; //0:��� 1:�ƶ� 2:���
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

//�ʻ���������Ҫ��Ϊ�ʻ���ͷ���ʻ��м䡢�ʻ���β���������֮ǰ�������ʻ�
typedef enum _stroke_item_e
{
    //�����ʻ�����ʵʱ�����£���ʾ���ߴ洢�ıʻ��� �ڷ�ʵʱ����ʵ���£���ʾ�����ʻ�����
    E_STROKE_ITEM_ENTIRE,

    //�ʻ���ͷ,�ʻ���ͷ���������,ʵ�ʵײ�������ʻ�ͷ�����������
    E_STROKE_ITEM_START,

    //�ʻ��м�
    E_STROKE_ITEM_MIDDLE,

    //�ʻ���β�������������
    E_STROKE_ITEM_END
}stroke_item_e;

//ÿ���ʻ������������������,����Ҫ���ڣ��ʻ���ͷ���ʻ��м䡢�ʻ���β�����������������ʻ������
#define DOT_NUM_PER_STROKE_PACKET_ITEM		8*2 //��λ��1�������

typedef struct _STROKE_ITEM{
    //���ڱ����˱ʻ����ݰ��ıʻ�����
    stroke_item_e e_stroke_item_type;

    vector<OID_DOT_VAL> stroke_dot_array;
    unsigned int stroke_start_times_ms;
    unsigned int stroke_start_times_s;
    unsigned int page_code;

	//���������ռ仮�ֹ��������ıʻ���Ϣ���߼�ҳ���͡��߼�ҳID���������Ѿ������߼�ҳ��������
	//logical_page_type_e e_page_type;
    int logical_page_id;

#if DEBUG_FILTER_ALGORITHM_IN_PC_ENV
    //���л�
    friend QDataStream &operator <<(QDataStream &out, _STROKE_ITEM &obj){
        int dot_num = obj.stroke_dot_array.size();
        out << dot_num;
        for(int i=0; i<dot_num; i++){
            out << obj.stroke_dot_array[i];
        }
        out << obj.page_code;
        return out;
    }

    //�����л�
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

    //PC����Ҫ�õ��ı���
    //TODO: 0 ~ 3��2bit���ȣ� ��Ҫ���ڵ��ԣ�����Ӧ���õ�
    unsigned int stroke_sequence;

    //�Ƿ������߱ʻ�����
    bool b_history_stroke;

    //���߱ʻ����ݼ�������ÿ����һ�ʻ�����1
    int number_history_stroke;

}STROKE_ITEM;

#endif

#ifndef _VMC_DEF_H_
#define _VMC_DEF_H_
#include "ics_type.h"
#include <QVariant>
#include <QMetaType>

#pragma pack(push, 1)

#ifndef NULL
//#define NULL 0
#endif

typedef struct  
{
	//00
	UT32 ctrl_stu				:1;//���״̬
	UT32 RIU_err				:1;//RIU��BCUAͨ��ͨѶ����
	UT32 break_fault			:1;//ɲ������
	UT32 nslip_err				:1;//����
	UT32 off_break_err			:1;//�����ɲ��ʧЧ
	UT32 off_break				:1;//�����ɲ��״̬==>?
	UT32 drag_break				:1;//ǣ��ɲ��״̬==>?
	UT32 brake_nslip			:1;//ɲ���޷���״̬

	UT32 silence_singal			:1;//����Ĭ��ģʽ
	UT32 other_break_err		:1;//��һͨ��ɲ������
	UT32 break_ctrl_takeoff		:1;//ɲ�����ƿ���
	UT32 maintenance_BIT_stu	:1;//ά��bit
	UT32						:20;

	//01
	UT32 lsff_ztd_scdl				: 8; /*���ŷ�����ͨ���������*/
	UT32 lsff_btd_scdl				: 8; /*���ŷ�����ͨ���������*/
	UT32 rsff_ztd_scdl				: 8; /*���ŷ�����ͨ���������*/
	UT32 rsff_btd_scdl				: 8; /*���ŷ�����ͨ���������*/

	//02
	UT32 left_wheel_speed	:16;//ɲ������,��
	UT32 right_wheel_speed	:16;//ɲ������,��

	//03
	UT32 lbreak_cmd		:16;/*��ɲ��ָ��*/
	UT32 rbreak_cmd		:16;/*��ɲ��ָ��*/

	//04
	UT32 lbreak_pressure	:16;  //��ɲ��ѹ��
	UT32 rbreak_pressure	:16;  //��ɲ��ѹ��
}break_t;

typedef struct  
{
	break_t riu3;
	break_t riu4;
}InputBreak_t;


typedef struct
{
	/*----------64״̬��----------*/
	struct
	{
		UT32 break_vd					: 1; /*ɲ��������Ч*/
		UT32 off_break_err				: 1; /*�����ɲ��ʧЧ,RIU3-VMC-DATA1��0052��bit31��RIU4-VMC-DATA1��0052��bit31��ͬʱ��Ч���������ɲ��ʧЧVMC���˲����˲����ڣ�250ms*/
		UT32 break_fault				: 1; /*ɲ������,"RIU3-VMC-DATA1��0044��bit12��RIU4-VMC-DATA1��0044��bit12��ͬʱ��Ч����ɲ������VMC���˲����˲����ڣ�250ms" */
		UT32 nslip_err					: 1; /*��������,"���ж�RIU3-VMC-DATA1��0044��bit11���������״̬����RIU4-VMC-DATA1��0044��bit11���������״̬�����жϳ���ǰ�ĸ�ɲ���ӿ��ڿ�����������õ�ǰ���������ɲ���ӿ�RIU3-VMC-DATA1��0044��bit13��RIU4-VMC-DATA1��0044��bit13���Ľ���ϱ���������VMC���˲����˲����ڣ�250ms" */
		UT32 maintenance_BIT_stu		: 1; /*ά��BIT״̬ */
		UT32 off_break					: 1; /*�����ɲ��,"RIU3-VMC-DATA1��0056��bit5��RIU4-VMC-DATA1��0056��bit5��ȡ���򡱣��жϴ�״̬VMC���˲����˲����ڣ�250ms" */
		UT32 drag_break					: 1; /*ǣ��ɲ��,"RIU3-VMC-DATA1��0056��bit8��RIU4-VMC-DATA1��0056��bit8��ȡ���򡱣��жϴ�״̬VMC���˲����˲����ڣ�250ms"	*/
		UT32 break_no_nslip				: 1; /*ɲ���޷���,"���ж�RIU3-VMC-DATA1��0044��bit11���������״̬����RIU4-VMC-DATA1��0044��bit11���������״̬�����жϳ���ǰ�ĸ�ɲ���ӿ��ڿ�����������õ�ǰ���������ɲ���ӿ�RIU3-VMC-DATA1��0056��bit13��RIU4-VMC-DATA1��0056��bit13���Ľ��ȥ��ɲ���޷���״̬VMC���˲����˲����ڣ�250ms" */
		UT32 break_down					: 1; /*ɲ����Ƚ���,"RIU3-VMC-DATA1��0044��bit12��RIU4-VMC-DATA1��0044��bit12������һ����Ч����ɲ����Ƚ���VMC���˲����˲����ڣ�250ms" */
		UT32 l_break_pres				: 1; /*��ɲ����ѹ��, "�������Ե���ɲ��ѹ����С��1.5MPaʱ����λ����ЧVMC���˲����˲����ڣ�250ms"*/
		UT32 r_break_pres				: 1; /*��ɲ����ѹ��, "�������Ե���ɲ��ѹ����С��1.5MPaʱ����λ����ЧVMC���˲����˲����ڣ�250ms"*/
		UT32 traction_break             : 1; /*11 ǣ��ɲ��ָ�PIUָ� 0:�Ͽ���1����ͨ*/
		UT32 break_ctrl_takeoff         : 1; /*12 ɲ�����ƣ������ɲ���� 0:�Ͽ���1����ͨ*/
		UT32 break_ctrl_antiskid        : 1; /*13 ɲ�����ƣ�����ɲ���� 0:�Ͽ���1����ͨ*/
		UT32 break_ctrl_no_antiskid     : 1; /*14 ɲ�����ƣ��޷���ɲ���� 0:�Ͽ���1����ͨ*/
		UT32 back15                     :17; /*15~31 ���� */
	};
	/*----------68״̬��----------*/
	struct
	{
		UT32 left_wheel_speed			: 16; /*�����ٶ�*/
		UT32 right_wheel_speed			: 16; /*�����ٶ�*/
	};

	/*----------72״̬��----------*/
	struct
	{
		UT32 lbreak_cmd					: 16; /*��ɲ��ָ��*/
		UT32 rbreak_cmd					: 16; /*��ɲ��ָ��*/	
	};

	/*----------76״̬��----------*/
	struct
	{
		UT32 lsff_ztd_scdl				: 8; /*���ŷ�����ͨ���������*/
		UT32 lsff_btd_scdl				: 8; /*���ŷ�����ͨ���������*/
		UT32 rsff_ztd_scdl				: 8; /*���ŷ�����ͨ���������*/
		UT32 rsff_btd_scdl				: 8; /*���ŷ�����ͨ���������*/
	};
	/*----------80״̬��----------*/
	struct
	{
		UT32 lbreak_pressure			: 16; /*��ɲ��ѹ��*/
		UT32 rbreak_pressure            : 16; /*��ɲ��ѹ��*/
	};
}OutputBreak_t;
/*------------------------------------------------------
VMC������
*/
typedef struct
{
	//ɲ��
	InputBreak_t brk;//size 10 int
}Input_vmc;
/*------------------------------------------------------
VMC�����
*/
typedef struct
{
	//ɲ��
	OutputBreak_t brk;//size 5 int
}Output_vmc;

Q_DECLARE_METATYPE(OutputBreak_t)
Q_DECLARE_METATYPE(Input_vmc)
Q_DECLARE_METATYPE(Output_vmc)

//extern Input_vmc  g_input;
//extern Output_vmc g_output;

#pragma pack(pop)

#endif

/************************************************************************
* �ļ���	:ics_type.h
* 
* ������	:lzh
*
* ����		:2019/04/24
* 
* ����		:������������
*
* �޸���ʷ(����/�޸���/�޸�����):
*
************************************************************************/
#ifndef __ICS_TYPE_H__
#define __ICS_TYPE_H__


/*������������*/
typedef double					FT64;
typedef float					FT32;
typedef unsigned int			UT32;
typedef signed int				ST32;
typedef unsigned short			UT16;
typedef signed short			ST16;
typedef unsigned char			UT08;
typedef signed char				ST08;
typedef unsigned long long		UT64;
typedef long long				ST64;
#define RIU1_VMC_NDB_DATA_LEN		114
#define RIU2_VMC_NDB_DATA_LEN		114
#define RIU3_VMC_NDB_DATA_LEN		114
#define RIU4_VMC_NDB_DATA_LEN		114
#define VMC_GMP_1_NDB_DATA_LEN      114
#define VMC_GMP_2_NDB_DATA_LEN      114
#define VMC_GMP_3_NDB_DATA_LEN      114
#define VMC_RIU1_NDB_DATA_LEN		50 
#define VMC_RIU2_NDB_DATA_LEN		50 
#define VMC_RIU3_NDB_DATA_LEN		50 
#define VMC_RIU4_NDB_DATA_LEN		50 
#define GMP_VMC_NDB_DATA_LEN		50
#define PIU_BC_VMC_NDB_DATA_LEN		22
#define VMC_FDR_DATA_LEN			114
#define VMC_DEU_DATA_LEN			18
#define VMC_MCPU_DATA_LEN			5
#define MIU_VMC_MS_DATA_LEN			114
#define MIU_VMC_PVI_DATA_LEN		50
#define VMC_GME_FTI_DATA_LEN		92
#define CNT_OF_2S					(2 * 1000/CYC_TIME)

#define Pump_Supply_Start           0//��������״̬
#define Pump_Supply_Normal          1//��������״̬
#define VMC_PIU_LEN					18
#define VMC_MIU_1_NDB_DATA_LEN		114
#define VMC_MIU_2_NDB_DATA_LEN		114
#define VMC_MIU_3_NDB_DATA_LEN		114
#define VMC_MFD_DATA_LEN			50
#define VMC_UFCD_DATA_LEN			50
#define STOF_LEN					9
#define AC_Pump_check				6 //422�ü�Ϊ 6�ߵ�
#define DC_Pump_check				1 //ֱ���ü�Ϊ 1����

#define FUELFAST_0_0_0		1
#define FUELFAST_1_0_0		2
#define FUELFAST_0_1_0		3
#define FUELFAST_0_0_1		4
#define FUELFAST_0_1_1		5
#define FUELFAST_1_1_0		6
#define FUELFAST_1_0_1		7
#define FUELFAST_1_1_1		8
#ifndef bool	
//#define bool UT08
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#define CYC_TIME 12.5
#define DURATION(t) t* CYC_TIME
#define DEDURATION(t) ((t*1000)/CYC_TIME)
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
#define OUT_OF_RANGE(v,min1,max1)   ((v)>(max1)) || ((v)<(min1))
#define ONE_IN_RANGE(v,min1,max1)   ((v)>(min1))  && ((v)<(max1))
//#define DEBUG_FOLD
//#define DEBUG_SUPPLY
//#define DEBUG_SAVE
//#define MFL_DEBUG_FAKE_DATA
#define MODIFY_SAVE_20220422
#define MODIFY_AC_0P8_20220523
#define MODIFY_AC_GEAR_20220523
//#define MODIFY_20220424
#define SV_CHECK
#define DEBUG_0728
#define FDR
#define GMP0316 			/*�󷢡��ҷ���һ����60 ����Ϊ��ǰGMP�·����������ݾ�Ϊ0�����ҵ�ǰ��GMPͨѶ����*/
#define FUEL0316
/*
���ͱõ�λ����ָ��:
00H��������;    
03H���͵�;     
05H���е�;
06H���ߵ�;*/
#define CMD_HIGH_6 6
#define CMD_MID_5 5
#define CMD_LOW_3 3
#define CMD_STOP_0 0

/*ֱ������ͣ����:
0ֹͣ 
1����
*/
#define DC_CTRL_START_1 1
#define DC_CTRL_STOP_0 0

/*
00����Ч    01����    10���ر�    11����Ч
*/
#define CTRL_INVALID_0 0
#define CTRL_OPEN_1 1
#define CTRL_CLOSE_2 2
#define CTRL_INVALID_3 3

/*
����״̬:
0x00=������0x01=���ϣ�0x10=δ����
*/
#define STU_OK_0 0
#define STU_ERR_1 1
#define STU_NOWORK_2 2

/*�ü�����"00����Ч;01���ɹ�;10��ʧ��;11���쳣�˳�"*/
#define CHECK_INVAILD_0 0
#define CHECK_SUCCESS_1 1
#define CHECK_FAILED_2 2
#define CHECK_ERR_3 3

#define CHECK_BEGIN_1 1
#define CHECK_END_2 2

/*�ź���Ч*/
#define VALID_1 1
#define INVALID_0 0

//�ɿؿ��ȷ�����ָ��(0=�ر� 0x01=С���� 0x10=�п��� 0x11=�󿪶�,0x100��Ч,������Ч)
#define OPENING_COLSE_0 0
#define OPENING_SAMLL_1 1
#define OPENING_MID_2 2
#define OPENING_BIG_3 3
#define OPENING_INVAILD_4 4

//AC
//�շ�ָ��(00=��Ч,01=�������,10=�������,11=��Ч)
#define CMD_G_INVALID_0 0
#define CMD_G_EXT_1 1
#define CMD_G_RET_2 2
#define CMD_INVALID_3 3

//�����۵�/չƽָ��(011-�۵���100-չƽ��������Ч)
#define CMD_W_FOLD_3 3
#define CMD_W_DIS_4 4
#define CMD_W_INVAILD_0 0

//����ܼ�����״̬(00=��Ч/01=�ѷ���/10=������)
#define STU_INVALID_0 0
#define STU_DOWN_1 1
#define STU_UP_2 2

//���version�汾��Ϣ
#define VERSION_A 2
#define VERSION_BB 14
#define V_YEAR 22
#define V_MONTH 6
#define V_DAY 6

//�����ж�ʱ��:5��
#define FLOW_TIMER 5000
typedef struct _SOFTWARE_INFO
{
	struct 
	{
		UT32 software_version_A:3;		//����汾��:A ���汾��
		UT32 software_version_C:5;		//����汾��:C 1~26��ӦA~Z
		UT32 software_version_BB:8;		//����汾��:BB �汾�Ÿ�ʽA.B.C
		UT32 bak1:16;		//����1
	}softwaretype;
	struct
	{
		UT32 year:8;		//�����������:�ꣻ��ֵ+2000��Ӧ���
		UT32 month:8;		//�����������:�£�1~12
		UT32 day:8;		//�����������:�գ�1~31
		UT32 bak2:8;		//����2
	}softwaredate;
}Software_Version;

typedef struct _Software_V
{
	UT32 code					:2;		//��Ʒ��λ������
	UT32 software_version_A		:2;		//����汾��:A ���汾��0~3
	UT32 software_version_BB	:7;		//����汾��:BB
	UT32 software_version_C		:5;		//����汾��:C A~AF,0:A,1:B,11001:Z,11010:AA,11111:AF �汾�Ÿ�ʽA.BB.C
	UT32 year					:7;		//�����������:�ꣻ��ֵ+2000��Ӧ���
	UT32 month					:4;		//�����������:�£�1~12
	UT32 day					:5;		//�����������:�գ�1~31
}Software_V;

typedef struct _Software_V2
{
	UT32 software_version_A		:3;		//����汾��:A ���汾��0~3
	UT32 software_version_BB	:8;		//����汾��:BB
	UT32 software_version_C		:5;		//����汾��:C A~AF,0:A,1:B,11001:Z,11010:AA,11111:AF �汾�Ÿ�ʽA.BB.C
	UT32 year					:7;		//�����������:�ꣻ��ֵ+2000��Ӧ���
	UT32 month					:4;		//�����������:�£�1~12
	UT32 day					:5;		//�����������:�գ�1~31
}Software_V2;

/*�ź�����*/
typedef struct _FILTERDESC
{
	unsigned int nDelay;		/*�˲�������*/
	unsigned int nOldStatus;	/*ԭ״̬*/
	unsigned int nCycle;		/*�źű仯����*/
	unsigned int nStatus;		/*���״̬*/
}FilterDesc;

/*�ź�����*/
typedef struct _FILTER
{
	ST32 nOldStatus;	/*ԭ״̬*/
	UT32 nStatus;		/*���״̬*/
}Filter;

/*----------------------------------------------------------------------
����: �������ж�
����: szy
����: 2021/04/10
*/
int RisingEdge(FilterDesc* pDesc, unsigned int nStatus);
/*----------------------------------------------------------------------
����: �½����ж�
����: szy
����: 2021/04/10
*/
int FallingEdge(FilterDesc* pDesc, unsigned int nStatus);
/*----------------------------------------------------------------------
����: �ź��˲�
����: szy
����: 2021/04/10
*/
int SignalFilter(FilterDesc* pDesc, unsigned int nStatus);
/*----------------------------------------------------------------------
����: �ź��˲�������n->0
����: szy
����: 2021/04/10
*/
int SignalFilter_ExcludeZero(FilterDesc* pDesc, unsigned int nStatus);
/*----------------------------------------------------------------------
����: ѡƱ���ݽṹ
����: szy
����: 2021/04/10
*/
typedef struct _VOTE
{
	unsigned int on_ch1		:1;		/*��/����1ͨ��ֵ(����)*/
	unsigned int on_ch2		:1;		/*��/����2ͨ��ֵ(����)*/
	unsigned int off_ch1	:1;		/*�ر�/δ����1ͨ��ֵ(����)*/
	unsigned int off_ch2	:1;		/*�ر�/δ����2ͨ��ֵ(����)*/
	unsigned int on			:1;		/*��/�����ۺ�ֵ(���)*/
	unsigned int off		:1;		/*�ر�/δ�����ۺ�ֵ(���)*/
	unsigned int on_neq		:1;		/*��/����˫����źŲ�һ��(���)*/
	unsigned int off_neq	:1;		/*�ر�/δ����˫����źŲ�һ��(���)*/
	unsigned int error		:1;		/*����(���)*/
	unsigned int :23;
}Vote;
/*----------------------------------------------------------------------
����: 4��3���
����: szy
����: 2021/04/10
*/
unsigned int Voting(Vote* pVote);

/*
����: ����1λ�ź�,�����仯ʱ���1;�ޱ仯���0.��һ�����0
����: xuzd
����: 2021/06/10
*/
UT32 filter_XOR(Filter* pDesc, unsigned int nStatus);

#endif

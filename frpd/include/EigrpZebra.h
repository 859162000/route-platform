#ifndef _EIGRP_ZEBRA_H_
#define _EIGRP_ZEBRA_H_

#ifdef __cplusplus
extern"C"
{
#endif

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
#define ZEBRA_EIGRP_BUF_SIZE	2048
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
typedef struct	ResponseCmd_{
	U32	Response;
	U32	cmd;
	S32	noFlag;
	U32	asNum;
	S32	retVal;
	S32	private;
}ResponseCmd_st;
/*************************************************************************/
/*************************************************************************/
typedef struct	ResponseCmdTable_{
	U32	cmd;
	const char *cmdstr[2];
}ResponseCmdTable_st;
/*************************************************************************/
extern ResponseCmdTable_st ResponseCmdTable[];
/*************************************************************************/
/*************************************************************************/
typedef struct	ZebraEigrpCmd_{
	struct ZebraEigrpCmd_ *next;

	U32	type;
	S32	noFlag;
	U32	asNum;
	U8	ifName[256];
	U8	name[256];

	U32	u32Para1;
	U32	u32Para2;
	U32	u32Para3;
	U32	u32Para4;
	U32	u32Para5;
	
	void	*vsPara1;
	void	*vsPara2;

}ZebraEigrpCmd_st, *ZebraEigrpCmd_pt;
/*************************************************************************/
/*************************************************************************/
typedef	struct	ZebraEigrpSched_
{
	struct	ZebraEigrpSched_	*forw;
	S32 type;
#define ZEBRA_EIGRP_CMD	1
#define ZEBRA_EIGRP_FUNC	2
	S32 cmd;
	
	S32	(*func)(void *);
	void	*data;
	U32	count;	/* This member is only for the head of the list. */
	void	*sem;	/* This member is only for the head of the list. */
	
}ZebraEigrpSched_st, *ZebraEigrpSched_pt;
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
typedef	struct ZebraEigrpRt_{
	U32	target;
	U32	mask;
	U32	gateway;
	U32	metric;
	U32	proto;
	U32	ifindex;
	U32 distance;
}ZebraEigrpRt_st, *ZebraEigrpRt_pt;
/*************************************************************************/
/*************************************************************************/
#if (EIGRP_PLAT_TYPE == EIGRP_PLAT_BSD)
/*
typedef	struct EigrpIntfAddr_{
	U32	ipAddr;
	U32	ipMask;
	U32	ipDstAddr;
	
	U32	intfIndex;
	void	*intf;//����ָ���ַ�����ӿ�
	void	*curSysAdd;//����ָ����һ����ַ
}EigrpIntfAddr_st, *EigrpIntfAddr_pt;
*/
typedef	struct EigrpInterface{
	struct	EigrpInterface	*next;

	S8	name[128];	/* Interface name. */
	U32	ifindex;
	U32	flags;
	S32	metric;
	S32	mtu;
	U32	bandwidth;	/* In unit of kbps */
	U32	delay;	/*hanbing add 120707*/

	EigrpIntfAddr_st ipaddress;
}EigrpInterface_st, *EigrpInterface_pt;

#endif// (EIGRP_PLAT_TYPE == EIGRP_PLAT_BSD)
/*************************************************************************/
/*************************************************************************/
struct ZebraEigrpMaster
{
	void *master;//����ָ��thread�¼���master����ָ��
	int	asnum;//��ǰ����ϵͳ��
	long router_id;//ϵͳ·��ID��
	void *EigrpMaster;//δʹ��
#if (EIGRP_PLAT_TYPE == EIGRP_PLAT_BSD)	
	EigrpInterface_pt eigrpiflist;//�ӿ�����
#endif// (EIGRP_PLAT_TYPE == EIGRP_PLAT_BSD)
	EigrpQue_st		*ZebraCmdQue;//�߳�֮�佻��ʹ�õ��������
	ZebraEigrpSched_pt ZebraSched;//���ӵ��߳��¼����ȶ���

	ResponseCmd_st	Response;//����Ӧ�����ݽṹ

#if (EIGRP_OS_TYPE == EIGRP_OS_VXWORKS)
	int zEigrpTaskId;//����ID
#elif (EIGRP_OS_TYPE == EIGRP_OS_LINUX)
	pthread_t pThread;//�߳�ID
	struct vty  eigrpvty;//vty shell ���ݽṹ
#endif//(EIGRP_OS_TYPE == EIGRP_OS_LINUX)	
	
#ifdef EIGRP_PLAT_ZEBRA	//·��ƽ̨֧��
	struct list *iflist;//ϵͳ�ӿ�����
	struct zclient *zclient;//�ͻ������ݽṹ
#endif//EIGRP_PLAT_ZEBRA	
};
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
extern struct ZebraEigrpMaster *EigrpMaster;
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
#ifndef RTM_GET
#define RTM_GET	3
#endif
#ifndef RTM_ADD
#define RTM_ADD	1
#endif
#ifndef RTM_DELETE
#define RTM_DELETE	0
#endif
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
#ifndef EIGRP_PLAT_ZEBRA//û��·��ƽ̨֧��
/* Zebra message types. */
#define ZEBRA_INTERFACE_ADD                1
#define ZEBRA_INTERFACE_DELETE             2
#define ZEBRA_INTERFACE_ADDRESS_ADD        3
#define ZEBRA_INTERFACE_ADDRESS_DELETE     4
#define ZEBRA_INTERFACE_UP                 5
#define ZEBRA_INTERFACE_DOWN               6

#define ZEBRA_IPV4_ROUTE_ADD               7
#define ZEBRA_IPV4_ROUTE_DELETE            8
#define ZEBRA_IPV6_ROUTE_ADD               9
#define ZEBRA_IPV6_ROUTE_DELETE           10
#define ZEBRA_REDISTRIBUTE_ADD            11
#define ZEBRA_REDISTRIBUTE_DELETE         12
#define ZEBRA_REDISTRIBUTE_DEFAULT_ADD    13
#define ZEBRA_REDISTRIBUTE_DEFAULT_DELETE 14
#define ZEBRA_IPV4_NEXTHOP_LOOKUP         15
#define ZEBRA_IPV6_NEXTHOP_LOOKUP         16
#define ZEBRA_IPV4_IMPORT_LOOKUP          17
#define ZEBRA_IPV6_IMPORT_LOOKUP          18
#define ZEBRA_INTERFACE_RENAME            19

#define ZEBRA_ROUTER_ID_ADD               20
#define ZEBRA_ROUTER_ID_DELETE            21
#define ZEBRA_ROUTER_ID_UPDATE            22
#define ZEBRA_HELLO                       23
#define ZEBRA_MESSAGE_MAX                 24
/*************************************************************************/
/*************************************************************************/
/* Zebra route's types. */
#define ZEBRA_ROUTE_SYSTEM               0
#define ZEBRA_ROUTE_KERNEL               1
#define ZEBRA_ROUTE_CONNECT              2
#define ZEBRA_ROUTE_STATIC               3
#define ZEBRA_ROUTE_RIP                  4
#define ZEBRA_ROUTE_RIPNG                5
#define ZEBRA_ROUTE_OSPF                 6
#define ZEBRA_ROUTE_OSPF6                7
#define ZEBRA_ROUTE_ISIS                 8
#define ZEBRA_ROUTE_BGP                  9
#define ZEBRA_ROUTE_PIM                  10
#define ZEBRA_ROUTE_HSLS                 11
#define ZEBRA_ROUTE_OLSR                 12
#define ZEBRA_ROUTE_BABEL                13
#define ZEBRA_ROUTE_ICRP                 14
#define ZEBRA_ROUTE_FRP                  15
#define ZEBRA_ROUTE_MANAGE               16
#define ZEBRA_ROUTE_SWITCH               17
#define ZEBRA_ROUTE_MAX                  18
#endif//EIGRP_PLAT_ZEBRA
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
#define EIGRP_DEBUG_ZEBRA_INTERFACE     0x01
#define EIGRP_DEBUG_ZEBRA_REDISTRIBUTE  0x02
#define EIGRP_DEBUG_ZEBRA	       0x03


#define EIGRP_DEBUG_PACKET_ON(a, b)	debug_eigrp_ ## a |= (EIGRP_DEBUG_ ## b)
#define EIGRP_DEBUG_PACKET_OFF(a, b)	debug_eigrp_ ## a |= (EIGRP_DEBUG_ ## b)
#define IS_DEBUG_EIGRP(a, b)				(debug_eigrp_ ## a & EIGRP_DEBUG_ ## b)

extern unsigned long debug_eigrp_zebra;

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
extern int zebraEigrpCmdSetupResponse(EigrpCmd_pt pCmd,	S32	retVal, S32	private);
extern int zebraEigrpCmdResponse(void);
/*************************************************************************/
//���ӵ��̵߳��ȹ���API�ӿ�
extern ZebraEigrpSched_pt zebraEigrpUtilSchedInit();
extern int zebraEigrpUtilSchedClean(ZebraEigrpSched_pt);
extern int zebraEigrpUtilSchedCancel(ZebraEigrpSched_pt, ZebraEigrpSched_pt );
extern ZebraEigrpSched_pt zebraEigrpUtilSchedAdd(ZebraEigrpSched_pt, S32 (*func)(void *), void *, int );
extern ZebraEigrpSched_pt zebraEigrpUtilSchedGet(ZebraEigrpSched_pt);
extern int ZebraEigrpUtilSched();
/*************************************************************************/
/*************************************************************************/
//���ӵ������API�ӿ�
extern int ZebraEigrpCmdInit();
extern int ZebraEigrpCmdCancel();
extern int ZebraEigrpCmdProc(EigrpCmd_pt pCmd);
extern int ZebraEigrpCmdSched();
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
/*************************************************************************/
#if (EIGRP_PLAT_TYPE == EIGRP_PLAT_BSD)
//��ȡϵͳ�ӽӿ���Ϣ���ӵ�Eigrp�Ľӿ�������ZebraEigrpIntfInit��������
extern int kernel_list_init(int num);
extern int ZebraEigrpIntfInit(int num);
extern int ZebraEigrpIntfClean();
extern int ZebraEigrpIntfDel(EigrpInterface_pt pIntf);
extern int ZebraEigrpIntfAdd(EigrpInterface_pt pIntf);
//û��·��ƽ̨��ʱ����ʾEigrp·�ɵĽӿ�������Ϣ
//����ʾ�Ĵ�kernel��ȡ�Ľӿ���Ϣ����EigrpIntfShow������һ����
extern int	ZebraEigrpIntfShow();
#endif// (EIGRP_PLAT_TYPE == EIGRP_PLAT_BSD)
//��ʾEigrp·�ɵĽӿ�������Ϣ
extern int EigrpIntfShow();

extern S32 zebraEigrpIntfDel(EigrpIntf_pt  intf);
extern EigrpIntfAddr_pt zebraEigrpPortGetFirstAddr(void *pCirc);
extern EigrpIntfAddr_pt zebraEigrpPortGetNextAddr(EigrpIntfAddr_pt pAddr);
extern void zebraEigrpPortCopyIntfInfo(EigrpIntf_pt pEigrpIntf, void *pSysIntf);
extern void zebraEigrpPortGetAllSysIntf();
/*************************************************************************/
/*************************************************************************/
//��·��ƽ̨����·����Ϣ(ʹ�ù��Ӻ������)
//extern int zebraEigrpAddRoute(int proto, long dest, long next, long mask, int metric, int distance, int ifindex);
//extern int zebraEigrpDelRoute(int proto, long dest, long next, long mask, int metric, int distance, int ifindex);
#if (EIGRP_PLAT_TYPE == EIGRP_PLAT_BSD)
/*
 * û��·��ƽ̨��ʱ��ʹ�����������װ����Eigrpģ��ѧϰ���Ĺ��Ӻ���
 * ����ԭ�ͣ�int func(int type, int protocol, long dest, long next, long mask, int metric, int distance, int ifindex);
 * ��������������:RTM_ADD/RTM_DELETE��·�����ͣ�Ŀ�ĵ�ַ����һ����ַ����ַ���룬������������룬��������
 * ��ַ��Ĳ���ʹ�������ֽ�˳�� 
 */
extern int zebraEigrpRouteHandleCallBack(int (*callback)(int, int, long, long, long, int, int, int));
#endif// (EIGRP_PLAT_TYPE == EIGRP_PLAT_BSD)
/*************************************************************************/
/*************************************************************************/
#ifdef EIGRP_PLAT_ZEBRA
//��·��ƽ̨�����طֲ�������Ϣ
extern int zebraEigrpRedistributeSet (char *  type);
extern int zebraEigrpRedistributeUnset (char *  type);
extern int zebraEigrpRedistributeDefaultSet ();
extern int zebraEigrpRedistributeDefaultUnset ();
//
extern int ZebraClientEigrpUtilSched();
#endif// EIGRP_PLAT_ZEBRA
/*************************************************************************/
/*************************************************************************/
#ifdef EIGRP_PLAT_ZEBRA
#if (EIGRP_OS_TYPE == EIGRP_OS_LINUX)
extern int	zebraEigrpMasterPthreadInit(void);
#endif//(EIGRP_OS_TYPE == EIGRP_OS_LINUX)
#endif// EIGRP_PLAT_ZEBRA

extern int	zebraEigrpZclientInit(int daemon, int num, void *master, void *list);
extern int	zebraEigrpMasterInit(int daemon, void *master);
/*
#if (EIGRP_OS_TYPE == EIGRP_OS_VXWORKS)
extern int eigrp_zclient_daemon ();
#elif (EIGRP_OS_TYPE == EIGRP_OS_LINUX)
extern void * eigrp_zclient_daemon ();
#endif//(EIGRP_OS_TYPE == EIGRP_OS_LINUX)
*/

#ifdef __cplusplus
}
#endif

#endif

/*
 * tmf_cln_msg.h
 *
 *  Created on: 2017. 5. 24.
 *      Author: whwo0312
 */

#ifndef _TMF_CLN_MSG_H_
#define _TMF_CLN_MSG_H_


/*-----------------------------------------------------------------------------
 *	Message Naming Mask
 *----------------------------------------------------------------------------*/
#define CLN_MASK_MSG_INOREXT		0xf0000000
#define CLN_MASK_MSG_NAME			0x0ffff000
#define CLN_MASK_MSG_TYPE			0x00000f00
#define CLN_MASK_MSG_SENDER		0x000000f0
#define CLN_MASK_MSG_RECVER		0x0000000f

/*-----------------------------------------------------------------------------
 *	Message Naming Functions
 *----------------------------------------------------------------------------*/
#define	Cln_MsgInOrExt(y)			(y<<28)
#define	Cln_MsgName(y)				(y<<12)
#define Cln_MsgType(y)				(y<<8)
#define Cln_MsgSender(y)			(y<<4)
#define Cln_MsgReceiver(y)			(y<<0)

/*-----------------------------------------------------------------------------
 *	Message Getting or Setting Functions
 *----------------------------------------------------------------------------*/
#define	Cln_GetMsgInOrExt(x)			( ((x & CLN_MASK_MSG_INOREXT) >> 28) & 0xf )
#define	Cln_GetMsgName(x)				( ((x & CLN_MASK_MSG_NAME) >> 12) & 0xffff )
#define	Cln_GetMsgType(x)				( ((x & CLN_MASK_MSG_TYPE) >> 8) & 0xf )
#define	Cln_GetMsgSender(x)				( ((x & CLN_MASK_MSG_SENDER) >> 4) & 0xf )
#define	Cln_GetMsgReceiver(x)			( ((x & CLN_MASK_MSG_RECVER) >> 0) & 0xf )

#define	Cln_SetMsgInOrExt(x,y)			( x = (x&~CLN_MASK_MSG_INOREXT) | Cln_MsgInOrExt(y) )
#define	Cln_SetMsgName(x,y)			( x = (x&~CLN_MASK_MSG_NAME) | Cln_MsgName(y) )
#define	Cln_SetMsgType(x,y)			( x = (x&~CLN_MASK_MSG_TYPE) | Cln_MsgType(y) )
#define	Cln_SetMsgSender(x,y)			( x = (x&~CLN_MASK_MSG_SENDER) | Cln_MsgSender(y) )
#define	Cln_SetMsgReceiver(x,y)		( x = (x&~CLN_MASK_MSG_RECVER) | Cln_MsgReceiver(y) )

#define CLN_MAKE_MSG(a,b,c,d,e)		(Cln_MsgInOrExt(a)|Cln_MsgName(b)|Cln_MsgType(c)|Cln_MsgSender(d)|Cln_MsgReceiver(e))

/*
 * for message define
 */

#define ST_m			0x0
#define ST_M			0x1

#define ST_REQ			0x1		/* Request */
#define ST_RSP			0x2		/* Response */
#define ST_EVT			0x3		/* Event */
#define ST_RPT			0x3		/* Report */
#define rjt                 0x4
#define ntfy                0x5
#define clr                 0x6

#define ST_SCF			0x1		/* SCF Module */
#define ST_TMF			0x2		/* TMF Module */
#define ST_MSF			0x3		/* MSF Module */
#define ST_CLN			0x5		/* CLIENT Module */
#define ST_MONITOR		0x8 // todo 필요성?? by whwo0312

// Msg (CLN<->TMF)
#define M_Login_req_CLN_TMF					CLN_MAKE_MSG(ST_M,ST_Login, 				ST_REQ, ST_CLN, ST_TMF)
#define M_Login_resp_TMF_CLN				CLN_MAKE_MSG(ST_M,ST_Login, 				ST_RSP, ST_TMF, ST_CLN)
#define M_Logout_req_CLN_TMF				CLN_MAKE_MSG(ST_M,ST_Logout,				ST_REQ, ST_CLN, ST_TMF)
#define M_Logout_resp_TMF_CLN				CLN_MAKE_MSG(ST_M,ST_Logout,				ST_RSP, ST_TMF, ST_CLN)
#define M_WorkModeChange_req_CLN_TMF		CLN_MAKE_MSG(ST_M,ST_WorkModeChange, 		ST_REQ, ST_CLN, ST_TMF)
#define M_WorkModeChange_resp_TMF_CLN		CLN_MAKE_MSG(ST_M,ST_WorkModeChange, 		ST_RSP, ST_TMF, ST_CLN)
#define M_HeartBeat_req_CLN_TMF				CLN_MAKE_MSG(ST_M,ST_HeartBeat,				ST_REQ,ST_CLN,ST_TMF)
#define M_HeartBeat_resp_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_HeartBeat,				ST_RSP,ST_TMF,ST_CLN)
#define M_HeartBeat_req_TMF_CLN				CLN_MAKE_MSG(ST_M,ST_HeartBeat,				ST_REQ,ST_TMF,ST_CLN)
#define M_HeartBeat_resp_CLN_TMF			CLN_MAKE_MSG(ST_M,ST_HeartBeat,				ST_RSP,ST_CLN,ST_TMF)


#define	M_CenterStat_req_CLN_TMF			CLN_MAKE_MSG(ST_M,ST_CenterStat,			ST_REQ,ST_CLN,ST_TMF)
#define M_CenterStat_resp_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_CenterStat,			ST_RSP,ST_TMF,ST_CLN)
#define M_CallPresent_evt_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_CallPresent,			ST_EVT,ST_TMF,ST_CLN)
#define M_CallConnect_evt_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_CallConnect,			ST_EVT,ST_TMF,ST_CLN)
#define M_ConnectionClear_evt_TMF_CLN		CLN_MAKE_MSG(ST_M,ST_ConnectionClear,		ST_EVT,ST_TMF,ST_CLN)
#define M_ConnectionClear_req_CLN_TMF		CLN_MAKE_MSG(ST_M,ST_ConnectionClear,		ST_REQ,ST_CLN,ST_TMF)
#define M_ConnectionClear_resp_TMF_CLN		CLN_MAKE_MSG(ST_M,ST_ConnectionClear,		ST_RSP,ST_TMF,ST_CLN)
#define M_CallHold_req_CLN_TMF				CLN_MAKE_MSG(ST_M,ST_CallHold,				ST_REQ,ST_CLN,ST_TMF)
#define M_CallHold_resp_TMF_CLN				CLN_MAKE_MSG(ST_M,ST_CallHold,				ST_RSP,ST_TMF,ST_CLN)
#define M_CallMake_req_CLN_TMF				CLN_MAKE_MSG(ST_M,ST_CallMake,				ST_REQ,ST_CLN,ST_TMF)
#define M_CallMake_resp_TMF_CLN				CLN_MAKE_MSG(ST_M,ST_CallMake,				ST_RSP,ST_TMF,ST_CLN)
#define M_CallConsult_req_CLN_TMF			CLN_MAKE_MSG(ST_M,ST_CallConsult,			ST_REQ,ST_CLN,ST_TMF)
#define M_CallConsult_resp_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_CallConsult,			ST_RSP,ST_TMF,ST_CLN)
#define M_CallConsult_evt_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_CallConsult,			ST_EVT,ST_TMF,ST_CLN)
#define M_CallConference_req_CLN_TMF		CLN_MAKE_MSG(ST_M,ST_CallConference,		ST_REQ,ST_CLN,ST_TMF)
#define M_CallConference_evt_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_CallConference,			ST_EVT,ST_TMF,ST_CLN)
#define M_CallConference_resp_TMF_CLN		CLN_MAKE_MSG(ST_M,ST_CallConference,		ST_RSP,ST_TMF,ST_CLN)
#define M_CallConsultCancel_req_CLN_TMF		CLN_MAKE_MSG(ST_M,ST_CallConsultCancel,		ST_REQ,ST_CLN,ST_TMF)
#define M_CallConsultCancel_resp_TMF_CLN	CLN_MAKE_MSG(ST_M,ST_CallConsultCancel,		ST_RSP,ST_TMF,ST_CLN)
#define M_SendMsg_req_CLN_TMF				CLN_MAKE_MSG(ST_M,ST_SendMsg,				ST_REQ,ST_CLN,ST_TMF)
#define M_SendMsg_resp_TMF_CLN				CLN_MAKE_MSG(ST_M,ST_SendMsg,				ST_RSP,ST_TMF,ST_CLN)
#define M_IvrAnnounce_req_CLN_TMF			CLN_MAKE_MSG(ST_M,ST_IvrAnnounce,			ST_REQ,ST_CLN,ST_TMF)
#define M_IvrAnnounce_resp_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_IvrAnnounce,			ST_RSP,ST_TMF,ST_CLN)
#define M_AgentState_req_CLN_TMF			CLN_MAKE_MSG(ST_M,ST_AgentState,			ST_REQ,ST_CLN,ST_TMF)
#define M_AgentState_resp_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_AgentState,			ST_RSP,ST_TMF,ST_CLN)
#define M_Reset_req_CLN_TMF					CLN_MAKE_MSG(ST_M,ST_Reset,					ST_REQ,ST_CLN,ST_TMF)
#define M_Reset_resp_TMF_CLN				CLN_MAKE_MSG(ST_M,ST_Reset,					ST_RSP,ST_TMF,ST_CLN)
#define M_Reset_evt_TMF_CLN					CLN_MAKE_MSG(ST_M,ST_Reset,					ST_EVT,ST_TMF,ST_CLN)
#define M_CallTransferSimple_req_CLN_TMF	CLN_MAKE_MSG(ST_M,ST_CallTransferSimple,	ST_REQ,ST_CLN,ST_TMF)
#define M_CallTransferSimple_resp_TMF_CLN	CLN_MAKE_MSG(ST_M,ST_CallTransferSimple,	ST_RSP,ST_TMF,ST_CLN)
#define M_CallTransfer_req_CLN_TMF			CLN_MAKE_MSG(ST_M,ST_CallTransfer,			ST_REQ,ST_CLN,ST_TMF)
#define M_CallTransfer_resp_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_CallTransfer,			ST_RSP,ST_TMF,ST_CLN)
#define M_CallTransfer_evt_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_CallTransfer,			ST_EVT,ST_TMF,ST_CLN)
#define M_CallConferenceSimple_req_CLN_TMF	CLN_MAKE_MSG(ST_M,ST_CallConferenceSimple,	ST_REQ,ST_CLN,ST_TMF)
#define M_CallConferenceSimple_resp_TMF_CLN	CLN_MAKE_MSG(ST_M,ST_CallConferenceSimple,	ST_RSP,ST_TMF,ST_CLN)
#define M_CallConferenceSimpleCancel_req_CLN_TMF	CLN_MAKE_MSG(ST_M,ST_CallConferenceSimpleCancel,ST_REQ,ST_CLN,ST_TMF)
#define M_CallConferenceSimpleCancel_resp_TMF_CLN	CLN_MAKE_MSG(ST_M,ST_CallConferenceSimpleCancel,ST_RSP,ST_TMF,ST_CLN)
#define M_PermissionChange_req_CLN_TMF		CLN_MAKE_MSG(ST_M,ST_PermissionChange,		ST_REQ,ST_CLN,ST_TMF)
#define M_PermissionChange_resp_TMF_CLN		CLN_MAKE_MSG(ST_M,ST_PermissionChange,		ST_RSP,ST_TMF,ST_CLN)
#define M_PermissionChange_evt_TMF_CLN		CLN_MAKE_MSG(ST_M,ST_PermissionChange,		ST_EVT,ST_TMF,ST_CLN)
#define M_Bill_req_CLN_TMF					CLN_MAKE_MSG(ST_M,ST_Bill,					ST_REQ,ST_CLN,ST_TMF)
#define M_Bill_resp_TMF_CLN					CLN_MAKE_MSG(ST_M,ST_Bill,					ST_RSP,ST_TMF,ST_CLN)
#define	M_BillCancel_req_CLN_TMF			CLN_MAKE_MSG(ST_M,ST_BillCancel,			ST_REQ,ST_CLN,ST_TMF)
#define M_BillCancel_resp_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_BillCancel,			ST_RSP,ST_TMF,ST_CLN)
#define M_AgentState_req_CLN_TMF			CLN_MAKE_MSG(ST_M,ST_AgentState,			ST_REQ,ST_CLN,ST_TMF)
#define M_AgentState_resp_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_AgentState,			ST_RSP,ST_TMF,ST_CLN)
#define M_AgentReconnect_req_CLN_TMF		CLN_MAKE_MSG(ST_M,ST_AgentReconnect,		ST_REQ,ST_CLN,ST_TMF)
#define M_AgentReconnect_resp_TMF_CLN		CLN_MAKE_MSG(ST_M,ST_AgentReconnect,		ST_RSP,ST_TMF,ST_CLN)
#define M_IvrFail_evt_TMF_CLN				CLN_MAKE_MSG(ST_M,ST_IvrFail,				ST_EVT,ST_TMF,ST_CLN)
#define M_CallConferenceSimple_req_CLN_TMF	CLN_MAKE_MSG(ST_M,ST_CallConferenceSimple,	ST_REQ,ST_CLN,ST_TMF)
#define M_CallConferenceSimple_resp_TMF_CLN	CLN_MAKE_MSG(ST_M,ST_CallConferenceSimple,	ST_RSP,ST_TMF,ST_CLN)
#define M_IvrNumEvent_evt_CLN_TMF		    CLN_MAKE_MSG(ST_M,ST_IvrNumEvent,			ST_EVT,ST_CLN,ST_TMF)
#define M_IvrCancel_req_CLN_TMF				CLN_MAKE_MSG(ST_M,ST_IvrCancel,				ST_REQ,ST_CLN,ST_TMF)
#define M_IvrCancel_resp_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_IvrCancel,				ST_RSP,ST_TMF,ST_CLN)
#define M_SecretMonitor_req_CLN_TMF			CLN_MAKE_MSG(ST_M,ST_SecretMonitor,			ST_REQ,ST_CLN,ST_TMF)
#define M_SecretMonitor_resp_TMF_CLN		CLN_MAKE_MSG(ST_M,ST_SecretMonitor,			ST_RSP,ST_TMF,ST_CLN)
#define M_AgentStatus_evt_CLN_TMF			CLN_MAKE_MSG(ST_M,ST_AgentStatus, 			ST_EVT, ST_CLN, ST_TMF)
#define M_AgentEvent_evt_CLN_TMF			CLN_MAKE_MSG(ST_M,ST_AgentEvent, 			ST_EVT, ST_CLN, ST_TMF)
#define M_AgentEvent_evt_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_AgentEvent, 			ST_EVT, ST_TMF, ST_CLN)
#define M_IvrAnnounce2_req_CLN_TMF			CLN_MAKE_MSG(ST_M,ST_IvrAnnounce2, 			ST_REQ, ST_CLN, ST_TMF)
#define M_IvrAnnounce2_resp_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_IvrAnnounce2, 			ST_RSP, ST_TMF, ST_CLN)
#define M_CallRetrieve_req_CLN_TMF				CLN_MAKE_MSG(ST_M,ST_CallRetrieve,				ST_REQ,ST_CLN,ST_TMF)
#define M_CallRetrieve_resp_TMF_CLN			CLN_MAKE_MSG(ST_M,ST_CallRetrieve,				ST_RSP,ST_TMF,ST_CLN)


#endif /* _TMF_CLN_MSG_H_ */

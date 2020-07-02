#ifndef __MESSAGE_STRUCTURE_HPP__
#define __MESSAGE_STRUCTURE_HPP__


#define MAX_MSG_SIZE				(8*1024)

typedef struct stMsgHeader{
	char            			cFrame[2];		///< Message frame, must be set to 0xFEFE
	unsigned short  			usLength; 		///< Total message length (Header length + Body length)
	unsigned int 				unMsgName;		///< Message name
	unsigned long		    	ulSeq;			///< Message sequence
	unsigned int				unGwRteVal;		///< G/W route value
	short						sRet;			///< Result
	unsigned char				ucVersion;		///< Version
	unsigned char				ucReserved;		///< Reserved

	void Clear(){
		cFrame[0] = '\0'; cFrame[1] = '\0';
		usLength = 0;
		unMsgName = 0;
		ulSeq = 0;
		unGwRteVal = 0;
		sRet = 0;
		ucVersion = 0;
		ucReserved = 0;
	}
}_MSG_HEADER;

typedef struct stMessage{
	_MSG_HEADER			stHeader;
	char				cBody[MAX_MSG_SIZE - sizeof(_MSG_HEADER)];

	void Clear(){
		stHeader.Clear();
		cBody[0] = '\0';
	}
}_MESSAGE;



typedef struct stClnHeader {
	int nType;

	void Clear() {
		nType = -1;
	}
} _CLN_HEADER;

//#define TMF_CLN_BODY_SIZE			(TMF_CLN_MSG_SIZE - sizeof(_CLN_HEADER)) //임시

#pragma pack(push, 4) // sizeof(_CLN_PACKET) 값을 908로 맞추기 위해 4 byte 단위로 pack 설정
typedef struct stClnPacket {
	_CLN_HEADER stHeader;
	union {
		C_HEARTBEAT_REQ stHeartBeatReq;
		C_HEARTBEAT_RESP stHeartBeatResp;

		C_LOGIN_REQ stLoginReq;
		C_LOGOUT_REQ stLogoutReq;
		C_CENTERSTAT_REQ stCenterStatReq;
		C_CENTERSTAT_RESP stCenterStatRsp;
		C_AGTINFO_STATUS stAgentInfoStatus;
		C_WORKMODECHANGE_REQ stWorkModeChangeReq;
		C_CALLPRESENT_EVENT stCallPresentEvent;
		C_CALLCONNECT_EVENT stCallConnectEvent;
		C_CONNECTIONCLEAR_EVENT stConnectionClearEvent;
		C_CONNECTIONCLEAR_REQ stConnectionClearReq;
		C_CALLHOLD_REQ stCallHoldReq;
		C_CALLMAKE_REQ stCallMakeReq;
		C_CALLCONSULT_REQ stCallConsultReq;
		C_CALLCONSULT_EVENT stCallConsultEvent;
		C_CALLCONFERENCE_REQ stCallConferenceReq;
		C_CALLCONSULTCANCEL_REQ stCallConsultCancelReq;
		C_SENDMSG_REQ stSendMsgReq;
		C_AGTINFO_EVENT stAgentInfoEvent;
		C_IVRANNOUNCE_REQ stIvrAnnounceReq;
		C_IVRANNOUNCE_REQ2 stIvrAnnounceReq2;

		C_RESET_REQ stResetReq;
		C_RESET_EVENT stResetEvent;
		C_CALLTRANSFERSIMPLE_REQ stCallTransferSimpleReq;
		C_CALLTRANSFER_REQ stCallTransferReq;
		C_CALLCONFERENCESIMPLE_REQ stCallConferenceSimpleReq;
		C_CALLCONFERENCESIMPLECANCEL_REQ stCallConferenceSimpleCancelReq;
		//C_PERMISSIONCHANGE_REQ stPermissionChangeReq;
		C_PERMISSIONCHANGE_EVENT stPermissionChangeEvent;
		C_BILL_REQ stBillReq;
		C_BILLCANCEL_REQ stBillCancelReq;
		C_AGENTSTATE_REQ stAgentStateReq;
		C_AGENTSTATE_RESP stAgentStateResp;
		C_AGENTRECONNECT_REQ stAgentReconnectReq;
		C_IVRFAIL_EVENT stIvrFailEvent;
		C_CALLCONFERENCESIMPLE_EVENT stCallConferenceSimpleEvent;
		C_IVRNUM_EVENT stIvrNumEvent;
		C_IVRCANCEL_REQ stIvrCancelReq;
		C_SECRETMONITOR_REQ stSecretMonitorReq;
		C_CALLRETRIEVE_REQ stCallRetrieveReq;

		C_RESPONSE stResponse;
//	char cReserved[TMF_CLN_BODY_SIZE];
	} stData;

	void Clear() {
		stHeader.Clear();
		memset(&stData, 0x00, sizeof(stData));
	}
} _CLN_PACKET;
#pragma pack(pop) //pack 단위 원복











#endif
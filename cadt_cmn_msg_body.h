/*
 * cadt_cmn_msg_body.h
 *
 *  Created on: 2017. 6. 27.
 *      Author: whwo0312
 */

#ifndef INC_APP_CADT_CADT_CMN
#define INC_APP_CADT_CADT_CMN


#define GET_MSGN_NAME(Msg)					( Msg & 0xffff )

/* define */
//기존 cti 소스 define
#define		CID_RECORD_MAXCOUNT			5
#define 	MAX_MSG_CNT             			22
#define 	MAX_PERMISSION_CNT				50
#define 	MAX_PERMISSION_CNT_CLIENT  	12
#define 	MAX_USRINFO_IN_BILL     			8

//added by ghlee 2017.06.29 - Request Buffer관리를 위해 추가함
#define		MAX_REQBUF_CNT						4

//추가 define by whwo0312
#define		MAX_AGENT_CALL_CNT				3										/* 에이전트당 연관된 최대 CALL 개수 */
//#define		MAX_CADT_MSG_SIZE				(8*1024)							/* todo 임시.. 정의 필요 */
#define		MAX_CADT_CLN_CNT				10000								/* todo 명칭 변경 필요. (공용이므로) _AGENT_INFO의 Index == 내선번호 */
#define 	MAX_CADT_CLN_SESS_CNT			1400
#define		MAX_TMF_FNSIF_THREAD_CNT		8



#define MAX_CADT_ID_LEN 				20
#define MAX_CADT_NAME_LEN 				128
#define MAX_CADT_DN_LEN 				24
#define MAX_CADT_GROUP_ID_LEN 			24
#define MAX_CADT_QUEUE_ID_LEN 			24
#define MAX_CALLKEY_LEN					24
#define MAX_CADT_RECORD_CNT 			5
#define MAX_CADT_SENDMSG_CNT 			22
#define MAX_CADT_TEAM_ID_LEN 			24
#define MAX_CADT_SEARCHKEY_LEN 			30
#define MAX_CADT_ADDRS_LEN 				80
#define MAX_CADT_AUTO_GUIDE_LEN 		4
#define MAX_CADT_IVR_MENT_LEN 			100
#define MAX_CADT_DIALED_NUMBER_LEN	8



/* common typedef */
typedef char 		_AGENTID[20];
typedef char 		_FNSIFID[20];
typedef char		_NAME[128];
typedef char		_PHONENUMBER[24];
typedef char		_AGENTID[20];
typedef char		_SEARCHKEY[30];
typedef char		_GROUPID[24];   /* paul added 990503 */
typedef char		_QUEUEID[24];   /* paul added 990503 */
typedef int			_AGENTDN;   	/* paul added 990503 */
typedef char   		_RECORDFILE[32];
typedef char   		_ADDRS[80];
typedef char   		_DEVICE[24];
typedef int     	_BILLKIND;   	/* paul added 990503 */
typedef int     	_CALLID;

typedef enum //안내단말 내부 전화기 상태값
{
	FSM_LOGOUT = 0,
	FSM_NOTREADY,
	FSM_READY,
	FSM_PRESENT, //호인입
	FSM_CALL, //통화중
    FSM_IVR, //자동안내중
    FSM_HOLD, //보류
    FSM_EMERGENCY_CALL, //비상 호출. 기능 제외됨
    FSM_EMERGENCY,//?
    FSM_LEADER_CONSULT, //감독통화 가기전 상담상태
    FSM_LEADER, //감독통화
    FSM_CONFERENCE_CONSULT, //3자통화 상담상태
    FSM_CONFERENCE,//3자통화
    FSM_TRANSFER_CONSULT, //호전환 상담상태
    FSM_CALLMAKE, //발신중
    FSM_MONITOR,//?
    FSM_HOSTDOWN, //기능 제한
    FSM_HOSTDOWN_RECORVER,
	FSM_VOC
} _FSM_STATE;


enum enCadtLocation{
	CADT_LOCATION_INIT = 0,
	CADT_LOCATION_LOCAL,
	CADT_LOCATION_REMOTE
};

typedef enum {
	MSF_TMF_HB_INIT = 0,
	MSF_TMF_RECONNECT_AUDIT = 1
} _MSF_TMF_HB_TYPE;



typedef enum {
    DS_False = 0,
    DS_True = 1
} _BOOLEAN;

typedef enum{
	WM_RC_LOGIN = 0,
	WM_RC_REST = 201,
	WM_RC_MEAL = 202,
	WM_RC_EDU = 203,
	WM_RC_ETC = 204

}_WORKMODE_REASONCODE;

typedef enum {
    RT_CREATE	= 1,
    RT_APPEND
} _RECORDTYPE;

typedef enum {
    AT_Agent,
    AT_Manager
} _AGENTTYPE;

/* agent work mode */
typedef enum {
	WM_NotReady = 0,        /* 준비 */
	WM_Ready,               /* 대기 */
	WM_Call,                /* 안내중 */
	WM_WorkReady = 8,		/* 후처리 */
	WM_Logout = 9,           /* Logout (Not def'd in TMS header ) */
	WM_LoginTrying = 10,     /* TMF 신규 추가 : FNSIF로 LoginReq 보낸 상태 */
	WM_ReconnectTrying = 11,	 /* TMF 신규 추가 : Reconnect후 Fnsif로 보낸 상태 */
	WM_ReconnectCall = 12,	/* TMF 신규 추가 : Reconnect 한 단말의 상태가 Call인 상태. Rsp값이 Call로 오지 않으므로 저장 후 상태값을 Call로 하기위함. */
	WM_UnKnown = 99
} _WORKMODE;

/* customer phone type */
typedef enum {
    PT_Normal,
    PT_Public
} _PHONETYPE;

/* customer & guide phone type in AgentInfoEvent 추가 by whwo0312 / 20170930*/
typedef enum {
	AGTEVT_Normal = 0x01,
	AGTEVT_Public = 0x02,
	AGTEVT_Wireless = 0x03,
	AGTEVT_VoIP = 0x04,
	AGTEVT_None = 0x99
} _AGTEVT_PHONETYPE;

/* 호 종류 (TMS Header와 동일) */
typedef enum {
	CT_Normal = 0,          /* 일반 인입호  (IB) */
	CT_Transfer,            /* 전환호 */
	CT_Reconnect,           /* 재접속호 */
	CT_Consult,             /* 3자 문의호 */
	CT_Conference,          /* 3자 통화호 */
	CT_Internal,            /* 내선호 (O/B) */
	CT_External,            /* OutBound */
	CT_None = 9             /* no call */
} _CALLTYPE;

/* make call type (conference call type) */
typedef enum {
    MKCT_Undefine = -1,	/* internal call  (general conference call)  */
    MKCT_Internal = 0,	/* internal call  (general conference call)  */
    MKCT_External,	/* external call  (external conference call) */
    MKCT_Leader		/* leader call    (leader conference call)   */
} _MKCALLTYPE;

/* operation code (used in _IVRANNOUNCE_REQ) Edit by whwo0312*/
#if _OLD_VER
typedef enum {
    OC_Success,
    OC_NotRegister,
    OC_CanNotAnnounce,
    OC_NotAcceptPublicPhone,
    OC_NotAcceptDirectConn,
    OC_NotGeneralPhoneNumber,
    OC_NotAinPhoneNumber,
    OC_NotAnnounceDirectConn
} _OPCODETYPE;
#else
typedef enum {
    OC_AutoGuide = 0,
    OC_DirectConn,
    OC_IndirectConn,
    OC_Direct_IndirectConn,
    OC_SmsTransmission,
    OC_AgentFinishMent,
} _OPCODETYPE;
#endif

/* inquiry types (used in _IVRANNOUNCE_REQ) */
/*
typedef enum {
    INT_GENERAL_NUMBER,
    INT_OFFICE_NUMBER,
    INT_AREA_CODE,
    INT_NATION_CODE
} _INQSERVICETYPE;
*/

/* TRANSFER TYPE */
typedef enum {
    TT_GROUP,	/* Group Transfer call */
    TT_AGENT	/* Agent Transfer call */
} _TRANSFERTYPE;

/* message type */
typedef enum {
    OT_ALL,
    OT_GROUP,
    OT_AGENT,
	OT_MANAGER
} _OBJECTTYPE;

typedef enum {
    BT_ReMark,
    BT_Change
} _BILLMSGTYPE;

typedef enum {
    BT_Origination,
    BT_Destination
} _BILLTYPE;

typedef enum {
    PT_ExternalCall,
    PT_ConferenceCall
} _PERMISSIONTYPE;

typedef enum {
    CR_TRANSFER = 1,
    CR_IVR = 2,
    CR_CALLEDPARTY_BUSY = 		0x0302,
    CR_NOANSWER =			0x0303,
    CR_CONGESTION = 			0x0304,
    CR_FAXDETECT = 			0x0309
} _CALLRECORDTYPE;	/* call record type */

typedef enum {
    WCT_Undefine,	/* 미정의 */
    WCT_Internal_OB,	/* 내선발신 */
    WCT_External_OB,	/* 외선발신 */
    WCT_Internal_IB,	/* 내선착신 */
    WCT_External_IB,	/* 외선착신(안내호) */
    WCT_Hold,		/* 보류 */
    WCT_Conference,	/* 3자통화*/
    WCT_ConferenceSimple/* 비상호출 */
} _WORKCALLTYPE;

typedef enum {
	RM_NOT_READY = 0,
	RM_READY,
	RM_WORK_READY = 8,
	RM_LOGOUT,
	RM_PBX_LOGOUT,
	RM_FNS_ALL_DOWN,
} _RESETMODE;

typedef enum {
    CT_IB_Normal = 1,		/* 안내호 착신 		*/
    CT_IB_Reconnect,		/* 재접속호 착신 	*/
    CT_IB_Consult,		/* 문의 착신  		*/
    CT_IB_AgentTransfer,	/* 안내원 호전환호 착신	*/
    CT_IB_GroupTransfer,	/* 그룹 호전환호 착신  	*/
    CT_IB_Conference,		/* 3자통화 착신  	*/
    CT_IB_Emergency,		/* 비상호출 착신 	*/
    CT_IB_Internal,		/* 내선 착신 		*/
    CT_Req_Consult,		/* 문의 요청 		*/
    CT_Req_AgentTransfer,	/* 안내원 호전환 요청 	*/
    CT_Req_GroupTransfer,	/* 그룹 호전환 요청 	*/
    CT_Req_Conference,		/* 3자통화 요청 	*/
    CT_Req_Emergency,		/* 비상호출 요청 	*/
    CT_Req_Internal,		/* 내선 발신 		*/
    CT_Req_External,		/* 외선 발신 요청 	*/
    CT_Logout,
    CT_PutResult
} _CONTACTTYPE;

typedef enum {
	BT_OUTBOUND = 0,
	BT_INBOUND = 1,
} _BOUNDTYPE;


//Finesse Call Type (in callVariables)
typedef enum {
	FNSCT_UNKNOWN = 0, 				//분석못함(UNKNOWN)
	FNSCT_INBOUND	= 1, 					//인입호(INBOUND)
	FNSCT_AUTOCONNECT = 2, 			// 직접연결호(AUTOCONNECT)
	FNSCT_RECONNECT = 3, 				// 재접속호(RECONNECT)
	FNSCT_OUTBOUND = 4, 				// 외부발신호(OUTBOUND)
	FNSCT_TRANSFER	 = 5, 				// 전환호(TRANSFER)
	FNSCT_GROUP_TRANSFER = 6, 	// 그룹전환호(GROUP_TRANSFER)
	FNSCT_INTERNAL = 7, 					// 내선통화호(INTERNAL)
	FNSCT_EMERGENCY = 8, 				// 비상호출호(EMERGENCY)
	FNSCT_INT_CONFERENCE = 9, 		// 내부 3자통화호 (INT_CONFERENCE)
	FNSCT_EXT_CONFERENCE = 10, 	// 외부 3자통화호 (EXT_CONFERENCE)
	FNSCT_CONSULT = 11, 				// 회의호 (CONSULT)
	FNSCT_FAX = 12, 							// FAX 안내호 (FAX)
	FNSCT_MANY_GUIDE = 13, 			// 다량안내호(MANY_GUIDE)
	FNSCT_AUTO_GUIDE = 14, 			// 자동안내호(AUTO_GUIDE)
	FNSCT_AGENT_GUIDE = 15, 		// 육성안내호(AGENT_GUIDE)
	FNSCT_NON_GUIDE	= 16, 			// 미안내호(NON_GUIDE)
	FNSCT_INFO_GUIDE	= 17, 			// 생활정보안내호 (INFO_GUIDE)
	FNSCT_CUST_DROP	= 18, 			// 포기호 (CUST_DROP)
	FNSCT_URGENCY	= 19, 				// 긴급특번
	FNSCT_INDIRECT	= 20,				// 간접연결호
	FNSCT_REJECT_GUIDE	= 21, 		// 차단호 (REJECT_GUIDE)
} _FNSCALLTYPE;


//Client Call Type (in C_AGTINFO_EVENT)
typedef enum {
	CLNCT_NON_GUIDE = FNSCT_NON_GUIDE,		//미안내 (16)
	CLNCT_INFO_GUIDE = FNSCT_INFO_GUIDE,		//생활안내 (17)
	CLNCT_AGENT_GUIDE = FNSCT_AGENT_GUIDE,	//육성안내 (15)
	CLNCT_AUTO_GUIDE = FNSCT_AUTO_GUIDE,		//자동안내 (14)
}_CLNCALLTYPE;



#pragma pack(push, 4) // sizeof(_CLN_PACKET) 값을 908로 맞추기 위해 4 byte 단위로 pack 설정

typedef struct {
		char		szDn[24];
		char		szLoginId[20];
		char		szFnsLoginId[20];
		int		 	nCid;
		char		szCallKey[24];
} C_CALLRETRIEVE_REQ;

typedef struct {
		char szDn[24];
		char szLoginId[20];
		char szAgentName[128];
		int nInqLocalType;
		int nInqServiceType;
		char szSearchKey[30];
		char szPadding[2];
		char szResultNumber;
		_CALLRECORDTYPE enCRType;
} _CID_RECORD;

typedef struct {
		char szAgentId[128];
//    _AGENTDN		nAgentDn;
		short nExternalOutboundPermission;
		short nExternalConsultPermission;
} _AGENTDETAIL;

typedef struct stLoginReq {
		char		 	szDn[24];
		char 			szLoginId[20];
		char 			szFnsLoginId[20];
		char 			szUserName[128];
		char	 		szGroupId[24];
		char			szNormalQueueId[24];
		char 			szUserInfo[52];
		int				nAgentType;
		short 			sExternalOutboundPermission;
		short 			sExternalConsultPermission;
		int				nAutoAnswerFlag;

} C_LOGIN_REQ;

typedef struct stLogoutReq {
		char			szDn[24];
		char			szLoginId[20];
		char 			szFnsLoginId[20]; // 실제 미사용
		char 			szGroupId[24]; //실제 미사용
		int				nAgentType; // 실제 미사용
} C_LOGOUT_REQ;

typedef struct {
		char			szDn[24];
		char 			szLoginId[20];
		char			szGroupId[24];
		_WORKMODE		nAgentStatus;	//추가
		_FSM_STATE		enClientState;
} C_CENTERSTAT_REQ;

typedef struct {
		int				nReady;			///< receive 대기호수
		int				tReady;			///< receive 대기시간
		int 			nExistMsg;		///< 신규 메세지 존재 여부
		int				nVaSvc1; 		//todo 주석적ㄱ
		int				nVaSvc2;
} C_CENTERSTAT_RESP;

typedef struct {
		char			szDn[24]; 	/* 내선번호 */
		char			szAgentId[20];
		char			szFnsLoginId[20];
		char			szAgentName[128];
		char			szGroupId[24];
		_WORKMODE		nAgentStatus; 			/* 상담사 상태 */
		_AGENTTYPE		nAgentType; 			/* 상담사 종류 */
} C_AGTINFO_STATUS;

typedef struct stWorkModeChangeReq {
		char 			szDn[24];
		char 			szLoginId[20];
		char 			szFnsLoginId[20];
		char			szGroupId[24];
		int 			nCause;		/*준비 변경 사유 */
		_WORKMODE 		enNewMode;	/*변경할 상담사 상태*/
		_AGENTTYPE		nAgentType; /*상담사 종류(안내, 감독)*/
} C_WORKMODECHANGE_REQ;

typedef struct {
		char			szPlayDevice[24]; 	/*playing channel number*/
		char			szCalling[24]; 	/*인입호 전화번호*/
		char			szOrigCalling[24]; /*호 전환시 전화번호*/
#if 0
		char			szOID[99];						/*접속번호 정보*/
#else
		char			szOID[50];						/*접속번호 정보*/
		char			szAgentAtime[24];			/*호 인입 시간*/
		char			szCallKey[24];					/*Call Key*/
#endif
		char			cVip;							/*VIP 유무*/
		char			cBadUserGrade;		/*관심고객레벨*/
		int				nCid;							/*호 ID*/
		_PHONETYPE		enPhoneType;					/*전화 종류*/
		_CALLTYPE		enCallType;						/*호 종류*/
		int				tWaitingInQueue;				/*큐 대기 시간*/
		int				nTransferCnt;					/*전환된 호 개수*/
		int 			nServedLogCnt;					/**/
		_CID_RECORD		stCR[MAX_CADT_RECORD_CNT];
} C_CALLPRESENT_EVENT, C_CONFERENCE_EVENT, C_CALLTRANSFER_EVENT;

typedef struct {
		char			szCalling[24];	/*발신번호*/
		int			nPrimaryCid;								/*최초 인입호*/
		int			nSecondaryCid;							/*상담 인입호*/
} C_CALLCONSULT_EVENT;

typedef struct {
		char			szCalling[24]; /*발신번호*/
		int				nReady; 					/*receive 대기호수 */
		int 			tReady; 					/*receive 대기시간 */
		int 			nCid; 						/*호 ID*/
		_CALLTYPE 		enCallType;
		int 			nIsInbound;					/*Inbound 여부*/
		char			szCallKey[24];
} C_CALLCONNECT_EVENT;

typedef struct {
		int 			nCid;
		int 			enCallType; 			// 1:Secondary On, 0:OFF
		int 			nIsInbound;
		char			szCallKey[24];
} C_CONNECTIONCLEAR_EVENT;

typedef struct {
		char			szDn[24];
		char			szLoginId[20];
		char			szFnsLoginId[20];
		_CALLID nCid;
		char			szCallKey[24];
} C_CONNECTIONCLEAR_REQ;

typedef struct {
		char			szDn[24];
		char			szLoginId[20];
		char			szFnsLoginId[20];
		_CALLID 		nCid;
		char			szCallKey[24];
} C_CALLHOLD_REQ;


typedef struct {
		char			szDn[24];
		char			szLoginId[20];
		char			szFnsLoginId[20];
		char			szDestination[24];
		_MKCALLTYPE 	enMkCallType;
} C_CALLMAKE_REQ;

typedef struct {
		char			szDn[24];
		char			szLoginId[20];
		char			szFnsLoginId[20];
		char			szDestination[24]; /*대상 전화번호*/
		int		 		nCid;
		_MKCALLTYPE 	enMkCallType;
		char			szCallKey[24];
		char			szDialedNumber[MAX_CADT_DIALED_NUMBER_LEN]; // CONSULT 요청 전 UPDATE_CALL_DATA 때
} C_CALLCONSULT_REQ;

typedef struct {
		char			szDn[24];
		char 			szLoginId[20];
		char 			szFnsLoginId[20];
		int 			nPrimaryCid;		/*최초인입호*/
		int 			nSecondaryCid;		/*전환인입호*/
		char			szDestination[24]; /*대상 전화번호*/
		char			szCallKey[24];
} C_CALLCONFERENCE_REQ;

typedef struct {
		char			szDn[24];
		char			szLoginId[20];
		char			szFnsLoginId[20];
		_CALLID 		nCid;
		char			szCallKey[24];
} C_CALLCONSULTCANCEL_REQ;

#define MAX_SENDMSG_AGENTID_CNT 24

typedef struct {
		char			szDn[24];
		char			szLoginId[20];
		char			szGroupId[24];
		_OBJECTTYPE 	enObjectType;		/*메시지 타입*/
		int 			nAgentCnt;			/*메시지 수신 Agent 수*/
		char			szReceiveId[20 * MAX_SENDMSG_AGENTID_CNT]; //최대 개인은 24개, 그룹은 22개
} C_SENDMSG_REQ;

#pragma pack(pop) //pack 단위 원복

#pragma pack(push, 4)

typedef struct {
		char szDeviceId[24];		/*내선번호*/
		unsigned int unCallId; 			/*인입호 ID*/
		int  nSearchCount; 			/*자동안내까지의 검색 횟수*/
		int  nCellPos;				/*Cell Pos 값*/
		unsigned short usSelSvc; 			/*검색서비스지역*/
		char cCustType;				/*고객 유형*/
		char cCallType; 			/*호타입*/
		char szCustomerANI[16]; 	/*고객번호*/
		char szCustomerName[16]; /*고객이름	*/
		unsigned char ucCustomerPhone; 		/*고객전화기 타입*/
		char cCustomerCarrier; 		/*고객사업자*/
		char cCustomerSvcFlag; 		/*고객기준서비스 플래그*/
		char cVip;					/*VIP 유무*/
		char cBadUserGrade;			/*관심고객레벨*/
//		char cCallcase; 			/*인입유형*/
//		char cSelArea; 				/*검색선택*/
		char	szAgentIP[20];		/*상담사 좌석 IP*/
		char	szTeamID[20];		/*팀 ID*/
		char szGuideNumber[16]; 	/*안내번호*/
		char szGuideName[64]; 		/*안내상호*/
		unsigned char ucGuidePhone; 			/*안내번호 전화기 타입*/
		char cGuideCarrier; 		/*안내번호 사업자*/
		char cGuideSvcFlag; 		/*안내기준 서비스 플래그*/
		char cGuidePriority;		/*안내우선유무*/
		char cCallDist;				/*균등유무*/
		char szSearchSvcCode[10];		/*검색서비스코드*/
		char szSearchWord[16]; 		/*검색어*/
//		char cSearchResult; 		/*검색결과*/
		char cSubsFlag; 			/*상품가입여부*/
		char szDongCode[12]; 		/*동코드*/
		char szDongDiv[10];			/*안내동코드(dong_div)*/
		char szUpjongCode[8]; 		/*업종코드*/
		char cSmsType;				/*없음0, SMS1, LMS2, MMS3*/
		char cTerminationType;		/*상담사 종료 유형*/
		char szAdditionInfo[60];	/*후처리 입력 정보*/
		char szAutoGuide[2];		/*자동안내 유형*/
		char cAgentShortCut;		/*상담사 정보 제공*/
		char	cTransferCount;		/*전환된 호 개수*/
		char	cBillCount;				/*과금 횟수*/
		char szCallKey[24];
		char szAgentAtime[24];	/*호 인입 시간*/ //추가 by whwo0312 / 20171024
} C_AGTINFO_EVENT;

#pragma pack(pop) //pack 단위 원복

#pragma pack(push, 4)

typedef struct {
		char					szDn[24];
		char					szLoginId[20];
		char					szFnsLoginId[20];
		int					nCid;
		_OPCODETYPE nOpCode;
		char					szAutoGuide[MAX_CADT_AUTO_GUIDE_LEN];
		char					szAnnText1[MAX_CADT_IVR_MENT_LEN];
		char					szAnnText2[MAX_CADT_IVR_MENT_LEN];
		char					szResultNumber[24];
} C_IVRANNOUNCE_REQ;

typedef struct {
		C_IVRANNOUNCE_REQ stIvrAnnounceReq;
		C_AGTINFO_EVENT stAgentInfoEvent;
} C_IVRANNOUNCE_REQ2;


typedef struct {
    _PHONENUMBER	szDn;
    unsigned int        t_Login;			/* 당일 최초 login 시각*/
    int				t_NotReady;			/* 당일 총 준비시간(초단위)*/
    int				t_Ready;			/* 당일 총 대기시간(초단위)*/
    int				t_TotWork;			/* 총 근무 시간 (초단위)*/
    int				n_IB;				/* 총 착신 호수*/
    int				n_OB;				/* 총 발신 호수*/
    int				t_Call;				/* 당일 총 통화시간(초단위)*/
    int 			nAutoCall;			/* 자동 안내 호수 */
    int 			nMultiCall; 		/* 다량안내 처리 호수*/
    int 			nMultiCallCnt; 		/* 다량 안내 처리 건수*/
    int 			nManualCall;   		/* 육성 안내 호수 */
} C_AGENTSTATE_RESP;


typedef struct {
		char					szLoginDn[24];
		char					szLoginId[20];
		char					szFnsLoginId[20];
		char					szGroupId[24];			// add
		char					szTargetDn[24];
		_RESETMODE 	enResetMode;
		_AGENTTYPE 	nAgentType;			// add
} C_RESET_REQ;

typedef struct {
		char					szDn[24];
		_RESETMODE	enResetMode;
} C_RESET_EVENT;

typedef struct {
		char		szDn[24];
		char		szLoginId[20];
		char		szFnsLoginId[20];
		char		szDestination[24];
		int		nCid;
		int		nDestinationQ;
		int		nInqLocalType;
		int		nInqServiceType;
		char		szSearchKey[MAX_CADT_SEARCHKEY_LEN];
		char		szAniAddrs[MAX_CADT_ADDRS_LEN];
		char			szCallKey[24];
} C_CALLTRANSFERSIMPLE_REQ;

typedef struct {
		char		szDn[24];
		char		szLoginId[20];
		char		szFnsLoginId[20];
		int		nSourceCid;
		int		nTargetCid;
		int		nInqLocalType;
		int		nInqServiceType;
		char		szSearchKey[MAX_CADT_SEARCHKEY_LEN];
		char			szCallKey[24];
} C_CALLTRANSFER_REQ;

typedef struct {
		_PHONENUMBER szDn;
		char szLoginId[128];
		_CALLID nCid;
//    _PHONENUMBER	szDestination;   // 단말에서 없음
		_QUEUEID nDestQueueId;
		_ADDRS szAniAddrs;
} C_CALLCONFERENCESIMPLE_REQ;

typedef struct {
		_PHONENUMBER szDn;
		char szLoginId[128];
		_CALLID nCid;
		_PHONENUMBER szDestination;
		_QUEUEID nDestQueueId;
} C_CALLCONFERENCESIMPLECANCEL_REQ;

typedef struct {
		_PHONENUMBER szDn;
		char szLoginId[128];
		_OBJECTTYPE enObjectType; /* 0 : all, 1 : group, 2 : agent */
		int nAgentCnt;
		_AGENTDETAIL stAgentDetail[MAX_PERMISSION_CNT_CLIENT];
} C_PERMISSIONCHANGE_REQ;

typedef struct {
		_PHONENUMBER szDn;
		int nAgentCnt;
		struct {
				int szAgentDn;
				int nResult;
		} stAgentDetail[MAX_PERMISSION_CNT];
} C_PERMISSIONCHANGE_EVENT;

typedef struct {
		char		szDn[24];
		char		szLoginId[20];
		char		szFnsLoginId[20];
		char		szBillDn[24];			// 과금 대상 Dev ID */
		int			nCid;
		_BILLMSGTYPE enBillMsgType;
		_BILLTYPE enBillType;
		char cUsrInfo[MAX_USRINFO_IN_BILL];
		int nBillCount;
		char			szCallKey[24];
} C_BILL_REQ;

typedef struct {
		_PHONENUMBER szDn;
		char szLoginId[128];
		int nBillKind; /* Inbound,Transfer,Conference...*/
		int nBillingInfo;
		char szStartTime[24];
		char szEndTime[24];
		char szOrgNum[24];
		char szTermNum[24];
		char szBillingNum[24];
		int nVAXNum;
		int nTelNumCnt;		// fax data count
		int nImageCnt;
		int nPageCnt;
		int nReserved;
} C_BILLCANCEL_REQ;

typedef struct {
		char		szDn[24];
		char		szLoginId[20];
} C_AGENTSTATE_REQ;

typedef struct {
		char						szPadding1[4];
		C_LOGIN_REQ					stLoginReq;
		int							nRequestMsgId;	/* request message id */
		_WORKMODE					enWorkMode;		/* current work mode */
		int							nPrimaryCid;		/* primary call ID */
		int							nSecondaryCid;	/* secondary call ID */
//		_CALLTYPE					enCallType;
		_FSM_STATE					enClientState;
		_WORKMODE					enReservedWorkMode; //Work_Ready(과금 요청 중이었을 때), Not_Ready(통화 중 준비 예약했을 때)
		int 						nLastestNotReadyReasonCode;
		char						szPadding2[4];
		C_AGTINFO_EVENT				stAgentInfo;
} C_AGENTRECONNECT_REQ;

typedef struct {
		_CALLID nCid;
		int nFailCause;
} C_IVRFAIL_EVENT;

typedef struct {
		_PHONENUMBER szDn;
		char szLoginId[128];
		_CALLID nCid;
		_PHONENUMBER szDestination;
		int nNumOfQueuedCall;
} C_CALLCONFERENCESIMPLE_EVENT;

typedef struct {
		short sPrt_ID;
		short sID;
		char szTelNum[24];
		unsigned int unTime_t;
		char szAni[24];
		char szAgentId[12];
} C_IVRNUM_EVENT;

typedef struct {
		_PHONENUMBER szDn;
		char szLoginId[128];
		_CALLID nCid;
//    long		nTime;	/*	time reserved	단말 없음 */
} C_IVRCANCEL_REQ;

typedef struct {
		_PHONENUMBER szDn;
		char szLoginId[128];
		_PHONENUMBER szTargetDn;
} C_SECRETMONITOR_REQ;

typedef struct stResponse {
		char				szUsedDn[24]; /* login시 id 사용중인 내선번호*/
		char				szUsedLoginID[20]; /* login시 내선번호 사용중인 id*/
		char				szGroupID[24];
		char				szPlayDevice[24];  /* playing channel number 990713*/
		char				szTeamId[MAX_CADT_TEAM_ID_LEN];
		int					nErrorCode;
		_WORKMODE			enWorkMode;
		int					nPrimaryCid;
		int					nSecondaryCid;
		int					nExistMsg; /* New Message Exist(TRUE) or Not Exist(FALSE) */
		int					nPauseSecond;
		short 				sExternalOutboundPermission;
		short 				sExternalConsultPermission;
		char				szCallKey[24];
} C_RESPONSE;

typedef struct {
		_PHONENUMBER szDn;
		char szLoginId[128];
} C_HEARTBEAT_REQ, C_HEARTBEAT_RESP;

typedef struct{
		char 		szDn[24];
		char		szId[20];
		int 		nErrorCode;
		int 		nBillCount;
}C_BILL_RSP;

#pragma pack(pop) //pack 단위 원복
#endif /* INC_APP_CADT_CADT_CMN */

/*
** Bloomberg Application Programming Interface
**
** bbapi.h - General API Header  
*/

#ifndef __BBAPI_H
#define __BBAPI_H

#ifndef lint
static char RCSid_bbapi_h[] = "$Id: $ $CCId: /bbcm/api_backend/bbcomm_user/bbapit/bbapi.h /main/bb/91 2007/09/07 16:14:39 rsriniv $";
#endif

#ifndef __BBUNIX_H
#include <bbunix.h>
#endif

#ifndef MAIN
#define Extern extern
#else
#define Extern
#endif



enum apiErrorCode {
    INVALID_ARG = -9,
    TCP_IP_CONNECT_ERR = -8,
    DATA_RECV_ERR = -7,
    DATA_SEND_ERR = -6,
    SOCKET_SELECT_ERR =-5,
    APP_ID_INFO_NOT_FOUND = -4,
    SEND_CLIENT_VERSION_INFO_ERR = -3,
    CLIENT_LIBRARY_TOO_LOW_VERSION = -2,
    REGISTRATION_TIMEOUT =-1,
    NO_ERRORS,
    DUPLICATE_REGISTRATION,
    XML_PARSE_ERROR,
    XML_INVALID_ERROR,
    CHANGE_APP_CERT_INFO,
    APP_INFO_EXISTS,
    APP_UNREGISTERED,
    APP_MISSING_EXE,
    APP_INFO_NOT_ALLOWED,
    APP_ROOTKEY_NO_MATCH,
    APP_REG_COMPONENTS_EXIST,
    OTHER
};

/* Service codes (the routing logic of Comm Server depends mainly on these codes) */

#define BB_SVC_MIN                    -64
#define BB_SVC_MAX                     70
#define BB_SVC_NUM                     ((BB_SVC_MAX)-(BB_SVC_MIN)+1)
#define EXTENDED_HEADER			0x80000000
#define BB_SVC_INCOMPLETE               0     /* Partial message read. Call bb_rcvdata() again. */
#define BB_SVC_DEFAULTROUTE             0     /* Default entry in the Routing Table */
#define BB_SVC_GETHEADER                1     /* Basic security information */
#define BB_SVC_TICKMONITOR              2     /* Monitor ticks */
#define BB_SVC_GETDATA                  3     /* Field value */
#define BB_SVC_TICKDATA                 4     /* Tick data from the ticker */
#define BB_SVC_STOPMONITOR              5     /* Stop monitoring by MonId */
#define BB_SVC_STOPALL                  6     /* Stop all monitoring */
#define BB_SVC_GETINTRATICKS            7     /* Intraday ticks */
#define BB_SVC_GETHISTORY               8     /* Historical data request */
#define BB_SVC_STATUS                   9     /* Status report from bbcomm to appl */
#define BB_SVC_CONTROLCOMM             10     /* Control from client to local bbcomm */
#define BB_SVC_CONTROLDB               11     /* Control from client to local bbdb */
#define BB_SVC_PROBE                   12     /* Message with no data to check routing */
#define BB_SVC_TKLOOKUP                13     /* Ticker lookup request */
#define BB_SVC_RESUMEMONITOR           14     /* Resume monitoring by MonId */
#define BB_SVC_GETHEADER_TYPED         15     /* Basic security information by non-ticker */
#define BB_SVC_TICKMONITOR_TYPED       16     /* Monitor ticks by non-ticker */
#define BB_SVC_LUW                     17     /* LUW service from local BC */
#define BB_SVC_CLIENTREPORT			   17	  /* Holds info from client PC */
#define BB_SVC_RESUBSCRIBE             18     /* Resubscribe ticks (via BC) */
#define BB_SVC_SUBSCRIBE               19     /* Subscribe ticks via BC */
#define BB_SVC_DESUBSCRIBE             20     /* Desubscribe ticks (via BC) */
#define BB_SVC_TICKDATA_CONDITIONCODES 21     /* Monitor Ticks w/ Condition Codes. DRQS 1874365. */
#define BB_SVC_ENABLECCS               22     /* Request for Condition Codes */
#define BB_SVC_METADATA                22     /* Request for API Features */
#define BB_SVC_SUBSCRIBE_MONITOR       23     /* Subscribe and monitor ticks (via BC) */
#define BB_SVC_SUBSCRIBE_MONITOR_TYPED 24     /* Subscribe and monitor ticks by non-ticker (via BC) */
#define BB_SVC_DESUBSCRIBE_MONITOR     25     /* Desubscribe monitorable ticks (via BC) */
#define BB_SVC_DESUBSCRIBE_MONITOR_ALL 26     /* Desubscribe all monitorable ticks (via BC) */
#define BB_SVC_DESUBSCRIBE_CLASS       27     /* Desubscribe all ticks (via BC) as an entire class */
#define BB_SVC_GETHISTORYX             28     /* Historical data request */
#define BB_SVC_RESUBSCRIBE_MONITOR     29     /* Resubscribe ticks (via BC) */
#define BB_SVC_GETINTRATICKSX          30     /* Enhanced intraday tick request */
#define BB_SVC_ACCOUNTINGDATA          31     /* Accounting/management data */
#define BB_SVC_CONNECTSUCCEEDED        32     /* Async connection completed successfully */
#define BB_SVC_GETMONID                33     /* Deliveres monid without subscription */
#define BB_SVC_ACCOUNTINGCONTROL       34     /* Accounting/management control */
#define BB_SVC_GETMONID_TYPED          35     /* Deliveres monid without subscription by non-ticker */
#define BB_SVC_GETTIMEZONE             36     /* Gets users PDF timezone, in seconds from NY */
#define BB_SVC_GETDATAX                37     /* Get multisecurity field data call */
#define BB_SVC_GETHEADERX              38     /* Get header with extra options */
#define BB_SVC_GETHEADER_TYPEDX        39     /* Get header typed with extra options */
#define BB_SVC_GETMONID2                40     /* Deliveres monid without subscription plus handling instructions for price/yield quoted objects */
#define BB_SVC_GETMONID_TYPED2          41     /* Deliveres monid without subscription by non-ticker plus handling instructions for price/yield quoted objects */
#define BB_SVC_RESUMEMONITOR2           42     /* Resume monitoring by MonId plus handling instructions for price/yield quoted objects */
#define BB_SVC_TICKMONITOR_TYPED2       43     /* Monitor ticks by non-ticker */
#define BB_SVC_TICKMONITOR2             44     /* Monitor ticks */
#define BB_SVC_GETHEADERBF              45     /* Get Header By Fields */
#define BB_SVC_MGETHISTORYX             46     /* Gethistory for multiple securities multiple fields */
#define BB_SVC_GETMONIDX                47     /* Enhanced tick stream monid retrieval */
#define BB_SVC_GETMONID_TYPEDX          48     /* Enhanced tick stream monid retrieval by non-ticker */
#define BB_SVC_TICKMONITOR_TYPEDX       49     /* Enhanced Monitor ticks by non-ticker */
#define BB_SVC_TICKMONITORX             50     /* Enhanced Monitor ticks */
#define BB_SVC_SSLHANDSHAKE             51     /* All SSL handshake messages */
#define BB_SVC_SSLCLOSE                 52     /* An SSL close messages */
#define BB_SVC_GETHEADER_TYPEDBF        53     /* Get Header Typed By Fields */
#define BB_SVC_GETMONID3                54     /* getmonid2 equivalent       */
#define BB_SVC_GETMONID_TYPED3          55     /* getmonid_typed2 equivalent */
#define BB_SVC_GETMONIDY                56     /* getmonidx equivalent       */
#define BB_SVC_TICKMONITOR_BF           57     /* Monitor ticks ..byfield monid*/
#define BB_SVC_GETMONID_BF              58  
#define BB_SVC_RESUMEMONITOR_BF         59
#ifdef INMS_RESUME
#define BB_SVC_INMS_REPORT              60     /* generates inms statistics. */
#endif
#define BB_SVC_FULLGETHISTORY           61     /* full multiple get history with currency */
#define BB_SVC_STOPMONITOR_BF           62     /* stop by field */
/* SVC 63 used by bbdb */
#define BB_SVC_RESUMEMONITOR_ENHANCED   65     /* resume by monid, obj, security-key */
#define BB_SVC_GETMONID_TYPEDY          66     /* getmonid_typedx equivalent */
#define BB_SVC_QUERY_REALTIME_PERMIT    67     /* Server Api client query if realtime data allowed */
#define BB_SVC_TICKMONITOR_ENHANCED     68     /* tick monitor enhanced */
#define BB_SVC_STOPMONITOR_ENHANCED     69     /* stop monitoring enhanced subscriptions */
#define BB_SVC_GET_AUTHORIZATION        70     /* Server Api realtime query */
#define BB_SVC_USER_ENTITLEMENTS        71
#define BB_SVC_SECURITY_ENTITLEMENTS    72
/* SVC 73 reserved for internal use */
#define BB_SVC_VALIDATE_BLBG_LOGON      74     /* Server Api application BLP logon validation */
#define BB_SVC_INTRADAY_RAWTICKS        75
#define BB_SVC_TICKMONITOR_VWAP         76
#define BB_SVC_STOPMONITOR_VWAP         77
#define BB_SVC_SUBSCRIPTION_DATA        78
#define BB_SVC_RESOLVE                  79
#define BB_SVC_SECURITY_ENTITLEMENTS_FOR_USER    80    /* Security Entitlements for a user */
#define BB_SVC_RESOLVE2                  81     /* Resolve2 request */
#define BB_SVC_INTRADAY_DATA             82     /* Java API for intraday data request */
#define BB_SVC_BAR_DATA                  83     /* Java API for bar data request */ 
#define BB_SVC_REFERENCE_DATA            84     /* Java API for reference data request */
#define BB_SVC_HISTORICAL_DATA           85     /* Java API for historical data request */
#define BB_SVC_INITIAL_PAINT             86    /* initial paint for new API */
#define BB_SVC_GETHEADER_TYPEDENHANCED   87    /* Extesion to typedx */
#define BB_SVC_INITIAL_PAINT_VIAGETDATA  88    /* initial paint for new API */
#define BB_SVC_FULLGETHISTORYX           95    /* full multiple get history
                                                   with currency and other overrides */

#define BB_SVC_USER                   256     /* From here on up...*/
#define BB_SVC_AUTHORIZATION           -1     /* Security/authorization violation */
#define BB_SVC_LOSTNOTIFY              -2     /* Notification of a lost packet */
#define BB_SVC_CONNECTFAILED           -3     /* Async connection attempt failed */
#define BB_SVC_TICKAFTERSTOP           -4     /* Ticks after STOPALL or STOPMONITOR */
#define BB_SVC_SYSTEMDOWN              -9     /* Notification from DB Server */

/* Service codes from 0x1800 to 0x18ff used by bbcomm */
#define BB_SVC_WATCH_EVENT         0x1801     /* for reports on watch events - 6145 */

/* Limits on number of items per message */

#define BB_MAX_SECS                    10
#define BB_MAX_MONIDS                  10
#define BB_MAX_TICKS                   10
#define BB_MAX_FIELDS                  50
#define BB_MAX_OVRRDS                  20
#define BB_MAX_CATEGORIES              10

/* bbtest_api buffer limit - 256k */

#define BBTEST_MAX_BUF_SIZE            4*256*256

/* Missing data value (pow (2, 30))*/

#define BB_VAL_MISSING        -1073741824      /* =xC0000000 */

/* Return codes from API subroutines and in the STATUS message */

#define ExitOK                               0
#define ExitOKEXITCOMMSERVER              1901
#define ExitOKEXITDBSERVER                1902
#define ExitUSAGE                         1910
#define ExitOKSTOPMNTR                    1947
#define ExitOKREROUTE                     1953
#define ExitFAILOPENFILE                 -1901
#define ExitFAILACCEPT                   -1902
#define ExitFAILCLOSE                    -1903
#define ExitFAILSETPEERFLAGS             -1904
#define ExitFAILCONNECT                  -1905
#define ExitFAILNOMORE                   -1906
#define ExitFAILCONNECTION               -1907
#define ExitFAILFUNCTION                 -1908
#define ExitFAILERRORCODE                -1909
#define ExitFAILCREATESOCKET             -1910
#define ExitFAILCREATETHREAD             -1911
#define ExitFAILDISCONNECT               -1912
#define ExitFAILGETDATA                  -1913
#define ExitFAILGETHEADER                -1914
#define ExitFAILMALLOC                   -1915
#define ExitFAILHOLDRECEIVE              -1916
#define ExitFAILMSGLEN                   -1917
#define ExitFAILGETINTRATICKS            -1918
#define ExitFAILTKLOOKUP                 -1919
#define ExitFAILMSGQID                   -1920
#define ExitFAILMSGTYPE                  -1921
#define ExitFAILSSL                      -1922
#define ExitFAILBLPAUTH                  -1923
#define ExitFAILMSGBUSY                  -1924
#define ExitFAILMSGRECEIVE               -1925
#define ExitFAILMSGSEND                  -1926
#define ExitFAILPACKETID                 -1927
#define ExitFAILPEER                     -1928
#define ExitFAILRECEIVE                  -1930
#define ExitFAILRECEIVEBUFFER            -1931
#define ExitFAILREGISTERREQUEST          -1932
#define ExitFAILREGISTERSERVICE          -1933
#define ExitFAILROUTE                    -1935
#define ExitFAILROUTELOAD                -1936
#define ExitFAILROUTETYPE                -1937
#define ExitFAILSENDTIMEOUT              -1938
#define ExitFAILSENDBUFFERFULL           -1939
#define ExitFAILSEND                     -1940
#define ExitFAILSENDNOBUFFER             -1941
#define ExitFAILSENDTOCLOSEDSOCKET       -1942
#define ExitFAILSERVICE                  -1943
#define ExitFAILSHAREDMEMORY             -1944
#define ExitFAILSOCKET                   -1945
#define ExitFAILSTOPMNTR                 -1947
#define ExitFAILSERVICECODE              -1948
#define ExitFAILSERVICEPARM              -1949
#define ExitFAILTICKMNTR                 -1950
#define ExitFAILGETTIMESERIES            -1951
#define ExitFAILTIMESERIESBARS           -1952
#define ExitFAILGETHOSTNAME              -1953
#define ExitFAILGETHOST                  -1955
#define ExitFAILGETMSGQUEUE              -1956
#define ExitFAILSETSOCKETOPTION          -1957
#define ExitFAILSETNONBLOCKING           -1958
#define ExitFAILBIND                     -1959
#define ExitFAILLISTEN                   -1961
#define ExitFAILTIMEOUT                  -1963
#define ExitFAILTOOMANYFIELDS            -1965
#define ExitFAILREQUESTTOOLONG           -1967
#define ExitFAILSENDHELD                 -1971
#define ExitFAILRECEIVEHELD              -1973
#define ExitFAILHISTORY                  -1975
#define ExitFAILNOHANDLER                -1977
#define ExitFAILBADPEER                  -1981
#define ExitFAILBADPACKET                -1982
#define ExitFAILFLUSH                    -1983
#define ExitFAILSENDBUFFER               -1985
#define ExitFAILSENDPIPE                 -1986
#define ExitFAILREQUESTTABLE             -1987
#define ExitFAILTAILADD                  -1988
#define ExitFAILTAILEXTRACT              -1989
#define ExitFAILTAILSTORE                -1990
#define ExitFAILHASHREQNUM               -1991
#define ExitFAILLISTACCESS               -1992
#define ExitFAILLOCKOUT                  -1993
#define ExitFAILEXTRACTPACKET            -1994
#define ExitFAILPARM                     -1996
#define ExitFAILCOMPRESS                 -1997
#define ExitFAILNEWPEERINDEX             -1998
#define ExitFAILPEERLOOKUP               -1999
#define ExitFAILMONIDCTL                 -2000
#define ExitSERVERREQUESTEDDISCONNECT    -2001
#define ExitFAILCC						 -2002	 /* Condition Code error */
#define ExitFAILNOCCS					 -2003	 /* Condition Code error 
                            -did not request ccs or not applicable to ticks*/
#define	ExitFAILHASHEXPAND				 -2004	 /* couldn't expand hash */
#define ExitFAILHASHCREATE				 -2005
#define ExitFAILREQUESTNOTSUPPORTED		 -2006
#define ExitFAILBERENCODE                -2007
#define ExitFAILBERDECODE                -2008
#define ExitFAILSEND_HIGH_WATERMARK      -2009

/* Message Types */

#define bMsgTypeMIN                        900
#define bMsgTypeCLIENTREQUEST              950
#define bMsgTypeCONNECTASK                 951
#define bMsgTypeCONNECTGRANT               952
#define bMsgTypeDISCONNECT                 953
#define bMsgTypeNOTIFICATION               954
#define bMsgTypeECHOCOMM                   955
#define bMsgTypeERRORCOMM                  956
#define bMsgTypeERRORBBDB                  957
#define bMsgTypeRESETCOMM                  961
#define bMsgTypeSERVERRESPONSE             962
#define bMsgTypeNOTIFY_LUW                 963
#define bMsgTypeTICKDATA                   965
#define bMsgTypeCOMPACT_TICKDATA           966
#define bMsgTypeTRACEDB                    970
#define bMsgTypeTRACECOMM                  971
#define bMsgTypeLOOKUPADDRESS              972
#define bMsgTypeLOOKUPRESPONSE             973
#define bMsgTypeHEARTBEAT                  980
#define bMsgTypeWAITSELECT                 981
#define bMsgTypeSENDACCUM                  982
#define bMsgTypePEERFLAGS                  983
#define bMsgTypeALIVE                      984
#define bMsgTypeREPORTCOMM                 986
#define bMsgTypeREPORTDB                   987
#define bMsgTypeKILLUSER                   988
#define bMsgTypeEXITCOMM                   990
#define bMsgTypeEXITDB                     991
#define bMsgTypeCOMMPARMSET                993
#define bMsgTypeSETVALUES                  993
#define bMsgTypeROUTEADD                   995
#define bMsgTypeROUTEDELETE                996
#define bMsgTypeROUTEREPLACE               997
#define bMsgTypeROUTEFILE                  998
#define bMsgTypeREROUTEREQUEST             999
#define bMsgTypeSEND_TEST_WRAP_TICK       1000
#define bMsgTypeCONTROLLER_HEARTBEAT      1024
#define bMsgTypeCONTROLLER_VERSION        1025
#define bMsgTypeCONTROLLER_LUW            1026
#define bMsgTypeCONTROLLER_TICKDATA       1027
#define bMsgTypeCONTROLLER_SUBSCRIBE      1028
#define bMsgTypeCONTROLLER_DESUBSCRIBE    1029
#define bMsgTypeCONTROLLER_MISCTEXT       1030
#define bMsgTypeCONTROLLER_RESUBSCRIBE    1031
#define bMsgTypeCOOKIEON		  1032
#define bMsgTypeCOOKIEOFF		  1033
#define bMsgTypeCOOKIESTATS		  1034
#define bMsgTypeCOOKIEFLAGS		  1035

#define bMsgTypeGENERATE_TICK             1036
#define bMsgTypeTRACE_SVC_RT_REQUEST      1037
#define bMsgTypeTRACE_SVC_RT_RESPONSE     1038
#define bMsgTypeSOBSTATUS                 1050    /* msg from SOB containing serial numbers */
#define bMsgTypeCONTROLSOB                1051    /* SOB Control message					   */

/* Message Types for requesting watch events and receiving information */
#define bMsgTypeWATCH_EVENT_REQUEST       1052
#define bMsgTypeWATCH_EVENT_REPORT        1053

#define bMsgTypeRE_READ_WRAPFILE          1054    /* instructs bbcomm to re-read wrapfile */

#define bMsgTypeBBC_CONTROL_REQ           1055    /* delivers instructions to bbcomm */
#define bMsgTypeBBC_CONTROL_RESP          1056    /* response to previous request */
#define bMsgTypeBBCOMMCONFIG              1057    /* bbcomm configuraion msg from client */

/* Start of definitions of message types associated with virtrual circuit */
#define bMsgTypeDOWNSTREAM_SESSION_MSG    1058     /* msg sent to session clients by server */
#define bMsgTypeUPSTREAM_SESSION_MSG      1059     /* msg sent to session server by client */

/* notifiaction of route down sent to session client by bbcomm */
#define bMsgTypeUPSTREAM_SESSION_DOWN_MSG    1060     

/* notifiaction of route down sent to session server by bbcomm */
#define bMsgTypeCLIENT_SESSION_LOST_MSG      1061

/* return message back to server if whatever an error occours 
   in forwarding downstream message to session client */
#define bMsgTypeRETURN2SERVER_SESSION_MSG    1062


/* return message back to client if whatever an error occours 
 * in forwarding upstream message to session server 
 */
#define bMsgTypeRETURN2CLIENT_SESSION_MSG    1063


#define bMsgTypeUPSTREAM_SESSION_UP_MSG      1064


#define bMsgTypeBBCOMM_QUERY_REQUEST        1065

#define bMsgTypeBBCOMM_QUERY_RESPONSE       1066

#define bMsgTypeCONNECTREMOTE    1070


#define bMsgTypeRESUME_ON_DEMAND		  1099    /* I'm making this way more than the previous
												  ** msg type since there are other types being
                                                  ** developed during this emergency change.
                                                  */
#define bMsgTypeCONTROL_SSL               1100    /* SSL Control for exemptions and future needs. */
#define bMsgTypeSSL_REVOCATION            1101    /* SSL revocation message */

/* msg type 1200 - 1999 are reserved for internal use only */

#define bMsgTypeMAX                       1999



/* Trace Types (can be OR'ed together when calling bb_trace) */

#define bTraceOFF          0x00000000                 /* Trace - all off */
#define bTraceSEND         0x00000001                 /* Low level sending */
#define bTraceRECV         0x00000002                 /* Low level receiving */
#define bTraceNET          (bTraceSEND | bTraceRECV)  /* Low level sending and receiving */
#define bTraceINIT         0x00000004                 /* Start-up processing */
#define bTraceREQUEST      0x00000008                 /* Service request */
#define bTraceREPLY        0x00000010                 /* Server response */
#define bTraceALARM        0x00000020                 /* Alarm handling */
#define bTraceSIG          0x00000040                 /* General signal handling */
#define bTraceEXCP         0x00000080                 /* Socket exceptions handling */
#define bTraceTICK         0x00000100                 /* Ticks processing */
#define bTracePACKET       0x00000200                 /* Getting network packets */
#define bTraceMEMORY       0x00000400                 /* Memory allocation/freeing */
#define bTraceFREELIST     0x00000800                 /* Free list, list and hash management */
#define bTraceFLUSH        0x00001000                 /* Flush output socket buffers */
#define bTraceTIMEDELAY    0x00002000                 /* Watch for tick time, report delay */
#define bTraceHOSTNET      0x00004000                 /* Host->Network and back format conversion */
#define bTraceFLUSHMSGQ    0x00008000                 /* Flush MagQ buffer */
#define bTraceMSGLOOP      0x00010000                 /* Msg loop around main select() */
#define bTraceTICKSTAT     0x00020000                 /* Accumulate tick frequency histogram */
#define bTraceRCVSTAT      0x00040000                 /* Accumulate receive statistics */
#define bTraceOVERFLOW     0x00080000                 /* Detect buffer overflow */
#define bTraceFLUSHERROR   0x00100000                 /* Flush to output socket error */
#define bTraceSTOPMON      0x00200000                 /* Trace STOPMONITOR and STOPALL requests */
#define bTraceROUTE        0x00400000                 /* Trace routing */
#define bTraceINOUT        0x00800000                 /* Trace input/output packets only */
#define bTraceTICKBUF      0x01000000                 /* Trace SOURCE and SEQ of tkrmon bufs */
#define bTraceACCOUNTING   0x02000000                 /* Trace accounting data from Accounting Server */
#define bTraceERROR        0x04000000                 /* Sending error messages */
#define bTraceREQMON       0x08000000                 /* cRequest and cMonitor management */
#define bTraceNEWS	       0x10000000		          /* news bit map and more */
#define bTraceSSL          0x20000000                 /* SLL related activity */
#define bTraceWATCH        0x40000000                 /* Watch Events */
#define bTraceALL          0xFFFFFFFF                 /* Trace - all on */

/* Connect Status */

#define ConnectStatusERROR       2001  /* connect() on non-blocking socket really failed */
#define ConnectStatusOK          2002  /* (unlikely) successful connect() on non-blocking socket */
#define ConnectStatusPENDING     2003  /* (most probable) connection pending */


/* Peer Flags */

#define PeerALIVE          0x00000001  /* Enable 'I am alive' message */
#define PeerHOLDSND        0x00000002  /* Hold all sending to peer */
#define PeerHOLDRCV        0x00000004  /* Hold all receiving from peer */
#define PeerTRACE          0x00000008  /* Enable message tracing for peer */
#define PeerSERVER         0x00000010  /* This peer accepted our connection and is a server peer */
#define PeerLUW            0x00000020  /* This peer is a Bloomberg controller */
#define PeerLUWCOMM        0x00000040  /* bbcomm receiving ticks via Bloomberg controller */
#define PeerNOROUTING      0x00000080  /* Prohibit routing to this port */
#define PeerWAITACCEPT     0x00000100  /* Peer attempted connection, waits for "Hello" */
#define PeerWAITGRANT      0x00000200  /* Peer made a connection, asked and waits for grant */
#define PeerWAITSOCKSADDR  0x00000400  /* Peer is waiting for address of socks 5 server */
#define PeerWAITSOCKSCONN  0x00000800  /* Peer is waiting to connect to socks 5 server, or to send auth message  */
#define PeerWAITSOCKSAUTH  0x00001000  /* Peer is connected to socks server, is waiting for authorization */
#define PeerSENDSOCKSREQ   0x00002000  /* Peer is waiting to send socks connection request */
#define PeerWAITSOCKSREQ   0x00004000  /* Peer is authorized by socks server, is waiting for through connection */
#define PeerCOMMSERVER     0x00008000  /* Peer is functionning as a comm server for some client */
#define PeerDISCONNECT     0x00100000  /* Directive to disconnect */
#define PeerLOCKOUT        0x00200000  /* Directive to disconnect and lockout */
#define PeerTOOBUSY        0x00400000  /* This peer is overloaded with requests, hold sending */
#define PeerADDRESSTHREAD  0x01000000  /* This is an internal socket used to queue name lookup requests */
#define PeerFILE           0x02000000  /* Transaction log file */
#define PeerMANAGER        0x04000000  /* Managing peer */
#define PeerDBSERVER       0x08000000  /* Peer is a socket from a DB server on a Bloomberg host */
#define PeerLISTEN         0x10000000  /* Peer is a socket listening for connections */
#define PeerPIPE           0x20000000  /* Peer is a pipe from tkrmon */
#define PeerMSGQUEUE       0x40000000  /* Peer is a message queue to DB server */
#define PeerUNKNOWN        0x80000000  /* Peer made a connection without a handshake */
#define PeerSERVERTYPES    (PeerUNKNOWN | PeerSERVER | PeerLUW | PeerMANAGER | PeerDBSERVER | PeerLISTEN | PeerPIPE | PeerADDRESSTHREAD)
#define PeerNOTIFYCLIENTS  (PeerUNKNOWN | PeerSERVER | PeerLUW | PeerDBSERVER | PeerLISTEN | PeerPIPE | PeerADDRESSTHREAD)
#define PeerCLIENTALLOW    (PeerALIVE | PeerHOLDSND | PeerHOLDRCV | PeerTRACE | PeerDISCONNECT | PeerLOCKOUT | PeerMANAGER | PeerDBSERVER)
#define PeerERRORCLIENT    (PeerALIVE | PeerTRACE | PeerMANAGER)
#define PeerPENDINGSOCKS   (PeerWAITSOCKSADDR | PeerWAITSOCKSCONN | PeerWAITSOCKSAUTH | PeerSENDSOCKSREQ | PeerWAITSOCKSREQ)
#define PeerPENDINGCONNECT (PeerUNKNOWN | PeerWAITACCEPT | PeerPENDINGSOCKS)

/* Report Types (can be OR'ed together when calling bb_report_...) */

#define bReportSERVICES    0x00000001  /* Services requested by clients */
#define bReportREQUESTS    0x00000002  /* Requests from Comm Server to DB Server */
#define bReportPEERS       0x00000004  /* All links to clients and servers */
#define bReportROUTES      0x00000008  /* Routing table (by service code) */
#define bReportSTAT        0x00000010  /* Statistics */
#define bReportHASH        0x00000020  /* Hash table */
#define bReportCLIENT      0x00000040  /* All services and requests from one client */
#define bReportPACING      0x00000080  /* Peers with pacing info */
#define bReportUSEAGE      0x00000100  /* Peers with bandwith info */
#define bReportREROUTE     0x00000200  /* Reroute table */
#define bReportMONITORS    0x00000400  /* All currently monitored sec/monID's */
#define bReportWRAPTIMES   0x00000800  /* Report Wrap Times Table*/
#define bReportAMN         0x00001000  /* Report "health" of an AMN host */
#ifdef INMS_REPORT
#define bReportINMS        0x00002000  /* INMS report request. */
#endif
#define bReportTRACE1      0x00004000  /* Trace control message. */
#define bReportADVISE      0x80000000  /* Send response back to whoever asked via socket */

/* Values to set with bb_setcommvalue call */

#define BB_SET_PEERSENDPACING   1           /* Set bytes per sec, etc, for a peer */
#define BB_SET_DEFSENDPACING    2           /* Set bytes per sec, etc. for new peers */
#define BB_SET_ALLSENDPACING    3           /* Set same for all current peers and new peers */
#define BB_SET_PEERRCVPACING    4           /* Set messages per sec for a peer */
#define BB_SET_DEFRCVPACING     5           /* Set messages per sec for new peers */
#define BB_SET_ALLRCVPACING     6           /* Set same for all current peers and new peers */
#define BB_SET_ADAPT_ON         7           /* Turn adaptive routing on */
#define BB_SET_ADAPT_OFF        8           /* Turn adaptive routing off */
#define BB_SET_DELAY_ALARM      9           /* Set delay alarm parameters */
#define BB_SET_REROUTETABLE    10           /* Load/Set Reroute table CEA 09/03/99 */
#define BB_SET_PACINGTABLE     11           /* Load/Set Pacing  table CEA 09/16/99 */
#define BB_SET_INMSFILE        12           /* Set up INMS Stat file  CEA 10/18/99 */
#define BB_SET_REHANDSHAKE     13           /* Force SSL re-handshake */
/* Accounting Server control */

#define AccountFILE        0x00000001

/* Bloomberg internal functions */

#define bFuncREAD_TICDB      19961008

/* Dummy for bbcomm connection structure */
#define bb_connect_t         void

/*
** User Return Codes delivered from the
** DB Server back to the user in the UserID
** field and put into comm_header.return_code 
*/

#define SecOK                     0
#define SecUNKNOWN               10
#define SecDATAINCOMPLETE		667          /* used with enhanced timeseries request */
#define SecNOTPRICED            777
#define SecPROHIBFIELD          888
#define SecTYPENOTSUPPORTED     998
#define SecOTHERERROR           999
#define SecINVALIDDATE          -8           /* only 6 or 8 digit dates are allowed for history requests */

/* accounting logic error codes */
#define SecOVERLIMITS            -7          /* security not allowed for history and intraticks */
/* end of accounting error codes */

#define SecNOBUFFER             -9           /* malloc could not create buffer for mgethistory */
#define SecLOADAREAFAILED       -10
#define SecIDNOTFOUND           -11
#define SecPREFIXNOTFOUND       -12
#define SecWRONGPRODUCTTYPE     -13
#define SecINVALIDID            -14
#define SecFUNDDBERROR          -15
#define SecOUTOFMEMORY          -16
#define SecTOOMANYFIELDS        -17
#define SecTOOMANYPOINTS        -18
#define SecDATERANGEERROR       -19
#define SecCURRENCYNOTFOUND     -20
#define SecBUFFEROVERFLOW       -21   /* temporary till buffer is increased */

#define SecINVALIDREQUEST		-30
#define SecTIMEOUT				-31
#define SecRESTART				-32
#define SecNOPRODUCTSFOUND      -33
#define	SecINVALIDREPLY			-3000

#define SecNOREALTIMEALLOWED    -3999

/* Real Time Metering - return codes from tickmonitor_enhanced response */
#define ErrCodeMAX_SECS_REACHED              -3001
#define ErrCodeMAX_CORE_SECS_REACHED         -3001
#define ErrCodeMAX_MARKET_DEPTH_SECS_REACHED -3002
#define ErrCodeMAX_GREEKS_SECS_REACHED       -3004
#define ErrCodeMAX_OVERLIMIT_VALUE           -3998

#define ErrOVERLIMITS_UPPER_BOUND            -3000
#define ErrOVERLIMITS_LOWER_BOUND            -4023

#define ErrOVERLIMITS_CORE              0x00000001
#define ErrOVERLIMITS_MARKET_DEPTH      0x00000002
#define ErrOVERLIMITS_GREEKS            0x00000004
#define ErrOVERLIMITS_UNUSED            0x00000008

#define FeatureCC					1
#define FeatureALL_PRICE_ETC		2
#define FeatureALL_PRICE_COND_CODE	(FeatureCC|FeatureALL_PRICE_ETC)

/*
** Compression types.  The client app bitwise or's together the types of compression
** that it is prepared to accept. The server returns the one it used.
*/
#define BBCompressNone				0
#define BBCompressCDE				1
#define BBCompressInter				2


/* Limits on number of items per multiple get history request */
#define BB_MAX_MHIST_SECS               8      /* maximum number of securities per mhistoryx request */
#define BB_MAX_MHIST_FLDS               5      /* maximum number of fields per mhistoryx request */
#define BB_MAX_SECURITY_TYPE           20      /* maximum length of the security type string (CUSIP, etc) */
#define BB_MAX_SEC_DESCRIPTION         32      /* maximum length of the security description string */
#define MAX_FUNDAMENTAL_FIELDS        1076
#define BB_MHIST_MAX_NUM_POINTS      7320      /* maximum number of data points per field */

/* number of places required to shift history flags */ 
#define BB_SHIFT_YIELD_PRICE            4 
#define BB_SHIFT_CLOSE_GPA              5
#define BB_SHIFT_NOAX                   6
#define BB_SHIFT_NOAX_FORM              8

/*Packet id for client report msg: */
#define CLIENT_REPORT_PACKET_ID 0x7fffffff 
#define CLIENT_REPORT_PACKET_ID_3PASID (CLIENT_REPORT_PACKET_ID - 1)

/*BB_SVC_CLIENTREPORT Types: */
#define REPORT_NOTIFICATION_ACK	1
#define REPORT_VERSION_INFO		2
#define REPORT_APP_SESS_ID_INFO	3 /* 3rd Party App Registration */

/*Products that we supply info for; */
#define VERSION_INFO_PRODUCT_BBCOMM		1
#define VERSION_INFO_PRODUCT_API		2
#define VERSION_INFO_PRODUCT_DDE		3
#define VERSION_INFO_PRODUCT_DATACTRL	4
#define VERSION_INFO_PRODUCT_OS			5
#define VERSION_INFO_PRODUCT_EXCEL		6

/*API Access Types: */
#define API_ACCESS_TYPE_DDE			1
#define API_ACCESS_TYPE_DATACTRL	2
#define API_ACCESS_TYPE_TOOLS		3
#define API_ACCESS_TYPE_3RD_PARTY	-1  /*catch all case*/

/* ticker lookup rcodes: (maxcount == Maximum # of names to return -> define as 1000) */
#define RCODE_TKLOOKUP_OK		0	/*numitems <= maxcount */
#define RCODE_TKLOOKUP_TOOMANY	1	/*numitems > maxcount */
#define RCODE_TKLOOKUP_NONE		2	/*numitems <=0 */

/*
** Any message returned by Bloomberg Comm Server to application
** begins with the structure bb_comm_header_t and continues based
** on the service code. All the different structures are listed below.
** Message handler subroutine should cast the pointer to bb_comm_header_t
** to the type that is appropriate for the service code handled.
*/

struct bb_comm_header_struct      /* The header of each logical DB message */
{
  int4     request_id;    /* Request Id as returned by any request function */
  int4     service_code;  /* Header/monid/tickdata...etc... (see codes above) */
  int4     return_code;   /* Status of the request (0 - good, !0 - bad) */
  int4     num_items;     /* Number of data items that follows (used by most formats) */
};

typedef struct bb_comm_header_struct bb_comm_header_t;

/*
** Msg handler subroutine takes a pointer to msg as an argument.
*/

#ifndef KandR
typedef    void (*bb_msg_handler_t)(struct bb_comm_header_struct *);
#else
typedef    void (*bb_msg_handler_t)();
#endif


/*
** Decoded security header information - part of the message returned in
** response to bb_getheader()
**
** NOTE : many of the entries in the header correspond to API 
**        fields.  If so, the comment in the structure below contains
**        the field id, in hex.  NOTE : The realtime field ID's corespond
**        to the realtime tick types. (So tick id's are the same integer id
**        as the corresponding API field, whose entries in the header is
**        marked below.)
*/

typedef struct
{
    int4     status;                    /* Return status: */
                                        /*  0 = OK */
                                        /* -1 = no longer used */
                                        /* -2 = no longer used */
                                        /* -3 = invalid security */
                                        /* -4 = header not found */
                                        /* -5 =	no trade data available */
                                        /* -6 =	no realtime available */

    double   price_open;                /* 0x2D  open price */
    double   price_high;                /* 0x09 high price */
    double   price_low;                 /* 0x0A low price */
    double   price_last;                /* 0x01 last price */
    double   price_settle;              /* 0x06 settlement price */
    double   price_bid;                 /* 0x02 bid price */
    double   price_ask;                 /* 0x03 ask price */
    double   yield_bid;                 /* 0x0B bid yield */
    double   yield_ask;                 /* 0x0C ask yield */
    double   limit_up;                  /* 0x0B up limit (futures) */
    double   limit_down;                /* 0x0C down limit (futures) */
    double   open_interest;             /* 0x08 open interest (futures) */
    double   yest_price_last;           /* 0x35 last price of previous session */
    double   scale;                     /* scale factor */
    int4     time_last;                 /* 0x3ff time of last price */
    int4     exchange_last;             /* exchange of last trade */
    int4     tick_direction;            /* up/down/zero tick */
    int4     size_bid;                  /* 0x3FB bid size */
    int4     size_ask;                  /* 0x3FA ask size */
    int4     condition_bid;             /* bid condition */
    int4     condition_ask;             /* ask condition */
    int4     condition_last;            /* last trade condition */
    int4     condition_market;          /* market condition */
    int4     monitorable;               /* monitorable  */
    int4     volume_total;              /* 0x07 total trade volume */
    int4     ticks_total;               /* total number of ticks */
    int4     time_start;                /* session start time */
    int4     time_end;                  /* session end time */
    int4     rt_pcs;                    /* real time pricing source (was currency) */
    int4     format;                    /* price display format */
    char     sec_key[32];               /* canonical form of security key */
    int4     date;                      /* as-of date ccyymmdd */

}   bb_decode_header_t;

typedef struct {
  int4 version;
  
  double yield_open;
  double yield_open_tdy;

  double yield_high;
  double yield_high_tdy;

  double yield_low;
  double yield_low_tdy;

  double yield_last;
  double yield_last_tdy; /*Version 2*/
  double yest_yield_last;

  double price_mid;          /* LSE gives mids & lasts! */
  double price_mid_tdy; 
  
  double price_bid_indicative;
  double yield_bid_indicative;
  double price_ask_indicative;
  double yield_ask_indicative; /*Version 3*/

  int4   LSE_flags;
  double price_AT_trade;          
  double price_AT_trade_tdy; /*Version 4*/

  int4 use_prev_close_prior_to_open; /*Version 5*/

  double last_trade;
  double last_trade_tdy; /*Version 6*/

  double vwap;           /* Version 7 */
  double vwap_tdy;       /* Version 7 */

  short weather_sflag; /* Version 8*/
  short weather_ssflag;/* Version 8*/
  int4  apply_intraday_cash_dividend_adjustment;   /* Version 9 */

  /* version 10 */
  int4   is_yield_quoted_security;
  double yest_price_last_pdfe;  /* yest last price based on PDFE settings */

  char bid_exchange_code ;
  char ask_exchange_code ;
  char last_exchange_code ;
  char dummy_pad_exchange_codes ; /** padding to maintain alignment */

} bb_decode_xheaderx_t;

typedef struct {
  int4 version;
  
  double yield_open;
  double yield_open_tdy;

  double yield_high;
  double yield_high_tdy;

  double yield_low;
  double yield_low_tdy;

  double yield_last;
  double yield_last_tdy; /*Version 2*/
  double yest_yield_last;

  double price_mid;          /* LSE gives mids & lasts! */
  double price_mid_tdy; 
  
  double price_bid_indicative;
  double yield_bid_indicative;
  double price_ask_indicative;
  double yield_ask_indicative; /*Version 3*/

  int4   LSE_flags;
  double price_AT_trade;          
  double price_AT_trade_tdy; /*Version 4*/

  int4 use_prev_close_prior_to_open; /*Version 5*/

  double last_trade;
  double last_trade_tdy; /*Version 6*/

  double vwap;           /* Version 7 */
  double vwap_tdy;       /* Version 7 */

  short weather_sflag; /* Version 8*/
  short weather_ssflag;/* Version 8*/
} bb_decode_xheaderx_v8_t;

typedef struct {

  int4 version;
  
  double yield_open;
  double yield_open_tdy;

  double yield_high;
  double yield_high_tdy;

  double yield_low;
  double yield_low_tdy;

  double yield_last;
  double yield_last_tdy; /*Version 2*/
  double yest_yield_last;

  double price_mid;          /* LSE gives mids & lasts! */
  double price_mid_tdy; 
  
  double price_bid_indicative;
  double yield_bid_indicative;
  double price_ask_indicative;
  double yield_ask_indicative; /*Version 3*/

  int4   LSE_flags;
  double price_AT_trade;          
  double price_AT_trade_tdy; /*Version 4*/

  int4 use_prev_close_prior_to_open; /*Version 5*/

  double last_trade;
  double last_trade_tdy; /*Version 6*/
  double vwap;           /* Version 7 */
  double vwap_tdy;       /* Version 7 */

} bb_decode_xheaderx_v7_t;

typedef struct {
  int4 version;
  
  double yield_open;
  double yield_open_tdy;

  double yield_high;
  double yield_high_tdy;

  double yield_low;
  double yield_low_tdy;

  double yield_last;
  double yield_last_tdy; /*Version 2*/
  double yest_yield_last;

  double price_mid;          /* LSE gives mids & lasts! */
  double price_mid_tdy; 
  
  double price_bid_indicative;
  double yield_bid_indicative;
  double price_ask_indicative;
  double yield_ask_indicative; /*Version 3*/

  int4   LSE_flags;
  double price_AT_trade;          
  double price_AT_trade_tdy; /*Version 4*/

  int4 use_prev_close_prior_to_open; /*Version 5*/

  double last_trade;
  double last_trade_tdy; /*Version 6*/
} bb_decode_xheaderx_v6_t;

typedef struct {
  int4 version;
  
  double yield_open;
  double yield_open_tdy;

  double yield_high;
  double yield_high_tdy;

  double yield_low;
  double yield_low_tdy;

  double yield_last;
  double yield_last_tdy; /*Version 2*/
  double yest_yield_last;

  double price_mid;          /* LSE gives mids & lasts! */
  double price_mid_tdy; 
  
  double price_bid_indicative;
  double yield_bid_indicative;
  double price_ask_indicative;
  double yield_ask_indicative; /*Version 3*/

  int4   LSE_flags;
  double price_AT_trade;          
  double price_AT_trade_tdy; /*Version 4*/

  int4 use_prev_close_prior_to_open; /*Version 5*/

} bb_decode_xheaderx_v5_t;


typedef struct {
  int4 version;
  
  double yield_open;
  double yield_open_tdy;

  double yield_high;
  double yield_high_tdy;

  double yield_low;
  double yield_low_tdy;

  double yield_last;
  double yield_last_tdy; /*Version 2*/
  double yest_yield_last;

  double price_mid;          /* LSE gives mids & lasts! */
  double price_mid_tdy; 
  
  double price_bid_indicative;
  double yield_bid_indicative;
  double price_ask_indicative;
  double yield_ask_indicative; /*Version 3*/

  int4   LSE_flags;
  double price_AT_trade;          
  double price_AT_trade_tdy; /*Version 4*/

} bb_decode_xheaderx_v4_t;

/* values for LSE_flags */
#define HEADER_IS_LSE  0x01
#define HEADER_HAS_MID 0x02
#define HEADER_HAS_AT 0x04

typedef struct {
  int4 version;
  
  double yield_open;
  double yield_open_tdy;

  double yield_high;
  double yield_high_tdy;

  double yield_low;
  double yield_low_tdy;

  double yield_last;
  double yield_last_tdy; /*Version 2*/
  double yest_yield_last;

  double price_mid;          /* LSE gives mids & lasts! */
  double price_mid_tdy; /*Version 3*/

} bb_decode_xheaderx_v3_t;

typedef struct {
  int4 version;
  
  double yield_open;
  double yield_open_tdy;

  double yield_high;
  double yield_high_tdy;

  double yield_low;
  double yield_low_tdy;

  double yield_last;
  double yield_last_tdy; /*Version 2*/

} bb_decode_xheaderx_v2_t;

#define DECODE_XHEADERX_VERSION 11

/*typedef bb_decode_xheaderx_v8_t bb_decode_xheaderx_t;*/

typedef struct
{
    int4     status;                    /* Return status: */
                                        /*  0 = OK */
                                        /* -1 = no longer used */
                                        /* -2 = no longer used */
                                        /* -3 = invalid security */
                                        /* -4 = header not found */
                                        /* -5 =	no trade data available */
                                        /* -6 =	no realtime available */

    double   price_open;                /* 0x2D  open price */
    double   price_open_tdy;            /* 0x2D  open price */

    double   price_high;                /* 0x09 high price */
    double   price_high_tdy;            /* 0x09 high price */

    double   price_low;                 /* 0x0A low price */
    double   price_low_tdy;             /* 0x0A low price */

    double   price_last;                /* 0x01 last price */
    double   price_last_tdy;            /* 0x01 last price */

    double   price_settle;              /* 0x06 settlement price */

    double   price_bid;                 /* 0x02 bid price */
    double   price_bid_tdy;             /* 0x02 bid price */

    double   price_ask;                 /* 0x03 ask price */
    double   price_ask_tdy;             /* 0x03 ask price */

    double   yield_bid;                 /* 0x0B bid yield */
    double   yield_bid_tdy;             /* 0x0B bid yield */

    double   yield_ask;                 /* 0x0C ask yield */
    double   yield_ask_tdy;             /* 0x0C ask yield */

    double   limit_up;                  /* 0x0B up limit (futures) */
    double   limit_down;                /* 0x0C down limit (futures) */
    double   open_interest;             /* 0x08 open interest (futures) */
    double   yest_price_last;           /* 0x35 last price of previous session */
    double   scale;                     /* scale factor */
    int4     time_last;                 /* 0x3ff time of last price */
    int4     exchange_last;             /* exchange of last trade */
    int4     tick_direction;            /* up/down/zero tick */

    int4     size_bid;                  /* 0x3FB bid size */
    int4     size_bid_tdy;              /* 0x3FB bid size */

    int4     size_ask;                  /* 0x3FA ask size */
    int4     size_ask_tdy;              /* 0x3FA ask size */

    int4     condition_bid;             /* bid condition */
    int4     condition_ask;             /* ask condition */
    int4     condition_last;            /* last trade condition */
    int4     condition_market;          /* market condition */

    int4     monitorable;               /* monitorable  */

    int4     volume_total;              /* 0x07 total trade volume */
    int4     volume_total_tdy;

    int4     ticks_total;               /* total number of ticks */
    int4     ticks_total_tdy;

    int4     time_start;                /* session start time */
    int4     time_end;                  /* session end time */
    int4     rt_pcs;                    /* real time pricing source (was currency) */
    int4     format;                    /* price display format */
    char     sec_key[32];               /* canonical form of security key */

    int4     date;                      /* as-of date ccyymmdd */
    int4     date_tdy;                  /* current date ccyymmdd */

    bb_decode_xheaderx_t *extra;

#if !(defined(BB_PLATFORM_DECAXP) || defined(LINUX_ALPHA))
	int4 dummy;  /*PAD PAD PAD PAD!*/    
#endif

    int4 extra_size; /*Size of eXtra data*/

    int4	 future_use[5];		

}   bb_decode_headerx_t;



#define BB_HEADER_HAS_EXTRAFIELDS(X) (X->extra!=0)
#define BB_HEADER_IS_V2(X) (X->extrasize>=sizeof(bb_decode_xheaderx_v2_t))
#define BB_HEADER_IS_V1(X) ((!X->extra)||(X->extrasize<sizeof(bb_decode_xheaderx_v2_t)))
#define BB_HEADER_V2_SIZE (sizeof(bb_decode_xheaderx_v2_t))
#define BB_HEADER_V1_SIZE (0)


/*
** Decoded monitor tick data - part of the message returned with tick data
** following bb_tickmntr()
*/

/*
** Tick types in the structure below (types, not listed below, are to be
** disregarded for now)
*/

#define    bNTickTypes  37                  /* Number of available tick types below. */

#define    bTickTRADE                1
#define    bTickBID                  2
#define    bTickASK                  3
#define    bTickHIT                  4      /* Trade on Bid */
#define    bTickTAKE                 5      /* Trade on Ask */
#define    bTickSETTLE               6
#define    bTickVOLUME               7
#define    bTickOPEN_INTEREST        8
#define    bTickHIGH                 9      /* High Recap */
#define    bTickLOW                 10      /* Low Recap */
#define    bTickBID_YIELD           11      /* Up Limit */
#define    bTickASK_YIELD           12      /* Down Limit */
#define    bTickBT_LAST_RECAP       14      /* Used for intraday bars */
#define    bTickNEWS_STORY          27      /* Just an indicator */
#define    bTickBID_MKT_MAKER       29
#define    bTickASK_MKT_MAKER       30
#define    bTickBID_BEST            31      /* Used for intraday series */
#define    bTickASK_BEST            32      /* Used for intraday series */
#define    bTickBT_MID_PRICE        35      /* london Stock Exchange Mid Price */
#define    bTickBT_LSE_LAST         39      /* London Stock Exchange Last Trade */
#define    bTickNEW_MKT_DAY         43      /* Just an indicator */
#define    bTickCANCEL_CORRECT      44
#define    bTickOPEN                45      /* Used for intraday bars */
#define    bTickBT_BID_RECAP        46
#define    bTickBT_ASK_RECAP        47
#define    bTickMKT_INDICATOR       48
#define    bTickBT_MKT_TURN         49      /* Used for intraday bars */
#define    bTickVOLUME_UPDATE       50
#define    bTickBT_SEC_BID          51      /* Secondary Bid */
#define    bTickBT_SEC_ASK          52      /* Secondary Ask */
#define    bTickTICK_NUM            66      /* Used for intraday bars */
#define    bTickBID_LIFT            74      /* Just an indicator */
#define    bTickASK_LIFT            75      /* Just an indicator */
#define	   bTickPRICE_UPDATE		90
#define    bTickVWAP                94      /* Vwap tick type */


#define    bTickPRE_POST_BID       102
#define    bTickPRE_POST_ASK       103


#define		bTickMIN_LIMIT					111		/* Minimum Limit Price */
#define		bTickMAX_LIMIT					112		/* Maximum Limit Price */
#define		bTickTHEO_PRICE					113		/* Theoretical Price */
#define		bTickMIN_LIMIT_OUT_OF_SESSION	114		/* Minimum Limit Out Of Session */
#define		bTickMAX_LIMIT_OUT_OF_SESSION	115		/* Maximum Limit Out Of Session */
#define		bTickBID_WEIGHTED_AVG_SPREAD	116		/* Bid Weighted Average Spread */
#define		bTickASK_WEIGHTED_AVG_SPREAD	117		/* Ask Weighted Avergage Spread */
#define		bTickTRADING_PERIOD				118		/* Trading Period */
#define		bTickNYSE_LIQUIDITY_BID			119		/* NYSE Liquidity Quote Bid Price/Size */
#define		bTickNYSE_LIQUIDITY_ASK			120		/* NYSE Liquidity Quote Ask Price/Size */
#define		bTickPRE_POST_MARKET			121
#define		bTickINDICATIVE_BID				123
#define		bTickINDICATIVE_ASK				124
#define		bTickEVAL_JAPANESE				125     /* Japanese Evaluation Price */
#define     bTickSMART	                    127
#define     bTickSMART128                   128
#define     bTickSMART129                   129
#define     bTickSMART130                   130
#define     bTickSMART_QUOTE                131
#define     bTickSMART131                   131
#define     bTickSMART132                   132
#define     bTickSMART133                   133
#define     bTickBUY_SELL_INFO              133
#define     bTickSMART134                   134
#define     bTickSMART135                   135
#define     bTickSMART136                   136
#define     bTickSMART137                   137
#define     bTickSMART138                   138
#define     bTickSMART139                   139
#define     bTickSMARTMax                   140
#define     bTickTRADE_SPREAD               146
#define     bTickBID_SPREAD                 147
#define     bTickASK_SPREAD                 148
#define     bTickHIGH_YIELD                 150
#define     bTickLOW_YIELD                  151
#define     bTickYIELD                      152
#define     bTickAT_TRADE                   153
#define     bTickSETS_MID_PRICE             154
#define     bTick_API_INTERNAL              155
#define     bTickMARKET_DEPTH               156
#define     bTickALL_PRICE                  157
#define     bTickMAN_TRADE_WITH_SIZE        158   /* copy of bTickBT_LSE_LAST with size */
#define     bTickSETTLE_YIELD               159

#define     bTickSUBSCRIPTION	            1000
#define     bTickRT_API_MACHINE             1001
#define     bTickHEART_BEAT                 1002

#define MAX_FIELD_TYPES    255       
#define MAX_OBJ_STR_SIZE 12
#define RT_API_MACHINE_FLEN 10      /* length of machine name in bTickRT_API_MACHINE */

#define EXCHANGE_FLEN           3
#define CONDITION_CODE_FLEN     31
#define MAX_CONDCODES           6
#define CC_STR_SZ			    45

/*Field IDs: */
#define	bFldOPEN_INTEREST					0x010
#define bFldQUANTITY_LONG_REALTIME			0x0BF
#define bFldQUANTITY_SHORT_REALTIME			0x0C0
#define bFldQUANTITY_SHORT_COVER_REALTIME	0x0C1
#define bFldQUANTITY_LONG_LIQUID_REALTIME	0x0C2
#define bFldASK_OPEN_INTEREST_REALTIME		0x0C3
#define bFldBID_OPEN_INTEREST_REALTIME		0x0C4
#define bFldTOTAL_BUY_VOLUME_REALTIME		0x0C5
#define bFldTOTAL_SELL_VOLUME_REALTIME		0x0C6
#define bFldNET_OPEN_INTEREST_REALTIME		0x0C7
#define bFldNET_VOLUME_IDX_REALTIME			0x0C8

#define bFldVIRTX_OFF_ON_EXCH_VOLUME	0x0C9
#define bFldVIRTX_OFF_EXCH_VOLUME		0x0CA

#define bFldNASDAQ_OPEN			0x049
#define bFldNASDAQ_FIRST_TRADE	0x04A
#define bFldNASDAQ_PREV_BID		0x04B
#define bFldNASDAQ_PREV_ASK		0x04C

#define	bFldEXCH_VWAP			0x03D

#define bFldTRADING_DT_REALTIME				0xD4
#define bFldPREV_CLOSE_VALUE_REALTIME		0xAD
#define bFldPREV_VAL_ADJ_CORP_ACTIONS_RT	0xF3

#define bFldBEST_BID1		0x3A3
#define bFldBEST_BID2		0x3A4
#define bFldBEST_BID3		0x3A5
#define bFldBEST_BID4		0x3A6
#define bFldBEST_BID5		0x3A7

#define bFldBEST_ASK1		0x3A8
#define bFldBEST_ASK2		0x3A9
#define bFldBEST_ASK3		0x3AA
#define bFldBEST_ASK4		0x3AB
#define bFldBEST_ASK5		0x3AC

#define bFldBEST_BID1_SZ	0x3AD
#define bFldBEST_BID2_SZ	0x3AE
#define bFldBEST_BID3_SZ	0x3AF	/*3B0 is skipped because its used already */
#define bFldBEST_BID4_SZ	0x3B1
#define bFldBEST_BID5_SZ	0x3B2

#define bFldBEST_ASK1_SZ	0x3B3
#define bFldBEST_ASK2_SZ	0x3B4
#define bFldBEST_ASK3_SZ	0x3B5
#define bFldBEST_ASK4_SZ	0x3B6
#define bFldBEST_ASK5_SZ	0x3B7

#define bFldALL_PRICE_COND_CODE	0x3B8 /*TRD_COND_CODE is now obsolete */
#define bFldTRD_COND_CODE	0x3B8
#define bFldBID_COND_CODE	0x3B9
#define bFldASK_COND_CODE	0x3BA

#define bFldPX_SETTLE_ACTUAL_RT 0x169 /* RQ361 */

/* These are the API IDs for Condition Code Fields (same as RQ Num) */
#define bFldBID_YLD_COND_CODE   363
#define bFldYLD_COND_CODE       364
#define bFldASK_YLD_COND_CODE   365

/* Fld IDs needed for treq 515738 */
#define bFldALL_SESSION_TRADE 134
#define bFldALL_SESSION_BID 174
#define bFldALL_SESSION_ASK 175

#define SZ_DECODE_TICKX_CHARS	8
#define MAX_MRKT_DEPTH_LEVELS	5
#define MAX_MRKT_DEPTH_DIMENSIONS	2

/* Define these sizes to unaligned numbers only on WIN32 */
#ifdef WIN32
#define SZ_EMPTY_TICK_EXTRA_T	21
#define SZ_EMPTY_TICK_DATA_T	17
#else
#define SZ_EMPTY_TICK_EXTRA_T	(sizeof(bb_decode_tick_extra_t))
#define SZ_EMPTY_TICK_DATA_T	(sizeof(bb_decode_tick_data_t))
#endif

/*API data type definitions: */
typedef enum{
	bTypeSTRING		= 1,	/*char*/
	bTypeNUMERIC	= 2,	/*int4 */
	bTypePRICE		= 3,	/*double */
	bTypeSECURITY	= 4,
	bTypeDATE		= 5,
	bTypeTIME		= 6,
	bTypeDATETIME	= 7,
	bTypeBULK		= 8,
	bTypeMONTHYEAR	= 9,
	bTypeBOOLEAN	= 10,
	bTypeISOCODE	= 11
}bDataTYPE;


typedef struct
{
    int4			mon_id;			/* Monitor id for the security.		*/
    int4			action;			/* Action that occurred (tick type)	*/  
	unsigned char	trans_id;		/* Transaction ID -  A number which 
										will be the same for all fields
										affected by a specific action.	*/
	unsigned char	filler[7];
    int4			time;			/* time								*/

    union
    {
      struct                /* type == bTickTRADE */
      {
        double   price;
        int4     size;
		int4	 time;
      } TRADE;

      struct                /* type == bTickBID */
      {
        double   price;
        int4     size;
      } BID;

      struct                /* type == bTickASK */
      {
        double   price;
        int4     size;
      } ASK;

      struct                /* type == bTickHIT */
      {
        double   price;
        int4     size;
      } HIT;

      struct                /* type == bTickTAKE */
      {
        double   price;
        int4     size;
      } TAKE;

      struct                /* type == bTickSETTLE */
      {
        double   price;
      } SETTLE;

      struct                /* type == bTickSETTLE_YIELD */
      {
        double   yield;
      } SETTLE_YIELD;

      struct                /* type == bTickVOLUME */
      {
        int4     volume;
      } VOLUME;

      struct                /* type == bTickOPEN */
      {
        double   price;
      } OPEN;

      struct                /* type == bTickHIGH */
      {
        double   price;
      } HIGH;

      struct                /* type == bTickLOW */
      {
        double   price;
      } LOW;

      struct                /* type == bTickBID_YIELD */
      {
        double   yield;
	int4     size;      
      } BID_YIELD;

      struct                /* type == bTickASK_YIELD */
      {
        double   yield;
	int4     size;      
      } ASK_YIELD;

      struct                /* type == bTickBID_MKT_MAKER */
      {
        double   price;
        int4     size;
        int4     mkt_maker;
      } BID_MKT_MAKER;

      struct                /* type == bTickASK_MKT_MAKER */
      {
        double   price;
        int4     size;
        int4     mkt_maker;
      } ASK_MKT_MAKER;

      struct                /* type == bTickMKT_INDICATOR */
      {
          BOOL trading;
          BOOL quotation;
          int4 exch_mkt_status;
          int4 simpl_sec_status;
          
      } MKT_INDICATOR;
        
      struct                /* type == bTickBT_MID_PRICE */
      {
        double   price;
        int4     size;
      } BT_MID_PRICE;

      struct                /* type == bTickBT_LSE_LAST */
      {
        double   price;
        int4     size;
      } BT_LSE_LAST;

      struct                /* type == bTickVOLUME_UPDATE */
      {
        double   price;
        int4     size;
      } VOLUME_UPDATE;

      struct                /* type == bTickHIGH_YIELD */
      {
	      double   yield;
      } HIGH_YIELD;
      
      struct                /* type == bTickLOW_YIELD */
      {
	      double   yield;
      } LOW_YIELD;
      
      struct                /* type == bTickYIELD */
      {
	      double   yield;
      } YIELD;

      struct                /* type == bTickTHEO_PRICE */
      {
        double   price;
        int4     size;
      } THEO_PRICE;

      struct                /* type == bTickBID_WEIGHTED_AVG_SPREAD */
      {
	      double   price;
      } BID_WEIGHTED_AVG_SPREAD;

      struct                /* type == bTickASK_WEIGHTED_AVG_SPREAD */
      {
	      double   price;
      } ASK_WEIGHTED_AVG_SPREAD;

      struct                /* type == bTickMIN_LIMIT */
      {
	      double   price;
      } MIN_LIMIT;

      struct                /* type == bTickMAX_LIMIT */
      {
	      double   price;
      } MAX_LIMIT;

	  struct				/* type == bTickMIN_LIMIT_OUT_OF_SESSION */
	  {
		  double   price;
	  } MIN_LIMIT_OUT_OF_SESSION;

	  struct				/* type == bTickMAX_LIMIT_OUT_OF_SESSION */
	  {
		  double   price;
	  } MAX_LIMIT_OUT_OF_SESSION;
	
	  struct				/* type == bTickTRADING_PERIOD */
	  {
		BOOL trading;
		BOOL quotation;
		int4 trading_period;
		int4 simpl_sec_status;
	  } TRADING_PERIOD;

	 struct                /* type == bTickNYSE_LIQUIDITY_BID */
      {
        double   price;
        int4     size;
      } NYSE_LIQUIDITY_BID;

	 struct                /* type == bTickNYSE_LIQUIDITY_ASK */
      {
        double   price;
        int4     size;
      } NYSE_LIQUIDITY_ASK;

	 struct				   /* type == bTickEVAL_JAPANESE */
	 {
		 double price;
	 } EVAL_JAPANESE;

	 struct				   /* type == bTickINDICATIVE_BID */
	 {
		 double price;
	 } INDICATIVE_BID;

	 struct				   /* type == bTickINDICATIVE_ASK */
	 {
		 double price;
	 } INDICATIVE_ASK;

	 struct				   /* type == bTickALL_PRICE */
	 {
		 double price;
		 int4   size;
	 } ALL_PRICE;

	 struct				   /* type == bTickPRE_POST_MARKET */
	 {
		 double price;
		 int4   size;
	 } PRE_POST_MARKET;

      struct                /* type == bTickBT_SEC_BID */
      {
        double   price;
      } BT_SEC_BID;

      struct                /* type == bTickBT_SEC_ASK */
      {
        double   price;
      } BT_SEC_ASK;

      struct                /* type == bTickTRADE */
      {
        double   price;
        int4     size;
      } AT_TRADE;

      struct                /* type == bTickVWAP */
      {
         double   price;
         int4     size;
      } VWAP;

      struct                /* type == bTickRT_API_MACHINE */
      {
         char pulse;
         char name[RT_API_MACHINE_FLEN+1];
         int4 port;
      } RT_API_MACHINE;

      struct                /* type == bTickHEART_BEAT */
      {
         int4 timeSeconds;
         int4 timeMicroSeconds;
         int4 level;
      } HEART_BEAT;

    } data;

}   bb_decode_tickx_t;

typedef struct
{
	int4		field_id;	/*The field Id assigned in the API data dictionary. */
	int4		data_type;	/*The data type of 'data.' */
	int4		size;		/*The number of bytes that follow the rcode (the size of data). */
	int4		rcode;		/* The return code for pertaining field.  Will hold a default */
    /*value for most fields.*/
    char 		data[1];	/* The actual data of the field. */
   
}  bb_decode_tick_data_t;

typedef struct                                
{
  	int4		count; 				/* The number of fields returned in this extra structure. */
   	bb_decode_tick_data_t data[1]; 	/* This structure repeats count times */
}  bb_decode_tick_extra_t;

/* Macro to align SIZE to integer boundaries */
#ifdef WIN32
#define BB_ALIGN(SIZE) (SIZE)
#else
#define BB_ALIGN(SIZE) (((unsigned int)(SIZE) + (sizeof(double) - 1)) &~ (sizeof(double) - 1))
#endif

/* sizeof the 4 static fields in bb_decode_tick_data_t */
#define SZ_DECODE_TICK_EXTRA_DATA_STATIC_PART (4 *sizeof(int4))

/* sizeof the count static field in bb_decode_tick_extra_t */
#define SZ_DECODE_TICK_EXTRA_STATIC_PART (sizeof(int4))

/* Please change SZ_DECODE_TICK_EXTRA_DATA_STATIC_PART and SZ_DECODE_TICK_EXTRA_STATIC_PART
   if you change bb_decode_tick_extra_t or bb_decode_tick_data_t */

typedef struct
{
    int4     mon_id;        /* Monitor id for the security.  */
    int4     type;          /* tick type                     */    
    double   value;         /* meaning depends on tick type  */
    int4     time;          /* time                          */

    union
    {
      struct                /* type == bTickTRADE */
      {
        double   price;
        int4     size;
        int4	 time;
      } TRADE;

      struct                /* type == bTickBID */
      {
        double   price;
        int4     size;
      } BID;

      struct                /* type == bTickASK */
      {
        double   price;
        int4     size;
      } ASK;

      struct                /* type == bTickHIT */
      {
        double   price;
        int4     size;
      } HIT;

      struct                /* type == bTickTAKE */
      {
        double   price;
        int4     size;
      } TAKE;

      struct                /* type == bTickSETTLE */
      {
        double   price;
      } SETTLE;

      struct                /* type == bTickSETTLE_YIELD */
      {
        double   yield;
      } SETTLE_YIELD;

      struct                /* type == bTickVOLUME */
      {
        int4     volume;
      } VOLUME;

      struct                /* type == bTickOPEN */
      {
        double   price;
      } OPEN;

      struct                /* type == bTickHIGH */
      {
        double   price;
      } HIGH;

      struct                /* type == bTickLOW */
      {
        double   price;
      } LOW;

      struct                /* type == bTickBID_YIELD */
      {
        double   yield;
	int4     size;      
      } BID_YIELD;

      struct                /* type == bTickASK_YIELD */
      {
        double   yield;
	int4     size;      
      } ASK_YIELD;

      struct                /* type == bTickBID_MKT_MAKER */
      {
        double   price;
        int4     size;
        int4     mkt_maker;
      } BID_MKT_MAKER;

      struct                /* type == bTickASK_MKT_MAKER */
      {
        double   price;
        int4     size;
        int4     mkt_maker;
      } ASK_MKT_MAKER;

      struct                /* type == bTickMKT_INDICATOR */
      {
          BOOL trading;
          BOOL quotation;
          int4 exch_mkt_status;
          int4 simpl_sec_status;
        
      } MKT_INDICATOR;
        
        struct                /* type == bTickBT_MID_PRICE */
      {
        double   price;
        int4     size;
      } BT_MID_PRICE;

      struct                /* type == bTickBT_LSE_LAST */
      {
        double   price;
        int4     size;
      } BT_LSE_LAST;

      struct                /* type == bTickVOLUME_UPDATE */
      {
        double   price;
        int4     size;
      } VOLUME_UPDATE;

      struct                /* type == bTickHIGH_YIELD */
      {
	      double   yield;
      } HIGH_YIELD;
      
      struct                /* type == bTickLOW_YIELD */
      {
	      double   yield;
      } LOW_YIELD;
      
      struct                /* type == bTickYIELD */
      {
	      double   yield;
      } YIELD;

      struct                /* type == bTickTHEO_PRICE */
      {
        double   price;
        int4     size;
      } THEO_PRICE;

      struct                /* type == bTickBID_WEIGHTED_AVG_SPREAD */
      {
	      double   price;
      } BID_WEIGHTED_AVG_SPREAD;

      struct                /* type == bTickASK_WEIGHTED_AVG_SPREAD */
      {
	      double   price;
      } ASK_WEIGHTED_AVG_SPREAD;

      struct                /* type == bTickMIN_LIMIT */
      {
	      double   price;
      } MIN_LIMIT;

      struct                /* type == bTickMAX_LIMIT */
      {
	      double   price;
      } MAX_LIMIT;

	  struct				/* type == bTickMIN_LIMIT_OUT_OF_SESSION */
	  {
		  double   price;
	  } MIN_LIMIT_OUT_OF_SESSION;

	  struct				/* type == bTickMAX_LIMIT_OUT_OF_SESSION */
	  {
		  double   price;
	  } MAX_LIMIT_OUT_OF_SESSION;
	 
      struct				/* type == bTickTRADING_PERIOD */
	  {
		BOOL trading;
		BOOL quotation;
		int4 trading_period;
		int4 simpl_sec_status;
	  } TRADING_PERIOD;

      struct                /* type == bTickNYSE_LIQUIDITY_BID */
      {
        double   price;
        int4     size;
      } NYSE_LIQUIDITY_BID;

	 struct                /* type == bTickNYSE_LIQUIDITY_ASK */
      {
        double   price;
        int4     size;
      } NYSE_LIQUIDITY_ASK;

	 struct				   /* type == bTickEVAL_JAPANESE */
	 {
		 double price;
	 } EVAL_JAPANESE;

	 struct				   /* type == bTickINDICATIVE_BID */
	 {
		 double price;
	 } INDICATIVE_BID;

	 struct				   /* type == bTickINDICATIVE_ASK */
	 {
		 double price;
	 } INDICATIVE_ASK;

	 struct				   /* type == bTickALL_PRICE */
	 {
		 double price;
		 int4   size;
	 } ALL_PRICE;

	 struct				   /* type == bTickPRE_POST_MARKET */
	 {
		 double price;
		 int4   size;
	 } PRE_POST_MARKET;

      struct                /* type == bTickBT_SEC_BID */
      {
        double   price;
      } BT_SEC_BID;

      struct                /* type == bTickBT_SEC_ASK */
      {
        double   price;
      } BT_SEC_ASK;

      struct                /* type == bTickTRADE */
      {
        double   price;
        int4     size;
      } AT_TRADE;

      struct                /* type == bTickVWAP */
      {
         double   price;
         int4     size;
        int4 combined_override;
      } VWAP;

      struct                /* type == bTickRT_API_MACHINE */
      {
         char pulse;
         char name[RT_API_MACHINE_FLEN+1];
         int4 port;
      } RT_API_MACHINE;

      struct                /* type == bTickHEART_BEAT */
      {
         int4 timeSeconds;
         int4 timeMicroSeconds;
         int4 level;
      } HEART_BEAT;

    } data;

}   bb_decode_tick_t;


/*
** Decoded intraday tick data - part of the message returned with tick data
** following bb_gettimeseries
*/

typedef struct
{
    int4     type;    /* tick type                     */    
    double   value;   /* meaning depends on tick type  */
    int4     time;    /* time                          */

    union
    {
      struct
      {
        double   price;
        int4     size;
      } TRADE;

      struct
      {
        double   price;
        int4     size;
      } BID;

      struct
      {
        double   price;
        int4     size;
      } ASK;

      struct
      {
        double   price;
        int4     size;
      } BID_BEST;

      struct
      {
        double   price;
        int4     size;
      } ASK_BEST;

      struct
      {
        double   price;
        int4     size;
      } HIT;

      struct
      {
        double   price;
        int4     size;
      } TAKE;

      struct
      {
        double   price;
      } SETTLE;

      struct
      {
        double   yield;
      } BID_YIELD;

      struct
      {
        double   yield;
      } ASK_YIELD;

      struct
      {
        double   price;
        int4     size;
        int4     mkt_maker;
      } BID_MKT_MAKER;

      struct
      {
        double   price;
        int4     size;
        int4     mkt_maker;
      } ASK_MKT_MAKER;

      struct
      {
        double   price;
        int4     size;
      } AT_TRADE;

      struct
      {
        double   price;
        int4     size;
      } BT_MID_PRICE;

    } data;

}   bb_decode_intra_tick_t;

typedef struct {

    char exchange[EXCHANGE_FLEN+1];
    char conditionCodes[CONDITION_CODE_FLEN+1];

} bb_decode_condcode_t;

typedef struct {
	int4 rcode;				/* return code */
	char conditionCodes[1];	/* condition code string - can be up to CC_STR_SZ*/
} bb_decode_cc_t;

/*
** Decoded historical data - message returned with 
** historical data requested by bb_gethistory()
*/

typedef struct
{
   int4     date;                             /* Date of field value            */    
   int4     filler;                           /* To resolve alignment problems  */
   double   value;                            /* Field value                    */
}
  bb_decode_history_t;


/* structure to define/access variable length data block */
typedef struct {
                        long length;
                        char data[1];
                } length_element_t;


/*
** Strucrures that combine communication data with real information.
** They represent a data layout within an application buffer as
** returned by bbcomm.tsk
**
** Each service code is represented by its own structure.
** The recommended usage is: cast a pointer to a buffer with data
** from bbcomm.tsk to bb_comm_header_t*, then analyse the service
** code andthen cast it into a pointer to one of the structures below.
*/

typedef struct                                /* Message with security header data */
{                                             /* service code BB_SVC_GETHEADER     */
   bb_comm_header_t        comm_header;
   bb_decode_header_t      sec_header[BB_MAX_SECS];
}
  bb_msg_header_t;

typedef struct                                /* Message with security header data */
{                                             /* service code BB_SVC_GETHEADERX     */
   bb_comm_header_t        comm_header;
   bb_decode_headerx_t      sec_header[BB_MAX_SECS];
}
  bb_msg_headerx_t;


typedef struct                                /* Message with monid's              */
{                                             /* service code BB_SVC_TICKMONITOR   */
   bb_comm_header_t        comm_header;
   int4                    mon_id[BB_MAX_MONIDS];
}
  bb_msg_monid_t;

typedef struct             /* Message with monid's                     */
{                          /* service code BB_SVC_TICKMONITOR_ENHANCED */
    bb_comm_header_t    comm_header;
    int4                mon_id[BB_MAX_MONIDS];
#if defined(WIN32) && !defined(DISABLE_MSG_MONID_ENHANCED_UNION)
    union {
    int4                subscription_status[BB_MAX_MONIDS];
#endif
    int4                return_code[BB_MAX_MONIDS];
#if defined(WIN32) && !defined(DISABLE_MSG_MONID_ENHANCED_UNION)
    };
#endif
} bb_msg_monid_enhanced_t;

typedef struct
{
    int4 TickType;
    int4 size;
    char data[1];
}
bb_override_t;


/* new message type for monitoring by field */
typedef struct
{
    bb_comm_header_t  comm_header;
    int4              *mon_id;
    int4              num_fields;
    int4              *fields;
    length_element_t  *overrides;
}
bb_msg_mon_bf_t;


typedef struct                                /* Message with tick data            */
{                                             /* service code BB_SVC_TICKDATA      */
   bb_comm_header_t        comm_header;
   bb_decode_tick_t        tick_data[BB_MAX_TICKS];
   bb_decode_condcode_t    condcode_data[BB_MAX_TICKS];
}
  bb_msg_tick_t;


typedef struct                                /* Message with tick data            */
{                                             /* service code BB_SVC_GETINTRATICKS */
   bb_comm_header_t        comm_header;
   bb_decode_header_t      sec_header;
   bb_decode_intra_tick_t  intratick_data[1];
}
  bb_msg_timeseries_t;

typedef struct                                /* Message with field values         */
{                                             /* service code BB_SVC_GETDATA       */
   bb_comm_header_t        comm_header;
   char                    data_byte[1];
}
  bb_msg_fields_t;

typedef struct                                 /* Message with multiple security field values */ 
{                                              /* service code BB_SVC_GETDATAX     */
   bb_comm_header_t         comm_header;
   int4                     NumFields;
   char *                   field_ptr[10];
   char                     data_byte[1];
}
  bb_msg_fieldsx_t;

typedef struct                                 /* Message with tick data         */
{                                              /* service code BB_SVC_GETHISTORY */
   bb_comm_header_t        comm_header;
   bb_decode_history_t     history_data[1];
}
  bb_msg_history_t;

typedef struct 
{
   bb_decode_history_t    mhist_data[1];      /* format of multiple history data */  
} 
  bb_decode_mhistory_t;

typedef struct
{
   bb_comm_header_t        comm_header;
   int4                    num_of_securities;  /* number of securities returned */
   int4                    num_of_fields;      /* number of fields returned per security */
   int4                    mhistory_data[1];   /* variable data area                     */
}
  bb_msg_mhistory_t;

typedef struct                                 /* Message with status data          */
{                                              /* service code BB_SVC_STATUS        */
   bb_comm_header_t        comm_header;
   char                    data_byte[1];
}
  bb_msg_status_t;

typedef struct                                 /* Message with results from ticker lookup   */
{                                              /* service code BB_SVC_TKLOOKUP              */
   bb_comm_header_t        comm_header;
   int4                    rcode;
   char                   *token;
   char                  **namebuf;            /*   char *namebuf[]    */
   char                  **uniqbuf;            /*   char *uniqbuf[]    */
   int4                   *flags;
   int4                   *idtype;
   char                    buf[1];
}
  bb_msg_tklookup_t;

typedef struct
{
	bb_comm_header_t    comm_header;
	int4				notifNum;	/*NotificationNumber */
	int4				notifLang;	/*NotificationLanguage */
	char				notifMsg[1];	/*NotificationMessage*/
}
  bb_msg_notify_t;

typedef struct                          /* Message with tick data           */
{                                       /* service code BB_SVC_TICKDATA	    */
   bb_comm_header_t        comm_header;
   bb_decode_tickx_t       tick_data[1];
   bb_decode_tick_extra_t  tick_extra_data[1]; 
}
bb_msg_tickx_t;
/*	Note:  The number of bb_decode_tick_extra_t data structures that will be returned 
will equal the amount of bb_decode_tickx_t structures in the message. This count can 
be determined from comm_header.num_items.  However, when unpacking this message, do not 
use sizeof() for the number of bytes to move the pointer, use the defined sizes (i.e.
SZ_EMPTY_TICK_EXTRA_T).*/

/* Tick data iterator */
typedef struct _bb_tickiterator
{
    bb_msg_tick_t          *d_tickMsg_p;                /* Pointer to original tick message */
    bb_decode_tick_t       *d_currentTick;              /* Pointer to a the tick this iterator represents */
    int                     d_currentTickType;          /* The type of the current tick */
    int                     d_numTicks;                 /* Total number of ticks in this message */
    int                     d_currentTickNo;            /* no of ticks processes in this tick message */
    bb_decode_tick_extra_t *d_currentTickExtraData;     /* Extra data for current tick */
    bb_decode_tick_data_t  *d_currentSmartTick;         /* Pointer to the smart tick this iterator represents */
    int                     d_currentTickNumSmartTicks; /* Number of smart ticks in current tick */
    int                     d_currentSmartTickNo;       /* Number of smart ticks procecessed in current tick */
} bb_tickiterator;

typedef struct
{
	bb_comm_header_t    comm_header;
	int4				feature_id;
} bb_msg_feature_t;

typedef struct
{
    int4 format;
    char data[1];
} bb_query_response_t;

typedef struct
{
    bb_comm_header_t        comm_header;
    bb_query_response_t     queryResponse;
} bb_query_msg_t;

#define StatMSG_BBCOMM_QUERY_REPSONSE -2168

/*
** Realtime Permission/Authorization
*/

typedef struct {
  int uuid;               /* UUID                     */
  int sid;                /* Session SID              */
  int sidInst;            /* Session SID instance     */
  int terminalSid;        /* Terminal SID             */
  int terminalSidInst;    /* Terminal SID instance    */  
  int isRealTimeEnabled;  /* User can request data if */
			  /* this value is non-zero:  */
} QueryClientRealTimeEnabled_t;  

typedef struct                                 /* Message with realtime permission   */
{                                              /* service code  BB_SVC_QUERY_REALTIME_PERMIT */
   bb_comm_header_t        comm_header;
   QueryClientRealTimeEnabled_t query_realtime_allowed;
} bb_msg_realtime_permit_t;

typedef struct
{
    int4    entitlement_id;     /* unique identifier for contributor product offerings */
    int4    reason_code;        /* reason for authorization failure */
    int4    has_pricing_info;   /* if yes, failure resulted from 
                                 * pricing_source/pricing_class mismatch */
    int4    pricing_source;     /* Code used to identify 3rd party pricing providers */
    int4    pricing_class;      /* Security class that the PCS can privilege users on */
    int4    has_mop;            /* if yes, failure resulted from multiple
                                 * outside pricing level mismatch */
    int4    asid_has_inside_price;
    int4    asid_moplevel;      /* multiple outside pricing level for ASID */
    int4    user_has_inside_price;
    int4    user_moplevel;      /* multiple outside pricing level for USER */
} bb_priv_check_info_t;

/* Message with authorization status - BB_SVC_GET_AUTHORIZATION
 * The "status" will be zero if user is authorized.
 * The number of failures returned will be stored in "comm_header.num_items".
 * There is a limit to how many failures will be returned. The field
 * "total_failures" currently returns the same value as "num_items" but may
 * be enhanced in the future to return the total failures.
 */
typedef struct
{
    bb_comm_header_t        comm_header;
    int4                    status;         /* 0 = SUCCESS, !0 = FAILURE   */
    int4                    total_failures; /* total # of failures         */
    bb_priv_check_info_t    failures[1];    /* check comm_header.num_items */
} bb_msg_get_authorization_t;

enum asid_priv_check_reason_code
{
    FAIL_ASID_PRIVCHK_REALTIME         = 10, /* Real-time EID is on for ASID but off for USER */
    FAIL_ASID_PRIVCHK_NFPV             = 20, /* Privilege Bit for 3rd Party (NFPV) product is 
                                              * on for ASID, but off for USER */
    FAIL_ASID_PRIVCHK_NFPV_PCSCLASS    = 30, /* 3rd party pricing product defined by PCS/CLASS
                                              * is enabled for ASID, but disabled for USER */
    FAIL_ASID_PRIVCHK_NFPV_MOP_LEVEL   = 40, /* 3rd party pricing product defined by PCS/CLASS
                                              * is enabled at a different MOP level for ASID
                                              * than it is for USER */
    FAIL_ASID_PRIVCHK_NFPV_UNSEASONED  = 50, /* ASID is privileged to get PCS for unseasoned bonds
                                              * in the CLASS, but the USER is blocked from PCS
                                              * for unseasoned bonds in the CLASS */
    FAIL_ASID_PRIVCHK_NFPV_144A        = 60  /* ASID is priveleged to get PCS for 144a bonds 
                                              * in the CLASS, but the USER is blocked from 
                                              * getting PCS for 144a bonds in the CLASS */
};

/* Response for BB_SVC_USER_ENTITLEMENTS */
typedef struct
{
    bb_comm_header_t    comm_header;
    int4                eids[1];    /* array of entitlements ids */
} bb_msg_user_entitlements_t;

typedef struct
{
    int4    status;     /* 0 - Success, Non-Zero - Failure/Security does not Exist */
    int4    num_eids;   /* Number of entitlements to follow */
    int4    eids[1];    /* array of entitlement ids */
} bb_sec_eids_t;

/* Response for BB_SVC_SECURITY_ENTITLEMENTS */
typedef struct
{
    bb_comm_header_t    comm_header;
    bb_sec_eids_t       buffer[1];  /* Note: variable length items in buffer */
} bb_msg_security_entitlements_t;

/* Error response codes for BB_SVC_SECURITY_ENTITLEMENTS_FOR_USER */
typedef enum 
{
	USER_VERIFCATION_SUCCESS = 0,
	INVALID_UUID,
	INVALID_SID,
	FIRM_MISMATCH,
	SID_UUID_MISMATCH,
	USER_EIDS_FAILURE	
}bUserVerificationError;

typedef enum 
{
    SEC_LOAD_SUCCESS = 0,
    SEC_LOAD_FAILED=62000,
    CALC_EID_FAILED=63000
}bSecurityUserEIDStatusValue;


typedef bb_sec_eids_t security_user_eid_result_t;

/* Response for BB_SVC_SECURITY_ENTITLEMENTS_FOR_USER*/
typedef struct
{
	bb_comm_header_t             comm_header; 
	security_user_eid_result_t   *buffer[1];  
} bb_security_user_eid_data_t;


/* Response for BB_SVC_VALIDATE_BLBG_LOGON */
typedef struct
{
    bb_comm_header_t    comm_header;
    int4                response;
} bb_msg_validate_blbg_logon_t;

enum validation_result_code {
        USER_LOGGED_OFF                  = -2,  /* The UUID of the submitted IP is not logged onto Bloomberg */
        BLBG_LOGON_VALIDATION_FAILED     = -1,  /* The IP supplied for the UUID didn't match Bloomberg IP    */
        BLBG_LOGON_VALIDATION_SUCCEEDED  = 0    /* The IPs matched  */
};

/******************************************************************************/

#define TK_IS_UNIQUE        0x01
#define TK_SPECIAL_ID       0x02

typedef struct     /* One hop in a probe response */
{
    int4    IPaddr;
    int4    port;
    int4    flags;
}   bb_probe_hop_t;

/* flag values for each hop */
#define PHOP_HOP          0
#define PHOP_TIMEOUT      1
#define PHOP_SERVER_PORT  2
#define PHOP_STUB         3
#define PHOP_NOCLIENTS    4
#define PHOP_CLIENT       5
#define PHOP_OLDBBCOMM    6
#define PHOP_ROUTEDOWN    7
#define PHOP_SERVER_QUEUE 8

typedef struct  /* Message with probe results data          */
{
   bb_comm_header_t        comm_header;
   int4     NumHops;
   int4     flags;
   bb_probe_hop_t    hops[1];
}
  bb_msg_probe_t;

/* flag values for probe response message */
#define PFLAG_DONE      0
#define PFLAG_MORE      1

/* The following definition will be used in initiating arrays */
/* Compillation of the program that contains main() should be */
/* done with MAIN defined (option -DMAIN on the compile line. */


/***/
/*** Table of Security Identification Types ***/
/***/

#define BB_IDX_TCM            701 /* Ticker-Coupon-Maturity    */
#define BB_IDX_CUSIP          702 /* Committee on Uniform      */
                                  /* Securities Identification */
                                  /* Procedures (CUSIP)        */
                                  /* (8 chars + 1 check digit) */
#define BB_IDX_EUROCLEAR      703
#define BB_IDX_ISMA           704 /*                           */
#define BB_IDX_SEDOL1         705 /* Stock Exchange Daily      */
                                  /* Official List (London)    */
                                  /* (7 digits)                */
#define BB_IDX_SEDOL2         706 /* Stock Exchange Daily      */
                                  /* Official List (London)    */
                                  /* (7 digits)                */
#define BB_IDX_CEDEL          707
#define BB_IDX_WPK            708 /* Wertpapier Kenn-Nummer,   */
                                  /* German Identification     */
                                  /* Number (6 digits )        */
#define BB_IDX_RGA            709
#define BB_IDX_ISIN           710 /* International Securities  */
                                  /* Identification Number     */
#define BB_IDX_DUTCH          711
#define BB_IDX_VALOREN        712 /* Telekurs assigned number, */
                                  /* Official in Switzerland   */
#define BB_IDX_FRENCH         713 /* SICOVAM                   */
#define BB_IDX_COMMON_NUMBER  714 /* Common number             */
#define BB_IDX_CUSIP8         715 /* CUSIP (8 chars)           */
#define BB_IDX_JAPAN          716
#define BB_IDX_BELGIAN        717 /* SVM Code                  */
#define BB_IDX_DANISH         718
#define BB_IDX_AUSTRIAN       719
#define BB_IDX_LUXEMBOURG     720
#define BB_IDX_SWEDEN         721
#define BB_IDX_NORWAY         722
#define BB_IDX_ITALY          723
#define BB_IDX_JAPAN_COMPANY  724
#define BB_IDX_SPAIN          725
#define BB_IDX_FIRMID         726
#define BB_IDX_MISC_DOMESTIC  727
#define BB_IDX_AIBD           728
#define BB_IDX_CINS           729 /* CUSIP International       */
                                  /* Numbering System          */
                                  /* (8 chars + 1 check digit) */
#define BB_IDX_TICKERX        730 /* Ticker, exchange          */
#define BB_IDX_CUSIPX         731 /* CUSIP, exchange           */
#define BB_IDX_SCM            732 /* State-Coupon-Maturity     */
                                  /* (Municipal)               */
#define BB_IDX_TICKER         733 /* Ticker                    */
#define BB_IDX_STCM           734 /* State-Ticker-Coupon-Mrty  */
                                  /* (Municipal)               */
#define BB_IDX_TICKERDIV      735 /* Ticker-Divident           */
                                  /* (Preferred)               */
#define BB_IDX_CLIENTPORT     736 /* Client-Portfolio          */
#define BB_IDX_TCA            737 /* Ticker-Coupon-Age         */
                                  /* (Mortgage Generic)        */
#define BB_IDX_IRISH_SEDOL    738 /* Irish SEDOL Number        */
#define BB_IDX_CATS           739 /* Malaysian CATS Code       */

#define BB_IDX_OBJECT_ID      740 /* get monid by object id    */
#define BB_IDX_CURVE		  741 /* curve type				   */

#define BB_IDX_APIR           742 /* APIR code */
                                  /* APIR codes are a 9-character alphanumeric id*/
                                  /* used as the standard for identifying mutual */
                                  /* funds in Australia.  The first three characters*/
                                  /* are letters to represent the company the next */
                                  /* four characters are numbers to represent the */
                                  /* fund, and the last two are letters to represent */
                                  /* the country it is issued in. */

  typedef struct
          { int4 IdNum;           /* Numeric Identifier */
            int4 IdLen;           /* Total Key Length */
            int4 IdCode;          /* Internal GETIDENT code */
            char IdName[10];      /* Short Name */
            char IdDesc[32];
          } bb_sec_id_t;

#define MAX_SecId  64  

  Extern    bb_sec_id_t   bbSecIdArray[MAX_SecId]
#ifdef  MAIN
/*
** The following array must be kept in order of the IdNum (1st field)
** since it is used in a binary search in x_history
*/
              =
       {
        { BB_IDX_TCM,           0,  0, "TCM",      "Ticker-Coupon-Maturity" },
        { BB_IDX_TICKERX,       0,  0, "TICKERX",  "Ticker-Exchange"        },
        { BB_IDX_CUSIP,         8,  1, "CUSIP",    "CUSIP"                  },
        { BB_IDX_CUSIP8,        8,  1, "CUSIP8",   "CUSIP (8 char)"         },
        { BB_IDX_CUSIPX,        8,  0, "CUSIPX",   "CUSIP-Exchange"         },
        { BB_IDX_TICKER,        8,  0, "TICKER",   "Ticker"                 },
        { BB_IDX_EUROCLEAR,     0,  5, "EUROCLR",  "Euroclear"              },
        { BB_IDX_ISMA,          0,  9, "ISMA",     "ISMA"                   },
        { BB_IDX_SEDOL1,        7, 25, "SEDOL1",   "Sedol-1"                },
        { BB_IDX_SEDOL2,        7,  2, "SEDOL2",   "Sedol-2"                },
        { BB_IDX_CEDEL,         0,  3, "CEDEL",    "Cedel"                  },
        { BB_IDX_WPK,           6,  6, "WERTP",    "Wertpapier"             },
        { BB_IDX_RGA,           0,  7, "RGA",      "RGA"                    },
        { BB_IDX_ISIN,         11,  8, "ISIN",     "ISIN"                   },
        { BB_IDX_DUTCH,         0, 12, "DUTCH",    "Dutch"                  },
        { BB_IDX_VALOREN,       6, 10, "VALOREN",  "Valoren"                },
        { BB_IDX_FRENCH,        6, 23, "FRENCH",   "French"                 },
        { BB_IDX_COMMON_NUMBER, 0,  9, "COMNUM",   "Common Number"          },
        { BB_IDX_JAPAN,         0, 18, "JAPAN",    "Japanese"               },
        { BB_IDX_BELGIAN,       0, 11, "BELG",     "Belgian"                },
        { BB_IDX_DANISH,        0, 13, "DENMRK",   "Danish"                 },
        { BB_IDX_AUSTRIAN,      0, 14, "AUSTRIA",  "Austrian"               },
        { BB_IDX_LUXEMBOURG,    0, 15, "LUXEMBRG", "Luxembourgeois"         },
        { BB_IDX_SWEDEN,        0, 21, "SWEDEN",   "Swedish"                },
        { BB_IDX_NORWAY,        0, 17, "NORWAY",   "Norwegian"              },
        { BB_IDX_ITALY,         0, 20, "ITALY",    "Italian"                },
        { BB_IDX_JAPAN_COMPANY, 0, 22, "JNCOMNUM", "Japan Company Number"   },
        { BB_IDX_SPAIN,         0, 19, "SPAIN",    "Spanish"                },
        { BB_IDX_FIRMID,        0,  9, "FIRMID",   "Firm Identifier"        },
        { BB_IDX_MISC_DOMESTIC, 0, 16, "MISC",     "Misc. Domestic"         },
        { BB_IDX_AIBD,          0,  4, "AIBD",     "AIBD"                   },
        { BB_IDX_CINS,          8, 24, "CINS",     "CUSIP International"    },
        { BB_IDX_IRISH_SEDOL,   7, 26, "IRISH",    "Irish Sedol Number"     },
        { BB_IDX_CATS,          4, 27, "CATS",     "Malaysian CATS Code"    },
        { BB_IDX_STCM,          0,  0, "STCM",      "State-Ticker-Coupon-Mrty" },
        { BB_IDX_TICKERDIV,     0,  0, "TICKERDIV", "Ticker-Dividend"          },
        { BB_IDX_CLIENTPORT,    0,  0, "CLIENT",    "Client-Portfolio"         },
        { BB_IDX_TCA,           0,  0, "TCA",       "Ticker-Coupon-Age"        },
        { BB_IDX_OBJECT_ID,     0,  0, "OBJECTID",  "Get monid by object id"   },
		{ BB_IDX_APIR,          0,  0, "APIR",      "APIR"                     },
        { 0,                    0,  0, "",          ""                         }
       }
#endif
 ;
    

/***/
/*** Description of Security Market Sectors                      ***/
/*** The default ID types should be used as default for getting  ***/
/*** the field values (bb_getdata) in case user request does not ***/
/*** specify it                                                  ***/
/***/

#define BB_SEC_COMMODITY           1
#define BB_SEC_EQUITY              2
#define BB_SEC_MUNICIPAL_BOND      3
#define BB_SEC_PREFERRED_STOCK     4
#define BB_SEC_CLIENT_PORTFOLIO    5
#define BB_SEC_MONEY_MARKET        6
#define BB_SEC_GOVERNMENT          7
#define BB_SEC_CORPORATE_BOND      8
#define BB_SEC_INDEX               9
#define BB_SEC_CURRENCY           10
#define BB_SEC_MORTGAGE           11



  typedef struct
          { int4 SecMarketNum;
            char SecMarketName[8];
            char SecMarketDesc[32];
            int4 SecMarketIdType;		/* Default Id Type */
          } bb_sec_market_t;

#define MAX_SecMarket  16 

  Extern    bb_sec_market_t  bbSecMarketArray[MAX_SecMarket]
#ifdef  MAIN
              =
       {
        { BB_SEC_COMMODITY,        "Comdty",  "Commodity",        BB_IDX_TICKER     },
        { BB_SEC_EQUITY,           "Equity",  "Equity",           BB_IDX_TICKERX    },
        { BB_SEC_MUNICIPAL_BOND,   "Muni",    "Municipal Bond",   BB_IDX_STCM       },
        { BB_SEC_PREFERRED_STOCK,  "Pfd",     "Preferred Stock",  BB_IDX_TICKERDIV  },
        { BB_SEC_CLIENT_PORTFOLIO, "Client",  "Client Portfolio", BB_IDX_CLIENTPORT },
        { BB_SEC_MONEY_MARKET,     "M-Mkt",   "Money Market",     BB_IDX_TICKER     },
        { BB_SEC_GOVERNMENT,       "Govt",    "Government Bond",  BB_IDX_TCM        },
        { BB_SEC_CORPORATE_BOND,   "Corp",    "Corporate Bond",   BB_IDX_TCM        },
        { BB_SEC_INDEX,            "Index",   "Index",            BB_IDX_TICKER     },
        { BB_SEC_CURRENCY,         "Curncy",  "Currency",         BB_IDX_TICKER     },
        { BB_SEC_MORTGAGE,         "Mtge",    "Mortgage",         BB_IDX_TCA        },
        { 0,                       "",        "",                 0                 }
       }
#endif
        ;





/***
   A part of an API is a Bloomberg Fields Data Dictionary. It combines
   the concepts of Field Category, Field Subcategory and Field ID into 
   a file that an application can load into a table provided below
   using a function bb_load_datadict().

   The data dictionary file, bbfields.tbl, is an ASCII delimited file with the
   vertical bar character ("|") as the field delimiter and newline as the
   record delimiter.

   The fields for this record are as follows:

catcode|catname|subcode|subname|id|desc|mnemonic|market|source|format

    where:

    catcode      - a unique number-identifier for the category
    catname      - a display string to identify the category to a user in a pick list or menu
    subcode      - a unique number-identifier for the subcategory: further devision of the
                   category that narrows the search for a field
    subname      - a display string to identify the subcategory to a user in a pick list or menu
    id           - a unique hex number for the field. This is the field id which must be
                   passed to Bloomberg API functions like bb_getdata().
    desc         - a display string to identify the field to a user in a pick list or menu
    mnemonic     - is intended to be used as the command mnemonic in spreadsheet cells and
                   therefore is the item returned by an applications data dictionary
                   selection widget to the cell formula. It is intended that users will
                   ultimately learn the several mnemonics they use most often and enter
                   them into the cell formulas directly, without resorting to the data
                   dictionary widget.
    market       - an integer which should be interpreted as 32bit bitflag. The low order
                   eleven bits represent whether the field is appropriate for the
                   corresponding market segment (i.e. Bloomberg Yellow Key). Enums and a macro
                   are provided below for use in testing the bits. Fields which are	not
                   appropriate to the market segment the user has identified should either
                   be removed from the user's consideration or "greyed out".
    source       - an integer interpreted as a 32bit bitfield. The low order five bits determine
                   which API requests could be used to acquire this field. Each bit correspondes
                   to one type of request. If more than one bit is set for the field - several
                   types of requests can deliver this field.
    format       - a code that specifies the type of the contents of the field
                   (numeric, string, etc.)

***/

/* Market Applicability Bits (used in FieldMarket flag of the table below) */
/* The following enumaration and MarketValid macro can be used to validate */
/* the request for a specific field of a given security                    */

typedef enum MarketFlags {
                           Comdty = (1 << BB_SEC_COMMODITY),
                           Equity = (1 << BB_SEC_EQUITY),
                           Muni   = (1 << BB_SEC_MUNICIPAL_BOND),
                           Pfd    = (1 << BB_SEC_PREFERRED_STOCK),
                           Client = (1 << BB_SEC_CLIENT_PORTFOLIO), 
                           MMkt   = (1 << BB_SEC_MONEY_MARKET),
                           Govt   = (1 << BB_SEC_GOVERNMENT),
                           Corp   = (1 << BB_SEC_CORPORATE_BOND),
                           Index  = (1 << BB_SEC_INDEX),
                           Curncy = (1 << BB_SEC_CURRENCY),
                           Mtge   = (1 << BB_SEC_MORTGAGE)

                         } YellowKeyFlags;

#define bbMarketValid( Id, Flag ) ((Flag) & (Id))


/**
*** Field Identification Table 
*** This table should be loaded by bb_load_datadict() API function
**/

typedef struct
{
    int4 FieldCatCode;      /* Category code                                  */
    char FieldCatName[40];  /* Category name                                  */
    int4 FieldSubCode;      /* Subcategory code                               */
    char FieldSubName[32];  /* Subcategory name                               */
    int4 FieldId;           /* Field Id                                       */
    char FieldDesc[40];     /* Field name                                     */
    char FieldMnemonic[32]; /* Field Mnemonic                                 */
    int4 FieldMarket;       /* See market applicability bits above            */
    int4 FieldSource;       /* bitfield :                                     */
                            /* 0 -> use bb_getheader()                        */
                            /* 1 -> use bb_tickmntr()                         */
                            /* 2 -> use bb_getdata()                          */
                            /* 3 -> use bb_gethistory()                       */
                            /* 4 -> use bb_gettimeseries()                    */
    int4 FieldFormat;       /* =1 -> ASCII string                             */
                            /* =2 -> Regular Numeric (use sscanf() to convert */
                            /* =3 -> Price (use bb_pricetodouble() to convert */
} bb_field_info_t;

/**
*** Field Identification Table 
*** This table should be loaded by bb_load_datadictx() API function
**/

/*
** Fix put in to address longstanding bug in bb_field_info_t structure 
** (bb_load_datadict()) - field mnemonics of 32 characters (i.e.
** ELECT_PLANT_IN_SERV_TO_TOT_ASSET) are truncated to first 31 characters to
** allow for \0.  new structure bb_field_infox_t (bb_load_datadictx()) changes
** FieldMnonmic to 33 byte array.  New function will allow backward
** compatibility for production code.
*/
typedef struct
{
    int4 FieldCatCode;      /* Category code                                  */
    char FieldCatName[40];  /* Category name                                  */
    int4 FieldSubCode;      /* Subcategory code                               */
    char FieldSubName[32];  /* Subcategory name                               */
    int4 FieldId;           /* Field Id                                       */
    char FieldDesc[40];     /* Field name                                     */
    char FieldMnemonic[33]; /* Field Mnemonic (Updated Size for bugfix)       */
    int4 FieldMarket;       /* See market applicability bits above            */
    int4 FieldSource;       /* bitfield :                                     */
                            /* 0 -> use bb_getheader()                        */
                            /* 1 -> use bb_tickmntr()                         */
                            /* 2 -> use bb_getdata()                          */
                            /* 3 -> use bb_gethistory()                       */
                            /* 4 -> use bb_gettimeseries()                    */
    int4 FieldFormat;       /* =1 -> ASCII string                             */
                            /* =2 -> Regular Numeric (use sscanf() to convert */
                            /* =3 -> Price (use bb_pricetodouble() to convert */
} bb_field_infox_t;

/*
** MAX_Field is now an extern int, defined below
** with bbFieldsTable
*/

/*
** Status error messages
*/
#define ErrMSG_USER_LOGEDOFF      -5002
#define ErrMSG_BLPAUTH_OTHER      -5001
#define ErrMsg_MANUALSHUTOFF      -4003
#define ErrMsg_MONTHLYSHUTOFF     -4002
#define ErrMsg_DAILYSHUTOFF       -4001
#define ErrMSG_FULL_REQ_TABLE     -2200
#define ErrMSG_REQ_TIME_OUT       -2199
#define ErrMSG_COMM_SERVER_DOWN   -2198
#define ErrMSG_BBDB_SERVER_DOWN   -2197
#define ErrMSG_UNAUTHORIZED       -2196
#define ErrMSG_NO_ROUTE           -2195
#define ErrMSG_READ_TKRMON_PIPE   -2194
#define ErrMSG_TKRMON_SEQUENCE    -2193
#define ErrMSG_TKRMON_EXCEPT      -2192
#define ErrMSG_LISTEN_EXCEPT      -2191
#define ErrMSG_FULL_PEER_TBL      -2190
#define ErrMSG_ROUTE_CHANGE       -2189
#define ErrMSG_FULL_LOCK_TBL      -2188
#define ErrMSG_BAD_RCV_BUFF       -2187
#define ErrMSG_BAD_SND_BUFF       -2186
#define ErrMSG_BAD_MSGQ_PKT_TYPE  -2185
#define ErrMSG_BAD_MSGQ_PKT_LEN   -2184
#define ErrMSG_BAD_MSGQ_SEND      -2183
#define ErrMSG_USER_ON_HOLD       -2182
#define ErrMSG_USER_OFF_HOLD      -2181
#define ErrMSG_FULL_SERV_TBL      -2180
#define ErrMSG_CANCEL_MONITOR     -2179
#define ErrMSG_SND_BUFF_OVERFLW   -2178
#define ErrMSG_RCV_BUFF_OVERFLW   -2177
#define ErrMSG_BAD_TAIL           -2176
#define ErrMSG_RCV_BUF_OVRFLW_W   -2175
#define ErrMSG_SND_BUF_OVRFLW_W   -2174
#define ErrMSG_RCV_BUF_OVRFLW_N   -2173
#define ErrMSG_SND_BUF_OVRFLW_N   -2172
#define ErrMSG_SSL_CHAN_STAT      -2171
#define ErrMSG_NOTIFICATION 	  -2169
#define ErrMSG_RT_METER_CONTROL	  -2168
#define ErrMSG_WATCH_EVENT        -2167
#define ErrMSG_UPSTREAM_SESSIONDWN -2166
#define ErrMSG_DOWNSTREAM_SESSIONDWN -2165
#define ErrMSG_UPSTREAM_SESSIONUP  -2164
#define ErrMSG_LOGNOTIFICATION    -2163
#define ErrMSG_REQUEST_HIGH_WATERMARK   -2162
#define ErrMSG_REQUEST_LOW_WATERMARK    -2161

/*
** Array of these struct's is sent in the body of an error msg
** when the routing status of the bbcomm changes (ErrMSG_ROUTE_CHANGE=-2189)
*/
typedef struct
        { int4 ServiceCode;
          int4 RouteStatus;     /* TRUE=up  FALSE=down */
          int4 RouteAddr;
          int4 RoutePort;
        } bb_route_status_t;

typedef struct
{  bb_comm_header_t        comm_header;
   int4     SourceIP;
   int4     SourcePort;
   int4     NumRoutes;
   bb_route_status_t       routes[1];
}
  bb_msg_route_t;

/* Flags for bb_tickmntrx(), bb_tickmntr_typedx().  DRQS 1874365. */
#define BTickMonitorENHANCEDSTREAM 0x00000001
#define BTickMonitorCONDITIONCODES 0x00000002

/* Flags for getheaderx, getheader_typedx */
#define BHeaderDEFAULTSEARCH  0x00000001
#define BHeaderTODAYONLY      0x00000002
#define BHeaderENHANCEDSEARCH 0x00000003
#define BHeaderGARYPSEARCH    0x00000004
#define BHeaderGETSECINFO_ONLY    0x00000005
#define BHeaderBYOBJECTID     0x00000006

/* Flags for timeseriesx */

#define BTimeSeriesSEARCH     0x00000001  /* Search back if specified day has no data */
#define BTimeSeriesBARS       0x00000002  /* Return n-minute bars instead of a tickstream */
#define BTimeSeriesNOFLTR     0x00000004  /* Do not filter out cancel, out of order, etc. ticks */
/* I.K. 1/24/2002 flags for enhanced intraticks */
#define BTimeSeriesBARSFILL   0x00000010  /* Fill in last bar */
#define BTimeSeriesRAWTICKS   0x00000100  /* Return enhanced raw tickstream */

/* Flags for gethistoryx */

#define BHistoryxPERIODMASK   0x0000000F  /* This bits specifies periodicity         */
#define BHistoryxDEFAULT      0x00000000  /* default                                 */
#define BHistoryxDAILY        0x00000001  /* Return daily points                     */
#define BHistoryxWEEKLY       0x00000006  /* Return weekly points (ending on friday) */
#define BHistoryxMONTHLY      0x00000007  /* Return monthly points                   */
#define BHistoryxQUARTERLY    0x00000008  /* Return quarterly points                 */
#define BHistoryxYEARLY       0x00000009  /* Return yearly points                    */

#define BHistoryxQUOTEMASK    0x00000010  /* This bit specifies price/yield          */

#define BHistoryxYIELD        0x00000000  /* Return yields                           */
#define BHistoryxPRICE        0x00000010  /* Return prices                           */

#define BHistoryxFUNCMASK     0x00000020  /* This bit specifies closing/GPA price    */

#define BHistoryxCLOSE        0x00000000  /* Return close                            */
#define BHistoryxGPA          0x00000020  /* Return GPA                              */

#define BHistoryxSHOWNOAXMASK 0x000000C0  /* This set of bits specify view option.   */

#define BHistoryxOMITNOAX     0x00000000  /* Omit non-active date data.              */
#define BHistoryxINCLUDENOAX  0x00000040  /* Include non-active date data.           */
#define BHistoryxALLCALDAYS   0x00000080  /* Include all calendar dates data.        */

#define BHistoryxNOAXFORMMASK 0x00000300  /* These bits specify the return format of */
					  /* user-requested non-active date.         */

#define BHistoryxBBHANDLES    0x00000000  /* Bloomberg handles display format.       */
#define BHistoryxSHOWPREVIOUS 0x00000100  /* Display data from previous active date. */
#define BHistoryxNONUM        0x00000200  /* Display no number.                      */

#define BHistoryxYield2       0x00000400   /* additional yield flag for blph         */
/*
** If bb_gettimeseriesx call is used to request bars instead of a row
** tick stream, the sixth parameter should be a pointer to this structure
** instead of NULL
*/
typedef struct
{
  time_t StartTime;
  time_t EndTime;
  int4   BarSize;
  int4   Field;
} bb_bar_request_t;

/*
** Each bar returned by bb_gettimeseriesx with BTimeSeriesBARS set in the Flags parameter
** will be summarized by a group of ticks with the timestamp of the last second of that
** bar. As of 06/24/97 we send up to seven ticks for each bar. The tick types and what
** will be in the value field are:
** bTickOPEN           -  The value of the first tick in the time range for this bar;
** bTickHIGH           -  The value of the highest valued tick in the time range for this bar;
** bTickLOW            -  The value of the lowest valued tick in the time range for this bar;
** bTickBT_LAST_RECAP  -  The value of the last tick in the time range for this bar;
** bTickVOLUME         -  The total volume of the ticks for the time range for this bar.
**                        This will be provided if it makes sense to compute a volume for
**                        the field that you asked for. For example, if you asked for
**                        LAST_TRADE, the VOLUME tick you get back will have the total number
**                        of shares traded. On the other hand, if you asked for BID on an
**                        exchange where bid's do not have associated volumes, there will be
**                        no VOLUME ticks in the response;
** bTickBT_MKT_TURN    -  The total value of the ticks for the time range for this bar;
** bTickTICK_NUM       -  The number of ticks for this bar.
*/

/* For bb_get_intraday_rawticks */
typedef struct
{
    int4    Options;
    time_t  StartTime;
    time_t  EndTime;
    int4    NumTickTypes;
    int4   *TickTypes;
} bb_intraday_rawticks_request;

typedef enum {
    bIntradayRawTickOptionCC          = 0x00000001, /* to request condition codes         */
    bIntradayRawTickOptionNOFILTER    = 0x00000002, /* do not filter cancelled order, etc */
    bIntradayRawTickOptionSCALEVOLUME = 0x00000004, /* need to scale volume               */
    bIntradayRawTickOptionEC          = 0x00000008  /* to request exchange code           */
} bIntradayRawTickOptions;

/*
** (De)Subscription Categories for bb_tickmntr_enhanced and bb_stopmntr_enhanced
** Notes:
**  1) All previous tickmntr calls will subscribe for core ticks only.
**  2) bb_stopmntr will stop all categories that are subscribed.
*/
typedef enum 
{
    bCategoryCORE = 0,                      /* subscribe for core ticks         */
    bCategoryMARKET_DEPTH = 1,              /* subscribe for market depth ticks */
    bCategoryGREEKS = 2,                    /* subscribe for option greeks      */
    bCategoryCONDITION_CODES = 3,           /* subscribe for condition codes    */
    bCategoryEXCHANGE_CODE = 4,             /* subscribe for exchange-code in   */
                                            /* BID/ASK and TRADE ticks          */
    bCategoryRESERVED_1 = 5,                /* Reserved                         */
    bCategoryRESERVED_2 = 6,                /* Reserved                         */
    bCategoryUNUSED,                        /* for future expansion             */
    bCategoryNUM_TICKMNTR_CATEGORIES        /* num of items                     */
} bTickMntrCategory;

/* custom vwap */
enum VWAPErrorCode {
    SERVICE_NOT_AVAILABLE = 1,
    INVALID_SECURITY_KEY  = 2,
    INVALID_TOPIC_STRING  = 3,
    INVALID_OVERRIDES     = 4,
    INVALID_UTS           = 5,
    RT_LIMITS_REACHED     = 6,
    NOT_AUTHORIZED        = 7,
    SERVICE_TIMEDOUT      = 8,
    INVALID_SUBSCRIPTION  = 9,
    DELAYED_USER          = 10,
    INTERNAL_ERROR        = 11
};

enum VWAPType {
    BLOOMBERG_VWAP      = 0x5E,
    MARKET_DEFINED_VWAP = 0x6C
};

typedef struct
{
	bb_comm_header_t	comm_header;
	int8				stream_id;
	int8                subscription_handle;
	int4				return_code;
} bb_msg_monid_custom_vwap_t;

typedef struct
{
    int8    stream_id;       /* 64-bit monid */
    int4    time;            /* time of tick */
    int4    event_type;      /* may be useful to have in future */
    int4    count;           /* count of how many elements in array 
                                below */
    bb_decode_tick_data_t
           *fields[1];       /* array of pointers point to each 
                                Individual field. */
} bb_subscription_data_event_t;


typedef struct
{
    bb_comm_header_t    comm_header;    /* contains num_items */
    bb_subscription_data_event_t 
                       *tick_data[1];   /* array of pointers point to each
                                           individual tick, length of
                                           array is equal to num_items */
} bb_msg_subscription_data_t;


/*** Function prototypes ***/
/*** Function prototypes ***/
/*** Function prototypes ***/
/*** Function prototypes ***/
/*** Function prototypes ***/
/*** Function prototypes ***/

#ifndef KandR


#ifdef BB_PLATFORM_WINDOWS_DLL

#ifdef __cplusplus
#define  ExternC extern "C" __declspec( dllexport )
#else
#define  ExternC            __declspec( dllexport )
#endif

#else

#ifdef BB_USING_DLL
#ifdef __cplusplus
#define  ExternC extern "C" __declspec( dllimport )
#else
#define  ExternC            __declspec( dllimport )
#endif

#else

#ifdef __cplusplus
#define  ExternC extern "C"
#else
#define  ExternC
#endif

#endif

#endif

#ifdef BB_PLATFORM_WINDOWS_NT

/* This is ExternC for NT because it lives in the .DLL's address space */
ExternC  bb_field_info_t *bbFieldArray;
/* DRQS 4351033 */
ExternC  bb_field_infox_t *bbFieldArrayx;

ExternC  int4             MAX_Field;

#define STDCALL __stdcall
#else

#ifdef __cplusplus
extern "C" bb_field_info_t *bbFieldArray;
extern "C" bb_field_infox_t *bbFieldArrayx;
extern "C" int4 MAX_Field;
#else
extern     bb_field_info_t *bbFieldArray;
extern     bb_field_infox_t *bbFieldArrayx;
extern     int4 MAX_Field;
#endif

#define STDCALL 
#endif


ExternC int4 STDCALL     
 bb_accounting_control    /* Control Accounting Server         */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,
      int4,
      int4,
      int4,
      int4
    );                    /* Normal return: Connection Status  */
                          /* Error return:  ExitFAILCONNECTION */

ExternC int4 STDCALL
 bb_add_msg_handler       /* Register a handler for a message  */
    ( int4,               /* Service code from the message     */
      bb_msg_handler_t    /* -> function that handles message  */
    );                    /* Normal return: ExitOK             */
                          /* Error return:  ExitFAILSERVICE    */

ExternC int4 STDCALL         
 bb_check_connection      /* Returns status of asynch connect  */
    ( bb_connect_t *      /* -> connection description object  */
    );                    /* Normal return: Connection Status  */
                          /* Error return:  ExitFAILCONNECTION */

ExternC int4 STDCALL
 bb_comm_parm_set         /* Set some bbcomm server parameter  */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* count of number of parameters     */
      int4 *);            /* pointer to array of parameters,   */
                          /* first one is what to set (see the */
                          /* BB_SET_ constants defined above   */

ExternC bb_connect_t * STDCALL
 bb_connect               /* Connect to local Comm Server      */
    ( int4                /* Port # the Comm Server is bound   */
    );                    /* Normal return: -> connection      */
                          /*                description object */
                          /* Error return:  NULL               */


ExternC bb_connect_t * STDCALL
 bb_connect_asynch        /* Connect asynchronously to Comm Srv*/
    ( int4                /* Port # the Comm Server is bound   */
    );                    /* Normal return: -> connection      */
                          /*                description object */
                          /* Error return:  NULL               */

ExternC bb_connect_t * STDCALL
 bb_connect2              /* As above, but no "I am alive"     */
    ( int4                /* Port # the Comm Server is bound   */
    );                    /* Normal return: -> connection      */
                          /*                description object */
                          /* Error return:  NULL               */

ExternC bb_connect_t * STDCALL
 bb_connect_signal        /* Reserved for internal usage       */
    ( int4,
      int4
    );

ExternC bb_connect_t * STDCALL
 bb_connect_remote_signal /* Reserved for internal usage       */
    ( char *,
      int4,
      int4
    );

ExternC bb_connect_t * STDCALL
 bb_connect_remote        /* Connect to remote Comm Server     */
    ( char *,             /* Remote IP address ("NN.NN.NN.NN") */
      int4                /* Port # the Comm Server is bound   */
    );                    /* Normal return: -> connection      */
                          /*                description object */
                          /* Error return:  NULL               */

ExternC bb_connect_t * STDCALL
 bb_connect_server        /* Connect to remote Comm Server     */
    ( int4 *,             /* return code */
      char *,             /* Remote IP address ("NN.NN.NN.NN") */
      int4                /* Port # the Comm Server is bound   */
    );                    /* Normal return: -> connection      */
                          /*                description object */
                          /* Error return:  NULL               */

ExternC bb_connect_t * STDCALL
 bb_connect_server_user   /* Connect to remote Comm Server     */
    ( int4 *,             /* return code */
      char *,             /* Remote IP address ("NN.NN.NN.NN") */
      int4,               /* Port # the Comm Server is bound   */
      int4,               /* uuid */
      int4,               /* userSid */
      int4,               /* userSid instance */
      int4,               /* termSid */
      int4                /* termSid instance */
    );                    /* Normal return: -> connection      */
                          /*                description object */
                          /* Error return:  NULL               */
ExternC bb_connect_t * STDCALL
 bb_connect_server_asynch /* Asynchronously connect to remote Comm Server*/
    ( int4 *,             /* return code */
      char *,             /* Remote IP address ("NN.NN.NN.NN") */
      int4                /* Port # the Comm Server is bound   */
    );                    /* Normal return: -> connection      */
                          /*                description object */
                          /* Error return:  NULL               */

ExternC bb_connect_t * STDCALL
 bb_connect_server_user_asynch  /* asynchronously Connect to remote Comm Server  */
    ( int4 *,                   /* return code */
      char *,                   /* Remote IP address ("NN.NN.NN.NN") */
      int4,                     /* Port # the Comm Server is bound   */
      int4,                     /* uuid */
      int4,                     /* userSid */
      int4,                     /* userSid instance */
      int4,                     /* termSid */
      int4                      /* termSid instance */
    );                          /* Normal return: -> connection      */
                                /*                description object */
                                /* Error return:  NULL               */

#ifdef BB_PLATFORM_WINDOWS_NT
  /* DEPRICATED */
  ExternC BOOL STDCALL bb_is_open_bloomberg_running();
#endif /* #ifdef BB_PLATFORM_WINDOWS_NT */

  /* Server API client application address verification */
  ExternC int4 STDCALL bb_validate_blbg_logon(
      bb_connect_t *,     /*  -> connection description object  */
      int4,               /* uuid                              */
      int4,               /* sid                               */
      int4,               /* sidInst                           */
      int4,               /* terminalSid                       */
      int4,               /* terminalSidInst                   */
      int4);              /* server api client application address in the network byte order */
                          /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*                ExitFAILPARM       */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC bb_connect_t * STDCALL
 bb_connect_remote_asynch /* Connect asynchronously to Comm Srv*/
    ( char *,             /* Remote IP address ("NN.NN.NN.NN") */
      int4                /* Port # the Comm Server is bound   */
    );                    /* Normal return: -> connection      */
                          /*                description object */
                          /* Error return:  NULL               */

ExternC int4 STDCALL        
 bb_disconnect            /* Disconnect from Comm Server       */
    ( bb_connect_t *      /* -> connection description object  */
    );                    /* Normal return: ExitOK             */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILPEERLOOKUP */

ExternC int4 STDCALL        
 bb_dispatch_msg          /* Call msg handler after receive    */
    ( bb_comm_header_t *  /* ->Msg received                    */
    );                    /* Normal return: ExitOK             */
                          /* Error return:  ExitFAILSERVICE    */
                          /*                ExitFAILNOHANDLER  */

ExternC int4 STDCALL        
 bb_send_wrap             /* Comm Server sends wrap tick       */
    ( bb_connect_t *,     /* -> connection description object  */
      int4                /* Security MonID to send wrap for   */
    );                    /* Normal return: 0                  */

ExternC int4 STDCALL        
 bb_echo_comm             /* Comm Server echoes this back      */
    ( bb_connect_t *      /* -> connection description object  */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
			  /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_exit_comm             /* Send a signal to exit Comm Server */
    ( bb_connect_t *      /* -> connection description object  */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_exit_db               /* Send a signal to exit DB Server   */
    ( bb_connect_t *      /* -> connection description object  */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_getdata               /* Send request to get field values  */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Type of id (TCM, CUSIP...)        */
      char [32],          /* -> 32 bytes of security key       */
      int4,               /* # fields requested for security   */
      int4 *,             /* -> array of requested field id's  */
      int4,               /* # fields to override              */
      int4 *,             /* -> array of field id to override  */
      char *              /* -> array of 32 bytes strings      */
                          /*    with values to override        */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILGETDATA    */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*             ExitFAILTOOMANYFIELDS */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL
bb_getdatax
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Number of securities              */
      int4 *,             /* -> array of types of tickers      */
      char *,             /* -> array of security tickers      */
      int4,               /* Number of fields requested        */ 
      int4 *,             /* Array of requested field id's     */
      int4,               /* Number of fields to override      */
      int4 *,             /* -> array of field ID's to override*/
      char *              /* -> array of 32 byte strings of    */
                          /*               override values     */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILGETDATA    */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*             ExitFAILTOOMANYFIELDS */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_getheader             /* Group request for basic fields    */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Number of security keys (<=10)    */
      char *              /* -> security keys (32 bytes each)  */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILGETHEADER  */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_getheaderx            /* Group request for basic fields    */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Flags                             */
      int4,               /* Reserved                          */
      int4,               /* Number of security keys (<=10)    */
      char *              /* -> security keys (32 bytes each)  */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILGETHEADER  */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_getheader_typed       /* Group request for basic fields    */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Number of security keys (<=10)    */
      int4 *,             /* -> types of keys (TCM, CUSIP...)  */
      char *              /* -> security keys (32 bytes each)  */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILGETHEADER  */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_getheader_typedx      /* Group request for basic fields    */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Flags                             */
      int4,               /* Reserved                          */
      int4,               /* Number of security keys (<=10)    */
      int4 *,             /* -> types of keys (TCM, CUSIP...)  */
      char *              /* -> security keys (32 bytes each)  */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILGETHEADER  */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL 
 bb_gethistory            /* Send request to get history data  */
     ( bb_connect_t *,    /* -> connection description object  */
       char [32],         /* -> 32 bytes of security key       */
       int4,              /* Start date in YYYYMMDD format     */
       int4,              /* End date in YYYYMMDD format       */
       int4,              /* Requested field id                */
       int4,              /* Price source (for now must be 0)  */
       int4               /* Max number of points to deliver   */
     );                   /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL
 bb_gethistoryx           /* Enhanced request to get history   */
     ( bb_connect_t *,    /* -> connection description object  */
       char [32],         /* -> 32 bytes of security key       */
       int4,              /* security key type                 */
       int4,              /* Start date in YYYYMMDD format     */
       int4,              /* End date in YYYYMMDD format       */
       int4,              /* Requested field id                */
       int4,              /* Price source (for now must be 0)  */
       int4,              /* Max number of points to deliver   */
       int4               /* Various ORed flags (BHistoryx...) */
     );                   /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */


ExternC int4 STDCALL
 bb_fullgethistory        /* full gethistory with currency request */
     ( bb_connect_t *,    /* -> connection description object  */
       int4,              /* number of securities ( <= 10 )    */
       char *,            /* -> security keys (32 bytes each)  */
       int4 *,            /* -> key types (CUSIP...) ( <= 10)  */
       int4 *,            /* Currency types ( <= 10)           */
       char *,            /* Start date in YYYYMMDD format     */
       char *,            /* End date in YYYYMMDD format       */
       int4,              /* number of fields ( <= 10 )        */
       int4 *,            /* ->  array of Requested field ids  */
       int4,              /* Various ORed flags (BHistoryx...) */
       int4               /* Maximum number of points          */
     );                   /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */


ExternC int4 STDCALL
bb_fullgethistoryx  
    ( bb_connect_t *, /* Connection description object       */
      int4,           /* Number of securities  (<=10)        */
      char *,         /* Security key strings                */
      int4 *,         /* Security Types (CUSIP, etc)         */
      int4 *,         /* Currency Types                      */
      char *,         /* Start Date YYYYMMDD                 */
      char *,         /* End date YYYYMMDD                   */
      int4,           /* number of fields                    */
      int4 *,         /* Fields to retrieve                  */
      int4,           /* Number of fields to override        */
      int4 *,         /* Array of field ID's to override     */
      char *,         /* Array of strings of override values */
      int4,           /* Flags                               */
      int4            /* Maximum number of points            */
    );                /* Normal Return: request ID (>0)      */
                      /* Error return:  ExitFAILCONNECTION   */
                      /*                ExitFAILMALLOC       */
                      /*                ExitFAILCONNECT      */
                      /*                ExitFAILROUTE        */
                      /*                ExitFAILSEND         */
                      /*                ExitFAILFLUSH        */
                      /*            ExitFAILSENDBUFFERFULL   */


ExternC int4 STDCALL
 bb_mgethistoryx          /* multiple gethistoryx request      */
     ( bb_connect_t *,    /* -> connection description object  */
       int4,              /* number of securities ( <= 10 )    */
       char *,            /* -> security keys (32 bytes each)  */
       int4 *,            /* -> key types (CUSIP...) ( <= 10)  */
       int4,              /* Start date in YYYYMMDD format     */
       int4,              /* End date in YYYYMMDD format       */
       int4,              /* number of fields ( <= 10 )        */
       int4 *,            /* ->  array of Requested field ids  */
       int4               /* Various ORed flags (BHistoryx...) */
     );                   /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */
 

ExternC int4 STDCALL         
 bb_getsocket             /* Get socket from connection object */
    ( bb_connect_t *      /* -> connection description object  */
    );                    /* Normal return: socket number (>0) */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILSOCKET     */

ExternC int4 STDCALL         
 bb_getticks              /* Get most current ticks            */
    ( bb_connect_t *,     /* -> connection description object  */
      char [32]           /* -> 32 bytes of security key       */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*             ExitFAILGETTIMESERIES */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */
                          /* NOTE: This is a shortcut to the   */
                          /*       bb_gettimeseries() with     */
                          /*       DB#=0 and search back=1     */

ExternC int4 STDCALL         
 bb_gettimeseries         /* Send request for time series data */
    ( bb_connect_t *,     /* -> connection description object  */
      char [32],          /* -> 32 bytes of security key       */
      int4,               /* DB#: today(0), yesterday(1) etc.  */
      int4                /* search back if the DB is empty 0/1*/
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*             ExitFAILGETTIMESERIES */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL        
 bb_gettimeseriesx        /* Send request for time series data - enhanced */
    ( bb_connect_t *,     /* -> connection description object  */
      char [32],          /* -> 32 bytes of security key       */
      int4,               /* security key type                 */
      int4,               /* DB#: today(0), yesterday(1) etc.  */
      int4,               /* flags (including search flag)     */
      bb_bar_request_t *  /* -> to param's for requesting bars */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*             ExitFAILGETTIMESERIES */
                          /*            ExitFAILTIMESERIESBARS */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL
 bb_get_intraday_rawticks /* Send request for intraday rawticks */
    ( bb_connect_t *,     /* -> connection description object   */
      const char *Key,    /* -> 32 bytes of security key        */
      int4 KeyType,       /* security key type                  */
      bb_intraday_rawticks_request *, /* request parameters     */
      int4 RequestLen     /* length of request object           */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*             ExitFAILGETTIMESERIES */
                          /*            ExitFAILTIMESERIESBARS */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

/* custom vwap subscription/desubscription */
ExternC int4 STDCALL
  bb_tickmntr_custom_vwap(       /* subscribe to custom vwap               */
    bb_connect_t *AppMonitor,    /* connection description object          */
    const int4    VwapType,      /* BLOOMBERG_VWAP (0x5E) or
                                    MARKET_DEFINED_VWAP (0x6C)             */
    const int4	  KeyType,	     /* key type                               */
    const char	  Key[32],	     /* security key                           */
    const int4	  NumOverrides,  /* number of fields id to override        */
    const int4	 *FieldIds,	     /* array of field ids                     */
    const char	 *Overrides,     /* array of 32 bytes each override string */
    const int4    OptionsFlag    /* reserved for future use                */
);                               /* Normal return: request ID (>0)         */
                                 /* Error return:  ExitFAILCONNECTION      */
                                 /*                ExitFAILMALLOC          */
                                 /*                ExitFAILCONNECT    */
                                 /*                ExitFAILROUTE      */
                                 /*                ExitFAILSEND       */
                                 /*                ExitFAILFLUSH      */
                                 /*                ExitFAILPARM       */
                                 /*                ExitFAILBDEENCODE  */


ExternC int4 STDCALL 
    bb_stopmntr_custom_vwap(     /* desubscribe to custom vwap             */
    bb_connect_t *ApplMonitor,   /* connection description object          */
    int8          SubHandle      /* subscription handle                    */
);                               /* Normal return: request ID (>0)         */
                                 /* Error return:  ExitFAILCONNECTION      */
                                 /*                ExitFAILMALLOC          */
                                 /*                ExitFAILCONNECT    */
                                 /*                ExitFAILROUTE      */
                                 /*                ExitFAILSEND       */
                                 /*                ExitFAILFLUSH      */
                                 /*                ExitFAILPARM       */
                                 /*                ExitFAILBDEENCODE  */


ExternC int4 STDCALL
 bb_gettimezone           /* Start/stop time zone adjustmnet   */
    ( bb_connect_t *,     /* -> connection description object  */
      int4                /* !=0 adjustment is on, =0 turn off */
    );                    /* For turn adjustment off request:  */
                          /* Normal return: request ID (>0)    */
                          /* Error return: ExitFAILCONNECTION  */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */
                          /* For turn adjustment off request:  */
                          /* Normal return: ExitOK (0)         */
                          /* Error return: ExitFAILCONNECTION  */
				

ExternC int4 STDCALL
 bb_enablefeature		  /* Enables feaures like CCs and AllPrice */
	( bb_connect_t *,	  /* -> connection description object  */
	  int4,				  /* -> ORed feature defines		   */
	  void*				  /* -> Set aside for expansion		   */
	);					  /* Normal return: request ID (>0)    */
                          /*				ExitOK (if feature */
						  /*				was already requested)*/
                          /* Error return:  ExitFAILCONNECTION */
						  /*                ExitFAILMALLOC     */

ExternC int4 STDCALL
 bb_enableccs			  /* Requests Condition Codes		   */
	( bb_connect_t *	  /* -> connection description object  */
	);					  /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */

ExternC char* STDCALL
 bb_retrieveccstrings	  /* Retrieves Condition Code str array*/
	(
	);					  /* Normal return: char* buffer	   */
                          /* Error return:  NULL			   */
ExternC char* STDCALL
 bb_retrieveecstrings();  /* Retrieves Exchange Code charr array   */
                          /* Normal return: char* buffer	   */
                          /* Error return:  NULL		   */

ExternC void STDCALL
 bb_getversion              /* fills version number (of library) */
    ( int *Major,           /* -> to area to put major version   */
      int *Minor            /* and minor version                 */
    );

ExternC int4 STDCALL
 bb_get_library_version();  /* Get full version of api library              */
                            /* Returns version packed into int4             */
                            /*   Ex. 0x02090102 would be version 2.9.1.2    */

ExternC int4 STDCALL
 bb_get_server_version      /* Get full version of server                   */
    ( bb_connect_t *        /* connection description object                */
                            /* Returns version packed into int4             */
                            /*   Ex. 0x02090102 would be version 2.9.1.2    */
                            /*   If no socket is connected, 0 is returned   */
    );

ExternC int4 STDCALL         
 bb_tklookup              /* Request ticker symbol data        */
    ( bb_connect_t *,     /* -> connection description object  */
      char *,             /* Product key, ie "Corp" or "Mtge"  */
      char *,             /* Name of what we want to find      */
      char *              /* State information to tk funcs     */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILTKLOOKUP   */
                          /*                ExitFAILMALLOC     */
                          /*            ExitFAILREQUESTTOOLONG */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */
#ifndef BB_PLATFORM_LINUX_INTEL
ExternC int4 STDCALL         
 bb_identify              /* Obtain network authorization id   */
    ( Display *,          /* -> Display from XOpenDisplay - in */
      int4 *              /* -> Network authorization ID - out */
                          /*   an array of 4 int4 integers     */    
                          /*   to fill for use by bb_setuser() */
    );                    /* Normal return: 0                  */
                          /* Error return:                     */
#endif

ExternC int4 STDCALL         
 bb_load_datadict         /* Load external field definitions   */
    ( char *              /* -> Field definition file name     */
    );                    /* Normal return: # of fields (>0)   */
                          /* Error return:  ExitFAILOPENFILE   */

/* DRQS 4351033 - fix put in to address longstanding bug in bb_field_info_t structure 
   (bb_load_datadict()) - field mnemonics of 32 characters (i.e. ELECT_PLANT_IN_SERV_TO_TOT_ASSET) are 
   truncated to first 31 characters to allow for \0.  new structure bb_field_infox_t 
   (bb_load_datadictx()) changes FieldMnonmic to 33 byte array.  New function will allow backward 
   compatibility for production code
*/

ExternC int4 STDCALL         
 bb_load_datadictx         /* Load external field definitions   */
    ( char *              /* -> Field definition file name     */
    );                    /* Normal return: # of fields (>0)   */
                          /* Error return:  ExitFAILOPENFILE   */


ExternC int4 STDCALL      /* For Bloomberg internal usage only */
 bb_monitor_monid         /* Enable tick stream for monid's    */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Number of monids                  */
      int4 *,             /* -> monids                         */
      char *              /* -> object ids (12 bytes each)     */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILTICKMNTR   */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_get_realtime_permission /* Group request for basic fields  */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* uuid                              */
      int4,               /* sid                               */
      int4,               /* sidInst                           */
      int4,               /* terminalSid                       */
      int4                /* terminalSidInst                   */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_get_authorization     /* Is user authorized for realtime?  */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* uuid                              */
      int4,               /* sid                               */
      int4,               /* sidInst                           */
      int4,               /* terminalSid                       */
      int4                /* terminalSidInst                   */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL
 bb_get_user_entitlements /* Request for user entitlements     */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* uuid                              */
      int4,               /* sid                               */
      int4,               /* sidInst                           */
      int4,               /* terminalSid                       */
      int4                /* terminalSidInst                   */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILPARM       */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL
 bb_get_security_entitlements /* Request for user entitlements */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Number of security keys (<=10)    */
      const int4 *,       /* -> types of keys (TCM, CUSIP...)  */
      const char *        /* -> security keys (32 bytes each)  */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILPARM       */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */
ExternC int4 STDCALL
 bb_get_security_entitlements_for_user  /* Request for user entitlements */
    ( bb_connect_t *ApplMonitor,        /* -> connection description object  */
	  int4         uuid,                /* UUID                              */
	  int4         sid,                 /* SID                               */
      int4         numSecurities,       /* Number of security keys (<=10)    */
      const int4 * securityTypes,       /* -> types of keys (TCM, CUSIP...)  */
      const char * securityKeys         /* -> security keys (32 bytes each)  */

    );                    
	                      /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILPARM       */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */


ExternC double STDCALL      
 bb_pricetodouble         /* Convert string price into double  */
    ( unsigned char *     /* Price: 10.25 or 10 1/4 or 10-08   */
    );                    /* Normal return: price (>=0)        */
			  /* Error return:  <0                 */

ExternC int4 STDCALL        
 bb_probe_network         /* Send a probe message to route     */
    ( bb_connect_t *      /* -> connection description object  */
    );                    /* Normal retuen: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_rcvdata               /* Receive message from Comm Server  */
    ( bb_connect_t *,     /* -> connection description object  */
      void *,             /* -> data buffer for next DB packet */
      unsigned int4       /* max length of data                */
    );                    /* Normal return: Service code of a  */
                          /*              packet received (>0) */
                          /*              or BB_SVC_INCOMPLETE */
                          /* Error return:  BB_SVC_SYSTEMDOWN  */
                          /*                BB_SVC_LOSTNOTIFY  */
                          /*              BB_SVC_AUTHORIZATION */
                          /*              BB_SVC_TICKAFTERSTOP */
                          /*                ExitFAILCONNECTION */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILRECEIVE    */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCOMPRESS   */
                          /*             ExitFAILRECEIVEBUFFER */

ExternC int4 STDCALL        
 bb_report_comm           /* Ask bbcomm to print stat data     */
    ( bb_connect_t *,     /* -> connection description object  */
      int4                /* Report type (see bReport)         */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_report_db             /* Ask local bbdb to print stat data */
    ( bb_connect_t *,     /* -> connection description object  */
      int4                /* Report type (see bReport...)      */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_resubscribe           /* Resubscribe all monitorable items */
    ( bb_connect_t *      /* -> connection description object  */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL        
 bb_route_add             /* Add new route to Comm Server      */
    ( bb_connect_t *,     /* -> connection description object  */
      char *              /* String with route description     */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILROUTELOAD  */

ExternC int4 STDCALL         
 bb_route_delete          /* Delete a route from Comm Server   */
    ( bb_connect_t *,     /* -> connection description object  */
      char *              /* String with route description     */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILROUTELOAD  */

ExternC int4 STDCALL         
 bb_route_replace         /* Replace a route                   */
    ( bb_connect_t *,     /* -> connection description object  */
      char *,             /* String with old route description */
      char *              /* String with new route description */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILROUTELOAD  */

ExternC int4 STDCALL         
 bb_route_file            /* Specifies new Routing File        */
    ( bb_connect_t *,     /* -> connection description object  */
      char *              /* String with route description     */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILROUTELOAD  */

ExternC int4 STDCALL         
 bb_set_heart_beat        /* Set heart beat for output flush   */
    ( bb_connect_t *,     /* -> connection description object  */
      int4                /* New value in micsec (init 250000) */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_set_wait_select       /* Set select timeout value          */
    ( bb_connect_t *,     /* -> connection description object  */
      int4                /* New value in micsec (init 250000) */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_set_peer_flags        /* Set peer flags (see Peer)         */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Peer number                       */
      int4,               /* New value                         */
      char *              /* Password                          */
    );                    /* Return: Old value of flags        */
                          /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */ 
                          /*              ExitFAILSETPEERFLAGS */ 
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_set_send_accum        /* Set size of accumulation to send  */
    ( bb_connect_t *,     /* -> connection description object  */
      int4                /* New value (init 256)              */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_setuser               /* Set Network authorization ID      */
    ( bb_connect_t *,     /* -> connection description object  */
      int4 *              /* -> Network authorization ID       */
                          /*   (returned by bb_identify())     */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */

ExternC int4 STDCALL
 bb_sizeof_nextmsg        /* Returns size of buffer needed for next bb_rcvdata */
    ( bb_connect_t *);

ExternC int4 STDCALL         
 bb_stopall               /* Send request to stop all ticks    */
    ( bb_connect_t *      /* -> connection description object  */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_stopmntr              /* Send group request to stop ticks  */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Number of mon id's                */
      int4 *              /* -> array of monitor id's          */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILSTOPMNTR   */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */


ExternC int4 STDCALL
 bb_stopmntr_enhanced             /* Send group request to stop ticks    */
    (bb_connect_t *ApplMonitor,   /* -> connection description object    */
     int4          NumIds,        /* Number of mon id's                  */
     const int4   *Ids,           /* -> array of monitor id's            */
     int4          NumCategories, /* Number of categories                */
     const int4   *Categories     /* -> array of categories to stop      */
    );                            /* Normal return: request ID (>0)      */
                                  /* Error return:  ExitFAILCONNECTION   */
                                  /*                ExitFAILSTOPMNTR     */
                                  /*                ExitFAILMALLOC       */
                                  /*                ExitFAILCONNECT      */
                                  /*                ExitFAILROUTE        */
                                  /*                ExitFAILSEND         */
                                  /*                ExitFAILFLUSH        */
                                  /*            ExitFAILSENDBUFFERFULL   */

ExternC int4 STDCALL         
 bb_tickmntr              /* Send a group request for mon id's */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Number of security keys           */
      char *              /* -> security keys (32 bytes each)  */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILTICKMNTR   */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_tickmntr_typed        /* Send a group request for mon id's */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Number of security keys           */
      int4 *,             /* -> types of keys (TCM, CUSIP...)  */
      char *              /* -> security keys (32 bytes each)  */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILTICKMNTR   */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */
/***** BEGIN ENHANCED TICKER STREAM *********/
ExternC int4 STDCALL         
 bb_tickmntrx              /* Send a group request for mon id's */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Number of security keys           */
      char *,             /* -> security keys (32 bytes each)  */
      int4                /* options_flags                     */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILTICKMNTR   */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */

ExternC int4 STDCALL         
 bb_tickmntr_typedx       /* Send a group request for mon id's */
    ( bb_connect_t *,     /* -> connection description object  */
      int4,               /* Number of security keys           */
      int4 *,             /* -> types of keys (TCM, CUSIP...)  */
      char *,             /* -> security keys (32 bytes each)  */
      int4                /* options_flags                     */
    );                    /* Normal return: request ID (>0)    */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILTICKMNTR   */
                          /*                ExitFAILMALLOC     */
                          /*                ExitFAILCONNECT    */
                          /*                ExitFAILROUTE      */
                          /*                ExitFAILSEND       */
                          /*                ExitFAILFLUSH      */
                          /*            ExitFAILSENDBUFFERFULL */


ExternC int4 STDCALL
  bb_tickmntr_enhanced            /* Send a group request for mon id's      */
    (bb_connect_t *ApplMonitor,   /* -> connection description object       */
     int4          NumKeys,       /* Number of security keys                */
     const int4   *KeyType,       /* -> types of keys (TCM, CUSIP...)       */
     const char   *Key,           /* -> security keys (32 bytes each)       */
     int4          NumCategories, /* Number of subscription categories      */ 
     const int4   *Categories,    /* -> array of subscription categories    */
                                  /* (bCategoryCORE, bCategoryMARKET_DEPTH) */
     int4          OptionsFlags   /* Options Flags                          */
    );                            /* Normal return: request ID (>0)         */
                                  /* Error return:  ExitFAILCONNECTION      */
                                  /*                ExitFAILTICKMNTR        */
                                  /*                ExitFAILMALLOC          */
                                  /*                ExitFAILCONNECT         */
                                  /*                ExitFAILROUTE           */
                                  /*                ExitFAILSEND            */
                                  /*                ExitFAILFLUSH           */
                                  /*            ExitFAILSENDBUFFERFULL      */

/****** END ENHANCED TICKER STREAM **********/

ExternC int4 STDCALL         
 bb_trace_appl            /* Trace control for local appl      */
    ( bb_connect_t *,     /* -> connection description object  */
      int4                /* Trace type (see bTrace...)        */
    );                    /* Normal return: 0                  */
                          /* Error return:                     */

ExternC int4 STDCALL         
 bb_trace_comm            /* Trace control for Comm Server     */
    ( bb_connect_t *,     /* -> connection description object  */
      int4                /* Trace type (see bTrace...)        */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */

ExternC int4 STDCALL         
 bb_trace_db              /* Trace control for DB Server       */
    ( bb_connect_t *,     /* -> connection description object  */
      int4                /* Trace type (see bTrace...)        */
    );                    /* Normal return: 0                  */
                          /* Error return:  ExitFAILCONNECTION */
                          /*                ExitFAILMALLOC     */

ExternC int4 STDCALL
 bb_typeof_nextmsg        /* Returns type of message returned by next bb_rcvdata */
    ( bb_connect_t *);

ExternC char * STDCALL
 TimePrint                /* Converts time_t to date or time   */
                          /* mm/dd/yy format (if > 24 hours)   */
			  /* hh:mm:ss format (if <= 24 hours)  */
    ( time_t,             /* time_t to convert                 */
      char *              /* Output buffer to fill up          */
	  );              /* Normal return: -> to output buffer*/
                          /* Error return:                     */

ExternC int4 STDCALL
 bb_set_error_handler     /* Sets up a user defined function   */
                          /* to handle library's error messages*/
    ( void (*userFunc)(char *) /*-> to a user defined function */
    );                    /* Normal return: 0                  */
                          /* Error return:                     */
ExternC void STDCALL
 bb_tickiterator_init(
     bb_tickiterator *,   /* Pointer to tick iterator */
     bb_msg_tick_t *      /* Pointer to tick message to iterate */
     );

ExternC bb_decode_tick_t* STDCALL
 bb_tickiterator_getNextTick(
     bb_tickiterator *    /* Pointer to already initialized tick iterator */
     );                   /* returns NULL if there are no ticks, or returns a
                             pointer to the next available tick */

#define bb_tickiterator_getNumCC(ITER) (bb_tickiterator_getNumSmartTicks(ITER))

#define bb_tickiterator_getNextCC(ITER) (bb_tickiterator_getNextSmartTick(ITER))

ExternC int STDCALL
 bb_tickiterator_getNumSmartTicks(
     bb_tickiterator *    /* Pointer to already initialized tick iterator */
     );                   /* returns the number of smar ticks for the
                             current tick */
ExternC bb_decode_tick_data_t* STDCALL
 bb_tickiterator_getNextSmartTick(
     bb_tickiterator *    /* Pointer to already initialized tick iterator */
     );                   /* returns NULL if there are no smart ticks,
                             or returns a pointer to the next smart tick */

int4 STDCALL bb_cookie_flags (bb_connect_t *ApplMonitor, int4 cookie_flags);
int4 STDCALL bb_cookie_on (bb_connect_t *ApplMonitor, int4 cookie_number);
int4 STDCALL bb_cookie_off (bb_connect_t *ApplMonitor, int4 cookie_number);
int4 STDCALL bb_cookie_stat (bb_connect_t *ApplMonitor);

#ifdef INMS_REPORT
int4 STDCALL bb_report_INMS (bb_connect_t *ApplMonitor, int4 ReportType, int4 bbcSN, int4 bbcIP);
#endif
int4 STDCALL bb_report_sob (bb_connect_t *ApplMonitor, int4 ReportType, int4 SN, int4 iTrace);

#else

int4 STDCALL
 bb_accounting_control();    /* Control Accounting Server         */

int4 STDCALL
 bb_add_msg_handler ();      /* Register a handler for a message  */

int4 STDCALL
 bb_check_connection();      /* Returns status of asynch connect  */

ExternC int4 STDCALL
 bb_comm_parm_set();         /* Sets comm server parameters       */

bb_connect_t * STDCALL
 bb_connect         ();      /* Connect to local Comm Server      */

bb_connect_t * STDCALL
 bb_connect_asynch  ();      /* Connect asynchronously to Comm Srv*/

bb_connect_t * STDCALL
 bb_connect2        ();      /* As above, but no "I am alive"     */

bb_connect_t * STDCALL
 bb_connect_signal  ();      /* Reserved for internal usage       */

bb_connect_t * STDCALL
 bb_connect_remote_signal(); /* Reserved for internal usage       */

bb_connect_t * STDCALL
 bb_connect_remote  ();      /* Connect to remote Comm Server     */

bb_connect_t * STDCALL
 bb_connect_server  ();      /* Connect to remote Comm Server     */

bb_connect_t * STDCALL
 bb_connect_remote_asynch(); /* Connect async to remote Comm Srv  */

bb_connect_t * STDCALL
 bb_connect_server_asynch(); /* Connect async to remote Comm Srv  */
int4 STDCALL     
 bb_disconnect      ();      /* Disconnect from Comm Server       */

int4 STDCALL         
 bb_dispatch_msg    ();      /* Call msg handler after receive    */

int4 STDCALL         
 bb_echo_comm       ();      /* Comm Server echoes this back      */

int4 STDCALL
 bb_exit_comm       ();      /* Send a signal to exit Comm Server */

int4 STDCALL
 bb_exit_db         ();      /* Send a signal to exit DB Server   */

int4 STDCALL
 bb_identify        ();      /* Obtain display's network id       */

int4 STDCALL
 bb_getdata         ();      /* Send request to get field values  */

int4 STDCALL
 bb_getheader       ();      /* Group request for basic fields    */

int4 STDCALL
 bb_getheaderx       ();     /* Group request for basic fields with a few more options   */

int4 STDCALL
 bb_getheader_typed ();      /* Group request for basic fields    */

int4 STDCALL
 bb_getheader_typedx ();     /* Group request for basic fields with a few more options   */

int4 STDCALL
 bb_gethistory      ();      /* Send request to get history data  */

int4 STDCALL
 bb_gethistoryx     ();      /* Send request to get history data  */

int4 STDCALL
 bb_fullgethistory     ();   /* Send request to full get history data  */

int4 STDCALL
 bb_mgethistoryx     ();      /* Send request to multiple get history data  */

int4 STDCALL         
 bb_getsocket       ();      /* Get socket from connection object */

int4 STDCALL         
 bb_getticks        ();      /* Get most current ticks            */

int4 STDCALL         
 bb_gettimeseries   ();      /* Send request for time series data */

int4 STDCALL
 bb_gettimeseriesx  ();      /* Send request for time series data, enhanced */

int4 STDCALL
 bb_gettimezone     ();      /* Send request for users time zone, and start adjusting ticks*/

int4 STDCALL
 bb_enablefeature	();		/* Enables feaures like CCs and AllPrice */
						  
int4 STDCALL
 bb_enableccs		();		 /* Requests Condition Codes		  */					  

char* STDCALL
 bb_retrieveccstrings();	 /* Retrieves Condition Code sts array*/

char* STDCALL
 bb_retrieveecstrings();  	/* Retrieves Exchange Code charr array   */

void STDCALL
 bb_getversion      ();      /* return version number             */

int4 STDCALL
 bb_tklookup        ();      /* Request ticker symbol lookup      */

int4 STDCALL
 bb_load_datadict   ();      /* Load external field definitions   */

/*
**  DRQS 4351033 - fix put in to address longstanding bug in bb_field_info_t structure 
**  (bb_load_datadict()) - field mnemonics of 32 characters (i.e. ELECT_PLANT_IN_SERV_TO_TOT_ASSET) are 
**  truncated to first 31 characters to allow for \0.  new structure bb_field_infox_t 
**  (bb_load_datadictx()) changes FieldMnonmic to 33 byte array.  New function will allow backward 
**  compatibility for production code
*/

int4 STDCALL
 bb_load_datadictx   ();      /* Load external field definitions   */


int4 STDCALL
 bb_monitor_monid   ();      /* Enable tick stream for monid's    */

double STDCALL       
 bb_pricetodouble   ();      /* Convert string price into double  */

int4 STDCALL         
 bb_probe_network   ();      /* Send a probe message to route     */

int4 STDCALL          
 bb_rcvdata         ();      /* Receive message from Comm Server  */

int4 STDCALL          
 bb_report_comm     ();      /* Ask bbcomm to print stat data     */

int4 STDCALL          
 bb_report_db       ();      /* Ask local bbdb to print stat data */

int4 STDCALL          
 bb_resubscribe     ();      /* Resubscribe all monitorable items */

int4 STDCALL          
 bb_route_add       ();      /* Add new route to Comm Server      */

int4 STDCALL          
 bb_route_delete    ();      /* Delete a route from Comm Server   */

int4 STDCALL          
 bb_route_replace   ();      /*  Replace a route                  */

int4 STDCALL          
 bb_route_file      ();      /* Specifies new Routing File        */

int4 STDCALL          
 bb_set_heart_beat  ();      /* Set heart beat for output flush   */

int4 STDCALL          
 bb_set_wait_select ();      /* Set select timeout value          */

int4 STDCALL          
 bb_set_peer_flags  ();      /* Set peer flags (see Peer)         */

int4  STDCALL         
 bb_set_send_accum  ();      /* Set size of accumulation to send  */

int4 STDCALL          
 bb_setuser         ();      /* Set Network authorization ID      */

int4 STDCALL 
 bb_sizeof_nextmsg  ();      /* Returns size of buffer needed for next bb_rcvdata */

int4 STDCALL          
 bb_stopall         ();      /* Send request to stop all ticks    */

int4 STDCALL          
 bb_stopmntr        ();      /* Send group request to stop ticks  */

int4 STDCALL          
 bb_stopmntr_enhanced  ();   /* Send group request to stop ticks  */

int4 STDCALL          
 bb_tickmntr        ();      /* Send a group request for mon id's */

int4 STDCALL          
 bb_tickmntr_enhanced  ();   /* Send a group request asking for market depth for mon id's */

int4 STDCALL          
 bb_tickmntr_typed  ();      /* Send a group request for mon id's */

int4 STDCALL          
 bb_tickmntrx       ();      /* Send a group enhanced request for mon id's */

int4 STDCALL          
 bb_tickmntr_typedx ();      /* Send a group enhanced request for mon id's */

int4 STDCALL          
 bb_trace_appl      ();      /* Trace control for local appl      */

int4 STDCALL          
 bb_trace_comm      ();      /* Trace control for Comm Server     */

int4 STDCALL          
 bb_trace_db        ();      /* Trace control for DB Server       */

int4 STDCALL
 bb_sizeof_nextmsg  ();      /* Returns size of buffer needed for next bb_rcvdata */

char * STDCALL 
 TimePrint          ();      /* Converts time_t to date or time   */

int4 STDCALL 
 bb_set_error_handler ();    /* Sets up a user's error handler    */

int4 STDCALL bb_cookie_flags();
int4 STDCALL bb_cookie_on();
int4 STDCALL bb_cookie_off();
int4 STDCALL bb_cookie_stats();


#endif

#endif /* __BBAPI_ */



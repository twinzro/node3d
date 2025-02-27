#include "stdafx.h"
#include "MSharedCommandTable.h"
#include "MCommandManager.h"

#include "MMatchChannel.h"
#include "MMatchObject.h"
#include "MMatchGlobal.h"

void MAddSharedCommandTable(MCommandManager* pCommandManager, int nSharedType)
{
	BEGIN_CMD_DESC(pCommandManager);

	C(MC_LOCAL_INFO, "Local.Info", "Local information", MCDT_LOCAL)
	C(MC_LOCAL_ECHO, "Local.Echo", "Local echo test", MCDT_LOCAL)
		P(MPT_STR, "Message");
	C(MC_LOCAL_LOGIN, "Local.Login", "Local Login", MCDT_LOCAL)
		P(MPT_UID, "uidComm")
		P(MPT_UID, "uidPlayer")

	C(MC_HELP, "Help", "This command", MCDT_LOCAL);
	C(MC_VERSION, "Version", "Version description", MCDT_LOCAL);

	C(MC_DEBUG_TEST, "DebugTest", "Debug Test", MCDT_MACHINE2MACHINE);

	C(MC_NET_ENUM, "Net.Enum", "Enum server list", MCDT_LOCAL);
	C(MC_NET_CONNECT, "Net.Connect", "Connect to server", MCDT_LOCAL)
		P(MPT_STR, "Address");
	C(MC_NET_DISCONNECT, "Net.Disconnect", "Disconnect to server", MCDT_LOCAL);
	C(MC_NET_CLEAR, "Net.Clear", "Clear Connection", MCDT_LOCAL);
		P(MPT_UID, "uid")
	C(MC_NET_CHECKPING, "Net.CheckPing", "Check ping time", MCDT_LOCAL);
		P(MPT_UID, "uid")
	C(MC_NET_PING, "Net.Ping", "Ping", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED)
		P(MPT_UINT, "TimeStamp")
	C(MC_NET_PONG, "Net.Pong", "Pong", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED)
		P(MPT_UINT, "TimeStamp")
	
	C(MC_HSHIELD_PING, "HShield.Ping", "Ping", MCDT_MACHINE2MACHINE | MCCT_HSHIELD_ENCRYPTED)
		P(MPT_UINT, "TimeStamp")
		P(MPT_BLOB, "CRCInfo")
	C(MC_HSHIELD_PONG, "HShield.Pong", "Pong", MCDT_MACHINE2MACHINE | MCCT_HSHIELD_ENCRYPTED)
		P(MPT_UINT, "TimeStamp")
		P(MPT_BLOB, "AckMsg")

	C(MC_NET_ONCONNECT, "Net.OnConnect", "On Connect", MCDT_LOCAL);
	C(MC_NET_ONDISCONNECT, "Net.OnDisConnect", "On Disconnect", MCDT_LOCAL);
	C(MC_NET_ONERROR, "Net.OnError", "On Error", MCDT_LOCAL);
		P(MPT_INT, "ErrorCode")

	C(MC_NET_CONNECTTOZONESERVER, "Net.ConnectToZoneServer", "Connect to zone-server", MCDT_LOCAL)
	

	C(MC_NET_REQUEST_INFO, "Net.RequestInfo", "Request Net information", MCDT_MACHINE2MACHINE)
	C(MC_NET_RESPONSE_INFO, "Net.ResponseInfo", "Response Net information", MCDT_MACHINE2MACHINE)
		P(MPT_STR, "Information");
	C(MC_NET_ECHO, "Net.Echo", "Echo test", MCDT_MACHINE2MACHINE)
		P(MPT_STR, "Message");

	C(MC_MATCH_ANNOUNCE, "Match.Announce", "Announce Server Message", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P(MPT_UINT, "Type")
		P(MPT_STR, "Msg");

	// MatchServer, Client 공용 명령어
	if(nSharedType&MSCT_MATCHSERVER || nSharedType&MSCT_CLIENT){
		C(MC_CLOCK_SYNCHRONIZE, "Clock.Synchronize", "Synchronize Clock", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "GlobalClock(msec)");
		C(MC_MATCH_LOGIN, "Match.Login", "Login Match Server", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "UserID");
			P(MPT_STR, "Password");
			P(MPT_INT, "CommandVersion");
			P(MPT_UINT, "nChecksumPack");
			P(MPT_BLOB,	"EncryptMD5Value");
		C(MC_MATCH_RESPONSE_LOGIN, "Match.ResponseLogin", "Response Login", MCDT_MACHINE2MACHINE)
			P(MPT_INT,	"Result")
			P(MPT_STR,	"ServerName")
			P(MPT_CHAR, "ServerMode")
			P(MPT_STR,	"AccountID")
			P(MPT_UCHAR, "UGradeID")
			P(MPT_UCHAR, "PGradeID")
			P(MPT_UID,	"uidPlayer")
			P(MPT_BOOL,	"bEnabledSurvivalMode")
			P(MPT_BOOL,	"bEnabledDuelTournament")
			P(MPT_BLOB,	"EncryptMsg")		// HShield에서 사용하는 암호메세지

			/* ServerKeeper에서도 사용을 하기위해서 외부로 옮김. - by 추교성.
		C(MC_MATCH_ANNOUNCE, "Match.Announce", "Announce Server Message", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "Type")
			P(MPT_STR, "Msg");
			*/
		C(MC_MATCH_RESPONSE_RESULT, "Match.Response.Result", "Response Result", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
		C(MC_MATCH_LOGIN_NETMARBLE, "Match.LoginNetmarble", "Login from Netmarble", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "AuthCookie");
			P(MPT_STR, "DataCookie");
			P(MPT_STR, "CPCookie");
			P(MPT_STR, "SpareParam");
			P(MPT_INT, "CommandVersion");
			P(MPT_UINT, "nChecksumPack");
		C(MC_MATCH_LOGIN_NETMARBLE_JP, "Match.LoginNetmarbleJP", "Login from Netmarble Japan", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "LoginID");
			P(MPT_STR, "LoginPW");
			P(MPT_INT, "CommandVersion");
			P(MPT_UINT, "nChecksumPack");
		C(MC_MATCH_LOGIN_FROM_DBAGENT, "Match.LoginFromDBAgent", "Login from DBAgent", MCDT_LOCAL)
			P(MPT_UID, "CommUID");
			P(MPT_STR, "LoginID");
			P(MPT_STR, "Name");
			P(MPT_INT, "Sex");
			P(MPT_BOOL, "bFreeLoginIP")
			P(MPT_UINT, "nChecksumPack")
		C(MC_MATCH_LOGIN_FROM_DBAGENT_FAILED, "Match.LoginFailedFromDBAgent", "Login Failed from DBAgent", MCDT_LOCAL)
			P(MPT_UID, "CommUID");
			P(MPT_INT, "Result")
		C(MC_MATCH_FIND_HACKING, "Match.FinH", "FinH", MCDT_MACHINE2MACHINE)
		C( MC_MATCH_DISCONNMSG, "MC_MATCH_DISCONNMSG", "disconnect reason", MCDT_MACHINE2MACHINE )
			P(MPT_UINT, "message id")
		C( MC_MATCH_LOGIN_NHNUSA, "MC_MATCH_LOGIN_NHNUSA", "Login from nhn usa.", MCDT_MACHINE2MACHINE );
			P(MPT_STR, "UserID" );
			P(MPT_STR, "szAuthStr");
			P(MPT_INT, "CommandVersion");
			P(MPT_UINT, "nChecksumPack");
			P(MPT_BLOB,	"EncryptMD5Value");
		C( MC_MATCH_LOGIN_GAMEON_JP, "MC_MATCH_LOGIN_GAMEON_JP", "Login from GameOn Japan", MCDT_MACHINE2MACHINE );
			P(MPT_STR, "szString");
			P(MPT_STR, "szStatIndex");
			P(MPT_INT, "CommandVersion");
			P(MPT_UINT, "nChecksumPack");
			P(MPT_BLOB,	"EncryptMD5Value");

		C(MC_MATCH_OBJECT_CACHE, "Match.ObjectCache", "Match Object Cache", MCDT_MACHINE2MACHINE)
			P(MPT_UCHAR, "Type")
			P(MPT_BLOB, "ObjectCache");
		C(MC_MATCH_BRIDGEPEER, "Match.BridgePeer", "Match BridgePeer", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED)
			P(MPT_UID, "uidPlayer")
			P(MPT_UINT, "dwIP")
			//P(MPT_STR, "strIP")
			P(MPT_UINT, "nPort")
		C(MC_MATCH_BRIDGEPEER_ACK, "Match.BridgePeerACK", "ACK for BridgePeer", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_INT, "nCode")

		C(MC_MATCH_REQUEST_RECOMMANDED_CHANNEL, "MatchServer.RequestRecommandedChannel", "Request recommanded channel", MCDT_MACHINE2MACHINE)
        C(MC_MATCH_RESPONSE_RECOMMANDED_CHANNEL, "MatchServer.ResponseRecommandedChannel", "Response recommanded channel", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid")
		C(MC_MATCH_CHANNEL_REQUEST_JOIN, "Channel.Join", "Join a Channel", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidChannel")
		C(MC_MATCH_CHANNEL_RESPONSE_JOIN, "Channel.ResponseJoin", "Response Join a Channel", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChannel")
			P(MPT_INT, "ChannelType")			// 접속한 채널 타입
			P(MPT_STR, "ChannelName")			// 접속한 채널 이름
			P(MPT_BOOL, "EnableInterface");		// 로비 인터페이스 사용 여부
		C(MC_MATCH_CHANNEL_REQUEST_JOIN_FROM_NAME, "Channel.RequestJoinFromName", "Join a Channel From Name", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			//P(MPT_INT, "nChannelType")
			P_MINMAX(MPT_INT, "nChannelType", 0, (MCHANNEL_TYPE_MAX-1))
			P(MPT_STR, "ChannelName")
		C(MC_MATCH_CHANNEL_LEAVE, "Channel.Leave", "Leave Channel", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidChannel")
		C(MC_MATCH_CHANNEL_LIST_START, "Channel.ListStart", "Channel List transmit start", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P_MINMAX(MPT_INT, "nChannelType", 0, (MCHANNEL_TYPE_MAX-1))
		C(MC_MATCH_CHANNEL_LIST_STOP, "Channel.ListStop", "Channel List transmit stop", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
		C(MC_MATCH_CHANNEL_LIST, "Channel.List", "Channel List", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "ChannelList");

		C(MC_MATCH_CHANNEL_REQUEST_CHAT, "Channel.Request.Chat", "Request Chat to Channel", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidChannel")
			P(MPT_STR, "Chat");

		C(MC_MATCH_CHANNEL_CHAT, "Channel.Chat", "Chat to Channel", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChannel")
			P(MPT_STR, "PlayerName")
			P(MPT_STR, "Chat");
			P(MPT_INT, "nGrade")

		C(MC_MATCH_CHANNEL_DUMB_CHAT, "Channel.PlayerDumb", "Notify to Dumb Player", MCDT_MACHINE2MACHINE)

		C(MC_MATCH_CHANNEL_REQUEST_RULE, "Channel.Request.Rule", "Request the Channel Rule", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChannel")
		C(MC_MATCH_CHANNEL_RESPONSE_RULE, "Channel.Response.Rule", "Response the Channel Rule", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChannel")
			P(MPT_STR, "RuleName")

		C(MC_MATCH_CHANNEL_REQUEST_ALL_PLAYER_LIST, "Channel.RequestAllPlayerList", "Request Channel All Player List", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidChannel")
			P(MPT_UINT, "PlaceFilter")		// 로비, 대기방, 게임중 인 플레이어들에 대한 필터
			P(MPT_UINT, "Options")			// 0 - 일반, 1 - 클랜에 가입되지 않은 사람, 2 - 내클랜만
		C(MC_MATCH_CHANNEL_RESPONSE_ALL_PLAYER_LIST, "Channel.ResponseAllPlayerList", "Response Channel All Player List", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChannel")
			P(MPT_BLOB, "PlayerList")

		C(MC_MATCH_STAGE_CREATE, "Stage.Create", "Create a Stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
			P(MPT_STR, "StageName")
			P(MPT_BOOL, "IsPrivate")
			P(MPT_STR, "Password")
		C(MC_MATCH_REQUEST_STAGE_JOIN, "Stage.RequestJoin", "Request Join a Stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidStage")
		C(MC_MATCH_REQUEST_PRIVATE_STAGE_JOIN, "Stage.RequestPrivateJoin", "Request Join a Private Stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidStage")
			P(MPT_STR, "Password")

		C(MC_MATCH_STAGE_JOIN, "Stage.Join", "Join a Stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidStage")
			P(MPT_UINT, "nRoomNo")
			P(MPT_STR, "StageName")
		C(MC_MATCH_STAGE_LEAVE, "Stage.Leave", "Leave Stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			// P(MPT_UID, "uidStage") // 서버에 있는 데이터를 사용한다.
		C(MC_MATCH_STAGE_REQUEST_PLAYERLIST, "Stage.Request.PlayerList", "Requst PlayerList from the Stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
		C(MC_MATCH_STAGE_FOLLOW, "Stage.Follow", "Follow User to Stage", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "strTarget")
		C(MC_MATCH_RESPONSE_STAGE_FOLLOW, "Stage.Response.Follow", "Response Follow User to Stage", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")

		C(MC_MATCH_RESPONSE_STAGE_JOIN, "Stage.ResponseJoin", "Response Join a Stage", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")

		C(MC_MATCH_STAGE_REQUIRE_PASSWORD, "Stage.RequirePassword", "Require password", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_STR, "StageName")


		C(MC_MATCH_REQUEST_GAME_INFO, "RequestGameInfo", "Request Game Info", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
			P(MPT_UID, "uidStage")
		C(MC_MATCH_RESPONSE_GAME_INFO, "ResponseGameInfo", "Response Game Info", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_BLOB, "GameInfo")
			P(MPT_BLOB, "RuleInfo")
			P(MPT_BLOB, "PlayerInfo")
		C(MC_MATCH_RESPONSE_STAGE_CREATE, "Stage.ResponseCreate", "Response Create a Stage", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")

		C(MC_MATCH_STAGE_REQUEST_ENTERBATTLE, "Stage.Request.EnterBattle", "Request Enter Stage Battle", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidStage")
		C(MC_MATCH_STAGE_ENTERBATTLE, "Stage.EnterBattle", "Enter Stage Battle", MCDT_MACHINE2MACHINE)
			//P(MPT_UID, "uidPlayer")
			//P(MPT_UID, "uidStage")
			P(MPT_UCHAR, "Param")
			P(MPT_BLOB, "CharData")

		C(MC_MATCH_STAGE_LEAVEBATTLE_TO_SERVER, "Stage.LeaveBattle.To.Server", "Leave Stage Battle To Server", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_BOOL, "bMenuLeaveBattle")

		C(MC_MATCH_STAGE_LEAVEBATTLE_TO_CLIENT, "Stage.LeaveBattle.To.Client", "Leave Stage Battle To Client", MCDT_MACHINE2MACHINE)
			P(MPT_UID,  "uidPlayer")
			P(MPT_BOOL, "IsRelayMapPlay")

		C(MC_MATCH_STAGE_START, "Stage.Start", "Start Stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidStage")
			P(MPT_INT, "nCountdown")
			
		C(MC_MATCH_STAGE_MAP, "Stage.Map", "Change Map", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_STR, "MapName")
	
		C(MC_MATCH_STAGE_RELAY_MAP_ELEMENT_UPDATE, "Stage.RelayMapElement", "RelayMapElement Update", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_INT, "RelayMapType")
			P(MPT_INT, "RelayMapRepeatCount")
		C(MC_MATCH_STAGE_RELAY_MAP_INFO_UPDATE, "Stage.RelayMapInfo", "RelayMapInfo Update", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_INT, "RelayMapType")
			P(MPT_INT, "RelayMapRepeatCount")
			P(MPT_BLOB, "RelayMapList")

			C(MC_MATCH_STAGE_CHAT, "Stage.Chat", "Chat to Stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidStage")
			P(MPT_STR, "Chat")

		C(MC_MATCH_STAGE_REQUEST_QUICKJOIN, "Stage.RequestQuickJoin", "Stage Request QuickJoin", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_BLOB, "Param")
		C(MC_MATCH_STAGE_RESPONSE_QUICKJOIN, "Stage.ResponseQuickJoin", "Stage Response QuickJoin", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
			P(MPT_UID, "uidStage")
		C(MC_MATCH_STAGE_GO, "Stage.StageGo", "Stage Go", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "RoomNo")


		C(MC_MATCH_STAGE_PLAYER_STATE, "Stage.State", "Change State In Stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidStage")
			P_MINMAX(MPT_INT, "nState", 0, (MOSS_END-1))
		C(MC_MATCH_STAGE_TEAM, "Stage.Team", "Change Team", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidStage")
			P(MPT_UINT, "nTeam")
		C(MC_MATCH_STAGE_MASTER, "Stage.Master", "Set Master", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_UID, "uidPlayer")
		C(MC_MATCH_STAGE_LIST_START, "Stage.ListStart", "Stage List transmit start", MCDT_MACHINE2MACHINE) 
		C(MC_MATCH_STAGE_LIST_STOP, "Stage.ListStop", "Stage List transmit stop", MCDT_MACHINE2MACHINE) 
		C(MC_MATCH_STAGE_LIST, "Stage.List", "Stage List", MCDT_MACHINE2MACHINE) 
			P(MPT_CHAR, "PrevStageListCount")
			P(MPT_CHAR, "NextStageListCount")
			P(MPT_BLOB, "StageList");
		C(MC_MATCH_REQUEST_STAGE_LIST, "Stage.RequestStageList", "Request Stage List", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidChannel")
			P(MPT_INT, "StageCursor")
			
		C(MC_MATCH_CHANNEL_REQUEST_PLAYER_LIST, "Channel.RequestPlayerList", "Request Channel Player List", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidChannel")
			P(MPT_INT, "PlayerListPage")
		C(MC_MATCH_CHANNEL_RESPONSE_PLAYER_LIST, "Channel.ResponsePlayerList", "Response Channel Player List", MCDT_MACHINE2MACHINE)
		//	P(MPT_UID, "uidChannel")
			P(MPT_UCHAR, "TotalPlayerCount")
			P(MPT_UCHAR, "PlayerListPage")
			P(MPT_BLOB, "PlayerList")

		C(MC_MATCH_REQUEST_STAGESETTING, "Stage.RequestStageSetting", "Request stage setting", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
		C(MC_MATCH_RESPONSE_STAGESETTING, "Stage.ResponseStageSetting", "Response stage setting", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_BLOB, "StageSetting")
			P(MPT_BLOB, "CharSetting")
			P(MPT_INT, "StageState")
			P(MPT_UID, "uidMaster")

		C(MC_MATCH_STAGESETTING, "Stage.StageSetting", "Setting up Stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidStage")
			P(MPT_BLOB, "StageSetting")

		C(MC_MATCH_STAGE_LAUNCH, "Stage.Launch", "Launch Stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_STR, "MapName")

		C(MC_MATCH_STAGE_RELAY_LAUNCH, "Stage.Relay.Launch", "Relay Launch Stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_STR, "MapName")
			P(MPT_BOOL, "BeIgnore")


		C(MC_MATCH_STAGE_FINISH_GAME, "Stage.Finish", "Finish Stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_BOOL, "IsRelayMapUnFinish")

		C(MC_MATCH_REQUEST_PEERLIST, "Stage.RequestPeerList", "Request peer list", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UID, "uidStage")
		C(MC_MATCH_RESPONSE_PEERLIST, "Stage.ResponsePeerList", "Response peer list", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_BLOB, "PeerList")
		C(MC_MATCH_LOADING_COMPLETE, "Loading.Complete", "Loading Complete", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "ChrUID")
			P(MPT_INT, "Percent")
		C(MC_MATCH_REQUEST_PEER_RELAY, "Match.RequestPeerRelay", "Request Peer Relay", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "PlayerUID");
			P(MPT_UID, "PeerCharUID");
		C(MC_MATCH_RESPONSE_PEER_RELAY, "Match.ResponsePeerRelay", "Response Peer Relay", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "PeerCharUID");
		C(MC_MATCH_GAME_ROUNDSTATE, "Stage.RoundState", "Sync State of a StageRound", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_INT, "nRound");
			P(MPT_INT, "nState");
			P(MPT_INT, "nArg");
		C(MC_MATCH_GAME_KILL, "Game.Kill", "Object Die", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "Attacker");
		C(MC_MATCH_GAME_REQUEST_SPAWN, "Game.Requst.Spawn", "Request Spawn", MCDT_MACHINE2MACHINE);
			P(MPT_UID, "CharUID");
			P(MPT_POS, "Position");
			P(MPT_DIR, "Direction");
		C(MC_MATCH_GAME_RESPONSE_SPAWN, "Game.Response.Spawn", "Response Spawn", MCDT_MACHINE2MACHINE);
			P(MPT_UID, "CharUID");
			P(MPT_SVECTOR, "Position");
			P(MPT_SVECTOR, "Direction");

		C(MC_MATCH_GAME_LEVEL_UP, "Game.LevelUp", "Game.LevelUp", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "Player");
			P(MPT_INT, "Level");
		C(MC_MATCH_GAME_LEVEL_DOWN, "Game.LevelDown", "Game.LevelDown", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "Player");
			P(MPT_INT, "Level");
		C(MC_MATCH_GAME_DEAD, "Game.Dead", "Game.Dead", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "Attacker");
			P(MPT_UINT, "AttackerArg");		// Exp | 경험치퍼센트
			P(MPT_UID, "Victim");
			P(MPT_UINT, "VictimArg");		// Exp | 경험치퍼센트
		C(MC_MATCH_GAME_TEAMBONUS, "Game.TeamBonus", "Game.TeamBonus", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "CharUID");
			P(MPT_UINT, "ExpArg");			// Exp | 경험치퍼센트

		C(MC_MATCH_GAME_REQUEST_TIMESYNC, "Game.RequestTimeSync", "Request TimeSync for Game", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "LocalTimeStamp");
		C(MC_MATCH_GAME_RESPONSE_TIMESYNC, "Game.ResponseTimeSync", "Response TimeSync for Game", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "LocalTimeStamp");
			P(MPT_UINT, "GlobalTimeStamp");
		C(MC_MATCH_GAME_REPORT_TIMESYNC, "Game.ReportTimeSync", "Report TimeSync for Verify SpeedHack", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "LocalTimeStamp");
			P(MPT_UINT, "MemoryChecksum");

		C(MC_MATCH_STAGE_REQUEST_FORCED_ENTRY, "Stage.RequestForcedEntry", "Request Forced Entry", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar");
			P(MPT_UID, "uidStage");
		C(MC_MATCH_STAGE_RESPONSE_FORCED_ENTRY, "Stage.ResponseForcedEntry", "Response Forced Entry", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result");

		C(MC_MATCH_ROUND_FINISHINFO, "Stage.RoundFinishInfo", "Update Round Finished Info", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_UID, "uidChar")
			P(MPT_BLOB, "PeerInfo")
			P(MPT_BLOB, "KillInfo")

		C(MC_MATCH_NOTIFY, "Match.Notify", "Notify Message", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "nMsgID")

		// 의사소통 관련
		C(MC_MATCH_USER_WHISPER, "Match.Whisper", "Whisper Message to a User", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "SenderName")
			P(MPT_STR, "TargetName")
			P(MPT_STR, "Message")
		C(MC_MATCH_USER_WHERE, "Match.Where", "Ask Player Location", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "TargetName")			
		C(MC_MATCH_USER_OPTION, "Match.UserOption", "Set User Option", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "OptionFlags")
		C(MC_MATCH_CHATROOM_CREATE, "ChatRoom.Create", "Create a ChatRoom", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_STR, "ChatRoomName")
		C(MC_MATCH_CHATROOM_JOIN, "ChatRoom.Join", "Join a ChatRoom", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "PlayerName")
			P(MPT_STR, "ChatRoomName")
		C(MC_MATCH_CHATROOM_LEAVE, "ChatRoom.Leave", "Leave a Chat Room", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "PlayerName")
			P(MPT_STR, "ChatRoomName")
		C(MC_MATCH_CHATROOM_SELECT_WRITE, "ChatRoom.SelectWrite", "Select ChatRoom to Write", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "ChatRoomName")
		C(MC_MATCH_CHATROOM_INVITE, "ChatRoom.Invite", "Invite a user to ChatRoom", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "SenderName")
			P(MPT_STR, "TargetName")
			P(MPT_STR, "ChatRoomName")
		C(MC_MATCH_CHATROOM_CHAT, "ChatRoom.Chat", "ChatRoom Chat", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "ChatRoomName")
			P(MPT_STR, "SenderName")
			P(MPT_STR, "Message")
		
		// 캐릭터 정보 관련
		C(MC_MATCH_REQUEST_ACCOUNT_CHARLIST, "Match.RequestAccountCharList", "Request Account Character List", MCDT_MACHINE2MACHINE)
//			P(MPT_BLOB, "SKey")
			P(MPT_BLOB, "EMsg")
		C(MC_MATCH_RESPONSE_ACCOUNT_CHARLIST, "Match.ResponseAccountCharList", "Response Account Character List", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "CharList")
		C(MC_MATCH_REQUEST_ACCOUNT_CHARINFO, "Match.RequestAccountCharInfo", "Request Account Character Info", MCDT_MACHINE2MACHINE)
			P_MINMAX(MPT_CHAR, "CharNum", 0, MAX_CHAR_COUNT)
		C(MC_MATCH_RESPONSE_ACCOUNT_CHARINFO, "Match.ResponseAccountCharInfo", "Response Account Character Info", MCDT_MACHINE2MACHINE)
			P(MPT_CHAR, "CharNum")
			P(MPT_BLOB, "CharInfo")
		C(MC_MATCH_REQUEST_SELECT_CHAR, "Match.RequestSelectChar", "Request Select Character", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid")
			P_MINMAX(MPT_UINT, "CharIndex", 0, MAX_CHAR_COUNT-1)
		C(MC_MATCH_RESPONSE_SELECT_CHAR, "Match.ResponseSelectChar", "Response Select Character", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
			P(MPT_BLOB, "CharInfo")
			//버프정보임시주석 P(MPT_BLOB, "CharBuffInfo")
			P(MPT_BLOB, "CharExtraInfo");			

		C(MC_MATCH_REQUEST_MYCHARINFO, "Match.RequestCharInfo", "Request Character Info", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid")
			P(MPT_UINT, "CharIndex")
		C(MC_MATCH_RESPONSE_MYCHARINFO, "Match.ResponseCharInfo", "Response Character Info", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid")
			P(MPT_BLOB, "CharInfo")
		C(MC_MATCH_REQUEST_DELETE_CHAR, "Match.RequestDeleteChar", "Request Delete Character", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid")
			P_MINMAX(MPT_UINT, "CharIndex", 0, MAX_CHAR_COUNT-1)
			P(MPT_STR, "CharName")
		C(MC_MATCH_RESPONSE_DELETE_CHAR, "Match.ResponseDeleteChar", "Response Delete Character", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
		C(MC_MATCH_REQUEST_CREATE_CHAR, "Match.RequestCreateChar", "Request Create Character", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid")
			P_MINMAX(MPT_UINT, "CharIndex", 0, MAX_CHAR_COUNT-1)
			P(MPT_STR, "Name")
			P(MPT_UINT, "Sex")
			P(MPT_UINT, "Hair")
			P(MPT_UINT, "Face")
			P(MPT_UINT, "Costume")
		C(MC_MATCH_RESPONSE_CREATE_CHAR, "Match.ResponseCreateChar", "Response Create Character", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")		// 결과
			P(MPT_STR, "CharName")		// 만들어진 캐릭터 이름
		C(MC_MATCH_REQUEST_COPY_TO_TESTSERVER, "Match.RequestCopyToTestServer", "Request Copy To TestServer", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
		C(MC_MATCH_RESPONSE_COPY_TO_TESTSERVER, "Match.ResponseCopyToTestServer", "Response Copy To TestServer", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
		C(MC_MATCH_REQUEST_CHARINFO_DETAIL, "Match.RequestCharInfoDetail", "Request Character Info Detail", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid")
			P(MPT_STR, "CharName")
		C(MC_MATCH_RESPONSE_CHARINFO_DETAIL, "Match.ResponseCharInfoDetail", "Response Character Info Detail", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "CharInfo")

		// 아이템 관련
		C(MC_MATCH_REQUEST_SIMPLE_CHARINFO, "Match.RequestSimpleCharInfo", "Request Simple CharInfo", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid")
		C(MC_MATCH_RESPONSE_SIMPLE_CHARINFO, "Match.ResponseSimpleCharInfo", "Response Simple CharInfo", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid")
			P(MPT_BLOB, "SimpleCharInfo")
		C(MC_MATCH_REQUEST_MY_SIMPLE_CHARINFO, "Match.RequestMySimpleCharInfo", "Request My Simple CharInfo", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
		C(MC_MATCH_RESPONSE_MY_SIMPLE_CHARINFO, "Match.ResponseMySimpleCharInfo", "Response My Simple CharInfo", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "MySimpleCharInfo")

		C(MC_MATCH_REQUEST_BUY_ITEM, "Match.RequestBuyItem", "Request Buy Item", MCDT_MACHINE2MACHINE)
			P(MPT_UID,  "uidChar")
			P(MPT_UINT, "ItemID")
			P(MPT_UINT, "ItemCount")

		C(MC_MATCH_RESPONSE_BUY_ITEM, "Match.ResponseBuyItem", "Response Buy Item", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "result")

		C(MC_MATCH_REQUEST_SELL_ITEM, "Match.RequestSellItem", "Request Sell Item", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
			P(MPT_UID, "uidItem")
			P(MPT_UINT, "ItemCount")

		C(MC_MATCH_RESPONSE_SELL_ITEM, "Match.ResponseSellItem", "Response Sell Item", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "result")


		C(MC_MATCH_REQUEST_SHOP_ITEMLIST, "Match.RequestShopItemList", "Request Shop Item List", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid")
			P(MPT_INT, "FirstItemIndex")
			P(MPT_INT, "ItemCount");
		C(MC_MATCH_RESPONSE_SHOP_ITEMLIST, "Match.ResponseShopItemList", "Response Shop Item List", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "GambleItemList");		// 위치 바꿈 - by SungE 2007-06-20
			P(MPT_BLOB, "ItemList");			

		C(MC_MATCH_REQUEST_CHARACTER_ITEMLIST, "Match.RequestCharacterItemList", "Request Character Item List", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid");

		C(MC_MATCH_REQUEST_CHARACTER_ITEMLIST_FORCE, "Match.RequestCharacterItemListForce", "Request Character Item List NonPrevent Duplicate Send", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid");

		C(MC_MATCH_RESPONSE_CHARACTER_ITEMLIST, "Match.ResponseCharacterItemList", "Response Character Item List", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Bounty")
			P(MPT_BLOB, "EquipItemList")		// 장비하고 있는 아이템
			P(MPT_BLOB, "ItemList");			// 장비한 아이템까지 포함한 갖고있는 아이템
			P(MPT_BLOB, "GambleItemList")		// 겜블 아이템 목록
			
		C(MC_MATCH_REQUEST_EQUIP_ITEM, "MatchRequestEquipItem", "Request Equip Item", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
			P(MPT_UID, "uidItem")		// 가진 아이템 UID
			P_MINMAX(MPT_UINT, "EquipmentSlot", 0, MMCIP_END-1)		// 장비하고자 하는 부위
		C(MC_MATCH_RESPONSE_EQUIP_ITEM, "MatchResponseEquipItem", "Response Equip Item", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
		C(MC_MATCH_REQUEST_TAKEOFF_ITEM, "MatchRequestTakeoffItem", "Request Takeoff Item", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid")
			P_MINMAX(MPT_UINT, "EquipmentSlot", 0, MMCIP_END-1)		// 벗고자 하는 부위
		C(MC_MATCH_RESPONSE_TAKEOFF_ITEM, "MatchResponseTakeoffItem", "Response Takeoff Item", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
		C(MC_MATCH_REQUEST_ACCOUNT_ITEMLIST, "Match.RequestAccountItemList", "Request Account Item List", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uid")
		C(MC_MATCH_RESPONSE_ACCOUNT_ITEMLIST, "Match.ResponseAccountItemList", "Response Account Item List" , MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "ItemList")
		C(MC_MATCH_REQUEST_BRING_ACCOUNTITEM, "Match.RequestBringAccountItem", "Request Bring Account Item", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
			P(MPT_INT, "AIID")
			P(MPT_INT, "ItemID")
			P(MPT_INT, "ItemCount")

		C(MC_MATCH_RESPONSE_BRING_ACCOUNTITEM, "Match.ResponseBringAccountItem", "Response Bring Account Item", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
		C(MC_MATCH_REQUEST_BRING_BACK_ACCOUNTITEM, "Match.RequestBringBackAccountItem", "Request BringBack Account Item", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
			P(MPT_UID, "uidItem")		// 가진 아이템 UID
			P(MPT_UINT, "ItemCount")

		C(MC_MATCH_RESPONSE_BRING_BACK_ACCOUNTITEM, "Match.ResponseBringBackAccountItem", "Response BringBack Account Item", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
		C(MC_MATCH_EXPIRED_RENT_ITEM, "Match.ExpiredRentItem", "Match.Expired Rent Item", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "ItemIDList")	// 기간 만료된 아이템 목록
		C(MC_MATCH_REQUEST_GAMBLE, "Match.ItemGamble", "Request Item Gamble", MCDT_MACHINE2MACHINE)	
			P(MPT_UID, "uidItem")		// 가진 뽑기 아이템 UID
		C(MC_MATCH_RESPONSE_GAMBLE, "Match.GambleResultItem", "Response Item Gamble Result Item", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "ItemID")				// 뽑기로 나온 아이템 ID
			P(MPT_UINT, "ItemCnt")
			P(MPT_UINT, "RentHourPeriod * 60")	// 뽑기로 나온 아이템 최대사용기간(분단위)

		C(MC_MATCH_REWARD_BATTLE_TIME, "Match.Reward BattleTime", "Reward Item", MCDT_MACHINE2MACHINE)
			P(MPT_UID,	"uidChar")
			P(MPT_STR,	"Name")
			P(MPT_STR,	"ResetDesc")
			P(MPT_UINT, "RewardItemID")
			P(MPT_UINT, "RewardItemCnt")
			P(MPT_UINT, "RentHourPeriod * 60")
			P(MPT_INT,	"RemainRewardCount");

		C(MC_MATCH_REQUEST_USE_SPENDABLE_NORMAL_ITEM, "Match.RequestUseSpendableNormalItem", "Request Use Spendable Normal Item", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidItem");				

		C(MC_MATCH_REQUEST_USE_SPENDABLE_BUFF_ITEM, "Match.RequestUseSpendableBuffItem", "Request Use Spendable Buff Item", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidItem");				

		C(MC_MATCH_RESPONSE_USE_SPENDABLE_BUFF_ITEM, "Match.ResponseUseSpendableBuffItem", "Response Use Spendable Buff Item", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidItem")				
			P(MPT_INT, "ErrorCode");

		C(MC_MATCH_SPENDABLE_BUFF_ITEM_STATUS, "Match.SpendableBuffItemStatusBlob", "Send Spendable Buff Item Status", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
			P(MPT_BLOB, "BuffBlob");
		
			
		C(MC_MATCH_REQUEST_SUICIDE, "Match.Request.Suicide", "Request Suicide", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")

		C(MC_MATCH_RESPONSE_SUICIDE, "Match.Response.Suicide", "Response Suicide", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
			P(MPT_UID, "uidChar")

		C(MC_MATCH_RESPONSE_SUICIDE_RESERVE, "Match.Response.SuicideReserve", "response suicide reserve", MCDT_MACHINE2MACHINE)

		C(MC_MATCH_NOTIFY_THROW_TRAPITEM, "Match.Notify.Throw.TrapItem", "Notify Throw TrapItem", MCDT_MACHINE2MACHINE)
			P(MPT_SHORT, "ItemID")

		C(MC_MATCH_NOTIFY_ACTIVATED_TRAPITEM, "Match.Notify.Activated.TrapItem", "Notify Activated TrapItem", MCDT_MACHINE2MACHINE)
			P(MPT_SHORT, "ItemID")
			P(MPT_SVECTOR, "ItemPos")

		C(MC_MATCH_NOTIFY_ACTIATED_TRAPITEM_LIST, "Match.Notify.Activated.TrapItem.List", "Notify Activated TrapItem List", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "ActiveTrapList")

		C(MC_MATCH_REQUEST_OBTAIN_WORLDITEM, "Match.Request.Obtain.WorldItem", "Request Obtain WorldItem", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
			P(MPT_INT, "nItemUID")
		C(MC_MATCH_OBTAIN_WORLDITEM, "Match.WorldItem.Obtain", "Obtain WorldItem", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
			P(MPT_INT, "nItemUID")
		C(MC_MATCH_SPAWN_WORLDITEM, "Match.WorldItem.Spawn", "Spawn WorldItem", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "SpawnInfo")
		C(MC_MATCH_REQUEST_SPAWN_WORLDITEM, "Match.Request.Spawn.WorldItem", "Request Spawn WorldItem", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
			P(MPT_INT, "ItemID")
			P(MPT_POS, "ItemPos")
			P(MPT_FLOAT, "ItemDropDelayTime")
		C(MC_MATCH_REMOVE_WORLDITEM, "Match.Request.Spawn.WorldItem", "Request Spawn WorldItem", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "nWorldItemUID")		// world item의 UID

		C(MC_MATCH_RESET_TEAM_MEMBERS, "Match.Reset.TeamMembers", "Reset Team Members", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "TeamMemberData")

		C(MC_MATCH_ASSIGN_COMMANDER, "Match.Assign.Commander", "Assign Commander", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidRedCommander")
			P(MPT_UID, "uidBlueCommander")

		C(MC_MATCH_SET_OBSERVER, "Match.Set.Observer", "Set Observer", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")

		// 래더 관련
		C(MC_MATCH_LADDER_REQUEST_CHALLENGE, "Match.Ladder.Request.Challenge", "Request Challenge a Ladder", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "MemberCount")		// 레더팀 멤버 수
			P(MPT_UINT, "Options")			// 옵션
			P(MPT_BLOB, "MemberNames")		// 레더팀 멤버 이름들
			
		C(MC_MATCH_LADDER_RESPONSE_CHALLENGE, "Match.Ladder.Response.Challenge", "Response Challenge a Ladder", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
		C(MC_MATCH_LADDER_SEARCH_RIVAL, "Match.Ladder.SearchRival", "Search a Ladder Rival", MCDT_MACHINE2MACHINE)
		C(MC_MATCH_LADDER_REQUEST_CANCEL_CHALLENGE, "Match.Ladder.Request.CancelChallenge", "Request Cancel Challenge", MCDT_MACHINE2MACHINE)
		C(MC_MATCH_LADDER_CANCEL_CHALLENGE, "Match.Ladder.CancelChallenge", "Cancel Ladder Challenge", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "CharName")
		C(MC_MATCH_LADDER_PREPARE, "Ladder.Prepare", "Prepare Ladder Game", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_INT, "nTeam")
		C(MC_MATCH_LADDER_LAUNCH, "Ladder.Launch", "Launch Ladder Game", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage")
			P(MPT_STR, "MapName")

		// 동의 요청
		C(MC_MATCH_REQUEST_PROPOSAL, "Match.RequestProposal", "Request Proposal", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")			// 요청한 캐릭터 UID
			P(MPT_INT, "ProposalMode")		// 동의 종류 - MMatchProposalMode의 int형
			P(MPT_INT, "RequestID")			// 요청ID - 클라이언트가 임의로 결정한다. 자신만 알고 있으면 됨.
			P(MPT_INT, "ReplierCount")		// 동의를 물어볼 사람수
			P(MPT_BLOB, "ReplierCharNames")	// 동의자 캐릭터 이름 - AskCount만큼이 BLOB에 들어있다.
		C(MC_MATCH_RESPONSE_PROPOSAL, "Match.ResponseProposal", "Response Proposal", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")			// 결과
			P(MPT_INT, "ProposalMode")		// 동의 종류 - MMatchAgreementMode의 int형
			P(MPT_INT, "RequestID")			// 요청ID
		C(MC_MATCH_ASK_AGREEMENT, "Match.AskAgreement", "Ask Agreement", MCDT_MACHINE2MACHINE)
			P(MPT_UID,	"uidProposer")		// 제안자 캐릭터 UID
			P(MPT_BLOB,	"MembersCharName")	// 참여자 캐릭터 이름들
			P(MPT_INT,	"ProposalMode")		// 동의 종류 - MMatchAgreementMode의 int형
			P(MPT_INT,	"RequestID")		// 요청ID
		C(MC_MATCH_REPLY_AGREEMENT, "Match.ReplyAgreement", "Reply Agreement", MCDT_MACHINE2MACHINE)
			P(MPT_UID,	"uidProposer")		// 제안자 캐릭터 UID
			P(MPT_UID,	"uidChar")			// 답변자 캐릭터 UID
			P(MPT_STR,	"Replier")			// 답변자 캐릭터 이름
			P(MPT_INT,	"ProposalMode")		// 동의 종류
			P(MPT_INT,	"RequestID")		// 요청 ID
			P(MPT_BOOL,	"Agreement")		// 동의 여부

			

		// 친구 관련
		C(MC_MATCH_FRIEND_ADD, "Match.Friend.Add", "Add a Friend", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "Name")
		C(MC_MATCH_FRIEND_REMOVE, "Match.Friend.Remove", "Remove a Friend", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "Name")
		C(MC_MATCH_FRIEND_LIST, "Match.Friend.List", "List Friend", MCDT_MACHINE2MACHINE)
		C(MC_MATCH_RESPONSE_FRIENDLIST, "Match.Response.FriendList", "Response List Friend", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "FriendList")
		C(MC_MATCH_FRIEND_MSG, "Match.Friend.Msg", "Message to Friends", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "Msg")

		// 클랜 관련
		C(MC_MATCH_CLAN_REQUEST_CREATE_CLAN, "Match.Clan.RequestCreateClan", "Request Create Clan", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")			// 요청한 캐릭터 UID
			P(MPT_INT, "RequestID")			// 요청ID - 클라이언트가 임의로 결정한다. 자신만 알고 있으면 됨.
			P(MPT_STR, "ClanName")			// 생성할 클랜 이름
			P(MPT_STR, "Member1CharName")	// 발기인 캐릭터 이름
			P(MPT_STR, "Member2CharName")	// 발기인 캐릭터 이름
			P(MPT_STR, "Member3CharName")	// 발기인 캐릭터 이름
			P(MPT_STR, "Member4CharName")	// 발기인 캐릭터 이름
        C(MC_MATCH_CLAN_RESPONSE_CREATE_CLAN, "Match.Clan.ResponseCreateClan", "Response Create Clan", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
			P(MPT_INT, "RequestID")			// 요청ID
		C(MC_MATCH_CLAN_ASK_SPONSOR_AGREEMENT, "Match.Clan.AskSponsorAgreement", "Ask Sponsor's Agreement", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "RequestID")			// 요청ID
			P(MPT_STR, "ClanName")
			P(MPT_UID, "uidClanMaster")		// 마스터 UID
			P(MPT_STR, "szClanMaster")		// 마스터 이름
		C(MC_MATCH_CLAN_ANSWER_SPONSOR_AGREEMENT, "Match.Clan.AnswerSponsorAgreement", "Answer Sponsor's Agreement", MCDT_MACHINE2MACHINE)
			P(MPT_INT,	"RequestID")			// 요청ID
			P(MPT_UID,	"uidClanMaster")		// 마스터 UID
			P(MPT_STR,	"SponsorCharName")		// 발기인 캐릭터 이름
			P(MPT_BOOL, "Answer")				// 동의 여부
		C(MC_MATCH_CLAN_REQUEST_AGREED_CREATE_CLAN, "Match.Clan.RequestAgreedCreateClan", "Request Agreed Create Clan", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")	// 요청한 캐릭터 UID
			P(MPT_STR, "ClanName")	// 생성할 클랜 이름
			P(MPT_STR, "Member1CharName")	// 발기인 캐릭터 이름
			P(MPT_STR, "Member2CharName")	// 발기인 캐릭터 이름
			P(MPT_STR, "Member3CharName")	// 발기인 캐릭터 이름
			P(MPT_STR, "Member4CharName")	// 발기인 캐릭터 이름
        C(MC_MATCH_CLAN_RESPONSE_AGREED_CREATE_CLAN, "Match.Clan.AgreedResponseCreateClan", "Response Agreed Create Clan", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
		C(MC_MATCH_CLAN_REQUEST_CLOSE_CLAN, "Match.Clan.RequestCloseClan", "Request Close Clan", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
			P(MPT_STR, "ClanName")
        C(MC_MATCH_CLAN_RESPONSE_CLOSE_CLAN, "Match.Clan.ResponseCloseClan", "Response Close Clan", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
		
		C(MC_MATCH_CLAN_REQUEST_JOIN_CLAN, "Match.Clan.RequestJoinClan", "Request Join Clan", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")		// 운영자 uid
			P(MPT_STR, "ClanName")		// 클랜 이름
			P(MPT_STR, "szJoiner")		// 가입자 캐릭터 이름
		C(MC_MATCH_CLAN_RESPONSE_JOIN_CLAN, "Match.Clan.ResponseJoinClan", "Response Join Clan", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
		C(MC_MATCH_CLAN_ASK_JOIN_AGREEMENT, "Match.Clan.AskJoinAgreement", "Ask Join Agreement", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "ClanName")				// 클랜 이름
			P(MPT_UID, "uidClanAdmin")			// 운영자 UID
			P(MPT_STR, "szClanAdmin")			// 운영자 캐릭터 이름
		C(MC_MATCH_CLAN_ANSWER_JOIN_AGREEMENT, "Match.Clan.AnswerJoinAgreement", "Answer Join Agreement", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidClanAdmin")
			P(MPT_STR,	"JoinerCharName")		// 가입자 캐릭터 이름
			P(MPT_BOOL, "Answer")

		C(MC_MATCH_CLAN_REQUEST_AGREED_JOIN_CLAN, "Match.Clan.RequestAgreedJoinClan", "Request Agreed Join Clan", MCDT_MACHINE2MACHINE)
			P(MPT_UID,	"uidClanAdmin")
			P(MPT_STR,	"ClanName")
			P(MPT_STR,	"szJoiner")
		C(MC_MATCH_CLAN_RESPONSE_AGREED_JOIN_CLAN, "Match.Clan.ResponseAgreedJoinClan", "Response Agreed Join Clan", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")

		C(MC_MATCH_CLAN_REQUEST_LEAVE_CLAN, "Match.Clan.RequestLeaveClan", "Request Leave Clan", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
		C(MC_MATCH_CLAN_RESPONSE_LEAVE_CLAN, "Match.Clan.ResponseLeaveClan", "Response Leave Clan", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")

		C(MC_MATCH_CLAN_UPDATE_CHAR_CLANINFO, "Match.Clan.UpdateCharClanInfo", "Update Char ClanInfo", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "ClanInfo")

		C(MC_MATCH_CLAN_MASTER_REQUEST_CHANGE_GRADE, "Match.Clan.Master.RequestChangeGrade", "Request Change ClanGrade", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidClanMaster")		// 클랜 마스터
			P(MPT_STR, "szMember")			// 변경하려고 하는 멤버 캐릭터이름
			P_MINMAX(MPT_INT, "Grade", 0, MCG_END-1)				// 변경하고자 하는 권한
		C(MC_MATCH_CLAN_MASTER_RESPONSE_CHANGE_GRADE, "Match.Clan.Master.ResponseChangeGrade", "Response Change ClanGrade", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")

		C(MC_MATCH_CLAN_ADMIN_REQUEST_EXPEL_MEMBER, "Match.Clan.Admin.RequestExpelMember", "Request Expel ClanMember", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidClanAdmin")
			P(MPT_STR, "szMember")
		C(MC_MATCH_CLAN_ADMIN_RESPONSE_EXPEL_MEMBER, "Match.Clan.Admin.ResponseLeaveMember", "Response Expel ClanMember", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")

		C(MC_MATCH_CLAN_REQUEST_MSG, "Match.Clan.Request.Msg", "Request Clan Msg", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidSender")
			P(MPT_STR, "Msg")

		C(MC_MATCH_CLAN_MSG, "Match.Clan.Msg", "Clan Msg", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "SenderName")
			P(MPT_STR, "Msg")

		C(MC_MATCH_CLAN_REQUEST_MEMBER_LIST, "Match.Clan.Request.ClanMemberList", "Request Clan Member List", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
		C(MC_MATCH_CLAN_RESPONSE_MEMBER_LIST, "Match.Clan.Response.ClanMemberList", "Response Clan Member List", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "ClanMemberList")
		C(MC_MATCH_CLAN_REQUEST_CLAN_INFO, "Match.Clan.Request.Clan.Info", "Request Clan Info", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
			P(MPT_STR, "ClanName")
			C(MC_MATCH_CLAN_RESPONSE_CLAN_INFO, "Match.Clan.Response.Clan.Info", "Response Clan Info", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "ClanInfo")
		C(MC_MATCH_CLAN_STANDBY_CLAN_LIST, "Match.Clan.Standby.ClanList", "Standby Clan List", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "PrevClanListCount")
			P(MPT_INT, "NextClanListCount")
			P(MPT_BLOB, "ClanList")
		C(MC_MATCH_CLAN_MEMBER_CONNECTED, "Match.Clan.Member.Connected", "Member Connected", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "szMember")
		C(MC_MATCH_CLAN_REQUEST_EMBLEMURL, "Match.Clan.Request.EmblemURL", "Request EmblemURL", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "ClanURLList")
		C(MC_MATCH_CLAN_RESPONSE_EMBLEMURL, "Match.Clan.Response.EmblemURL", "Response EmblemURL", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "ClanCLID")
			P(MPT_INT, "EmblemChecksum")
			P(MPT_STR, "EmblemURL")
		C(MC_MATCH_CLAN_LOCAL_EMBLEMREADY, "Match.Clan.Local.EmblemReady", "Notify Emblem Ready", MCDT_LOCAL)
			P(MPT_INT, "ClanCLID")
			P(MPT_STR, "EmblemURL")
		C(MC_MATCH_CLAN_ACCOUNCE_DELETE, "MC_MATCH_CLAN_ACCOUNCE_DELETE", "delete clan info announce to clan member", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "delete info" )

		// 투표 명령어
		C(MC_MATCH_CALLVOTE, "Match.Callvote", "Callvote", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "strDiscuss")
			P(MPT_STR, "strArg")
		C(MC_MATCH_NOTIFY_CALLVOTE, "Match.NotifyCallvote", "Notify Callvote", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "strDiscuss")
			P(MPT_STR, "strArg")
		C(MC_MATCH_NOTIFY_VOTERESULT, "Match.NotifyVoteResult", "Notify Vote Result", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "strDiscuss")
			P(MPT_INT, "nResult")	// 1=Passed , 0=Rejected
		C(MC_MATCH_VOTE_YES, "Match.VoteYes", "Vote", MCDT_MACHINE2MACHINE)
		C(MC_MATCH_VOTE_NO, "Match.VoteNo", "Vote", MCDT_MACHINE2MACHINE)
		C(MC_MATCH_VOTE_STOP, "Vote stop", "Vote stop", MCDT_MACHINE2MACHINE )

		C(MC_MATCH_BROADCAST_CLAN_RENEW_VICTORIES, "Match.Broadcast.ClanRenewVictories", "Broadcast Clan Renew Victories", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "strWinnerClanName")
			P(MPT_STR, "strLoserClanName")
			P(MPT_INT, "nVictories")
		C(MC_MATCH_BROADCAST_CLAN_INTERRUPT_VICTORIES, "Match.Broadcast.ClanInterruptVictories", "Broadcast Clan Interrupt Victories", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "strWinnerClanName")
			P(MPT_STR, "strLoserClanName")
			P(MPT_INT, "nVictories")

		C(MC_MATCH_BROADCAST_DUEL_RENEW_VICTORIES, "Match.Broadcast.DuelRenewVictories", "Broadcast Duel Renew Victories", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "strChampionName")
			P(MPT_STR, "strChannelName")
			P(MPT_INT, "nRoomNumber")
			P(MPT_INT, "nVictories")
		C(MC_MATCH_BROADCAST_DUEL_INTERRUPT_VICTORIES, "Match.Broadcast.DuelInterruptVictories", "Broadcast Duel Interrupt Victories", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "strChampionName")
			P(MPT_STR, "strInterrupterName")
			P(MPT_INT, "nVictories")


		C(MC_MATCH_ASSIGN_BERSERKER, "Match.Assign.Berserker", "Assign Berserker", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")

		C(MC_MATCH_DUEL_QUEUEINFO, "Match.Duel.Queue Info", "Queue Info", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "QueueInfo")

		C(MC_QUEST_PING, "Match.Quest.Ping", "QuestPing", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "nTimeStamp")

		C(MC_QUEST_PONG, "Match.Quest.Pong", "QuestPong", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "nTimeStamp")

		C( MC_QUEST_NPCLIST, "MC_QUEST_NPCLIST", "Send npc info list to client.", MCDT_MACHINE2MACHINE )
			P(MPT_BLOB, "NPC info list" )
			P(MPT_INT,  "eGameType")

		// 이벤트 마스터 명령어 ---------------------------------------------------------------
		C(MC_EVENT_CHANGE_MASTER, "Event.ChangeMaster", "Take out Master from Stage", MCDT_MACHINE2MACHINE)
		C(MC_EVENT_CHANGE_PASSWORD, "Event.ChangePassword", "Change Password on Stage", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "strPassword")
		C(MC_EVENT_REQUEST_JJANG, "Event.RequestJJang", "Request JJang mark to a Player", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "strTargetName")
		C(MC_EVENT_REMOVE_JJANG, "Event.RemoveJJang", "Remove JJang mark from a Player", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "strTargetName")
		C(MC_EVENT_UPDATE_JJANG, "Event.UpdateJJang", "Update JJang Player", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_BOOL, "bJjang")



		// 퀘스트 명령어 ---------------------------------------------------------------
		C(MC_QUEST_NPC_SPAWN,	"Quest.NPCSpawn", "Npc Spawn", MCDT_MACHINE2MACHINE)
			P(MPT_UID,		"uidChar")				// NPC 조종자
			P(MPT_UID,		"nNpcUID")				// 할당된 NPC ID
			P(MPT_UCHAR,	"nNpcType")				// NPC 종류
			P(MPT_UCHAR,	"PositionIndex")		// NPC 스폰 위치 인덱스

		C(MC_QUEST_ENTRUST_NPC_CONTROL,		"Quest.Entrust.NPC.Control", "Entrust Npc Control", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")		// NPC 조종자
			P(MPT_UID, "nNpcUID")		// NPC id
		C(MC_QUEST_CHECKSUM_NPCINFO,		"Quest.Checksum.NPCInfo",		"Checksum NPC Info", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")
			P(MPT_UINT, "checksum")
		C(MC_QUEST_REQUEST_NPC_DEAD,	"Quest.Request.NPCDead", "Request Npc Dead", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidChar")		// NPC 조종자
			P(MPT_UID, "uidNPC")		// 할당된 NPC ID
			P(MPT_SVECTOR, "NpcPosition")	// NPC 위치
		C(MC_QUEST_NPC_DEAD,	"Quest.NPCDead", "Npc Dead", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidKillerPlayer")	// 죽인 플레이어
			P(MPT_UID, "uidNPC")			// 죽는 NPC id
		C(MC_QUEST_REFRESH_PLAYER_STATUS,	"Quest.RefreshPlayerStatus", "Refresh Player Status", MCDT_MACHINE2MACHINE)

		C(MC_QUEST_NPC_ALL_CLEAR,	"Quest.NPC.AllClear", "Clear All NPC", MCDT_MACHINE2MACHINE)

		C(MC_QUEST_ROUND_START,	"Quest.Round.Start", "Quest Start Round", MCDT_MACHINE2MACHINE)
			P(MPT_UCHAR, "round")
		C(MC_MATCH_QUEST_REQUEST_DEAD, "Quest.RequestDead", "Quest Request Dead", MCDT_MACHINE2MACHINE)
		C(MC_MATCH_QUEST_PLAYER_DEAD, "Quest.PlayerDead", "Quest Player Dead", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "Victim");
		C(MC_QUEST_OBTAIN_QUESTITEM, "Quest.ObtainQuestItem", "Obtain QuestItem", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "QuestItemID");		// 퀘스트 아이템의 ID
		C(MC_QUEST_OBTAIN_ZITEM, "Quest.ObtainZItem", "Obtain ZItem", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "ItemID");			// 일반 아이템의 ID

		C(MC_QUEST_STAGE_MAPSET, "Quest.State.Mapset", "Change Stage Quest Mapset Setting", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidStage");			// 스테이지 UID
			P(MPT_CHAR, "QuestMapset");		// 퀘스트 맵셋 변경
		C(MC_QUEST_STAGE_GAME_INFO, "Quest.Stage.GameInfo", "Quest Stage GameInfo", MCDT_MACHINE2MACHINE)
			P(MPT_CHAR, "Quest level");			// 퀘스트 QL
			P(MPT_CHAR, "Mapset ID");			// 맵셋 ID
			P(MPT_UINT, "QuestScenarioID");		// 퀘스트 시나리오 ID

		C(MC_QUEST_SECTOR_BONUS, "Quest.SectorBonus", "Quest Sector Bonus", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")
			P(MPT_UINT, "XPBonus");		// Exp | 경험치퍼센트
			P(MPT_UINT, "BPBonus");

		C(MC_QUEST_GAME_INFO, "Quest.GameInfo", "Quest Game Info", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "Info");
		C(MC_QUEST_COMBAT_STATE, "Quest.Combat.State", "Quest Combat State", MCDT_MACHINE2MACHINE)
			P(MPT_CHAR, "CombatState")		// 퀘스트 게임 상태

		C(MC_QUEST_SECTOR_START, "Quest.Sector.Start", "Quest Sector Start", MCDT_MACHINE2MACHINE)
			P(MPT_CHAR, "SectorIndex")		// 새로운 섹터 인덱스
			P(MPT_UCHAR, "RepeatIndex")		// 현재 반복 횟수 (서바이벌용)

		C(MC_QUEST_COMPLETED, "Quest.Complete", "Complete Quest", MCDT_MACHINE2MACHINE)
			P(MPT_BLOB, "RewardInfo");		// 보상 내용
		C(MC_QUEST_FAILED, "Quest", "Quest failed", MCDT_MACHINE2MACHINE)	//퀘스트 실패.

		C(MC_QUEST_REQUEST_MOVETO_PORTAL, "Quest.Request.Moveto.Portal", "Request Moveto Portal", MCDT_MACHINE2MACHINE)
			P(MPT_CHAR, "CurrSectorIndex")
		C(MC_QUEST_MOVETO_PORTAL, "Quest.Moveto.Portal", "Moveto Portal", MCDT_MACHINE2MACHINE)
			P(MPT_CHAR, "SectorIndex")
			P(MPT_UCHAR, "RepeatIndex")		// 현재 반복 횟수 (서바이벌용)
			P(MPT_UID, "uidPlayer")
		C(MC_QUEST_READYTO_NEWSECTOR, "Quest.Readyto.NewSector", "Ready To New Sector", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "uidPlayer")

		C(MC_QUEST_PEER_NPC_BASICINFO,		"Quest.Peer.NPC.BasicInfo",		"NPC BasicInfo", MCDT_PEER2PEER)
			P(MPT_BLOB, "Info")
		C(MC_QUEST_PEER_NPC_HPINFO,			"Quest.Peer.NPC.HPInfo",		"NPC HPInfo", MCDT_PEER2PEER)
			P(MPT_INT, "nNPCCount")
			P(MPT_BLOB, "HPTable");
		C(MC_QUEST_PEER_NPC_ATTACK_MELEE,	"Quest.Peer.NPC.Attack.Melee",	"NPC Melee Attack", MCDT_PEER2PEER)
			P(MPT_UID, "uidOwner")		// 때린 NPC
//			P(MPT_INT, "AttackType")
//			P(MPT_VECTOR, "Position")
		C(MC_QUEST_PEER_NPC_ATTACK_RANGE,	"Quest.Peer.NPC.Attack.Range",	"NPC Range Attack", MCDT_PEER2PEER)
			P(MPT_UID, "uidOwner")		// 때린 NPC
			P(MPT_BLOB, "Info")
		C(MC_QUEST_PEER_NPC_SKILL_START,	"Quest.Peer.NPC.Skill.Start",	"NPC Skill Start", MCDT_PEER2PEER)
			P(MPT_UID, "uidOwner")		// 쓴 NPC
			P(MPT_INT, "nSkill")		// 스킬 번호
			P(MPT_UID, "uidTarget")		// target
			P(MPT_POS, "targetPos")		// 위치
		C(MC_QUEST_PEER_NPC_SKILL_EXECUTE,	"Quest.Peer.NPC.Skill.Execute",	"NPC Skill Start", MCDT_PEER2PEER)
			P(MPT_UID, "uidOwner")		// 쓴 NPC
			P(MPT_INT, "nSkill")		// 스킬 번호
			P(MPT_UID, "uidTarget")		// target
			P(MPT_POS, "targetPos")		// 위치

		C(MC_QUEST_PEER_NPC_DEAD,	"Quest.Peer.NPC.Dead",	"NPC Dead", MCDT_PEER2PEER)
			P(MPT_UID, "uidKillerPlayer")	// 죽인 플레이어
			P(MPT_UID, "uidNPC")			// 죽는 NPC id

		C(MC_QUEST_PEER_NPC_BOSS_HPAP,		"Quest.Peer.NPC.Boss.HpAp",		"NPC Boss HpAp", MCDT_PEER2PEER)
			P(MPT_UID, "uidBoss")
			P(MPT_FLOAT, "Hp")
			P(MPT_FLOAT, "Ap")

		C(MC_QUEST_TEST_REQUEST_NPC_SPAWN,	"Quest.Test.RequestNPCSpawn", "NPC Spawn", MCDT_MACHINE2MACHINE)
			P(MPT_INT,  "NPC Type")
			P(MPT_INT,	"NPC Count")
		C(MC_QUEST_TEST_REQUEST_CLEAR_NPC,		"Quest.Test.ClearNPC", "Clear NPC", MCDT_MACHINE2MACHINE)
		C(MC_QUEST_TEST_REQUEST_SECTOR_CLEAR,	"Quest.Test.SectorClear", "Sector Clear", MCDT_MACHINE2MACHINE)
		C(MC_QUEST_TEST_REQUEST_FINISH,			"Quest.Test.Finish", "Finish Quest", MCDT_MACHINE2MACHINE)


		// 테스트 명령어 ---------------------------------------------------------------
		C(MC_TEST_BIRDTEST1, "Test.BirdTest1", "BirdTest1", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Result")
			P(MPT_UID, "uidPlayer")
			P(MPT_BLOB, "Dummy");
			
		C(MC_TEST_PEERTEST_PING, "Test.PeerTest.Ping", "PeerTest Ping", MCDT_PEER2PEER | MCCT_NON_ENCRYPTED)
		C(MC_TEST_PEERTEST_PONG, "Test.PeerTest.Pong", "PeerTest Pong", MCDT_PEER2PEER | MCCT_NON_ENCRYPTED)
	}

	// 관리자 명령어
	if(nSharedType&MSCT_MATCHSERVER || nSharedType&MSCT_CLIENT || nSharedType&MSCT_AGENT) {
		if (nSharedType&MSCT_MATCHSERVER || nSharedType&MSCT_CLIENT || nSharedType&MSCT_AGENT) {
			C(MC_ADMIN_ANNOUNCE, "Admin.Announce", "Announce", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
				P(MPT_UID, "uidAdmin")
				P(MPT_STR, "Msg")
				P(MPT_UINT, "MsgType");
			C(MC_ADMIN_PING_TO_ALL, "Admin.PingToAll", "Ping to All Clients", MCDT_MACHINE2MACHINE)
		}

		if (nSharedType&MSCT_MATCHSERVER || nSharedType&MSCT_CLIENT) {
			C(MC_ADMIN_REQUEST_SERVER_INFO, "Admin.RequestServerInfo", "Request Server Info", MCDT_MACHINE2MACHINE)
				P(MPT_UID, "uidAdmin");
			C(MC_ADMIN_RESPONSE_SERVER_INFO, "Admin.ResponseServerInfo", "Response Server Info", MCDT_MACHINE2MACHINE)
				P(MPT_BLOB, "ServerInfo");
			C(MC_ADMIN_SERVER_HALT, "Admin.Halt", "Halt Server", MCDT_MACHINE2MACHINE)
				P(MPT_UID, "uidAdmin");
			C(MC_ADMIN_TERMINAL, "Admin.Terminal", "Admin.Terminal", MCDT_MACHINE2MACHINE)
				P(MPT_UID, "uidAdmin")
				P(MPT_STR, "message");
			C(MC_ADMIN_REQUEST_UPDATE_ACCOUNT_UGRADE, "Admin.RequestUpdateAccountUGrade", "Request Update Account UGrade", MCDT_MACHINE2MACHINE)
				P(MPT_UID, "uidAdmin")
				P(MPT_STR, "uidTargetCharName")
			C(MC_ADMIN_RESPONSE_UPDATE_ACCOUNT_UGRADE, "Admin.ResponseUpdateAccountUGrade", "Response Update Account UGrade", MCDT_MACHINE2MACHINE)
				P(MPT_INT, "Result")
				P(MPT_UID, "uidChar")

			C(MC_ADMIN_REQUEST_KICK_PLAYER, "Admin.RequestKickPlayer", "Request Kick Player", MCDT_MACHINE2MACHINE)
				P(MPT_STR, "uidTargetCharName");
			C(MC_ADMIN_RESPONSE_KICK_PLAYER, "Admin.ResponseKickPlayer", "Response Kick Player", MCDT_MACHINE2MACHINE)
				P(MPT_INT, "Result");

			C(MC_ADMIN_REQUEST_MUTE_PLAYER, "Admin.RequestMutePlayer", "Request Mute Player", MCDT_MACHINE2MACHINE)
				P(MPT_STR, "uidTargetCharName")
				P(MPT_INT, "nHour");
			C(MC_ADMIN_RESPONSE_MUTE_PLAYER, "Admin.ResponseMutePlayer", "Response Mute Player", MCDT_MACHINE2MACHINE)
				P(MPT_INT, "Result");

			C(MC_ADMIN_REQUEST_BLOCK_PLAYER, "Admin.RequestBlockPlayer", "Request Block Player", MCDT_MACHINE2MACHINE)
				P(MPT_STR, "uidTargetCharName")
				P(MPT_INT, "nHour");
			C(MC_ADMIN_RESPONSE_BLOCK_PLAYER, "Admin.ResponseBlockPlayer", "Response Block Player", MCDT_MACHINE2MACHINE)
				P(MPT_INT, "Result");

			C(MC_ADMIN_REQUEST_SWITCH_LADDER_GAME, "Admin.RequestSwitchLadderGame", "Request Switch LadderGame", MCDT_MACHINE2MACHINE)
				P(MPT_UID, "uidAdmin")	
				P(MPT_BOOL, "IsEnabled")
			C(MC_ADMIN_HIDE, "Admin.Hide", "Hide Admin Player", MCDT_MACHINE2MACHINE)
			C(MC_ADMIN_RELOAD_CLIENT_HASH, "Admin.ReloadClientHash", "Reload Client Hash", MCDT_MACHINE2MACHINE)
			C(MC_ADMIN_RESET_ALL_HACKING_BLOCK, "MC_ADMIN_RESET_ALL_HACKING_BLOCK", "reset all hacking block", MCDT_MACHINE2MACHINE)
			C(MC_ADMIN_RELOAD_GAMBLEITEM, "MC_ADMIN_RELOAD_GAMBLEITEM", "reload gamble item info", MCDT_MACHINE2MACHINE)
			C(MC_ADMIN_DUMP_GAMBLEITEM_LOG, "MC_ADMIN_DUMP_GAMBLEITEM_LOG", "dump gamble item info", MCDT_MACHINE2MACHINE)
			C(MC_ADMIN_ASSASIN, "MC_ADMIN_ASSASIN", "choose admin as commander", MCDT_MACHINE2MACHINE)
		}		
	}

	// ZoneServer, Master 공용 명령어
	if(nSharedType&MSCT_MASTER){
		C(MC_NET_REQUEST_UID, "Net.RequestUID", "Request UID", MCDT_MACHINE2MACHINE)
			P(MPT_INT, "Size");
		C(MC_NET_RESPONSE_UID, "Net.ResponseUID", "Response UID", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "Start");
		P(MPT_UID, "End");
	}

	// Client 명령어
	if (nSharedType&MSCT_CLIENT) {
/*
		C(MC_PEER_ECHO, "Peer.Echo", "Echo Test", MCDT_PEER2PEER)
			P(MPT_STR, "Msg");
		C(MC_PEER_SETPORT, "Peer.SetPort", "Set Port", MCDT_LOCAL)
			P(MPT_INT, "Port");
		C(MC_PEER_ADDPEER, "Peer.AddPeer", "Add Peer", MCDT_LOCAL)
			P(MPT_STR, "IP")
			P(MPT_INT, "Port");
		C(MC_PEER_CLEARPEERS, "Peer.ClearPeer", "Clear Peer", MCDT_LOCAL);
*/
		C(MC_PEER_OPENED, "Peer.Open", "Peer Connection Opened", MCDT_LOCAL)
			P(MPT_UID, "uidPlayer")

		C(MC_PEER_MOVE, "Peer.Move", "Move Object", MCDT_PEER2PEER)
			P(MPT_POS, "Position")
			P(MPT_VECTOR, "Direction")
			P(MPT_VECTOR, "Velocity")
			P(MPT_INT, "StateUpper")
			P(MPT_INT, "StateLower")

		// 우선은 보여지는 것들을 위한...점차적 인자 추가..
		// 시간등의 동기화 관련 인자는 나중에 추가..

		C(MC_PEER_CHANGE_WEAPON, "Peer.ObjectChangeWeapon", "Change Object Weapon", MCDT_PEER2PEER)
			P(MPT_INT, "WeaponID")

		C(MC_PEER_CHANGE_PARTS, "Peer.ObjectChangeParts", "Change Object Parts", MCDT_PEER2PEER)
			P(MPT_INT, "PartsType")
			P(MPT_INT, "PartsID")

		C(MC_PEER_ATTACK, "Peer.ObjectAttack", "Object Attack", MCDT_PEER2PEER)
			P(MPT_INT, "AttackType")
			P(MPT_VECTOR, "Position")

			C(MC_PEER_DAMAGE, "Peer.ObjectDamage", "Object Damage", MCDT_PEER2PEER)
			P(MPT_UID, "TargetUID")
			P(MPT_INT, "Damage")

		C(MC_PEER_CHAT, "Peer.Chat", "Chat", MCDT_PEER2PEER)
			P(MPT_INT, "TeamID")
			P(MPT_STR, "Msg");

		C(MC_PEER_CHAT_ICON, "Peer.ChatIcon", "ChatIcon", MCDT_PEER2PEER)
			P(MPT_BOOL, "bStart");

		C(MC_PEER_REACTION, "Peer.Reaction", "React", MCDT_PEER2PEER)
			P(MPT_FLOAT, "Time")
			P(MPT_INT, "ReactionID")

		C(MC_PEER_ENCHANT_DAMAGE, "Peer.EnchantDamage", "EnchantDamage", MCDT_PEER2PEER)
			P(MPT_UID, "OwnerUID")
			P(MPT_UID, "TargetUID")

		C(MC_PEER_BUFF_INFO, "Peer.BuffInfo", "BuffInfo", MCDT_PEER2PEER)
			P(MPT_BLOB, "Info")


		C(MC_PEER_SHOT, "Peer.Shot", "Shot", MCDT_PEER2PEER)
			P(MPT_BLOB, "Info")
/*
			P(MPT_FLOAT, "Time")
			P(MPT_POS, "Position")
			P(MPT_VECTOR, "Direction")
			P(MPT_INT, "SelType");
*/

		C(MC_PEER_SHOT_MELEE, "Peer.Shot.Melee", "ShotMelee", MCDT_PEER2PEER)
			P(MPT_FLOAT, "Time")
			P(MPT_POS, "Position")
			P(MPT_INT, "nShot");

		C(MC_PEER_SHOT_SP, "Peer.Shot.Sp", "ShotSp", MCDT_PEER2PEER)
			P(MPT_FLOAT, "Time")
			P(MPT_POS, "Position")
			P(MPT_VECTOR, "Direction")
			P(MPT_INT, "Type")
			P(MPT_INT, "SelType");

		C(MC_PEER_RELOAD, "Peer.Reload", "Reload", MCDT_PEER2PEER);

		C(MC_PEER_SPMOTION,"Peer.ObjectSpMotion","Object SpMotion",MCDT_PEER2PEER);
			P(MPT_INT, "SelType");

		C(MC_PEER_CHANGECHARACTER, "Peer.ChangeCharacter", "ChangeCharacter", MCDT_PEER2PEER);

		C(MC_PEER_DIE, "Peer.Die", "Die", MCDT_PEER2PEER)
			P(MPT_UID, "Attacker");

		C(MC_PEER_SPAWN, "Peer.Spawn", "Spawn", MCDT_PEER2PEER);
			P(MPT_POS, "Position");
			P(MPT_DIR, "Direction");

		C(MC_PEER_DASH, "Peer.Dash", "Dash", MCDT_PEER2PEER);
			P(MPT_BLOB, "DashInfo");

		C(MC_PEER_SKILL, "Peer.ObjectSkill", "Skill", MCDT_PEER2PEER)
			P(MPT_FLOAT, "Time")
			P(MPT_INT, "SkillID");
			P(MPT_INT, "SelType");

		C(MC_PEER_BASICINFO, "Peer.CharacterBasicInfo", "BasicInfo", MCDT_PEER2PEER)
			P(MPT_BLOB, "Info")

		C(MC_PEER_HPINFO, "Peer.CharacterHPInfo", "HPInfo", MCDT_PEER2PEER)
			P(MPT_FLOAT, "fHP")

		C(MC_PEER_HPAPINFO, "Peer.CharacterHPAPInfo", "HPAPInfo", MCDT_PEER2PEER)
			P(MPT_FLOAT, "fHP")
			P(MPT_FLOAT, "fAP")

		C(MC_PEER_DUELTOURNAMENT_HPAPINFO, "Peer.Dueltournament CharacterHPAPInfo", "DuelTournamentHPAPInfo", MCDT_PEER2PEER)
			P(MPT_UCHAR, "MaxHP")
			P(MPT_UCHAR, "MaxAP")
			P(MPT_UCHAR, "HP")
			P(MPT_UCHAR, "AP");

		C(MC_PEER_UDPTEST, "Peer.UDPTest", "UDP Test on Peer-to-Peer", MCDT_PEER2PEER | MCCT_NON_ENCRYPTED)
		C(MC_PEER_UDPTEST_REPLY, "Peer.UDPTestReply", "UDP Test Reply on Peer-to-Peer", MCDT_PEER2PEER | MCCT_NON_ENCRYPTED)

		C(MC_PEER_PING, "Peer.Ping", "Ping", MCDT_PEER2PEER | MCCT_NON_ENCRYPTED)
			P(MPT_UINT, "TimeStamp");
		C(MC_PEER_PONG, "Peer.Pong", "Pong", MCDT_PEER2PEER | MCCT_NON_ENCRYPTED)
			P(MPT_UINT, "TimeStamp");
	}

	// Agent 명령어
	if (nSharedType&MSCT_AGENT) {
		C(MC_AGENT_CONNECT, "Agent.Connect", "Connect Agent to MatchServer", MCDT_LOCAL)
			P(MPT_UID, "TargetUID")
			P(MPT_UID, "AllocUID")
			P(MPT_UINT, "TimeStamp")

		C(MC_AGENT_DISCONNECT, "Agent.Disconnect", "Unregister Agent from MatchServer", MCDT_LOCAL)
		C(MC_AGENT_LOCAL_LOGIN, "Agent.LocalLogin", "Client login", MCDT_LOCAL)
			P(MPT_UID, "uidComm")
			P(MPT_UID, "uidPlayer")
	}

	// MatchServer, Agent 공용 명령어
	if (nSharedType&MSCT_MATCHSERVER || nSharedType&MSCT_AGENT) {
		C(MC_MATCH_REGISTERAGENT, "Match.RegisterAgent", "Register Agent to MatchServer", MCDT_MACHINE2MACHINE)
			P(MPT_STR, "Address")
			P(MPT_INT, "Port")
			P(MPT_INT, "UDPPort")
		C(MC_MATCH_UNREGISTERAGENT, "Match.UnRegisterAgent", "Unregister Agent from MatchServer", MCDT_MACHINE2MACHINE)
		C(MC_MATCH_AGENT_REQUEST_LIVECHECK, "Match.Agent.RequestLiveCheck", "Request LiveCheck for Agent", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "TimeStamp")
			P(MPT_UINT, "StageCount")
			P(MPT_UINT, "UserCount")
		C(MC_MATCH_AGENT_RESPONSE_LIVECHECK, "Match.Agent.ResponseLiveCheck", "Response LiveCheck for Agent", MCDT_MACHINE2MACHINE)
			P(MPT_UINT, "TimeStamp")
		C(MC_AGENT_STAGE_RESERVE, "Agent.StageReserve", "Reserve stage on AgentServer", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "StageUID")
		C(MC_AGENT_STAGE_RELEASE, "Agent.StageRelease", "Release stage on AgentServer", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "StageUID")
		C(MC_AGENT_STAGE_READY, "Agent.StageReady", "Ready to Handle stage", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "StageUID")
		C(MC_AGENT_RELAY_PEER, "Agent.RelayPeer", "Let agent to Relay Peer", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "PlayerUID");
			P(MPT_UID, "PeerCharUID");
			P(MPT_UID, "StageUID");
		C(MC_AGENT_PEER_READY, "Agent.PeerReady", "Ready to relay peer", MCDT_MACHINE2MACHINE)
			P(MPT_UID, "PlayerUID");
			P(MPT_UID, "PeerCharUID");
	}

	// MatchServer, Agent, Client 공용 명령어
	if (nSharedType&MSCT_MATCHSERVER || nSharedType&MSCT_AGENT || nSharedType&MSCT_CLIENT) {
		C(MC_AGENT_LOCATETO_CLIENT, "Agent.LocateToClient", "Locate Agent to Client", MCDT_MACHINE2MACHINE);
		P(MPT_UID, "AgentUID")
			P(MPT_STR, "Address")
			P(MPT_INT, "Port")
			P(MPT_INT, "UDPPort")
		C(MC_AGENT_RESPONSE_LOGIN, "Agent.ResponseLogin", "Response Login result to Client", MCDT_MACHINE2MACHINE)
//		C(MC_AGENT_MATCH_VALIDATE, "Agent.MatchValidate", "Validate connection from MatchServer", MCDT_MACHINE2MACHINE)
		C(MC_AGENT_PEER_BINDTCP, "Agent.PeerBindTCP", "Bind Client to Peer by TCP", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED)
			P(MPT_UID, "CharUID")
		C(MC_AGENT_PEER_BINDUDP, "Agent.PeerBindUDP", "Bind Client to Peer by UDP", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED)
			P(MPT_UID, "CharUID")
			P(MPT_STR, "strLocalIP")
			P(MPT_UINT, "nLocalPort")
			P(MPT_STR, "strIP")
			P(MPT_UINT, "nPort")
		C(MC_AGENT_PEER_UNBIND, "Agent.PeerUnbind", "Unbind Client from Peer", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED)
			P(MPT_UID, "CharUID")
		C(MC_AGENT_ERROR, "Agent.Error", "Error about Agent", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED);
			P(MPT_INT, "ErrorCode")
		C(MC_AGENT_TUNNELING_TCP, "Agent.TunnelingTCP", "Tunneling TCP", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED);
			P(MPT_UID, "SendUID")
			P(MPT_UID, "RecvUID")
			P(MPT_BLOB, "Data")
		C(MC_AGENT_TUNNELING_UDP, "Agent.TunnelingUDP", "Tunneling UDP", MCDT_PEER2PEER | MCCT_NON_ENCRYPTED);
			P(MPT_UID, "SendUID")
			P(MPT_UID, "RecvUID")
			P(MPT_BLOB, "Data")
		C(MC_AGENT_ALLOW_TUNNELING_TCP, "Agent.AllowTunnelingTCP", "Allow Tunneling by TCP", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED);
		C(MC_AGENT_ALLOW_TUNNELING_UDP, "Agent.AllowTunnelingUDP", "Allow Tunneling by UDP", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED);
		C(MC_AGENT_DEBUGPING, "Agent.DebugPing", "Debug Ping Test for Agent", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED);
			P(MPT_UID, "TestUID")
		C(MC_AGENT_DEBUGTEST, "Agent.DebugTest", "Trigger Debug code for Agent", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED);
			P(MPT_STR, "strMsg")

		C(MC_UDP_PING, "Peer.Ping", "Ping", MCDT_PEER2PEER | MCCT_NON_ENCRYPTED)
			P(MPT_UINT, "TimeStamp");
		C(MC_UDP_PONG, "Peer.Pong", "Pong", MCDT_PEER2PEER | MCCT_NON_ENCRYPTED)
			P(MPT_UINT,"IPAddress");
			P(MPT_UINT, "TimeStamp");
	}


	// Alias
//	CA("connect", "Net.Connect");

	// MatchServer Schedule관련.
	C( MC_MATCH_SCHEDULE_ANNOUNCE_MAKE, "Announce.", "make announce for scheduler.", MCDT_LOCAL )
		P( MPT_STR, "strAnnounce" )
	C( MC_MATCH_SCHEDULE_ANNOUNCE_SEND, "Announce.", "send announce of scheduler.", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_STR, "strAnnounce" )
	C( MC_MATCH_SCHEDULE_CLAN_SERVER_SWITCH_DOWN, "Switch clan server status.", "if server type is clan server, then this command is can chage server status.", MCDT_LOCAL );
		// P( MPT_BOOL, "bEnable" )
	C( MC_MATCH_SCHEDULE_CLAN_SERVER_SWITCH_ON, "Switch clan server status.", "up", MCDT_LOCAL );

	C( MC_MATCH_SCHEDULE_STOP_SERVER, "MC_MATCH_SCHEDULE_STOP_SERVER", "stop server", MCDT_LOCAL );
		P( MPT_STR, "announce" )

	/// Keeper Manager && Keeper, Keeper && Server.
	C( MC_KEEPER_MANAGER_CONNECT, "test", "test", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_INT, "test code" )
	C( MC_RESPONSE_KEEPER_MANAGER_CONNECT, "MC_RESPONSE_KEEPER_MANAGER_CONNECT", "connect", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_UID, "KeeperManagerUID" )

	C( MC_REQUEST_KEEPERMGR_ANNOUNCE, "MC_REQUEST_KEEPERMGR_ANNOUNCE", "keeper manager request to keeper do that announce to it's match server", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_STR, "announce" )

	C( MC_REQUEST_KEEPER_ANNOUNCE, "MC_REQUEST_KEEPER_ANNOUNCE", "keeper request to matchserver do that announce", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_STR, "announce" )

	C( MC_CHECK_KEEPER_MANAGER_PING, "Check ping", "Check ping", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )

	C( MC_REQUEST_MATCHSERVER_STATUS, "request matchserver status", "request matchserver status from keeper", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )

	C( MC_RESPONSE_MATCHSERVER_STATUS, "response matchserver ststus", "response matchserver status", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_INT, "is open DB" )
		P( MPT_STR, "server release version" );
		P( MPT_UCHAR, "connected agent count" );

	// 2005.06.02 ~ 
	C( MC_REQUEST_DOWNLOAD_SERVER_PATCH_FILE, "MC_REQUEST_DOWNLOAD_SERVER_PATCH_FILE", "request download server patch file", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	
	C( MC_REQUEST_STOP_SERVER, "MC_REQUEST_STOP_SERVER", "request stop server", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	
	C( MC_REQUEST_CONNECTION_STATE, "MC_REQUEST_CONNECTION_STATE", "request current server state", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	C( MC_RESPONSE_CONNECTION_STATE, "MC_RESPONSE_CONNECTION_STATE", "response current server state", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_INT, "resut" )
	C( MC_REQUEST_SERVER_HEARBEAT, "MC_REQUEST_SERVER_HEARBEAT", "request server hearbeat check", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	C( MC_RESPONSE_SERVER_HEARHEAT, "MC_RESPONSE_SERVER_HEARHEAT", "response server hearbeat check", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )

	C( MC_REQUEST_START_SERVER, "MC_REQUEST_START_SERVER", "request start match server", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	
	C( MC_REQUEST_KEEPER_CONNECT_MATCHSERVER, "MC_REQUEST_KEEPER_CONNECT_MATCHSERVER", "request keeper connect to match server", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED );
	C( MC_RESPONSE_KEEPER_CONNECT_MATCHSERVER, "MC_RESPONSE_KEEPER_CONNECT_MATCHSERVER", "response keeper connect to match server", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED );
		P( MPT_UID, "uid" )

	C( MC_REQUEST_REFRESH_SERVER, "MC_REQUEST_REFRESH_SERVER", "request check match server heartbeat", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )

	C( MC_REQUEST_PREPARE_SERVER_PATCH, "MC_REQUEST_PREPARE_SERVER_PATCH", "request prepare patch", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	
	C( MC_REQUEST_SERVER_PATCH, "MC_REQUEST_SERVER_PATCH", "request patching", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	
	C( MC_REQUEST_LAST_JOB_STATE, "MC_REQUEST_LAST_JOB_STATE", "request last job state", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	C( MC_RESPONSE_LAST_JOB_STATE, "MC_RESPONSE_LAST_JOB_STATE", "response last job state", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_INT, "job" )
		P( MPT_INT, "result" )

	C( MC_REQUEST_CONFIG_STATE, "MC_REQUEST_CONFIG_STATE", "request config state", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	C( MC_RESPONSE_CONFIG_STATE, "MC_RESPONSE_CONFIG_STATE", "response config state", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_INT, "server config" )
		P( MPT_INT, "agent config" )
		P( MPT_INT, "download config" )
		P( MPT_INT, "prepare config" )
		P( MPT_INT, "patch config" )

	C( MC_REQUEST_SET_ONE_CONFIG, "MC_REQUEST_SET_ONE_CONFIG", "reqeust set one config", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_INT, "config id" )
		P( MPT_INT, "confing state" )
	C( MC_RESPONSE_SET_ONE_CONFIG, "MC_RESPONSE_SET_ONE_CONFIG", "response set one config", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_INT, "config id" )
		P( MPT_INT, "confing state" )

	C( MC_REQUEST_STOP_AGENT_SERVER, "MC_REQUEST_STOP_AGENT_SERVER", "request stop agent", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
    
    C( MC_REQUEST_START_AGENT_SERVER, "MC_REQUEST_START_AGENT_SERVER", "request start agent", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	
	C( MC_REQUEST_DOWNLOAD_AGENT_PATCH_FILE, "MC_REQUEST_DOWNLOAD_AGENT_PATCH_FILE", "request download agent patch file", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	
	C( MC_REQUEST_PREPARE_AGENT_PATCH, "MC_REQUEST_PREPARE_AGENT_PATCH", "request prepare agent patch", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	
    C( MC_REQUEST_AGENT_PATCH, "MC_REQUEST_AGENT_PATCH", "request agent patch", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	
	C( MC_REQUEST_RESET_PATCH, "MC_REQUEST_RESET_PATCH", "request reset patch job state", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )

	C( MC_REQUEST_DISCONNECT_SERVER, "MC_REQUEST_DISCONNECT_SERVER", "request disconnect match server", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )

	C( MC_REQUEST_REBOOT_WINDOWS, "MC_REQUEST_REBOOT_WINDOWS", "request restart windows", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )

	C( MC_REQUEST_ANNOUNCE_STOP_SERVER, "MC_REQUEST_ANNOUNCE_STOP_SERVER", "request stop server with administrator announce.", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	C( MC_RESPONSE_ANNOUNCE_STOP_SERVER, "MC_RESPONSE_ANNOUNCE_STOP_SERVER", "response stop server with administrator announce.", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )

	C( MC_REQUEST_KEEPER_MANAGER_SCHEDULE, "MC_REQUEST_KEEPER_MANAGER_SCHEDULE", "reqeust keeper manager schedule", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_INT, "type" )
		P( MPT_INT, "year" )
		P( MPT_INT, "month" )
		P( MPT_INT, "day" )
		P( MPT_INT, "hour" )
		P( MPT_INT, "min" )
		P( MPT_INT, "count" )
		P( MPT_INT, "command" )
		P( MPT_STR, "announce" )
	C( MC_RESPONSE_KEEPER_MANAGER_SCHEDULE, "MC_RESPONSE_KEEPER_MANAGER_SCHEDULE", "response keeper manager schedule", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_INT, "command type" )
		P( MPT_CHAR, "result" )

	C( MC_REQUEST_SERVER_AGENT_STATE, "MC_REQUEST_SERVER_AGENT_STATE", "request current state of server and agent", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	C( MC_RESPONSE_SERVER_AGENT_STATE, "MC_RESPONSE_SERVER_AGENT_STATE", "response current state of server and agent", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_INT, "server state" )
		P( MPT_INT, "agent state" )

	C( MC_REQUEST_SERVER_STATUS, "MC_REQUEST_SERVER_STATUS", "request server status", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	C( MC_RESPONSE_SERVER_STATUS, "MC_RESPONSE_SERVER_STATUS", "response server status resquest", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_INT, "is open DB" )
		P( MPT_STR, "server release vision" )
		P( MPT_STR, "server file was last modified" )
		P( MPT_STR, "agent file was last modified" )
		P( MPT_STR, "keeper file was last modified" )
		P( MPT_UINT64, "server file size" )
		P( MPT_UINT64, "agent file size" )
		P( MPT_UINT64, "keeper file size" )
		P( MPT_UCHAR, "agent count" )

	C( MC_REQUEST_START_SERVER_SCHEDULE, "MC_REQUEST_START_SERVER_SCHEDULE", "start server.", MCDT_LOCAL )

	C( MC_REQUEST_WRITE_CLIENT_CRC, "MC_REQUEST_WRITE_CLIENT_CRC", "request gunz client file crc32 checksum write on server.ini.", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_UINT, "gunz client file crc32 checksum" )
	C( MC_RESPONSE_WRITE_CLIENT_CRC, "MC_RESPONSE_WRITE_CLIENT_CRC", "response write client crc32 request", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_BOOL, "result" )
	C( MC_REQUEST_KEEPER_RELOAD_SERVER_CONFIG, "MC_REQUEST_KEEPER_RELOAD_SERVER_CONFIG", "keeper manager send to keeper request server reload server.ini file.", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_STR, "file list" )
	C( MC_REQUEST_RELOAD_CONFIG, "MC_REQUEST_RELOAD_CONFIG", "keeper request server reload server.ini file", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_STR, "file list" )
	C( MC_REQUEST_KEEPER_ADD_HASHMAP, "MC_REQUEST_KEEPER_ADD_HASHMAP", "", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_STR, "new hash value" )
	C( MC_RESPONSE_KEEPER_ADD_HASHMAP, "MC_RESPONSE_KEEPER_ADD_HASHMAP", "", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_BOOL, "result" )
	C( MC_REQUEST_ADD_HASHMAP, "MC_REQUEST_ADD_HASHMAP", "", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_STR, "new hash value" )
	C( MC_RESPONSE_ADD_HASHMAP, "MC_RESPONSE_ADD_HASHMAP", "", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_BOOL, "result" )
	///


	// 퀘스트 아이템 관련 커맨드.
	C( MC_MATCH_REQUEST_CHAR_QUEST_ITEM_LIST, "Quest item", "Request my quest item list", MCDT_MACHINE2MACHINE )
		P( MPT_UID, "uid" );
	C( MC_MATCH_RESPONSE_CHAR_QUEST_ITEM_LIST, "Quest item", "Response my quest item list", MCDT_MACHINE2MACHINE )
		P( MPT_BLOB, "My quest item list" );

    C( MC_MATCH_REQUEST_BUY_QUEST_ITEM, "Quest item", "Request buy quest item", MCDT_MACHINE2MACHINE )
		P( MPT_UID, "uidChar" )
		P( MPT_INT, "QuestItemID" )
		P( MPT_INT, "QuestItemCount" )

	C( MC_MATCH_RESPONSE_BUY_QUEST_ITEM, "Quest item", "Response buy quest item", MCDT_MACHINE2MACHINE )
		P( MPT_INT, "Result" )
		P( MPT_INT, "Player Bounty" )

	C( MC_MATCH_REQUEST_SELL_QUEST_ITEM, "Quest item", "Request sell quest item", MCDT_MACHINE2MACHINE )
		P( MPT_UID, "uidChar" )
		P( MPT_INT, "QuestItemID" )
		P( MPT_INT,	"Count" )
	C( MC_MATCH_RESPONSE_SELL_QUEST_ITEM, "Quest item", "Response sell quest item", MCDT_MACHINE2MACHINE )
		P( MPT_INT, "Result" )
		P( MPT_INT, "Player Bounty" )

	C( MC_MATCH_USER_REWARD_QUEST, "Quest", "Quest reward.", MCDT_MACHINE2MACHINE )
		P( MPT_INT, "XP" )
		P( MPT_INT, "Bounty" )
		P( MPT_BLOB, "Reward quest item" )
		P( MPT_BLOB, "Reward ZItem" )
		// P( MPT_BLOB, "Monster bible info" ) 사용하지 않기로 함.
		
	C( MC_MATCH_REQUEST_DROP_SACRIFICE_ITEM, "Quest", "Request drop sacrifice item", MCDT_MACHINE2MACHINE )
		P( MPT_UID, "Drop item owner" )
		P( MPT_INT, "Slot index" )
		P( MPT_INT, "ItemID" )
	C( MC_MATCH_RESPONSE_DROP_SACRIFICE_ITEM, "Quest", "Response drop sacrifice item", MCDT_MACHINE2MACHINE )
		P( MPT_INT, "Result" )
		P( MPT_UID, "requester of drop sacrifice item." )
		// P( MPT_UID, "owner of was drop." )	// MUID(0, 0)이면 빈 슬롯. 방장일 경우만 사용.
		P( MPT_INT, "Slot index" )
		P( MPT_INT, "ItemID" )

	C( MC_MATCH_REQUEST_CALLBACK_SACRIFICE_ITEM, "Quest", "Request callback sacrifice item", MCDT_MACHINE2MACHINE )
		P( MPT_UID, "Callback item requester" )
		P( MPT_INT, "Slot index" )
		P( MPT_INT, "ItemID" )
	C( MC_MATCH_RESPONSE_CALLBACK_SACRIFICE_ITEM, "Quest", "Request callback sacrifice item", MCDT_MACHINE2MACHINE )
		P( MPT_INT, "Result" )
		P( MPT_UID, "requester of callback sacrifice item." )
		// P( MPT_UID, "owner of was drop" )	// 방장일 경우만 사용.
		P( MPT_INT, "Slot index" )
		P( MPT_INT, "ItemID" )
	C( MC_MATCH_REQUEST_SLOT_INFO, "Quest", "Request slot info", MCDT_MACHINE2MACHINE )
		P( MPT_UID, "Sender" )
	C( MC_MATCH_RESPONSE_SLOT_INFO, "Quest", "Response slot info", MCDT_MACHINE2MACHINE )
		P( MPT_UID, "Owner 1" )
		P( MPT_INT, "ItemID 1" )
		P( MPT_UID, "Owner 2");
		P( MPT_INT, "ItemID 2" )

	C( MC_QUEST_REQUEST_QL, "Quest", "Request stage quest level", MCDT_MACHINE2MACHINE )
		P( MPT_UID, "sender" );
	C( MC_QUEST_RESPONSE_QL, "Quest", "Response stage quest level", MCDT_MACHINE2MACHINE )
		P( MPT_INT, "Quest level" )
	C( MC_QUEST_SURVIVAL_RESULT, "Quest", "Send survival result", MCDT_MACHINE2MACHINE )
		P( MPT_INT, "Reached round" )
		P( MPT_INT, "Point" )
	C( MC_SURVIVAL_RANKINGLIST, "Quest", "Send survival top ranking list", MCDT_MACHINE2MACHINE )
		P( MPT_BLOB, "Ranking list" )
	C( MC_SURVIVAL_PRIVATERANKING, "Quest", "Send survival private ranking", MCDT_MACHINE2MACHINE )
		P( MPT_UINT, "Rank" )
		P( MPT_UINT, "Point" )


	C( MC_GAME_START_FAIL, "Quest", "Failed start quest.", MCDT_MACHINE2MACHINE )
		P( MPT_INT, "Failed type." )
		P( MPT_UID, "pair param" )
		
	C( MC_MATCH_NEW_MONSTER_INFO, "monster info", "monster info", MCDT_MACHINE2MACHINE )
		P( MPT_CHAR, "monster db index" )

	C( MC_MATCH_REQUEST_MONSTER_BIBLE_INFO, "Quest", "request monster bible info", MCDT_MACHINE2MACHINE )
		P( MPT_UID, "requester" );

	C( MC_MATCH_RESPONSE_MONSTER_BIBLE_INFO, "Quest", "response monster bible info", MCDT_MACHINE2MACHINE )
		P( MPT_UID, "requester" );
		P( MPT_BLOB, "Monster bible info" );

	C( MC_REQUEST_SERVER_LIST_INFO, "MC_REQUEST_SERVER_LIST_INFO", "request connectable server list info.", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
	C( MC_RESPONSE_SERVER_LIST_INFO, "MC_RESPONSE_SERVER_LIST_INFO", "response connectable server list info", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_BLOB, "server list" )
	C( MC_RESPONSE_BLOCK_COUNTRY_CODE_IP, "MC_RESPONSE_BLOCK_COUNTRY_CODE_IP", "response connected ip country code is blocked", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_STR, "Country code" )
		P( MPT_STR, "Routing URL" )

	// filter.
	C( MC_RESPONSE_BLOCK_COUNTRYCODE, "MC_RESPONSE_BLOCK_COUNTRYCODE", "response block ip connected.", MCDT_MACHINE2MACHINE | MCCT_NON_ENCRYPTED )
		P( MPT_STR, "Comment" )
	C( MC_LOCAL_UPDATE_USE_COUNTRY_FILTER, "MC_LOCAL_UPDATE_USE_COUNTRY_FILTER", "update use country filter.", MCDT_LOCAL )

	C( MC_LOCAL_GET_DB_IP_TO_COUNTRY, "MC_LOCAL_GET_DB_IP_TO_COUNTRY", "get db ip to country code.", MCDT_LOCAL )
	C( MC_LOCAL_GET_DB_BLOCK_COUNTRY_CODE, "MC_LOCAL_GET_DB_BLOCK_COUNTRY_CODE", "get db block country code.", MCDT_LOCAL )
	C( MC_LOCAL_GET_DB_CUSTOM_IP, "MC_LOCAL_GET_DB_CUSTOM_IP", "get db custom ip.", MCDT_LOCAL )

	C( MC_LOCAL_UPDATE_IP_TO_COUNTRY, "MC_LOCAL_UPDAET_IP_TO_COUNTRY", "update ip to country code.", MCDT_LOCAL )
	C( MC_LOCAL_UPDATE_BLOCK_COUTRYCODE, "MC_LOCAL_UPDAET_BLOCK_COUTRYCODE", "update block country code.", MCDT_LOCAL )
	C( MC_LOCAL_UPDATE_CUSTOM_IP, "MC_LOCAL_UPDAET_CUSTOM_IP", "update custom ip.", MCDT_LOCAL )
	C( MC_LOCAL_UPDATE_ACCEPT_INVALID_IP, "MC_LOCAL_UPDATE_ACCEPT_INVALID_IP", "update accept invalid ip.", MCDT_LOCAL )
	// filter

	// XTRAP 4.1에는 사용하지 않는다.(이전과의 호환으로 디파인만 존재한다.)
	C( MC_REQUEST_XTRAP_HASHVALUE, "MC_REQUEST_XTRAP_HASHVALUE", "request new client hash value", MCDT_MACHINE2MACHINE )
		P( MPT_STR, "new random value" )
	C( MC_RESPONSE_XTRAP_HASHVALUE, "MC_RESPONSE_XTRAP_HASHVALUE", "response new client hash value", MCDT_MACHINE2MACHINE )
		P( MPT_STR, "new hash value" )
	C( MC_REQUEST_XTRAP_DETECTCRACK, "MC_REQUEST_XTRAP_DETECTCRACK", "request Irrational User", MCDT_MACHINE2MACHINE )
		P( MPT_BLOB, "communication buffer" )
	// XTRAP 실제 사용하는 커맨드
	C( MC_REQUEST_XTRAP_SEEDKEY, "MC_REQUEST_XTRAP_SEEDKEY", "request new client seed key", MCDT_MACHINE2MACHINE )
		P( MPT_BLOB, "communication buffer" )
	C( MC_RESPONSE_XTRAP_SEEDKEY, "MC_RESPONSE_XTRAP_SEEDKEY", "response client seed key", MCDT_MACHINE2MACHINE )
		P( MPT_BLOB, "communication buffer" )
	
	C( MC_REQUEST_GAMEGUARD_AUTH, "MC_REQUEST_GAMEGUARD_AUTH", "requet new gameguard auth", MCDT_MACHINE2MACHINE )
		P( MPT_UINT, "index" )
		P( MPT_UINT, "value1" )
		P( MPT_UINT, "value2" )
		P( MPT_UINT, "value3" )

	C( MC_RESPONSE_GAMEGUARD_AUTH, "MC_RESPONSE_GAMEGUARD_AUTH", "game client response new gameguard auth to server", MCDT_MACHINE2MACHINE )
		P( MPT_UINT, "index" )
		P( MPT_UINT, "value1" )
		P( MPT_UINT, "value2" )
		P( MPT_UINT, "value3" )

	C( MC_REQUEST_FIRST_GAMEGUARD_AUTH, "MC_REQUEST_GAMEGUARD_AUTH", "requet new gameguard auth", MCDT_MACHINE2MACHINE )
		P( MPT_UINT, "index" )
		P( MPT_UINT, "value1" )
		P( MPT_UINT, "value2" )
		P( MPT_UINT, "value3" )

	C( MC_RESPONSE_FIRST_GAMEGUARD_AUTH, "MC_RESPONSE_GAMEGUARD_AUTH", "game client response new gameguard auth to server", MCDT_MACHINE2MACHINE )
		P( MPT_UINT, "index" )
		P( MPT_UINT, "value1" )
		P( MPT_UINT, "value2" )
		P( MPT_UINT, "value3" )

	C( MC_REQUEST_GIVE_ONESELF_UP, "MC_REQUEST_GIVE_ONESELF_UP", "give oneself up", MCDT_MACHINE2MACHINE )

	C( MC_RESPONSE_GAMBLEITEMLIST, "MC_RESPONSE_GAMBLEITEMLIST", "send gamble item info list to client", MCDT_MACHINE2MACHINE )
		P( MPT_BLOB, "Gamble item list" )

	C( MC_MATCH_ROUTE_UPDATE_STAGE_EQUIP_LOOK, "MC_MATCH_ROUTE_UPDATE_STAGE_EQUIP_LOOK", "route updated user equip info", MCDT_MACHINE2MACHINE )
		P( MPT_UID, "user uid" )
		P( MPT_INT, "parts" )
		P( MPT_INT, "itemid" );

	C( MC_REQUEST_RESOURCE_CRC32, "MC_REQUEST_RESOURCE_CRC32", "MC_REQUEST_RESOURCE_CRC32", MCDT_MACHINE2MACHINE )
		P( MPT_UINT, "key" );
	C(MC_RESPONSE_RESOURCE_CRC32, "MC_RESPONSE_RESOURCE_CRC32", "MC_RESPONSE_RESOURCE_CRC32", MCDT_MACHINE2MACHINE )
		P( MPT_UINT, "crc32" );
		P( MPT_UINT, "xor" );


	C(MC_NET_BANPLAYER_FLOODING, "MC_NET_BANPLAYER_FLOODING", "Request To Server From CommandBuilder", MCDT_LOCAL )
		P( MPT_UID, "User UID");

	C(MC_MATCH_DUELTOURNAMENT_REQUEST_JOINGAME, "MC_MATCH_DUELTOURNAMENT_REQUEST_JOINGAME", "Request To Join Duel Tournament From Client", MCDT_MACHINE2MACHINE)
		P( MPT_UID, "User UID")
		P( MPT_INT, "TournamentType");

	C(MC_MATCH_DUELTOURNAMENT_RESPONSE_JOINGAME, "MC_MATCH_DUELTOURNAMENT_RESPONSE_JOINGAME", "Respone to Client About joinning dt", MCDT_MACHINE2MACHINE)
		P( MPT_INT, "Result");

	C(MC_MATCH_DUELTOURNAMENT_REQUEST_CANCELGAME, "MC_MATCH_DUELTOURNAMENT_REQUEST_CANCELGAME", "Request To Cancel Duel Tournament Game From Client", MCDT_MACHINE2MACHINE)
		P( MPT_UID, "User UID")
		P( MPT_INT, "TournamentType");

	C(MC_MATCH_DUELTOURNAMENT_CHAR_INFO, "MC_MATCH_DUELTOURNAMENT_CHAR_INFO", "DuelTournament Character Info", MCDT_MACHINE2MACHINE)
		P( MPT_INT, "TP")
		P( MPT_INT, "Wins")
		P( MPT_INT, "Loses")
		P( MPT_INT, "Ranking")
		P( MPT_INT, "RankingIncrease")
		P( MPT_INT, "Champion")
		P( MPT_INT, "LastWeekGrade");

	C(MC_MATCH_DUELTOURNAMENT_CHAR_INFO_PREVIOUS, "MC_MATCH_DUELTOURNAMENT_CHAR_INFO_PREVIOUS", "DuelTournament Character Info Previous", MCDT_MACHINE2MACHINE)
		P( MPT_INT, "TP")
		P( MPT_INT, "Wins")
		P( MPT_INT, "Loses")
		P( MPT_INT, "Ranking")
		P( MPT_INT, "Champion");

	C(MC_MATCH_DUELTOURNAMENT_REQUEST_SIDERANKING_INFO, "MC_MATCH_DUELTOURNAMENT_SIDERANKING_INFO", "Request to Server - Side Ranking Info", MCDT_MACHINE2MACHINE)
		P( MPT_UID, "User UID");

	C(MC_MATCH_DUELTOURNAMENT_RESPONSE_SIDERANKING_INFO, "MC_MATCH_DUELTOURNAMENT_SIDERANKING_INFO", "Response to Client - Side Ranking Info", MCDT_MACHINE2MACHINE)
		P( MPT_BLOB, "RankingInfo");

	C(MC_MATCH_DUELTOURNAMENT_GROUPRANKING_INFO, "MC_MATCH_DUELTOURNAMENT_GROUPRANKING_INFO", "Group Ranking Info to Client", MCDT_MACHINE2MACHINE)
		P( MPT_BLOB, "RankingInfo");	

	C(MC_MATCH_DUELTOURNAMENT_PREPARE_MATCH, "MC_MATCH_DUELTOURNAMENT_PREPARE_MATCH", "Prepare DuelTournament Match to Client", MCDT_MACHINE2MACHINE)
		P( MPT_UID,		"uidStage")
		P( MPT_INT,		"TournamentType")
		P( MPT_BLOB,	"PlayerInfo");

	C(MC_MATCH_DUELTOURNAMENT_LAUNCH_MATCH, "MC_MATCH_DUELTOURNAMENT_LAUNCH_MATCH", "Launch Duel Tournament Game", MCDT_MACHINE2MACHINE)
		P(MPT_UID, "uidStage")
		P(MPT_STR, "MapName");

	C(MC_MATCH_DUELTOURNAMENT_CANCEL_MATCH, "MC_MATCH_DUELTOURNAMENT_CANCEL_MATCH", "Canel Duel Tournament Game", MCDT_MACHINE2MACHINE)		
		P(MPT_INT, "ErrorCode");

	C(MC_MATCH_DUELTOURNAMENT_NOT_SERVICE_TIME, "MC_MATCH_DUELTOURNAMENT_CANCEL_MATCH", "Canel Duel Tournament Game", MCDT_MACHINE2MACHINE)		
		P(MPT_INT, "OpenStartTime");
		P(MPT_INT, "OpenEndTime");

	C(MC_MATCH_DUELTOURNAMENT_GAME_INFO, "Match.DuelTournament.Game Info", "Duel Tournament Game Info", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "GameInfo");

	C(MC_MATCH_DUELTOURNAMENT_GAME_ROUND_RESULT_INFO, "Match.DuelTournament.Game Round Result Info", "Duel Tournament Game Round-Result Info", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "GameRoundResultInfo");

	C(MC_MATCH_DUELTOURNAMENT_GAME_MATCH_RESULT_INFO, "Match.DuelTournament.Game Match Result Info", "Duel Tournament Game Match-Result Info", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "GameMatchResultInfo");

	C(MC_MATCH_DUELTOURNAMENT_GAME_PLAYER_STATUS, "Match.DuelTournament.Game Player Status Info", "Duel Tournament Game Player Status Info", MCDT_MACHINE2MACHINE)
		P(MPT_UID, "PlayerUID")
		P(MPT_FLOAT, "PlayerAttackPoint")
		P(MPT_FLOAT, "PlayerHealthPoint")
		P(MPT_FLOAT, "PlayerAmorPoint");

	C(MC_MATCH_DUELTOURNAMENT_GAME_NEXT_MATCH_PLYAERINFO, "Match.DuelTournament.Game Next Match Player Info", "Duel Tournament Game Next Match Player Info", MCDT_MACHINE2MACHINE)
		P(MPT_BLOB, "NextMatchPlayerInfo");

	END_CMD_DESC();
}
	
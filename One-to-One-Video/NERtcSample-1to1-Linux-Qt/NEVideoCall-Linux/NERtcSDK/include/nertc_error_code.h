/** @file nertc_error_code.h
  * @brief The definition of error codes of NERtc SDK.
  * @copyright (c) 2021, NetEase Inc. All rights reserved.
  */

#ifndef NERTC_ERROR_CODE_H
#define NERTC_ERROR_CODE_H

 /**
 * @namespace nertc
 * @brief namespace nertc
 */
namespace nertc
{
/** Error codes.

 Error codes are returned when a problem that cannot be recovered without app intervention has occurred. 
*/
typedef enum
{
	kNERtcNoError = 0,		/**< No errors. */
	//Error codes are returned when resources are wrongly assigned. Such kind of error code is not returned when the SDK sends the normal permissions.
	/** No permissions. Possible reasons: 
	 * - RTC 2.0 service is not enabled, whose trial period is overdue or fees are not renewed.
	 * - Token is not specified in safe mode when joining a channel.
	 * - Other permission-related problems.
	 */
	kNERtcErrChannelReservePermissionDenied = 403,	
	kNERtcErrChannelReserveTimeOut = 408,			/**< Request timeouts. */
	kNERtcErrChannelReserveErrorParam = 414,		/**< Error codes are returned when parameters are requested in the server. */
	kNERtcErrChannelReserveServerFail = 500,		/**< Unknown errors are returned when channels are assigned in the server. */
	kNERtcErrChannelReserveMoreThanTwoUser = 600,	/**< Only two users are supported in the same channel. If the third user wants to share the same channel name, assign another channel. */

    //livestream task
    kNERtcErrLsTaskRequestInvalid = 1301,	        /**< Invalid permission that is replaced by following operations. */
    kNERtcErrLsTaskIsInvaild = 1400,	            /**< Parameter format error. */
    kNERtcErrLsTaskRoomExited = 1401,	            /**< Exited the channel. */
    kNERtcErrLsTaskNumLimit = 1402,	                /**< Streaming tasks are over the limit. */
    kNERtcErrLsTaskDuplicateId = 1403,	            /**< Duplicates ID of streaming tasks. */
    kNERtcErrLsTaskNotFound = 1404,	                /**< No ID task or no channels. */
    kNERtcErrLsTaskRequestErr = 1417,	            /**< Permission failures. */
    kNERtcErrLsTaskInternalServerErr = 1500,	    /**< Internal errors in the server. */
    kNERtcErrLsTaskInvalidLayout = 1501,	        /**< Layout parameter errors. */
    kNERtcErrLsTaskUserPicErr = 1512,	            /**< Image errors of users. */


	//Other errors.
	kNERtcErrChannelStartFail = 11000,				/**< Fails to initiate a channel. */
	kNERtcErrChannelDisconnected = 11001,			/**< Disconnects the channel. */
	kNERtcErrVersionSelfLow = 11002,				/**< The local SDK version is too low to achieve compatibility. */
	kNERtcErrVersionRemoteLow = 11003,				/**< The remote SDK version is too low to achieve compatibility. */
	kNERtcErrChannelClosed = 11004,					/**< The channel is disabled. */
	kNERtcErrChannelKicked = 11005,					/**< The ID is removed from the channel. */
	kNERtcErrDataError = 11400,						/**< Data error. */
	kNERtcErrInvalid = 11403,						/**< Invalid operation. */
	// Server connection error.
	kNERtcErrChannelJoinTimeOut = 20101,			/**< Request timeouts. */
	kNERtcErrChannelJoinMeetingModeError = 20102,	/**< Meeting mode error. */
	kNERtcErrChannelJoinRtmpModeError = 20103,		/**< rtmp users join the channel that applies the non-rtmp protocol. */
	kNERtcErrChannelJoinRtmpNodesError = 20104,		/**< Users capacity is exceeded in the room that applies to the rtmp protocol. */
	kNERtcErrChannelJoinRtmpHostError = 20105,		/**< The role of host is specified. */
	kNERtcErrChannelJoinRtmpCreateError = 20106,	/**< Relayed live streaming is required where the host does not create the room. */
	kNERtcErrChannelJoinLayoutError = 20208,		/**< Errors occur when the host customized the channel layout. */
	kNERtcErrChannelJoinInvalidParam = 20400,		/**< Error parameters. */
	kNERtcErrChannelJoinDesKey = 20401,				/**< Password encryption error. */
	kNERtcErrChannelJoinInvalidRequst = 20417,		/**< Error request. */
	kNERtcErrChannelServerUnknown = 20500,			/**< Internal errors in the server. */
	//Engine error code
	kNERtcErrFatal = 30001,                         /**< Common errors. */
	kNERtcErrOutOfMemory = 30002,                   /**< Out of memory. */
	kNERtcErrInvalidParam = 30003,                  /**< Invalid parameters. */
	kNERtcErrNotSupported = 30004,                  /**< Unsupported operation. */
	kNERtcErrInvalidState = 30005,                  /**< Unsupported operations in the current state. */
	kNERtcErrLackOfResource = 30006,                /**< Depleted resources. */
	kNERtcErrInvalidIndex = 30007,                  /**< Invalid index. */
	kNERtcErrDeviceNotFound = 30008,                /**< Device is not found. */
	kNERtcErrInvalidDeviceSourceID = 30009,         /**< Invalid device ID. */
	kNERtcErrInvalidVideoProfile = 30010,           /**< Invalid profile type of video. */
	kNERtcErrCreateDeviceSourceFail = 30011,        /**< Device creation errors. */
	kNERtcErrInvalidRender = 30012,                 /**< Invalid rendering device. */
	kNERtcErrDevicePreviewAlreadyStarted = 30013,   /**< Device is already enabled. */
	kNERtcErrTransmitPendding = 30014,              /**< Transmission error. */
	kNERtcErrConnectFail = 30015,                   /**< Server connection error. */
    kNERtcErrCreateDumpFileFail = 30016,            /**< Fails to create Audio dump file. */
    kNERtcErrStartDumpFail = 30017,                 /**< Fails to enable Audio dump file. */
    kNERtcErrDesktopCaptureInvalidState = 30020,    /**< Fails to enable desktop screen recording if camera is started at the same time. */
    kNERtcErrDesktopCaptureInvalidParam = 30021,    /**< Parameters are invalid when the desktop screen recording is implemented. */
    kNERtcErrDesktopCaptureNotReady     = 30022,    /**< Desktop screen recording is not ready. */

	kNERtcErrChannelAlreadyJoined = 30100,    /**< Repeatedly joins the channel. */
	kNERtcErrChannelNotJoined = 30101,        /**< Does not join the channel. */
	kNERtcErrChannelRepleatedlyLeave = 30102, /**< Repeatedly leaves the channel. */
	kNERtcErrRequestJoinChannelFail = 30103,  /**< Fails to join the channel. */
	kNERtcErrSessionNotFound = 30104,         /**< Session is not found. */
	kNERtcErrUserNotFound = 30105,            /**< The user is not found. */
	kNERtcErrInvalidUserID = 30106,           /**< Invalid user ID. */
	kNERtcErrMediaNotStarted = 30107,         /**< Users do not connect the multi-media data. */
	kNERtcErrSourceNotFound = 30108,          /**< Source is not found. */
    kNERtcErrSwitchChannelInvalidState = 30109,        /**< Invalid state of switching channels. */
    kNERtcErrChannelMediaRelayInvalidState = 30110,    /**< Invalid state of relaying media streams. */
    kNERtcErrChannelMediaRelayPermissionDenied = 30111,/**< Invalid permissions of relaying streams. Check whether the mode is set as audience mode or 1v1 mode. */
    kNERtcErrChannelMediaRelayStopFailed = 30112,      /**< If you fail to stop relaying media streams, check whether the media stream forwarding is enabled. */
    kNERtcErrEncryptNotSuitable = 30113,               /**< If you set the different encryption password of media streams from other members in the room, you fail to join the room.  Sets new encryption password thorough enableEncryption. */
    
    kNERtcErrConnectionNotFound = 30200,          /**< Connection is not found. */
	kNERtcErrStreamNotFound = 30201,              /**< Media streams are not found. */
	kNERtcErrAddTrackFail = 30202,                /**< Fails to join the track. */
	kNERtcErrTrackNotFound = 30203,               /**< Track is not found. */
	kNERtcErrMediaConnectionDisconnected = 30204, /**< Media disconnection. */
	kNERtcErrSignalDisconnected = 30205,          /**< Signalling disconnection. */
	kNERtcErrServerKicked = 30206,                /**< The user is removed from the room. */
    kNERtcErrKickedForRoomClosed = 30207,         /**< Removed for the channel is already disabled. */
    kNERtcErrChannelLeaveBySwitchAction = 30208,  /**< Removed for the destination room is disabled. */
    
    kNERtcRuntimeErrADMNoAuthorize = 40000,              /**< No permission of audio devices. */
    
    kNERtcRuntimeErrVDMNoAuthorize = 50000,              /**< No permission of video devices. */
    
    kNERtcRuntimeErrScreenCaptureNoAuthorize = 60000,    /**< No permission of video recording. */

} NERtcErrorCode;

/** @enum NERtcRoomServerErrorCode The related error codes of room server. TODO:NERtcErrorCode. */
typedef enum
{
	kNERtcRoomServerErrOK               = 200,				/**< Successful operation. */
	kNERtcRoomServerErrAuthError        = 401,			    /**< Authentication error. */
	kNERtcRoomServerErrChannelNotExist  = 404,	            /**< Channel is not found. */
	kNERtcRoomServerErrUidNotExist      = 405,		        /**< The uid of the channel is not found. */
	kNERtcRoomServerErrDataError        = 417,			    /**< Request data error. */
	kNERtcRoomServerErrUnknown          = 500,			    /**< Internal error that request error occurs in the TurnServer. */
	kNERtcRoomServerErrServerError      = 600,		        /**< Internal errors in the server. */
	kNERtcRoomServerErrInvilid          = 11403,			/**< Invalid operation. */
} NERtcRoomServerErrorCode;

/** @enum NERtcAudioMixingErrorCode indicates error codes of audio mixing music files.
*/
typedef enum 
{
    kNERtcAudioMixingErrorOK            = 0,      			/**< No error. */
    kNERtcAudioMixingErrorFatal         = 1,      			/**< Common error. */
	kNERtcAudioMixingErrorCanNotOpen,						/**< Audio mixing is not enabled normally. */
	kNERtcAudioMixingErrorDecode,							/**< Audio decoding error. */
	kNERtcAudioMixingErrorInterrupt,						/**< Interruption codes in the operation. */
	kNERtcAudioMixingErrorHttpNotFound,						/**< 404 file not found，only for http / https. */
	kNERtcAudioMixingErrorOpen,								/**< Fails to enable streams/files. */
	kNERtcAudioMixingErrorNInfo,							/**< Decoding information failures or timeouts. */
	kNERtcAudioMixingErrorNStream,							/**< No audio streams. */
	kNERtcAudioMixingErrorNCodec,							/**< No decoder. */
	kNERtcAudioMixingErrorNMem,								/**< No memory. */
	kNERtcAudioMixingErrorCodecOpen,						/**< Failures or timeouts of enabling decoders. */
	kNERtcAudioMixingErrorInvalidInfo,						/**< Invalid audio parameters such as channels and sample rate. */
	kNERtcAudioMixingErrorOpenTimeout,						/**< Streams/files enabling timeouts. */
	kNERtcAudioMixingErrorIoTimeout,						/**< Network io timeouts. */
	kNERtcAudioMixingErrorIo,								/**< Network io errors. */
    //kNERtcAudioMixingErrorTooFrequentCall = 101,      	/**< Music files frequently enabled. */
    //kNERtcAudioMixingErrorInterruptedEOF= 102,      		/**< Music files playbacks interrupted. */
} NERtcAudioMixingErrorCode;

/** Error codes.

Error codes are returned when a problem that cannot be recovered without app intervention has occurred.
*/
typedef enum
{
    //ADM
    kNERtcRuntimeErrADMInitRecording        = 40001,     /**< Audio device module: Errors occur when initializing recording devices. Please check whether the recording device can work properly or have limited permissions, or try reconnecting to rejoin the room. */
    kNERtcRuntimeErrADMStartRecording       = 40002,     /**< Audio device module: Errors occur when enabling recording devices. Please check whether the recording device can work properly, or try reconnecting to rejoin the room. */
    kNERtcRuntimeErrADMStopRecording        = 40003,     /**< Audio device module: Errors occur when running recording devices. Please check whether the recording device can work properly, or try reconnecting to rejoin the room. */
    kNERtcRuntimeErrADMInitPlayout          = 40004,     /**< Audio device module: Errors occur when initializing playback devices. Please check whether the playback device can work properly or have limited permissions, or try reconnecting to rejoin the room. */
    kNERtcRuntimeErrADMStartPlayout         = 40005,     /**< Audio device module: Errors occur when enabling playback devices. Please check whether the playback device can work properly, or try reconnecting to rejoin the room. */
    kNERtcRuntimeErrADMStopPlayout          = 40006,     /**< Audio device module: Errors occur when running playback devices. Please check whether the playback device can work properly, or try reconnecting to rejoin the room. */

    //VDM
    kNERtcErrVDMCameraNoFrame               = 1502,     /**< Audio device module: The Camera has no data frame. Please check the camera or switch the camera. */
    kNERtcErrVDMCameraCreateFail            = 1503,     /**< Audio device module:Fails to enable camera. Please check whether the camera has exited or occupied. */

} NERtcDMErrorCode;

} // namespace nertc

#endif

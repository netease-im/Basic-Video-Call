/** @file nertc_introduction.h
* @brief The interface preview of NERTC SDK.
* All parameter descriptions of the NERTC SDK. All string-related parameters (char *) are encoded in UTF-8.
* @copyright (c) 2021, NetEase Inc. All rights reserved.
*/


/**
 @mainpage Introduction
 @brief<p>NetEase CommsEase NERTC SDK
 We provide a comprehensive Real-time Communication (RTC) development platform that allows developers to implement Internet-based peer-to-peer audio and video calls, and group audio and video conferencing. The SDK enables users to manage audio and video devices and switch audio and video modes during calls. The SDK also implements capturing video data callbacks and offers additional features, such as personalized image enhancement. </p>
 
 - \ref nertc::IRtcEngine "IRtcEngine" interface class includes main methods that application calls. 
 - \ref nertc::IRtcEngineEx "IRtcEngineEx"  interface class includes main methods that application calls.
 - \ref nertc::IRtcEngineEventHandler "IRtcEngineEventHandler" interface class is used to send callback notifications to the application. 
 - \ref nertc::IRtcEngineEventHandlerEx "IRtcEngineEventHandlerEx" interface class is used to send extension callback notification to the application. 
 - \ref nertc::IRtcMediaStatsObserver "IRtcMediaStatsObserver" interface class is used to send notification of media callback to apps. 
 - \ref nertc::INERtcAudioFrameObserver "INERtcAudioFrameObserver" interface class is used to send callback notification that sends audio data frame to apps.
 - \ref nertc::IAudioDeviceManager "IAudioDeviceManager" interface class is used to show methods of using audio devices to applications. 
 - \ref nertc::IVideoDeviceManager "IVideoDeviceManager" interface class is used to show methods of using video devices to applications. 
 - The \ref nertc::IRtcChannel "IRtcChannel" class provides methods that enable real-time communications in a specified channel. By creating multiple RtcChannel instances, users can join multiple channels.
 - The \ref nertc::IRtcChannelEventHandler "IRtcChannelEventHandler" class provides callbacks that report events and statistics of a specified channel.
 
 <h2 id="Room management">Room management</h2>

 <table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::createNERtcEngine "createNERtcEngine"  </td>
    <td>Creates an RTC engine object. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::destroyNERtcEngine "destroyNERtcEngine"</td>
    <td>Destroys an RTC engine object. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::initialize "initialize"</td>
    <td>Initializes the NERTC SDK service. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::release "release"</td>
    <td>Destroys an IRtcEngine object. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::getVersion "getVersion"</td>
    <td>Query the SDK version number. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::setChannelProfile "setChannelProfile"</td>
    <td>Sets a room scene. </td>
    <td>V3.6.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::setClientRole "setClientRole"</td>
    <td>Sets the role of a user in live streaming. </td>
    <td>V3.9.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::joinChannel "joinChannel"</td>
    <td>Joins an RTC channel. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::leaveChannel "leaveChannel"</td>
    <td>Leaves a room. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::switchChannel "switchChannel"</td>
    <td>Switches to destination room. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::getConnectionState "getConnectionState"</td>
    <td>Gets the state of network connection. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::queryInterface "queryInterface"</td>
    <td>Gets the pointer of device administrators object. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setParameters "setParameters"</td>
    <td>Sets parameters for audio and video calls. </td>
    <td>V3.5.0</td>
  </tr>
 </table>

 ## Room event
 
 <table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onClientRoleChanged "onClientRoleChanged"</td>
    <td>Occurs when a user changes the role in live streaming. </td>
    <td>V3.9.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onJoinChannel "onJoinChannel"</td>
    <td>Occurs when a user joins a room. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onRejoinChannel "onRejoinChannel"</td>
    <td>Occurs when a user rejoins a room. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onLeaveChannel "onLeaveChannel"</td>
    <td> Occurs when a user leaves a room. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onUserJoined "onUserJoined"</td>
    <td>Occurs when a remote user joins the current room. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onUserLeft "onUserLeft"</td>
    <td>Occurs when a remote user leaves a room. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onDisconnect "onDisconnect"</td>
    <td>Occurs when the server disconnected callback. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onReconnectingStart "onReconnectingStart"</td>
    <td>Starts reconnecting callbacks. </td>
    <td>V3.7.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onConnectionStateChange "onConnectionStateChange"</td>
    <td>Occurs when the state of network connection changes. </td>
    <td>V3.8.1</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onReleasedHwResources "onReleasedHwResources"</td>
    <td>Occurs when device resources release callbacks after the call ends. </td>
    <td>V3.5.0</td>
  </tr>
</table>

 ## Audio management

 <table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setAudioProfile "setAudioProfile"</td>
    <td> Sets the audio profile. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::adjustRecordingSignalVolume "adjustRecordingSignalVolume"</td>
    <td> Adjusts the volume of captured signals. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::adjustPlaybackSignalVolume "adjustPlaybackSignalVolume"</td>
    <td> Adjusts the volume of the audio local playback. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::adjustUserPlaybackSignalVolume "adjustUserPlaybackSignalVolume"</td>
    <td> Adjusts the local playback volume of the stream from a specified remote user. </td>
    <td>V4.2.1</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::enableLocalAudio "enableLocalAudio"</td>
    <td> Stops or resumes local audio capture. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::muteLocalAudioStream "muteLocalAudioStream"</td>
    <td> Enables or disables local audio for publishing. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::subscribeRemoteAudioStream "subscribeRemoteAudioStream"</td>
    <td>Subscribes to or unsubscribes from specified audio stream. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::enableLoopbackRecording "enableLoopbackRecording"</td>
    <td> Enables audio capture through sound card. </td>
    <td>V4.4.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::adjustLoopbackRecordingSignalVolume "adjustLoopbackRecordingSignalVolume"</td>
    <td>Adjusts the volume of captured signals of sound cards. </td>
    <td>V4.4.0</td>
  </tr>
</table>
 

 ## Video management
 
 <table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::enableLocalVideo "enableLocalVideo" [1/2]</td>
    <td>Enables or disables the local video stream. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setVideoConfig "setVideoConfig" [1/2]</td>
    <td>Sets the local video configuration. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::setupLocalVideoCanvas "setupLocalVideoCanvas"</td>
    <td>Sets the local video canvas. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::setupRemoteVideoCanvas "setupRemoteVideoCanvas"</td>
    <td>Sets the remote video canvas. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setLocalRenderMode "setLocalRenderMode"</td>
    <td> Sets the local view display mode. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setRemoteRenderMode "setRemoteRenderMode"</td>
    <td>Sets display mode for remote views. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::startVideoPreview "startVideoPreview"</td>
    <td>Starts video preview. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::stopVideoPreview "stopVideoPreview"</td>
    <td>Stops video preview. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::muteLocalVideoStream "muteLocalVideoStream"</td>
    <td>Stops/Resumes sending the local video stream. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngine::subscribeRemoteVideoStream "subscribeRemoteVideoStream"</td>
    <td>Subscribes to or unsubscribes from video streams from specified remote users. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setLocalVideoMirrorMode "setLocalVideoMirrorMode" [1/2]</td>
    <td>Sets the mirror mode of the local video. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::enableSuperResolution "enableSuperResolution "</td>
    <td>Enables or disables AI super resolution. </td>
    <td>V4.4.0</td>
  </tr>
</table>
 
<h2 id="Local media events">Local media events</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onFirstVideoDataReceived "onFirstVideoDataReceived"</td>
    <td> Occurs when the first video frame from a remote user is displayed. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onFirstAudioDataReceived "onFirstAudioDataReceived"</td>
    <td> Occurs when the local receives first audio frame from a remote audio stream. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onFirstAudioFrameDecoded "onFirstAudioFrameDecoded"</td>
    <td>Occurs when the first audio frame from a remote user is decoded. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onFirstVideoFrameDecoded "onFirstVideoFrameDecoded"</td>
    <td>Occurs when the remote video is received and decoded. </td>
    <td>V3.5.0</td>
  </tr>
</table>

<h2 id="Remote media event">Remote media event</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onUserAudioStart "onUserAudioStart"</td>
    <td>Occurs when a remote user enables audio. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onUserAudioStop "onUserAudioStop"</td>
    <td>Occurs when a remote user stops audio. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onUserVideoStart "onUserVideoStart"</td>
    <td>Occurs when a remote user enables video. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onUserVideoStop "onUserVideoStop"</td>
    <td>Occurs when a remote user disables video. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onUserVideoProfileUpdate "onUserVideoProfileUpdate"</td>
    <td>Occurs when video configurations of remote users are updated. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onUserAudioMute "onUserAudioMute"</td>
    <td>Occurs when a remote user specifies whether to mute. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onUserVideoMute "onUserVideoMute"</td>
    <td>Occurs when a remote user whether to disable video. </td>
    <td>V3.5.0</td>
  </tr>
</table>

<h2 id="Stats event">Stats event</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcMediaStatsObserver::onRemoteAudioStats "onRemoteAudioStats"</td>
    <td>Occurs when the stats of the remote audio stream in the call are collected. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcMediaStatsObserver::onRtcStats "onRtcStats"</td>
    <td>Occurs when the stats of the current call is collected. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcMediaStatsObserver::onNetworkQuality "onNetworkQuality"</td>
    <td>Occurs when the stats of uplink and downlink network quality for each user are reported during the call. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcMediaStatsObserver::onLocalAudioStats "onLocalAudioStats"</td>
    <td>Occurs when the stats of the local audio stream are collected. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcMediaStatsObserver::onLocalVideoStats "onLocalVideoStats"</td>
    <td> Occurs when the stats of the local video stream are collected. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcMediaStatsObserver::onRemoteVideoStats "onRemoteVideoStats"</td>
    <td>Occurs when the stats of the video stream in the call are collected. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setStatsObserver "setStatsObserver"</td>
    <td>Registers a stats observer. </td>
    <td>V3.5.0</td>
  </tr>
</table>

## Screen sharing

| <div style="width:400px">Method</div> | <div style="width:600px">Description</div> | <div style="width:200px">Initial version</div> |
|:---|:---|:---|
| \ref nertc::IRtcEngineEx::startScreenCaptureByDisplayId "startScreenCaptureByDisplayId" | Screen sharing through screen ID. The method only applies to macOS.  | V3.5.0 |
| \ref nertc::IRtcEngineEx::startScreenCaptureByScreenRect "startScreenCaptureByScreenRect" | Screen sharing through screen ID. The method only applies to Windows.  | V3.5.0 |
| \ref nertc::IRtcEngineEx::startScreenCaptureByWindowId "startScreenCaptureByWindowId" | Screen sharing through window ID. | V3.5.0 |
| \ref nertc::IRtcEngineEx::setExcludeWindowList "setExcludeWindowList" | Sets the window list that need to be blocked in capturing screens. | V4.2.0 |
| \ref nertc::IRtcEngineEx::updateScreenCaptureRegion "updateScreenCaptureRegion" | Update screen sharing region. | V3.5.0 |
| \ref nertc::IRtcEngineEx::pauseScreenCapture "pauseScreenCapture" | Pauses screen sharing. | V3.7.0 |
| \ref nertc::IRtcEngineEx::resumeScreenCapture "resumeScreenCapture" | Resumes screen sharing. | V3.7.0 |
| \ref nertc::IRtcEngineEx::stopScreenCapture "stopScreenCapture" | Stops screen sharing. | V3.5.0 |
| \ref nertc::IRtcEngineEx::setupLocalSubStreamVideoCanvas "setupLocalSubStreamVideoCanvas" | Sets a playback canvas for local video substream. | V3.9.0 |
| \ref nertc::IRtcEngineEx::setLocalSubStreamRenderMode "setLocalSubStreamRenderMode" | Sets the zoom and rendering mode of local substream. | V3.9.0 |
| \ref nertc::IRtcEngineEx::setupRemoteSubStreamVideoCanvas "setupRemoteSubStreamVideoCanvas" | Sets a playback canvas for remote video substream. | V3.9.0 |
| \ref nertc::IRtcEngineEx::setRemoteSubSteamRenderMode "setRemoteSubSteamRenderMode" | Sets the zoom and rendering mode of remote video substream video from screen sharing. | V3.9.0 |
| \ref nertc::IRtcEngineEx::subscribeRemoteVideoSubStream "subscribeRemoteVideoSubStream" | Subscribes to or unsubscribes from remote video substream from screen sharing. You can receive the video substream data only after you subscribe to the remote video substream. | V3.9.0 |


| <div style="width:400px">Event</div> | <div style="width:600px">Description</div> | <div style="width:200px">Initial version</div> |
|:---|:---|:---|
| \ref nertc::IRtcEngineEventHandlerEx::onUserSubStreamVideoStart "onUserSubStreamVideoStart" | Occurs when a remote user starts screen sharing through the substream.  | V3.9.0 |
| \ref nertc::IRtcEngineEventHandlerEx::onUserSubStreamVideoStop "onUserSubStreamVideoStop" | Occurs when a remote user stops screen sharing through the substream.  | V3.9.0 |
| \ref nertc::IRtcEngineEventHandlerEx::onScreenCaptureStatus "onScreenCaptureStatus" | Occurs when screen sharing status changes. The method only applies to macOS.  | V4.2.0 |

<h2 id="Music file playback and mixing">Music file playback and mixing</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::startAudioMixing "startAudioMixing"</td>
    <td>Starts to play a music file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::stopAudioMixing "stopAudioMixing"</td>
    <td>Stops playing a music file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::pauseAudioMixing "pauseAudioMixing"</td>
    <td> Pauses playing a music file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::resumeAudioMixing "resumeAudioMixing"</td>
    <td>Resumes playing a music file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setAudioMixingPlaybackVolume "setAudioMixingPlaybackVolume"</td>
    <td> Sets the playback volume of a music file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setAudioMixingSendVolume "setAudioMixingSendVolume"</td>
    <td>Sets the publishing volume of a music file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::getAudioMixingPlaybackVolume "getAudioMixingPlaybackVolume"</td>
    <td> Gets the playback volume of a music file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::getAudioMixingSendVolume "getAudioMixingSendVolume"</td>
    <td>Gets the publishing volume of a music file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::getAudioMixingDuration "getAudioMixingDuration"</td>
    <td>Gets the total duration of a music file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::getAudioMixingCurrentPosition "getAudioMixingCurrentPosition"</td>
    <td>Sets the playback position of a music file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setAudioMixingPosition "setAudioMixingPosition"</td>
    <td>Gets the current playback position of a music file. </td>
    <td>V3.5.0</td>
  </tr>
</table>

<table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onAudioMixingStateChanged "onAudioMixingStateChanged"</td>
    <td>Occurs when the playback status of a local music file changes. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onAudioMixingTimestampUpdate "onAudioMixingTimestampUpdate"</td>
    <td>Occurs when the timestamp of a music file is updated. </td>
    <td>V3.5.0</td>
  </tr>
</table>


<h2 id="Audio effect file playback management">Audio effect file playback management</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::getEffectPlaybackVolume "getEffectPlaybackVolume"</td>
    <td>Gets the playback volume of an audio effect file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setEffectPlaybackVolume "setEffectPlaybackVolume"</td>
    <td> Sets the playback volume of an audio effect file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::playEffect "playEffect"</td>
    <td>Plays back a specified audio effect file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::stopEffect "stopEffect"</td>
    <td>Stops playing a specified audio effect file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::stopAllEffects "stopAllEffects"</td>
    <td>Stops playing all audio effect files. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::pauseEffect "pauseEffect"</td>
    <td> Pauses the playback of an audio effect file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::pauseAllEffects "pauseAllEffects"</td>
    <td>Pauses all audio file playback. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::resumeEffect "resumeEffect"</td>
    <td>Resumes playing back a specified audio effect file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::resumeAllEffects "resumeAllEffects"</td>
    <td> Resumes playing back all audio effect files. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setEffectSendVolume "setEffectSendVolume"</td>
    <td>Adjusts the publishing volume of a effect file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::getEffectSendVolume "getEffectSendVolume"</td>
    <td>Gets the publishing volume of audio effect file. </td>
    <td>V3.5.0</td>
  </tr>
</table>

<table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onAudioEffectFinished "onAudioEffectFinished"</td>
    <td>Occurs when the playback of a music file ends. </td>
    <td>V3.5.0</td>
  </tr>
</table>


<h2 id="Voice change and reverberation">Voice change and reverberation</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setAudioEffectPreset "setAudioEffectPreset"</td>
    <td> Sets a voice change effect preset by the SDK. </td>
    <td>4.1.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setVoiceBeautifierPreset "setVoiceBeautifierPreset"</td>
    <td>Sets a voice beautifier effect preset by the SDK. </td>
    <td>4.0.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setLocalVoiceEqualization "setLocalVoiceEqualization"</td>
    <td> Sets the local voice equalization effect. You can customize the center frequencies of the local voice effects. </td>
    <td>4.0.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setLocalVoicePitch "setLocalVoicePitch"</td>
    <td>Sets the voice pitch of a local voice. </td>
    <td>4.1.0</td>
  </tr>
</table>



<h2 id="CDN relayed streaming">CDN relayed streaming</h2>

Note: This method is applicable only to Interactive Live Streaming V2.0.

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::addLiveStreamTask "addLiveStreamTask"</td>
    <td>Adds a streaming task in a room. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::updateLiveStreamTask "updateLiveStreamTask"</td>
    <td> Updates a streaming task in a room. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::removeLiveStreamTask "removeLiveStreamTask"</td>
    <td>Deletes a streaming task in a room. </td>
    <td>V3.5.0</td>
  </tr>
</table>

<table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onAddLiveStreamTask "onAddLiveStreamTask"</td>
    <td>Notifies to add the result of live streaming. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onUpdateLiveStreamTask "onUpdateLiveStreamTask"</td>
    <td>Notifies to updates the result of live streaming. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onRemoveLiveStreamTask "onRemoveLiveStreamTask"</td>
    <td>Notifies to delete the result of live streaming. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onLiveStreamState "onLiveStreamState"</td>
    <td>Notifies the state of live stream-pushing. </td>
    <td>V3.5.0</td>
  </tr>
 </table>

 <h2 id="Channel Media Relay">Channel Media Relay</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::startChannelMediaRelay "startChannelMediaRelay" </td>
    <td>Starts to relay media streams across rooms.</td>
    <td>V4.3.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::updateChannelMediaRelay "updateChannelMediaRelay"</td>
    <td>Updates the information of the destination room for the media stream relay.</td>
    <td>V4.3.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::stopChannelMediaRelay "stopChannelMediaRelay"</td>
    <td>Stops media stream relay across rooms.</td>
    <td>V4.3.0</td>
  </tr>
</table>

<table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onMediaRelayStateChanged "onMediaRelayStateChanged"</td>
    <td>Occurs when the state of the media stream relay changes.</td>
    <td>V4.3.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onMediaRelayEvent "onMediaRelayEvent" </td>
    <td> Reports events during the media stream relay.</td>
    <td>V4.3.0</td>
  </tr>
</table>

<h2 id="Supplemental enhancement information">Supplemental enhancement information</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::sendSEIMsg(const char* data, int length "sendSEIMsg" [1/2]</td>
    <td> Sends supplemental enhancement information (SEI) messages through the mainstream. </td>
    <td>V4.0.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::sendSEIMsg(const char* data, int length, NERtcVideoStreamType type) "sendSEIMsg" [2/2]</td>
    <td>Sends SEI messages. You can use the mainstream or substream channel to send SEI messages by calling this method. </td>
    <td>V4.0.0</td>
  </tr>
</table>

<table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onRecvSEIMsg "onRecvSEIMsg" </td>
    <td>Occurs when the message that contains the SEI of the remote stream. </td>
    <td>V4.0.0</td>
  </tr>
</table>

 <h2 id="Volume reminder">Volume reminder</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::enableAudioVolumeIndication "enableAudioVolumeIndication"</td>
    <td>Enables volume indication for the current speaker. </td>
    <td>V3.5.0</td>
  </tr>
</table>

<table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onRemoteAudioVolumeIndication "onRemoteAudioVolumeIndication"</td>
    <td>Occurs when the system indicates the active speaker and the audio volume. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onLocalAudioVolumeIndication "onLocalAudioVolumeIndication"</td>
    <td>Occurs when the system indicates current local audio volume in the room. </td>
    <td>V3.5.0</td>
  </tr>
</table>

 <h2 id="In-ears monitoring">In-ears monitoring</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::enableEarback "enableEarback"</td>
    <td>Enables the in-ear monitoring feature. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setEarbackVolume "setEarbackVolume"</td>
    <td> Sets the volume for in-ear monitoring. </td>
    <td>V3.5.0</td>
  </tr>
</table>

 <h2 id="Video dual stream mode">Video dual stream mode</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::enableDualStreamMode "enableDualStreamMode"</td>
    <td>Enables or disables the video dual stream mode. </td>
    <td>V3.5.0</td>
  </tr>
</table>

 <h2 id="Audio and video stream fallback">Audio and video stream fallback</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setLocalPublishFallbackOption "setLocalPublishFallbackOption"</td>
    <td>Sets the fallback option for the published local video stream for unreliable network conditions. </td>
    <td>V4.3.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setRemoteSubscribeFallbackOption "setRemoteSubscribeFallbackOption"</td>
    <td> Sets the fallback option for the subscribed remote audio and video stream for unreliable network conditions. </td>
    <td>V4.3.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setLocalMediaPriority "setLocalMediaPriority"</td>
    <td>Sets the priority of local media streams. </td>
    <td>V4.2.0</td>
  </tr>
</table>

<table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onLocalPublishFallbackToAudioOnly "onLocalPublishFallbackToAudioOnly"</td>
    <td>Occurs when the published local media stream falls back to an audio-only stream or switches back to an audio and video stream. </td>
    <td>V4.3.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onRemoteSubscribeFallbackToAudioOnly "onRemoteSubscribeFallbackToAudioOnly"</td>
    <td>Occurs when the subscribed remote media stream falls back to an audio-only stream or switches back to an audio and video stream. </td>
    <td>V4.3.0</td>
  </tr>
 </table>

 <h2 id="External audio source capture and rendering">External audio source capture and rendering</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setExternalAudioSource "setExternalAudioSource"</td>
    <td>Enables external audio source and sets the capture parameters. </td>
    <td>V3.9.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::pushExternalAudioFrame "pushExternalAudioFrame"</td>
    <td> Pushes the audio frame data captured from the external audio source to the internal audio engine. </td>
    <td>V3.9.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setExternalAudioRender "setExternalAudioRender"</td>
    <td>Sets external audio rendering. </td>
    <td>V4.0.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::pullExternalAudioFrame "pullExternalAudioFrame"</td>
    <td>Pulls the external audio data. </td>
    <td>V4.0.0</td>
  </tr>
</table>

 <h2 id="External video source capture">External video source capture</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setExternalVideoSource "setExternalVideoSource"</td>
    <td> Configure external video source. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::pushExternalVideoFrame "pushExternalVideoFrame"</td>
    <td>Pushes the external video frame data captured from the external video source. </td>
    <td>V3.5.0</td>
  </tr>
</table>

<h2 id="Raw audio data">Raw audio data</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setRecordingAudioFrameParameters "setRecordingAudioFrameParameters"</td>
    <td> Sets the audio recording format. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setPlaybackAudioFrameParameters "setPlaybackAudioFrameParameters"</td>
    <td>Sets the audio playback format. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setAudioFrameObserver "setAudioFrameObserver"</td>
    <td>Registers the audio frame observer. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setMixedAudioFrameParameters "setMixedAudioFrameParameters"</td>
    <td> Sets the sample rate of the mixed stream after the audio is captured and playback. You must call this method before you join a room. </td>
    <td>V3.5.0</td>
  </tr>
</table>

<table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::INERtcAudioFrameObserver::onAudioFrameDidRecord "onAudioFrameDidRecord"</td>
    <td>Occurs when the audio data is captured. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::INERtcAudioFrameObserver::onAudioFrameWillPlayback "onAudioFrameWillPlayback"</td>
    <td> Retrieves the audio playback data. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::INERtcAudioFrameObserver::onMixedAudioFrame "onMixedAudioFrame"</td>
    <td>Retrieves the mixed recorded and playback audio frame. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::INERtcAudioFrameObserver::onPlaybackAudioFrameBeforeMixing "onPlaybackAudioFrameBeforeMixing"</td>
    <td>Retrieves the audio frame of a specified user before mixing. </td>
    <td>V3.5.0</td>
  </tr>
</table>

 <h2 id="Raw video data">Raw video data</h2>

<table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onCaptureVideoFrame "onCaptureVideoFrame"</td>
    <td>Occurs when the video data is captured. </td>
    <td>V3.5.0</td>
  </tr>
</table>

 <h2 id="Screenshots">Screenshots</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::takeLocalSnapshot "takeLocalSnapshot"</td>
    <td>Takes a local video snapshot. </td>
    <td>V4.2.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::takeRemoteSnapshot "takeRemoteSnapshot"</td>
    <td>Takes a snapshot of a remote video screen. </td>
    <td>V4.2.0</td>
  </tr>
</table>

<table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::NERtcTakeSnapshotCallback::onTakeSnapshotResult "onTakeSnapshotResult"</td>
    <td>Returns the screenshot result. </td>
    <td>V4.2.0</td>
  </tr>
</table>

 <h2 id="Watermark">Watermark</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setLocalCanvasWatermarkConfigs "setLocalCanvasWatermarkConfigs"</td>
    <td>Adds a watermark to the local video canvas. The method is only supported on Windows. </td>
    <td>V4.2.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::setRemoteCanvasWatermarkConfigs "setRemoteCanvasWatermarkConfigs"</td>
    <td>Adds a watermark to the remote video canvas. The method is only supported on Windows. </td>
    <td>V4.2.0</td>
  </tr>
</table>

 <h2 id="Encryption">Encryption</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::enableEncryption "enableEncryption"</td>
    <td>Enables or disables media stream encryption. </td>
    <td>V4.4.0</td>
  </tr>
</table>

<h2 id="Client audio recording">Client audio recording</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::startAudioRecording "startAudioRecording"</td>
    <td>Starts an audio recording on the client. </td>
    <td>V4.2.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::stopAudioRecording "stopAudioRecording"</td>
    <td>Stops an audio recording on the client. </td>
    <td>V4.2.0</td>
  </tr>
</table>


<table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onAudioRecording "onAudioRecording"</td>
    <td>Returns the audio recording state. </td>
    <td>V4.2.0</td>
  </tr>
</table>

 <h2 id="Video device management">Video device management</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::enumerateRecordDevices "enumerateRecordDevices"</td>
    <td>Enumerates the audio capture device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::setRecordDevice "setRecordDevice"</td>
    <td>Sets the audio capture device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::getRecordDevice "getRecordDevice"</td>
    <td>Gets the audio capture device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::enumeratePlayoutDevices "enumeratePlayoutDevices"</td>
    <td>Enumerates the audio capture device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::setPlayoutDevice "setPlayoutDevice"</td>
    <td>Sets audio playback device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::getPlayoutDevice "getPlayoutDevice"</td>
    <td>Sets current audio playback device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::setRecordDeviceVolume "setRecordDeviceVolume"</td>
    <td>Sets the volume of current the audio capture device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::getRecordDeviceVolume "getRecordDeviceVolume"</td>
    <td>Gets the volume of current the audio capture device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::setPlayoutDeviceVolume "setPlayoutDeviceVolume"</td>
    <td>Sets the current playback volume of capturing device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::getPlayoutDeviceVolume "getPlayoutDeviceVolume"</td>
    <td>Gets the current playback volume of capturing device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::setPlayoutDeviceMute "setPlayoutDeviceMute"</td>
    <td>Sets the current mute state of capturing device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::getPlayoutDeviceMute "getPlayoutDeviceMute"</td>
    <td>Gets the current mute state of capturing device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::setRecordDeviceMute "setRecordDeviceMute"</td>
    <td>Sets the current mute state of capturing device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::getRecordDeviceMute "getRecordDeviceMute"</td>
    <td>Gets the current mute state of capturing device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::startRecordDeviceTest "startRecordDeviceTest"</td>
    <td>Starts the test of the audio capture device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::stopRecordDeviceTest "stopRecordDeviceTest"</td>
    <td>Stops the test of the audio capture device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::startPlayoutDeviceTest "startPlayoutDeviceTest"</td>
    <td>Starts the test of the audio play device circuit. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::stopPlayoutDeviceTest "stopPlayoutDeviceTest"</td>
    <td>Stops the test of the audio play device circuit. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::startAudioDeviceLoopbackTest "startAudioDeviceLoopbackTest"</td>
    <td>Starts the test of the audio play device circuit. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IAudioDeviceManager::stopAudioDeviceLoopbackTest "stopAudioDeviceLoopbackTest"</td>
    <td>Stops the test of the audio play device circuit. </td>
    <td>V3.5.0</td>
  </tr>
</table>

 <table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onAudioHowling "onAudioHowling"</td>
    <td>Occurs when howling is detected. </td>
    <td>V3.9.0</td>
  </tr>
</table>

 <h2 id="Video device management">Video device management</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IVideoDeviceManager::enumerateCaptureDevices "enumerateCaptureDevices"</td>
    <td>Enumerates video capturing device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IVideoDeviceManager::setDevice "setDevice"</td>
    <td>Sets video capturing device. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IVideoDeviceManager::getDevice "getDevice"</td>
    <td>Gets the current video capturing device. </td>
    <td>V3.5.0</td>
  </tr>
</table>

 <h2 id="Device management event">Device management Event</h2> 

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onAudioDeviceStateChanged "onAudioDeviceStateChanged"</td>
    <td>Occurs when the status of the audio playback device changes. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onAudioDefaultDeviceChanged "onAudioDefaultDeviceChanged"</td>
    <td>Occurs when the audio device is changed. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandlerEx::onVideoDeviceStateChanged "onVideoDeviceStateChanged"</td>
    <td>Occurs when the status of the audio playback device changes. </td>
    <td>V3.5.0</td>
  </tr>
</table>

 <h2 id="Troubleshooting">Troubleshooting</h2>

<table>
  <tr>
    <th width= 400><b>Method</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::startAudioDump "startAudioDump"</td>
    <td>Starts recording an audio dump file, which can be used to analyze audio issues. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::stopAudioDump "stopAudioDump"</td>
    <td>Stops recording an audio dump file. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::getErrorDescription "getErrorDescription"</td>
    <td>Gets error description. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEx::uploadSdkInfo "uploadSdkInfo"</td>
    <td>Uploads the log records collected by the SDK. </td>
    <td>V3.5.0</td>
  </tr>
</table>

 <table>
  <tr>
    <th width= 400><b>Event</b></th>
    <th width= 600><b>Description</b></th>
    <th width= 200><b>Initial version</b></th>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onError "onError"</td>
    <td>Occurs when an error occurs. </td>
    <td>V3.5.0</td>
  </tr>
  <tr>
    <td> \ref nertc::IRtcEngineEventHandler::onWarning "onWarning"</td>
    <td>Occurs when a warning occurs. </td>
    <td>V3.5.0</td>
  </tr>
</table>
*/

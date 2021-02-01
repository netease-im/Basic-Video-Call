import 'dart:math';

import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:nertc/nertc.dart';

class CallPage extends StatefulWidget {
  final String cid;

  CallPage({Key key, @required this.cid});

  @override
  _CallPageState createState() {
    return _CallPageState();
  }
}

class _UserSession {
  int uid;
  NERtcVideoRenderer renderer;
}

class _CallPageState extends State<CallPage> with NERtcChannelEventCallback {
  NERtcEngine _engine = NERtcEngine();
  _UserSession _local = _UserSession();
  _UserSession _remote = _UserSession();

  @override
  void initState() {
    super.initState();
    _initRtcEngine();
  }

  @override
  Widget build(BuildContext context) {
    return WillPopScope(
      child: Scaffold(
        body: buildCallingWidget(context),
      ),
      // ignore: missing_return
      onWillPop: () {
        _requestPop();
      },
    );
  }

  Widget buildCallingWidget(BuildContext context) {
    return Stack(children: <Widget>[
      NERtcVideoView(_remote.renderer),
      Align(
        alignment: Alignment(0.8, -0.8),
        child: Container(
          width: 150,
          height: 200,
          child: NERtcVideoView(_local.renderer),
        ),
      ),
      Align(
          alignment: Alignment(0.0, 0.9),
          child: Flex(
            direction: Axis.horizontal,
            children: <Widget>[
              Expanded(
                  flex: 1,
                  child: RawMaterialButton(
                    onPressed: () {
                      _requestPop();
                    },
                    child: new Icon(
                      Icons.call_end,
                      color: Colors.white,
                      size: 35,
                    ),
                    shape: new CircleBorder(),
                    elevation: 1.0,
                    fillColor: Colors.redAccent,
                    padding: const EdgeInsets.all(12.0),
                  )),
            ],
          ))
    ]);
  }

  void _requestPop() {
    Navigator.pop(context);
  }

  @override
  void dispose() {
    _leaveChannel();
    _releaseRtcEngine();
    super.dispose();
  }

  void _releaseRtcEngine() {
    _engine.release();
  }

  void _leaveChannel() {
    _engine.enableLocalVideo(false);
    _engine.enableLocalAudio(false);
    _engine.stopVideoPreview();
    if (_local.renderer != null) {
      _local.renderer.dispose();
      _local.renderer = null;
    }

    if (_remote?.renderer != null) {
      _remote.renderer.dispose();
      _remote.renderer = null;
    }
    _engine.leaveChannel();
  }

  void _initRtcEngine() async {
    _local.uid = Random().nextInt(1 << 32);
    NERtcOptions options = NERtcOptions(
      audioAutoSubscribe: true,
    );
    _engine
        .create(
            appKey: 'YOUR APP KEY',
            channelEventCallback: this,
            options: options)
        .then((value) => _initRenderer())
        .then((value) => _initAudio())
        .then((value) => _initVideo())
        .then((value) => _engine.joinChannel('', widget.cid, _local.uid));
  }

  Future<int> _initAudio() async {
    return _engine.enableLocalAudio(true);
  }

  Future<int> _initVideo() async {
    return _engine.enableLocalVideo(true);
  }

  Future<void> _initRenderer() async {
    _local.renderer = await VideoRendererFactory.createVideoRenderer();
    _local.renderer.attachToLocalVideo();
    _remote.renderer = await VideoRendererFactory.createVideoRenderer();
    setState(() {});
  }

  @override
  void onAudioHasHowling() {}

  @override
  void onClientRoleChange(int oldRole, int newRole) {}

  @override
  void onConnectionStateChanged(int state, int reason) {}

  @override
  void onConnectionTypeChanged(int newConnectionType) {}

  @override
  void onDisconnect(int reason) {}

  @override
  void onError(int code) {}

  @override
  void onFirstAudioDataReceived(int uid) {}

  @override
  void onFirstAudioFrameDecoded(int uid) {}

  @override
  void onFirstVideoDataReceived(int uid) {}

  @override
  void onFirstVideoFrameDecoded(int uid, int width, int height) {}

  @override
  void onJoinChannel(int result, int channelId, int elapsed) {}

  @override
  void onLeaveChannel(int result) {}

  @override
  void onLiveStreamState(String taskId, String pushUrl, int liveState) {}

  @override
  void onLocalAudioVolumeIndication(int volume) {}

  @override
  void onReJoinChannel(int result) {}

  @override
  void onReconnectingStart() {}

  @override
  void onRemoteAudioVolumeIndication(
      List<NERtcAudioVolumeInfo> volumeList, int totalVolume) {}

  @override
  void onUserAudioMute(int uid, bool muted) {}

  @override
  void onUserAudioStart(int uid) {}

  @override
  void onUserAudioStop(int uid) {}

  @override
  void onUserJoined(int uid) {
    _remote.uid = uid;
  }

  @override
  void onUserLeave(int uid, int reason) {
    _remote.uid = null;
  }

  @override
  void onUserSubStreamVideoStart(int uid, int maxProfile) {}

  @override
  void onUserSubStreamVideoStop(int uid) {}

  @override
  void onUserVideoMute(int uid, bool muted) {}

  @override
  void onUserVideoProfileUpdate(int uid, int maxProfile) {}

  @override
  void onUserVideoStart(int uid, int maxProfile) {
    if(_remote.uid != null && uid == _remote.uid) {
      _remote.renderer.attachToRemoteVideo(uid);
      _engine.subscribeRemoteVideo(uid, NERtcRemoteVideoStreamType.high, true);
    }
  }

  @override
  void onUserVideoStop(int uid) {

  }

  @override
  void onWarning(int code) {}
}

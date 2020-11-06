package io.netease.tutorials1v1vcall;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.netease.lava.nertc.sdk.NERtcCallback;
import com.netease.lava.nertc.sdk.NERtcConstants;
import com.netease.lava.nertc.sdk.NERtcEx;
import com.netease.lava.nertc.sdk.NERtcParameters;
import com.netease.lava.nertc.sdk.video.NERtcRemoteVideoStreamType;
import com.netease.lava.nertc.sdk.video.NERtcVideoView;
import com.netease.nmc.nertcsample.onetoonevideocall.R;

import java.util.Random;

//  Created by NetEase on 7/31/20.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//
public class MeetingActivity extends AppCompatActivity implements NERtcCallback, View.OnClickListener {

    private static final String TAG = "MeetingActivity";
    private static final String EXTRA_ROOM_ID = "extra_room_id";

    private boolean enableLocalVideo = true;
    private boolean enableLocalAudio = true;
    private boolean joinedChannel = false;

    private NERtcVideoView localUserVv;
    private NERtcVideoView remoteUserVv;
    private TextView waitHintTv;
    private ImageButton enableAudioIb;
    private ImageButton leaveIb;
    private ImageButton enableVideoIb;
    private ImageView cameraFlipImg;
    private View localUserBgV;

    public static void startActivity(Activity from, String roomId) {
        Intent intent = new Intent(from, MeetingActivity.class);
        intent.putExtra(EXTRA_ROOM_ID, roomId);
        from.startActivity(intent);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_meeting);
        initViews();
        setupNERtc();
        String roomId = getIntent().getStringExtra(EXTRA_ROOM_ID);
        long userId = generateRandomUserID();
        joinChannel(userId, roomId);
    }

    /**
     * 加入房间
     *
     * @param userID 用户ID
     * @param roomID 房间ID
     */
    private void joinChannel(long userID, String roomID) {
        Log.i(TAG, "joinChannel userId: " + userID);
        NERtcEx.getInstance().joinChannel(null, roomID, userID);
        localUserVv.setZOrderMediaOverlay(true);
        localUserVv.setScalingType(NERtcConstants.VideoScalingType.SCALE_ASPECT_FIT);
        NERtcEx.getInstance().setupLocalVideoCanvas(localUserVv);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        NERtcEx.getInstance().release();
    }

    @Override
    public void onBackPressed() {
        exit();
    }

    private void initViews() {
        localUserVv = findViewById(R.id.vv_local_user);
        remoteUserVv = findViewById(R.id.vv_remote_user);
        waitHintTv = findViewById(R.id.tv_wait_hint);
        enableAudioIb = findViewById(R.id.ib_audio);
        leaveIb = findViewById(R.id.ib_leave);
        enableVideoIb = findViewById(R.id.ib_video);
        cameraFlipImg = findViewById(R.id.img_camera_flip);
        localUserBgV = findViewById(R.id.v_local_user_bg);

        localUserVv.setVisibility(View.INVISIBLE);
        enableAudioIb.setOnClickListener(this);
        leaveIb.setOnClickListener(this);
        enableVideoIb.setOnClickListener(this);
        cameraFlipImg.setOnClickListener(this);
    }

    /**
     * 初始化SDK
     */
    private void setupNERtc() {
        NERtcParameters parameters = new NERtcParameters();
        parameters.set(NERtcParameters.KEY_AUTO_SUBSCRIBE_AUDIO, false);
        NERtcEx.getInstance().setParameters(parameters); //先设置参数，后初始化

        try {
            NERtcEx.getInstance().init(getApplicationContext(), getString(R.string.app_key), this, null);
        } catch (Exception e) {
            // 可能由于没有release导致初始化失败，release后再试一次
            NERtcEx.getInstance().release();
            try {
                NERtcEx.getInstance().init(getApplicationContext(), getString(R.string.app_key), this, null);
            } catch (Exception ex) {
                Toast.makeText(this, "SDK初始化失败", Toast.LENGTH_LONG).show();
                finish();
                return;
            }
        }
        setLocalAudioEnable(true);
        setLocalVideoEnable(true);
    }

    /**
     * 随机生成用户ID
     *
     * @return 用户ID
     */
    private int generateRandomUserID() {
        return new Random().nextInt(100000);
    }

    /**
     * 退出房间
     *
     * @return 返回码
     * @see com.netease.lava.nertc.sdk.NERtcConstants.ErrorCode
     */
    private boolean leaveChannel() {
        joinedChannel = false;
        setLocalAudioEnable(false);
        setLocalVideoEnable(false);
        int ret = NERtcEx.getInstance().leaveChannel();
        return ret == NERtcConstants.ErrorCode.OK;
    }

    /**
     * 退出房间并关闭页面
     */
    private void exit() {
        if (joinedChannel) {
            leaveChannel();
        }
        finish();
    }

    @Override
    public void onJoinChannel(int result, long channelId, long elapsed) {
        Log.i(TAG, "onJoinChannel result: " + result + " channelId: " + channelId + " elapsed: " + elapsed);
        if (result == NERtcConstants.ErrorCode.OK) {
            joinedChannel = true;
            // 加入房间，准备展示己方视频
            localUserVv.setVisibility(View.VISIBLE);
        }
    }

    @Override
    public void onLeaveChannel(int result) {
        Log.i(TAG, "onLeaveChannel result: " + result);
    }

    @Override
    public void onUserJoined(long uid) {
        Log.i(TAG, "onUserJoined uid: " + uid);
        // 已经有订阅，就不要变了
        if (remoteUserVv.getTag() != null) {
            return;
        }
        // 有用户加入，设置Tag，该用户离开前，只订阅和取消订阅此用户
        remoteUserVv.setTag(uid);
        // 不用等待了
        waitHintTv.setVisibility(View.INVISIBLE);
    }

    @Override
    public void onUserLeave(long uid, int reason) {
        Log.i(TAG, "onUserLeave uid: " + uid + " reason: " + reason);
        // 退出的不是当前订阅的对象，则不作处理
        if (!isCurrentUser(uid)) {
            return;
        }
        // 设置TAG为null，代表当前没有订阅
        remoteUserVv.setTag(null);
        NERtcEx.getInstance().subscribeRemoteVideoStream(uid, NERtcRemoteVideoStreamType.kNERtcRemoteVideoStreamTypeHigh, false);

        // 显示在等待用户进入房间
        waitHintTv.setVisibility(View.VISIBLE);
        // 不展示远端
        remoteUserVv.setVisibility(View.INVISIBLE);
    }

    @Override
    public void onUserAudioStart(long uid) {
        Log.i(TAG, "onUserAudioStart uid: " + uid);
        if (!isCurrentUser(uid)) {
            return;
        }
        NERtcEx.getInstance().subscribeRemoteAudioStream(uid, true);
    }

    @Override
    public void onUserAudioStop(long uid) {
        Log.i(TAG, "onUserAudioStop, uid=" + uid);
    }

    @Override
    public void onUserVideoStart(long uid, int profile) {
        Log.i(TAG, "onUserVideoStart uid: " + uid + " profile: " + profile);
        if (!isCurrentUser(uid)) {
            return;
        }

        NERtcEx.getInstance().subscribeRemoteVideoStream(uid, NERtcRemoteVideoStreamType.kNERtcRemoteVideoStreamTypeHigh, true);
        remoteUserVv.setScalingType(NERtcConstants.VideoScalingType.SCALE_ASPECT_FIT);
        NERtcEx.getInstance().setupRemoteVideoCanvas(remoteUserVv, uid);

        // 更新界面
        remoteUserVv.setVisibility(View.VISIBLE);
    }

    @Override
    public void onUserVideoStop(long uid) {
        Log.i(TAG, "onUserVideoStop, uid=" + uid);
        if (!isCurrentUser(uid)) {
            return;
        }
        // 不展示远端
        remoteUserVv.setVisibility(View.INVISIBLE);
    }

    @Override
    public void onDisconnect(int reason) {
        Log.i(TAG, "onDisconnect reason: " + reason);
        if (reason != NERtcConstants.ErrorCode.OK) {
            finish();
        }
    }

    /**
     * 判断是否为onUserJoined中，设置了Tag的用户
     *
     * @param uid 用户ID
     * @return 用户ID是否匹配
     */
    private boolean isCurrentUser(long uid) {
        Object tag = remoteUserVv.getTag();
        Log.i(TAG, "isCurrentUser tag=" + tag);
        return tag != null && tag.equals(uid);
    }

    /**
     * 改变本地音频的可用性
     */
    private void changeAudioEnable() {
        enableLocalAudio = !enableLocalAudio;
        setLocalAudioEnable(enableLocalAudio);
    }

    /**
     * 改变本地视频的可用性
     */
    private void changeVideoEnable() {
        enableLocalVideo = !enableLocalVideo;
        setLocalVideoEnable(enableLocalVideo);
    }

    /**
     * 设置本地音频的可用性
     */
    private void setLocalAudioEnable(boolean enable) {
        enableLocalAudio = enable;
        NERtcEx.getInstance().enableLocalAudio(enableLocalAudio);
        enableAudioIb.setImageResource(enable ? R.drawable.selector_meeting_mute : R.drawable.selector_meeting_unmute);
    }

    /**
     * 设置本地视频的可用性
     */
    private void setLocalVideoEnable(boolean enable) {
        enableLocalVideo = enable;
        NERtcEx.getInstance().enableLocalVideo(enableLocalVideo);
        enableVideoIb.setImageResource(enable ? R.drawable.selector_meeting_close_video : R.drawable.selector_meeting_open_video);
        localUserVv.setVisibility(enable ? View.VISIBLE : View.INVISIBLE);
        localUserBgV.setBackgroundColor(getResources().getColor(enable ? R.color.white : R.color.black));
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.ib_audio:
                changeAudioEnable();
                break;
            case R.id.ib_leave:
                exit();
                break;
            case R.id.ib_video:
                changeVideoEnable();
                break;
            case R.id.img_camera_flip:
                NERtcEx.getInstance().switchCamera();
                break;
            default:
                break;
        }
    }
}
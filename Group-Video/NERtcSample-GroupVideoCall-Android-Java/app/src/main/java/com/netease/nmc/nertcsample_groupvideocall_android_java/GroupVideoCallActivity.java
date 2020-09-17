package com.netease.nmc.nertcsample_groupvideocall_android_java;

import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;

import com.netease.lava.nertc.sdk.NERtc;
import com.netease.lava.nertc.sdk.NERtcCallback;
import com.netease.lava.nertc.sdk.NERtcConstants;
import com.netease.lava.nertc.sdk.NERtcParameters;
import com.netease.lava.nertc.sdk.video.NERtcRemoteVideoStreamType;
import com.netease.lava.nertc.sdk.video.NERtcVideoView;

import java.util.ArrayList;
import java.util.List;

public class GroupVideoCallActivity extends AppCompatActivity implements NERtcCallback {

    public static final String EXTRA_USER_ID = "extra_user_id";
    public static final String EXTRA_ROOM_ID = "extra_room_id";

    private ConstraintLayout mContainer;
    private NERtcVideoView mLocalUserVv;
    private List<NERtcVideoView> mRemoteUserVvList = new ArrayList<>();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_group_video_call);
        initViews();
        setupNERtc();

        long userID = getIntent().getLongExtra(EXTRA_USER_ID, -1);
        String roomID = getIntent().getStringExtra(EXTRA_ROOM_ID);
        joinChannel(userID, roomID);
    }

    private void joinChannel(long userID, String roomID) {
        NERtc.getInstance().joinChannel("", roomID, userID);
        mLocalUserVv.setZOrderMediaOverlay(true);
        mLocalUserVv.setScalingType(NERtcConstants.VideoScalingType.SCALE_ASPECT_BALANCED);
        NERtc.getInstance().setupLocalVideoCanvas(mLocalUserVv);
    }

    @Override
    public void onBackPressed() {
        leave();
    }

    private void leave() {
        NERtc.getInstance().leaveChannel();
    }

    private void initViews() {
        mContainer = findViewById(R.id.container);
        mLocalUserVv = findViewById(R.id.vv_local_user);
        mRemoteUserVvList.add(findViewById(R.id.vv_remote_user1));
        mRemoteUserVvList.add(findViewById(R.id.vv_remote_user2));
        mRemoteUserVvList.add(findViewById(R.id.vv_remote_user3));

        findViewById(R.id.btn_leave).setOnClickListener(view -> leave());
    }

    private void setupNERtc() {
        NERtcParameters parameters = new NERtcParameters();
        NERtc.getInstance().setParameters(parameters); //先设置参数，后初始化
        try {
            NERtc.getInstance().init(getApplicationContext(), getString(R.string.app_key), this, null);
            NERtc.getInstance().enableLocalAudio(true);
            NERtc.getInstance().enableLocalVideo(true);
        } catch (Exception e) {
            Toast.makeText(this, "SDK初始化失败", Toast.LENGTH_LONG).show();
            finish();
        }
    }

    @Override
    public void onUserJoined(long userID) {
        for (NERtcVideoView videoView : mRemoteUserVvList) {
            if (videoView.getTag() == null) {
                videoView.setZOrderMediaOverlay(true);
                videoView.setScalingType(NERtcConstants.VideoScalingType.SCALE_ASPECT_BALANCED);
                NERtc.getInstance().setupRemoteVideoCanvas(videoView, userID);
                videoView.setTag(userID);
                break;
            }
        }
    }

    @Override
    public void onUserLeave(long userID, int i) {
        NERtcVideoView userView = mContainer.findViewWithTag(userID);
        if (userView != null) {
            userView.setTag(null);
        }
    }

    @Override
    public void onUserVideoStart(long userID, int profile) {
        NERtc.getInstance().subscribeRemoteVideoStream(userID, NERtcRemoteVideoStreamType.kNERtcRemoteVideoStreamTypeHigh, true);
    }

    @Override
    public void onJoinChannel(int i, long l, long l1) {

    }

    @Override
    public void onLeaveChannel(int i) {
        NERtc.getInstance().release();
        finish();
    }

    @Override
    public void onUserAudioStart(long l) {

    }

    @Override
    public void onUserAudioStop(long l) {

    }

    @Override
    public void onUserVideoStop(long l) {

    }

    @Override
    public void onDisconnect(int i) {

    }

}

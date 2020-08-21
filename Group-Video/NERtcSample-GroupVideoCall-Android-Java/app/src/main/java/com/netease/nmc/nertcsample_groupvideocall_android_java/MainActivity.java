package com.netease.nmc.nertcsample_groupvideocall_android_java;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.app.ActivityCompat;

import com.netease.lava.nertc.sdk.NERtc;

import java.util.List;
import java.util.Random;

import static com.netease.nmc.nertcsample_groupvideocall_android_java.GroupVideoCallActivity.EXTRA_ROOM_ID;
import static com.netease.nmc.nertcsample_groupvideocall_android_java.GroupVideoCallActivity.EXTRA_USER_ID;

@SuppressWarnings("FieldCanBeLocal")
public class MainActivity extends AppCompatActivity {

    private static final int PERMISSION_REQUEST_CODE = 100;
    private EditText mUserIDEt;
    private EditText mRoomIDEt;
    private Button mJoinBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initViews();
        requestPermissionsIfNeeded();
        mUserIDEt.setText(generateRandomUserID());
    }

    private void requestPermissionsIfNeeded() {
        final List<String> missedPermissions = NERtc.checkPermission(this);
        if (missedPermissions.size() > 0) {
            ActivityCompat.requestPermissions(this, missedPermissions.toArray(new String[0]), PERMISSION_REQUEST_CODE);
        }
    }

    private void initViews() {
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        mUserIDEt = findViewById(R.id.et_user_id);
        mRoomIDEt = findViewById(R.id.et_room_id);
        mJoinBtn = findViewById(R.id.btn_join);
        mJoinBtn.setOnClickListener(v -> {
            String userIDText = mUserIDEt.getText() != null ? mUserIDEt.getText().toString() : "";
            if (TextUtils.isEmpty(userIDText)) {
                Toast.makeText(this, "请输入userID", Toast.LENGTH_SHORT).show();
                return;
            }
            String roomID = mRoomIDEt.getText() != null ? mRoomIDEt.getText().toString() : "";
            if (TextUtils.isEmpty(roomID)) {
                Toast.makeText(this, "请输入roomID", Toast.LENGTH_SHORT).show();
                return;
            }
            try {
                long userID = Long.parseLong(userIDText);
                Intent intent = new Intent(this, GroupVideoCallActivity.class);
                intent.putExtra(EXTRA_USER_ID, userID);
                intent.putExtra(EXTRA_ROOM_ID, roomID);
                startActivity(intent);
            } catch (NumberFormatException e) {
                Toast.makeText(this, "userID不合法", Toast.LENGTH_SHORT).show();
            }
            hideSoftKeyboard();
        });
    }

    private void hideSoftKeyboard() {
        if (getCurrentFocus() == null) return;
        InputMethodManager imm = (InputMethodManager) getSystemService(Activity.INPUT_METHOD_SERVICE);
        if (imm == null) return;
        imm.hideSoftInputFromWindow(getCurrentFocus().getWindowToken(), 0);
    }

    private String generateRandomUserID() {
        return String.valueOf(new Random().nextInt(100000));
    }

}

#ifndef NRTCENGINE_EVENT_HANDLER_H
#define NRTCENGINE_EVENT_HANDLER_H

#include "nertc_engine_event_handler_ex.h"

using namespace nertc;

class NRTCEngine;

class NRTCEngine_event_handler : public IRtcEngineEventHandlerEx
{
public:
    NRTCEngine_event_handler(NRTCEngine * engine);
    virtual void onUserVideoStop(nertc::uid_t uid) override;

    virtual void onJoinChannel(channel_id_t cid, nertc::uid_t uid, NERtcErrorCode result, uint64_t elapsed) override;

    virtual void onUserJoined(nertc::uid_t uid, const char * user_name) override;

    virtual void onUserLeft(nertc::uid_t uid, NERtcSessionLeaveReason reason) override;


private:
    NRTCEngine * m_engine;
};

#endif // NRTCENGINE_EVENT_HANDLER_H

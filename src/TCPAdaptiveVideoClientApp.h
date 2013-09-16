#ifndef TCPADAPTIVEVIDEOCLIENTAPP_H_
#define TCPADAPTIVEVIDEOCLIENTAPP_H_

#include <algorithm>
#include <TCPGenericCliAppBase.h>
#include <INETDefs.h>

class TCPAdaptiveVideoClientApp: public TCPGenericCliAppBase {
protected:

    // Adaptive Video (AV) parameters
    std::vector<int> video_packet_size_per_second;
    int video_buffer_max_length;
    int video_duration;
    int numRequestsToSend; // requests to send in this session. Each request = 1s of video
    int video_buffer; // current lenght of the buffer in seconds
    simsignal_t DASH_buffer_length_signal;
    int video_current_quality_index; // requested quality
    simsignal_t DASH_quality_level_signal;
    bool video_is_playing;
    simsignal_t DASH_video_is_playing_signal;
    int video_playback_pointer;
    simsignal_t DASH_playback_pointer;
    bool video_is_buffering = true;
    int video_buffer_min_rebuffering = 3; // if video_buffer < video_buffer_min_rebuffering then a rebuffering event occurs


    cMessage *timeoutMsg;
    simtime_t stopTime;

    /** Utility: sends a request to the server */
    virtual void sendRequest();

    /** Utility: cancel msgTimer and if d is smaller than stopTime, then schedule it to d,
     * otherwise delete msgTimer */
    virtual void rescheduleOrDeleteTimer(simtime_t d, short int msgKind);

public:
    TCPAdaptiveVideoClientApp();
    virtual ~TCPAdaptiveVideoClientApp();

protected:
    /** Redefined . */
    virtual void initialize(int stage);

    /** Redefined. */
    virtual void handleTimer(cMessage *msg);

    /** Redefined. */
    virtual void socketEstablished(int connId, void *yourPtr);

    /** Redefined. */
    virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg,
            bool urgent);

    /** Redefined to start another session after a delay (currently not used). */
    virtual void socketClosed(int connId, void *yourPtr);

    /** Redefined to reconnect after a delay. */
    virtual void socketFailure(int connId, void *yourPtr, int code);

};
#endif
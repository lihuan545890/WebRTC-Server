/*
 * IceClient.h
 *
 *  Created on: 2019/06/28
 *      Author: max
 *		Email: Kingsleyyau@gmail.com
 */

#ifndef ICE_ICECLIENT_H_
#define ICE_ICECLIENT_H_

#include <string>
using namespace std;

typedef struct _NiceAgent NiceAgent;
typedef struct _NiceCandidate NiceCandidate;
namespace mediaserver {
class IceClient;
class IceClientCallback {
public:
	virtual ~IceClientCallback(){};
	virtual void OnIceHandshakeFinish(IceClient *ice) = 0;
	virtual void OnIceRecvData(IceClient *ice, const char *data, unsigned int size, unsigned int streamId, unsigned int componentId) = 0;
};

class IceClient {
	friend void cb_closed(void *src, void *res, void *data);
	friend void cb_nice_recv(::NiceAgent *agent, unsigned int streamId, unsigned int componentId, unsigned int len, char *buf, void *data);
	friend void cb_candidate_gathering_done(::NiceAgent *agent, unsigned int streamId, void* data);
	friend void cb_component_state_changed(::NiceAgent *agent, unsigned int streamId, unsigned int componentId, unsigned int state, void *data);
	friend void cb_new_selected_pair_full(::NiceAgent* agent, unsigned int streamId, unsigned int componentId, ::NiceCandidate *lcandidate, ::NiceCandidate* rcandidate, void* data);

public:
	IceClient();
	virtual ~IceClient();

public:
	static bool GobalInit();

public:
	void SetCallback(IceClientCallback *callback);
	void SetRemoteSdp(const string& sdp);

public:
	bool Start();
	void Stop();
	int SendData(const void *data, unsigned int len);

public:
	const string& GetLocalAddress();
	const string& GetRemoteAddress();

private:
	void OnClose(::NiceAgent *agent);
	void OnNiceRecv(::NiceAgent *agent, unsigned int streamId, unsigned int componentId, unsigned int len, char *buf);
	void OnCandidateGatheringDone(::NiceAgent *agent, unsigned int streamId);
	void OnComponentStateChanged(::NiceAgent *agent, unsigned int streamId, unsigned int componentId, unsigned int state);
	void OnNewSelectedPairFull(::NiceAgent* agent, unsigned int streamId, unsigned int componentId, ::NiceCandidate *local, ::NiceCandidate* remote);

private:
	bool ParseRemoteSdp(unsigned int streamId);

private:
	::NiceAgent *mpAgent;
	string mSdp;
	IceClientCallback *mpIceClientCallback;

	unsigned int mStreamId;
	unsigned int mComponentId;

	string mLocalAddress;
	string mRemoteAddress;
};

} /* namespace mediaserver */

#endif /* ICE_ICECLIENT_H_ */
/*
 * UdpClient.h
 *
 *  Created on: 2019/07/02
 *      Author: max
 *		Email: Kingsleyyau@gmail.com
 */

#ifndef SOCKET_UDPCLIENT_H_
#define SOCKET_UDPCLIENT_H_

#include "ISocketSender.h"

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>
using namespace std;

namespace mediaserver {

class UdpClient: public SocketSender {
public:
	UdpClient();
	virtual ~UdpClient();

public:
	bool Init(const string& sendIp, int sendPort, int recvPort);
	void Close();
	int SendData(const void *data, unsigned int len);

private:
	// Socket
	string mSendIp;
	struct sockaddr_in mSendSockAddr;
	int mSendPort;
	int mRecvPort;
	int mFd;
};

} /* namespace mediaserver */

#endif /* SOCKET_UDPCLIENT_H_ */
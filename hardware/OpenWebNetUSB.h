#pragma once

#include "DomoticzHardware.h"
#include "ASyncSerial.h"

using namespace std;
class bt_openwebnet;

#define OPENWEBNET_DEVICE "OPENWEBNET"
#define ZIGBEE_SUFFIX "#9"
#define OPENWEBNET_BUFFER_SIZE 1024
#define OPENWEBNET_HEARTBEAT_DELAY 1
#define OPENWEBNET_STATUS_NB_HEARTBEAT 600
#define OPENWEBNET_STOP_DELAY 5
#define OPENWEBNET_RETRY_DELAY 30
#define OPENWEBNET_POLL_INTERVAL 1000
#define OPENWEBNET_SOCKET_SUCCESS 0
#define OPENWEBNET_SERIAL_BUFFER_SIZE 1028
#define RETRY_DELAY 30
#define SLEEP_READ_TIME 100

class COpenWebNetUSB : public AsyncSerial, public CDomoticzHardwareBase
{
public:
	COpenWebNetUSB(const int ID, const std::string& devname, unsigned int baud_rate);
	~COpenWebNetUSB(void);

	void Do_Work();
	bool WriteToHardware(const char *pdata, const unsigned char length);

protected:

	bool StartHardware();
	bool StopHardware();

	std::string m_szSerialPort;
	unsigned int m_iBaudRate;

	boost::shared_ptr<boost::thread> m_thread;

	int m_retrycntr;

	bool m_bHaveReceived;
	unsigned char m_readBuffer[OPENWEBNET_SERIAL_BUFFER_SIZE];
	int m_readBufferSize;

	bool sendCommand(bt_openwebnet& command, vector<bt_openwebnet>& response, bool silent = false);
	bool FindDevice(int deviceID, int deviceUnit, int subType, int* used);
	bool writeRead(const char* command, unsigned int commandSize, bool silent);
	void readCallback(const char *data, size_t len);
	bool ParseData(char* data, int length, vector<bt_openwebnet>& messages);//same as OpenWebNet class, TODO : inherit from mother class

	volatile bool m_bWriting;
	volatile bool m_stoprequested;
};

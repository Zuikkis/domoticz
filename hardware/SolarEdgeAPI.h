#pragma once

#include "DomoticzHardware.h"
#include <string>
#include <vector>

class SolarEdgeAPI : public CDomoticzHardwareBase
{
	struct _tInverterSettings
	{
		std::string name;
		std::string manufacturer;
		std::string model;
		std::string SN;
		uint16_t connectedOptimizers;
	};
public:
	SolarEdgeAPI(const int ID, const std::string &APIKey);
	~SolarEdgeAPI(void);
	bool WriteToHardware(const char *pdata, const unsigned char length);
private:
	int m_SiteID;
	std::string m_APIKey;
	std::vector<_tInverterSettings> m_inverters;

	double m_totalActivePower;
	double m_totalEnergy;


	volatile bool m_stoprequested;
	boost::shared_ptr<boost::thread> m_thread;

	bool StartHardware();
	bool StopHardware();
	void Do_Work();
	void GetSite();
	void GetInverters();
	void GetMeterDetails();
	void GetInverterDetails(const _tInverterSettings *pInverterSettings, const int iInverterNumber);
	int getSunRiseSunSetMinutes(const bool bGetSunRise);
};


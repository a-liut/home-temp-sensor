#ifndef H_HOME_MANAGER
#define H_HOME_MANAGER

#define HOME_MANAGER_REGISTRATION_URL "http://192.168.1.123:8080/devices"
#define HOME_MANAGER_DATA_URL "http://192.168.1.123:8080/devices/"

bool isRegistered();
int registerDevice(const char* id, int idSize);
int sendData(String propname, float val, String unit);

#endif

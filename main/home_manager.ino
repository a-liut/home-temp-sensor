#ifndef HOME_MANAGER
#define HOME_MANAGER

#include "home_manager.h"
#include "utils.h"

#include <ESP8266HTTPClient.h>

HTTPClient http;

bool registered = false;
int idSize = 0;
String _id;

bool isRegistered()
{
    return registered;
}

bool registerDevice()
{
    http.begin(HOME_MANAGER_REGISTRATION_URL);

    int httpCode = http.POST("");

    String payload = http.getString();

    http.end();

    if (httpCode == HTTP_CODE_OK)
    {
        idSize = payload.length() - 2;

        char id[100];
        for (int i = 0; i < idSize; i++)
        {
            id[i] = payload[i + 1];
        }

        _id = convertToString(id, idSize);

        registered = true;
        Serial.println(_id);

        return true;
    }

    return false;
}

// Builds the data enpoint URL
String buildUrl(String propname)
{
    return HOME_MANAGER_DATA_URL + _id + "/data/" + propname;
}

// Builds body for data send
void buildBody(char *body, float val, const char *unit)
{
    sprintf(body, "{\"value\": \"%f\", \"unit\": \"%s\"}", val, unit);
}

// Sends data to service
int sendData(String propname, float val, const char *unit)
{
    if (!registered)
    {
        Serial.println("Cannot send data to manager: Not registered.");
        return -1;
    }

    Serial.println("Sending data to manager");

    String url = buildUrl(propname);

    char body[100];
    buildBody(body, val, unit);

    //Serial.printf("url: %s\n", url);
    Serial.println(url);
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(body);

    http.end();

    return httpCode;
}

#endif

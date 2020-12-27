#pragma once

#include <MqttController.hpp>

class MqttController;
class MqttListener {
    public:
    MqttListener(MqttController& mqtt_controller, const char* topic);

    virtual void begin() {};
    virtual const char* getMQTTTopic() { return topic; };
    virtual bool parsePayload(const char *payload);
    virtual bool presentMessage(const char *topic,const char *payload);

    protected:
    MqttController& mqtt_controller;
    const char* topic;
    const int baselength;
};

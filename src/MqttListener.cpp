#include <MqttListener.hpp>

MqttListener::MqttListener(MqttController& mqtt_controller, const char* topic) 
        : mqtt_controller(mqtt_controller), topic(topic), 
          baselength(topic[strlen(topic)-1]=='#'?strlen(topic)-2:strlen(topic))
    {
        
        mqtt_controller.reg(this);
    };


bool MqttListener::presentMessage(const char *topic,const char *payload) {
    if (!strcmp(this->getMQTTTopic(), topic)) {
        return this->parsePayload(payload);
    } else {
        return false;
    }
}

bool MqttListener::parsePayload(const char *payload) {
    return false;
}
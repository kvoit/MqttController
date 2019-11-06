#include <MqttListener.hpp>

MqttListener::MqttListener(MqttController& mqtt_controller, const char* topic) 
        : mqtt_controller(mqtt_controller), topic(topic) {

        mqtt_controller.reg(this);
    };

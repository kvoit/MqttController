#include <MqttController.hpp>

void MqttController::begin() {
  
}

void MqttController::handle() {
    if (!psc.connected()) {
      reconnect();
    }
    psc.loop();
}

void MqttController::reg(MqttListener* ml) {
  listener.push_back(ml);
}

void MqttController::subscribe() {
      for(MqttListener* ml : listener) {
          bool subsc_stat = psc.subscribe(ml->getMQTTTopic());
      }
}

bool MqttController::reconnect() {
    if (psc.connect(mqttName, mqttUser, mqttPassword)) {
      this->subscribe();
      return true;
    }
    return false;
}

void MqttController::callback(const char* topic, const byte* payload, unsigned int length) {
    // Make const char* from byte*
  char p_payload[length + 1];
  for (unsigned int i = 0; i < length; i++)
  {
    p_payload[i] = payload[i];
  }
  p_payload[length] = '\0';

  for (MqttListener* ml : listener)
  {
    if (!strcmp(ml->getMQTTTopic(), topic))
    {
      if(ml->parsePayload(p_payload))
        return;
    }
  }
}

bool MqttController::sendMessage(const char* topic, const char* msg, bool retain) {
  this->handle();
  if( !psc.publish(topic, msg, retain) )
  {
    return false;
  } else {
    return true;
  }
  this->handle();
}

#ifndef _ROS_H_
#define _ROS_H_

#include "ros/node_handle.h"
#include "Arduino.h"

// Kind of a cheat to do this, but simplifies things elsewhere.
#include "time.cpp"
#include "duration.cpp"

class Leonardo {
  public:
    Leonardo() : io(&Serial), baud_(57600) {}

    void init() {
      io->begin(baud_);
    }

    int read() {
      return io->read();
    }

    void write(uint8_t* data, int length) {
      for(int i=0; i<length; i++) {
        io->write(data[i]);
      }
    }

    unsigned long time() {
      return millis();
    }

  protected:
    Serial_* io;
    long baud_;
};


namespace ros
{
  typedef NodeHandle_<Leonardo, 5, 5, 200, 200> NodeHandle;
}

#endif

//
// Created by ertemu on 6/7/17.
//

#include "Log.h"


Log *Log::myInstance = nullptr;

Log::Log()
{

}

static Log*
Log::getInst()
{

    if (Log::myInstance == nullptr)
    {
        Log::myInstance = new Log();
    }

    return Log::myInstance;

}

static void
Log::log(String message)
{ 
      Serial.println(message.c_str());
      String message2 = "[ARDU_LOG]" + message;
      Serial.println(message2);
      Serial.println("*LOGGING*"); 
}

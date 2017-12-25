//
// Created by ertemu on 6/7/17.
//

#ifndef PROJECTT_LOG_H
#define PROJECTT_LOG_H

#include <Arduino.h>


class Log
{
private:
    Log();

public :
    static Log* getInst();


    static void log(String message);

    static Log* myInstance;
};

#endif //PROJECTT_LOG_H

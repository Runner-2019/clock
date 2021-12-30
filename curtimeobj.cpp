#include "curtimeobj.h"

CurTimeObj::CurTimeObj()
{



}

QString CurTimeObj::getCurTime()
{
    QTime curTime = QTime::currentTime();
    return curTime.toString("hh:mm:ss");
}

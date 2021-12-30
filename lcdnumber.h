#ifndef LCDNUMBER_H
#define LCDNUMBER_H

#include <QLCDNumber>
#include <QObject>
#include <QWidget>

class LCDNumber
{
    Q_OBJECT
public:
    LCDNumber();
    QLCDNumber* lcdNumber;

public slots:

};

#endif // LCDNUMBER_H

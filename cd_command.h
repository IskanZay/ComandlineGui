#ifndef CD_COMMAND_H
#define CD_COMMAND_H
#include <QString>
#include <QVector>
#include <QDir>
#include "base_command.h"

class cd_command : public base_command
{
public:
    QString execute(QVector<QString>& args) override
    {
        return "";
    }
};

#endif // CD_COMMAND_H

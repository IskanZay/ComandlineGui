#ifndef EXIT_COMMAND_H
#define EXIT_COMMAND_H
#include "base_command.h"
#include <QApplication>

class exit_command : public base_command
{
public:
    QString execute(QVector<QString> &args) override
    {
        QApplication::quit();
        return "programm exit";
    }

};

#endif // EXIT_COMMAND_H

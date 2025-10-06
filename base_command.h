#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H
#include <QString>
#include <QVector>

class base_command
{
public:
    virtual ~base_command() = default;
    virtual QString execute(QVector<QString>& args) = 0;
};

#endif // BASE_COMMAND_H

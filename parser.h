#ifndef PARSER_H
#define PARSER_H
#include <QVector>
#include <QString>

class Parser
{
private:
    QString m_command_name;
    QVector<QString> m_argumments;

public:
    Parser();

    void Parse(QString str);

    QString get_command_name();

    QVector<QString> get_arguments();
};

#endif // PARSER_H

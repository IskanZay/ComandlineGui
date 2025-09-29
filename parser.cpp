#include "parser.h"

Parser::Parser() {}

void Parser::Parse(QString str)
{
    int space_pos = str.indexOf(' ');

    m_command_name = str.mid(0, space_pos);

    QString argument;
    str += " ";

    for (int i = space_pos + 1;i < str.length();i++)
    {
        if (str[i] == '"')
        {
            i++;
            while(str[i] != '"')
            {
                argument += str[i];
                i++;
            }
            m_argumments.push_back(argument);
            argument.clear();
        }
        else if (str[i] == ' ')
        {
            if (argument != "")
            {
            m_argumments.push_back(argument);
            argument.clear();
            }
        }
        else
        {
            argument += str[i];
        }
    }
}

QString Parser::get_command_name()
{
    return m_command_name;
}

QVector<QString> Parser::get_arguments()
{
    return m_argumments;
}

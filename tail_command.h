#ifndef TAIL_COMMAND_H
#define TAIL_COMMAND_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include "base_command.h"

class tail_command : public base_command
{
public:
    QString execute(QVector<QString>& args) override
    {
        if (args.isEmpty())
        {
            return "tail: отсустсвует аргумент\n";
        }

        QString file_path = "D:/VFS/root" + args[0];
        QFile file(file_path);

        if (!file.exists())
        {
            return "tail: не удаётся открыть файл '" + args[0] + "' для чтения: Отсутствует директория или файл\n";
        }

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return "tail: не удаётся открыть файл '" + args[0] + "' для чтения\n";
        }

        QTextStream in(&file);
        QStringList lines;

        while (!in.atEnd())
        {
            lines.append(in.readLine());
        }
        file.close();

        QString result;
        int start_index = lines.size() > 10 ? lines.size() - 10 : 0;

        for (int i = start_index; i < lines.size(); i++)
        {
            result += lines[i] + "\n";
        }

        return result;
    }
};

#endif // TAIL_COMMAND_H

#ifndef LS_COMMAND_H
#define LS_COMMAND_H

#include <QString>
#include <QVector>
#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include "base_command.h"

class ls_command : public base_command
{
public:
    QString execute(QVector<QString>& args) override
    {
        QString path = "/";
        if (!args.isEmpty())
        {
            path = args[0];
        }

        QDir dir("D:/VFS/root" + path);

        if (!dir.exists())
        {
            return "ls: не может получить доступ '" + path + "': Отсутствует такая директория или файл\n";
        }

        QStringList entries = dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name | QDir::DirsFirst);
        QString result;

        for (const QString& entry : entries)
        {
            QFileInfo info(dir.filePath(entry));
            if (info.isDir())
            {
                result += entry + "/\n";
            }
            else
            {
                result += entry + "\n";
            }
        }

        return result;
    }
};

#endif // LS_COMMAND_H

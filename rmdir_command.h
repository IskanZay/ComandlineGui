#ifndef RMDIR_COMMAND_H
#define RMDIR_COMMAND_H

#include <QString>
#include <QVector>
#include <QDir>
#include "base_command.h"

class rmdir_command : public base_command
{
public:
    QString execute(QVector<QString>& args) override
    {
        if (args.isEmpty())
        {
            return "rmdir: Пропущен аргумент\n";
        }

        QString path = "D:/VFS/root" + args[0];
        QDir dir(path);

        if (!dir.exists())
        {
            return "rmdir: ошибка удаления '" + args[0] + "': Отсутствует такая директория или файл\n";
        }

        if (!QFileInfo(path).isDir())
        {
            return "rmdir: ошибка удаления '" + args[0] + "': Не является директорией\n";
        }

        QFileInfoList entries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
        if (!entries.isEmpty())
        {
            return "rmdir: ошибка удаления '" + args[0] + "': Директория не пуста\n";
        }

        if (dir.rmdir(path))
        {
            return "";
        }
        else
        {
            return "rmdir: ошибка удаления '" + args[0] + "': Операция отклонена\n";
        }
    }
};

#endif // RMDIR_COMMAND_H

#ifndef CHMOD_COMMAND_H
#define CHMOD_COMMAND_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QFileInfo>
#include <QFileDevice>
#include "base_command.h"

class chmod_command : public base_command
{
public:
    QString execute(QVector<QString>& args) override
    {
        if (args.size() < 2)
        {
            return "chmod: Отсутвстует операнд\nИСпользование: chmod <mode> <file>\n";
        }

        QString mode_str = args[0];
        QString file_path = "D:/VFS/root" + args[1];
        QFile file(file_path);

        if (!file.exists())
        {
            return "chmod: нет возможности получить доступ'" + args[1] + "': No such file or directory\n";
        }

        bool ok;
        int mode = mode_str.toInt(&ok, 8);

        if (!ok || mode < 0 || mode > 0777)
        {
            return "chmod: некорректный режим: '" + mode_str + "'\n";
        }

        if (!file.setPermissions(parse_mode(mode)))
        {
            return "chmod: не удалось изменить права доступа для '" + args[1] + "'\n";
        }

        return "";
    }

private:
    QFile::Permissions parse_mode(int mode)
    {
        QFile::Permissions permissions;

        // для владелбца
        if (mode & 0400) permissions |= QFile::ReadOwner;
        if (mode & 0200) permissions |= QFile::WriteOwner;
        if (mode & 0100) permissions |= QFile::ExeOwner;

        // для группы
        if (mode & 0040) permissions |= QFile::ReadGroup;
        if (mode & 0020) permissions |= QFile::WriteGroup;
        if (mode & 0010) permissions |= QFile::ExeGroup;

        // остальные
        if (mode & 0004) permissions |= QFile::ReadOther;
        if (mode & 0002) permissions |= QFile::WriteOther;
        if (mode & 0001) permissions |= QFile::ExeOther;

        return permissions;
    }
};

#endif // CHMOD_COMMAND_H

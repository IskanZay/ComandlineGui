#ifndef TREE_COMMAND_H
#define TREE_COMMAND_H

#include <QString>
#include <QVector>
#include <QDir>
#include <QFileInfo>
#include "base_command.h"

class tree_command : public base_command
{
public:
    QString execute(QVector<QString>& args) override
    {
        QString path = "D:/VFS/root";
        if (!args.isEmpty())
        {
            path = "D:/VFS/root" + args[0];
        }

        QDir dir(path);
        if (!dir.exists())
        {
            return "tree: не удаётся получить доступ '" + (args.isEmpty() ? "" : args[0]) + "': отсутствует файл или директория\n";
        }

        return print_tree(dir, 0, "");
    }

private:
    QString print_tree(const QDir& dir, int level, const QString& prefix)
    {
        QString result;
        QFileInfoList entries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name | QDir::DirsFirst);

        for (int i = 0; i < entries.size(); i++)
        {
            bool isLast = (i == entries.size() - 1);
            QFileInfo entry = entries[i];


            QString line = prefix + (isLast ? "+-- " : "|-- ") + entry.fileName();
            if (entry.isDir())
            {
                line += "/";
            }
            result += line + "\n";

            if (entry.isDir())
            {
                QString newPrefix = prefix + (isLast ? "    " : "|   ");
                QDir subDir(entry.filePath());
                result += print_tree(subDir, level + 1, newPrefix);
            }
        }

        return result;
    }
};
#endif // TREE_COMMAND_H

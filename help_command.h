#ifndef HELP_COMMAND_H
#define HELP_COMMAND_H

#include <QString>
#include <QVector>
#include "base_command.h"

class help_command : public base_command
{
public:
    QString execute(QVector<QString>& args) override
    {
        QString help_text =
            "Доступные команды:\n"
            "  ls [path]        - список содержимого каталога\n"
            "  cd <path>        - Поменять текущую директорию\n"
            "  tree [path]      - Показать дерево файлов\n"
            "  tail <file>      - Показать последние 10 элементов в файле\n"
            "  rmdir <dir>      - Удалить пустую директорию\n"
            "  chmod <mode> <file> - Поменять права доступа к файлу\n"
            "  exit             - Выйти из программы\n"
            "  help             - Показать данное сообщение\n"
            "\n"
            "Пример работы:\n"
            "  ls /             - Показать корневую директорию\n"
            "  cd /etc          - Поменять текщую директорию на /etc\n"
            "  tree /etc        - Показать дерево структуры /etc\n"
            "  tail /etc/passwd.txt - Показать последние 10 строк из passwd\n"
            "  rmdir /empty_dir - Удалить пустую директорию\n"
            "  chmod 755 file.txt - Установить права доступа на file.txt - rwxr-xr-x\n";

        return help_text;
    }
};

#endif // HELP_COMMAND_H

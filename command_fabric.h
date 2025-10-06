#ifndef COMMAND_FABRIC_H
#define COMMAND_FABRIC_H
#include "cd_command.h"
#include "ls_command.h"
#include "exit_command.h"
#include "tree_command.h"
#include "tail_command.h"
#include "rmdir_command.h"
#include "chmod_command.h"
#include "help_command.h"
#include <QDebug>

class command_fabric
{
public:
    static base_command* create(const QString& command_name)
    {
        if (command_name == "ls")
        {
            return new ls_command();
        }
        else if (command_name == "cd")
        {
            return new cd_command();
        }
        else if (command_name == "exit")
        {
            return new exit_command();
        }
        else if (command_name == "tree")
        {
            return new tree_command();
        }
        else if (command_name == "tail")
        {
            return new tail_command();
        }
        else if (command_name == "rmdir")
        {
            return new rmdir_command();
        }
        else if (command_name == "chmod")
        {
            return new chmod_command();
        }
        else if (command_name == "help")
        {
            return new help_command();
        }

        qDebug() << "command not found" << command_name;
        return nullptr;
    }
};

#endif // COMMAND_FABRIC_H

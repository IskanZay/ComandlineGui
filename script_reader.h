#ifndef SCRIPT_READER_H
#define SCRIPT_READER_H
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>

class script_reader
{
public:
    QStringList read_data(QString& script_path)
    {
        QFile file(script_path);
        QTextStream in(&file);
        QStringList commands;

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(nullptr, "Warning", "Error to open file");
            return commands;
        }

        while (!in.atEnd())
        {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty())
            {
                commands.append(line);
            }
        }

        file.close();
        return commands;
    }
};

#endif // SCRIPT_READER_H

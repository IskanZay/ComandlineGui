#ifndef TREE_H
#define TREE_H

#include "file_data.h"
#include <QVector>
#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMap>
#include <QDebug>

class tree
{
private:
    file_data* m_root;
    QString m_base_path;
public:
    tree();
    tree(const QString& base_path);
    ~tree();

    file_data* get_root();

    void add(file_data* data);

    file_data* find(int id);
    file_data* find(int id, file_data* data);

    void create_file_csv();
    void delete_csv_file(const QString& filePath = "D:/VFS/FileSystem.csv");
    void load_from_csv();
    void create_file_system();
    void create_file_system(file_data* data, const QString& currentPath);
};

#endif // TREE_H

#include "tree.h"

tree::tree()
{
    m_root = new file_data(0);
}

tree::tree(const QString &base_path)
{
    m_root = new file_data(0);
    m_base_path = base_path;
}

tree::~tree()
{
    if (m_root)
    {
        delete m_root;
        m_root = nullptr;
    }
}

file_data* tree::get_root()
{
    return m_root;
}

file_data* tree::find(int id)
{
    return find(id, m_root);
}

file_data* tree::find(int id, file_data* data)
{
    if (!data)
    {
        return nullptr;
    }

    if (data->get_id() == id)
    {
        return data;
    }

    for (file_data* dt : data->get_children())
    {
        file_data* d = find(id, dt);
        if (d != nullptr)
        {
            return d;
        }
    }
    return nullptr;
}

void tree::add(file_data* data)
{
    if (data->get_parent_id() == 0)
    {
        m_root->add_child(data);
    }
    else
    {
        file_data* parent = find(data->get_parent_id());
        if (parent)
        {
            parent->add_child(data);
        }
        else
        {
            m_root->add_child(data);
        }
    }
}

void tree::create_file_csv()
{
    QFile file("D:/VFS/FileSystem.csv");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);

    out << "id;parent_id;name;type;content\n";
    out << "1;0;docs1;directory;\t\n";
    out << "2;0;docs2;directory;\t\n";
    out << "3;1;report.txt;file;hello world\n";
    out << "4;2;report2.txt;file;hello world2\n";

    file.close();
}

void tree::delete_csv_file(const QString& filePath)
{
    QFile file(filePath);
    file.remove();
}

void tree::load_from_csv()
{
    QFile file("D:/VFS/FileSystem.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    if (!file.exists())
    {
        return;
    }

    QTextStream in(&file);

    if (!in.atEnd())
    {
        QString header = in.readLine();
    }

    while (!in.atEnd())
    {
        QString line = in.readLine();
        file_data* file_dt = file_data::parse_csv_line(line);

        if (file_dt)
        {
            add(file_dt);
        }
    }

    file.close();
}

void tree::create_file_system()
{
    QDir baseDir;

    if (!baseDir.exists(m_base_path))
    {
        if (baseDir.mkpath(m_base_path))
        {
            // ничего
        }
        else
        {
            return;
        }
    }

    for (file_data* child : m_root->get_children())
    {
        create_file_system(child, m_base_path);
    }

}

void tree::create_file_system(file_data* data, const QString& currentPath)
{
    QString fullPath = currentPath + "/" + data->get_name();

    if (data->get_type() == "directory")
    {
        QDir dir;
        dir.mkpath(fullPath);

        for (file_data* child : data->get_children())
        {
            create_file_system(child, fullPath);
        }

    }
    else if (data->get_type() == "file")
    {
        QFile file(fullPath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << data->get_content();
            file.close();
        }
    }
}


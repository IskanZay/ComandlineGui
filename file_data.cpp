#include "file_data.h"

file_data::file_data(int id, int parent_id, QString name, QString type, QString content)
{
    m_id = id;
    m_parent_id = parent_id;
    m_name = name;
    m_type = type;
    m_content = content;
}

file_data::file_data(int id)
{
    m_id = id;
}

file_data::~file_data()
{
    for (file_data* child : m_children)
    {
        delete child;
    }
}

int file_data::get_id()
{
    return m_id;
}

int file_data::get_parent_id()
{
    return m_parent_id;
}

QString file_data::get_name()
{
    return m_name;
}

QString file_data::get_type()
{
    return m_type;
}

QString file_data::get_content()
{
    return m_content;
}

QVector<file_data*> file_data::get_children()
{
    return m_children;
}

void file_data::add_child(file_data* child)
{
     m_children.append(child);
}

file_data* file_data::parse_csv_line(const QString& line)
{
     if (line.trimmed().isEmpty())
     {
         return nullptr;
     }

     QStringList fields = line.split(';');

     if (fields.size() < 5)
     {
         return nullptr;
     }

     bool okId, okParentId;
     int id = fields[0].toInt(&okId);
     int parent_id = fields[1].toInt(&okParentId);

     if (!okId || !okParentId)
     {
         return nullptr;
     }

     QString name = fields[2].trimmed();
     QString type = fields[3].trimmed();
     QString content = fields[4].trimmed();

     return new file_data(id, parent_id, name, type, content);
 }


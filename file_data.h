#ifndef FILE_DATA_H
#define FILE_DATA_H

#include <QString>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QFile>
#include <QTextStream>

class file_data
{
private:
    int m_id;
    int m_parent_id;

    QString m_name;
    QString m_type;
    QString m_content;

    QVector<file_data*> m_children;

public:
    file_data(int id, int parent_id, QString name, QString type, QString content);

    file_data(int id);

    ~file_data();

    int get_id();
    int get_parent_id();
    QString get_name();
    QString get_type();
    QString get_content();

    QVector<file_data*> get_children();

    void add_child(file_data* child);

    static file_data* parse_csv_line(const QString& line);

    static QVector<file_data*> load_from_csv(const QString& filename);

    void print_structure(int indent = 0) const;
};

#endif // FILE_DATA_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QMessageBox>
#include "parser.h"
#include "tree.h"
#include "command_fabric.h"
#include "script_reader.h"
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_textEdit_copyAvailable(bool b);

private:
    Ui::MainWindow *ui;
    tree* m_tree;
    QString current_directory = "/";

    QString script_path;
    QString VFS_path;
    void print_motd();
    void setup_file_system();


};
#endif // MAINWINDOW_H

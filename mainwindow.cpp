#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_tree(nullptr)
{
    ui->setupUi(this);

    setup_file_system();
}

MainWindow::~MainWindow()
{
    if (m_tree)
    {
       delete m_tree;
       m_tree = nullptr;
    }
    delete ui;
}

void MainWindow::setup_file_system()
{
    m_tree = new tree("D:/VFS/root");

    m_tree->create_file_csv();
    m_tree->load_from_csv();
    m_tree->create_file_system();
    m_tree->delete_csv_file();
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    Parser prs;
    prs.Parse(str);
    QVector<QString> args = prs.get_arguments();

    QString com_name = prs.get_command_name();

    if (com_name == "ls")
    {
        QString res;
        res = "ls вызвана с аргументами: ";
        for (auto arg : args)
        {
            res += arg + " ";
        }
        ui->textEdit->append(res);
    }
    else if (com_name == "cd")
    {
        QString res;
        res = "cd вызвана с аргументами: ";
        for (auto arg : args)
        {
            res += arg + " ";
        }
        ui->textEdit->append(res);
    }
    else if (com_name == "exit")
    {
        QApplication::quit();
    }
}

void MainWindow::on_textEdit_copyAvailable(bool b){}

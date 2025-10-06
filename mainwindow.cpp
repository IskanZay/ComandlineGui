#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_tree(nullptr)
{
    ui->setupUi(this);

    setWindowTitle("VFS");

    QStringList args = QApplication::arguments();
    if (args.size() == 3)
    {
        script_path = args[1];
        VFS_path = args[2];
    }
    else
    {
        VFS_path = "D:/VFS/root";
        script_path = "D:/scripts/start_script.txt";
    }

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

void MainWindow::print_motd()
{
    QString motd_path = VFS_path + "/motd.txt";
    QFile file(motd_path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(nullptr, "Warning", "Error to open file");
        return;
    }

    QTextStream prt(&file);

    while (!prt.atEnd())
    {
        QString line = prt.readLine();
        ui->textEdit->append(line);
    }
}

void MainWindow::setup_file_system()
{
    m_tree = new tree(VFS_path);

    m_tree->create_file_csv();
    m_tree->load_from_csv();
    m_tree->create_file_system();
    m_tree->delete_csv_file();

    print_motd();

    script_reader script;
    QStringList commands = script.read_data(script_path);

    for (int i = 0; i < commands.length(); i++)
    {
        QString command_str = commands[i].trimmed();
        if (command_str.isEmpty()) continue;

        ui->textEdit->append("localhost:" + current_directory + "# " + command_str);

        Parser prs;
        prs.Parse(command_str);
        QVector<QString> args = prs.get_arguments();
        QString com_name = prs.get_command_name();

        if (com_name == "cd")
        {
            if (args.isEmpty())
            {
                ui->textEdit->append("cd: отсутствует аргумент");
            }
            else
            {
                QString new_path = args[0];
                if (new_path.startsWith("/"))
                {
                    current_directory = new_path;
                }
                else
                {
                    if (new_path == "..")
                    {
                        if (current_directory != "/")
                        {
                            int lastSlash = current_directory.lastIndexOf('/');
                            current_directory = current_directory.left(lastSlash);
                            if (current_directory.isEmpty()) current_directory = "/";
                        }
                     }
                     else if (new_path == ".")
                     {
                         // пустота
                     }
                     else if (new_path == "~")
                     {
                         current_directory = "/";
                     }
                     else
                     {
                         if (current_directory == "/")
                         {
                             current_directory = "/" + new_path;
                         }
                         else
                         {
                             current_directory += "/" + new_path;
                         }
                     }
                 }
             }
         }
         else
         {
             base_command* command = command_fabric::create(com_name);
             if (command)
             {
                 QString result = command->execute(args);
                 if (!result.isEmpty())
                 {
                     ui->textEdit->append(result);
                 }
                 delete command;
             }
         }
     }
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();
    ui->textEdit->append("localhost:" + current_directory + "# " + str);

    Parser prs;
    prs.Parse(str);
    QVector<QString> args = prs.get_arguments();
    QString com_name = prs.get_command_name();

    if (com_name == "cd")
    {
        if (args.isEmpty())
        {
            ui->textEdit->append("cd: отсутствует аргумент");
        }
        else
        {
            QString new_path = args[0];

            if (new_path.startsWith("/"))
            {
                current_directory = new_path;
            }
            else
            {
                if (new_path == "..")
                {
                    if (current_directory != "/")
                    {
                        int lastSlash = current_directory.lastIndexOf('/');
                        current_directory = current_directory.left(lastSlash);
                        if (current_directory.isEmpty()) current_directory = "/";
                    }
                }
                else if (new_path == ".")
                {
                    // ниче
                }
                else if (new_path == "~")
                {
                    current_directory = "/";
                }
                else
                {
                    if (current_directory == "/")
                    {
                        current_directory = "/" + new_path;
                    }
                    else
                    {
                        current_directory += "/" + new_path;
                    }
                }
            }
        }
    }
    else
    {
        base_command* command = command_fabric::create(com_name);
        if (command)
        {
            QString result = command->execute(args);
            if (!result.isEmpty())
            {
                ui->textEdit->append(result);
            }
            delete command;
        }
        else
        {
            ui->textEdit->append("Команда не найдена: " + com_name);
        }
    }

    ui->lineEdit->clear();
}

void MainWindow::on_textEdit_copyAvailable(bool b){}

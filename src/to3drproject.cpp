#include "to3drproject.h"
#include <qdir.h>
#include <QProcess>
#include <iostream>

#define PROCESSOR_PATH "C:\\Users\\aref\\source\\repos\\ConsoleApp1\\ConsoleApp1\\bin\\Debug\\ConsoleApp1.exe"

using namespace std;

To3DRProject::To3DRProject(const QString& project_name, const QString& project_url, void* tree_model):
    top_node(0),
    image_node(0),
    model_node(0)
{
    this->project_url = project_url;
    this->project_name = project_name;
    this->tree_model = (QStandardItemModel*)tree_model;

    initialize_folders();
}

To3DRProject::~To3DRProject()
{
    un_initialize_all();
}

void To3DRProject::un_initialize_all()
{
    if (top_node)
        delete top_node;
    if (image_node)
        delete image_node;
    if (model_node)
        delete model_node;
}

QString To3DRProject::combine_path(const QString& path, const QString& path2, const QString& path3, const QString& path4, const QString& path5)
{
    // TODO : implement windows support
    QString result = path;
    result += QDir::separator() + path2;
    if (path3 != "")
        result += QDir::separator() + path3;
    if (path4 != "")
        result += QDir::separator() + path4;
    if (path5 != "")
        result += QDir::separator() + path5;
    return result;
}

void To3DRProject::initialize_folders()
{
    un_initialize_all();
    {
        QDir dir(project_url);
        if (!dir.exists())
            dir.mkpath(".");
    }
    {
        QDir dir(combine_path(project_url, "images"));
        if (!dir.exists())
            dir.mkpath(".");
    }
    {
        QDir dir(combine_path(project_url, "features"));
        if (!dir.exists())
            dir.mkpath(".");
    }
    {
        QDir dir(combine_path(project_url, "model"));
        if (!dir.exists())
            dir.mkpath(".");
    }

    top_node = new QStandardItem(QString("Project (") + project_name + ")");

    image_node = new QStandardItem("Images");
    model_node = new QStandardItem("Model");
    top_node->appendRow(image_node);
    top_node->appendRow(model_node);
    top_node->appendRow(new QStandardItem("DEM"));

    tree_model->appendRow(top_node);
    // TODO : create project solution file
}

void To3DRProject::add_image_by_folder(const QString& path)
{

}

void To3DRProject::add_images(const QStringList& image_list)
{
    if (!image_list.size())
    {
        cout << "no image added..." << endl;
        return;
    }

    foreach (QString img_path, image_list)
    {
        cout << img_path.toStdString() << endl;
        QString file_name = img_path.mid(img_path.lastIndexOf('/')+1);
        QString file_name_without_extention = file_name.mid(0, file_name.lastIndexOf('.'));
        image_node->appendRow(new QStandardItem(file_name_without_extention));
        QFile::copy(img_path, combine_path(project_url, "images", file_name));
    }
}

bool To3DRProject::run_feature_extractor()
{
    cout << "runing feature extraction..." << endl;
    QStringList fe_params = QStringList() << "fe" << project_url;
    int result = run_process(fe_params);
    if (result == 0)
        cout << "[finished]" << endl;
    else
        cout << "[failed - " << result << "]" << endl;
    return result == 0;
}

bool To3DRProject::run_3d_recunstruct()
{
    cout << "runing feature extraction..." << endl;
    QStringList fe_params = QStringList() << "3dr" << project_url;
    int result = run_process(fe_params);
    if (result == 0)
        cout << "[finished]" << endl;
    else
        cout << "[failed - " << result << "]" << endl;
    return result == 0;

//    cout << "runing recunstruction..." << endl;
//    // check to see if the directory already exists
//    QString working_dir = combine_path(project_url, "features");
//    /*if (!QDir::exists(working_dir))
//    {
//        Directory.CreateDirectory(working_dir);
//    }
//    else if (Directory.GetFiles(working_dir).Count() > 0) //Directory.Exists(working_dir))
//    {
//        if (MessageBox.Show(
//            "Features has already been extracted for this project.\nBy running feature extraction again, old results will be deleted.\n\nDo you want to continue?",
//            "Warning", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.Yes)
//            Directory.Delete(working_dir, true);
//        else
//            return;
//    }*/

//    QStringList fe_params = QStringList() << QString("--ClusterToCompute=8")
//                                          << QString("--bundlerOutputPath=") + working_dir;

//    int result =  run_process("RunCMVS.py", fe_params, TOOLS_PATH, true);
//    if (result == 0)
//        cout << "[finished]" << endl;
//    else
//        cout << "[failed - " << result << "]" << endl;
//    return result == 0;
}

int To3DRProject::run_process(QStringList params)
{
    QProcess *process = new QProcess();
    process->start(PROCESSOR_PATH, params);
    process->waitForFinished();


    //process->startDetached(command, params, path);
    //process->setWorkingDirectory(path);

//    process->start(path + QDir::separator() + command, params);
    cout << "Outputs::\n" << process->readAllStandardOutput().toStdString() << endl;
    cout << "Errors::\n" << process->readAllStandardError().toStdString() << endl;

    int exitCode = process->exitCode();
    process->close();
    return exitCode;

//    QProcess *process = new QProcess();

//    if (isPythonic)
//    {
//        QString modified_command = (path == "") ? command : path + QDir::separator() + command;

//        path = PYTHON_PATH; // FIXME: check this
//        command = "python.exe";
//        params = QStringList(modified_command) + params;
//    }

//    //process->startDetached(command, params, path);
//    cout << "\ncmd:" << (path + QDir::separator() + command).toStdString() << endl;
//    foreach (QString p, params)
//    {
//        cout << "  " << p.toStdString() << endl;
//    }
//    cout << "\n\n" << endl;

//    process->start(path.replace(QChar('\\'), QChar('/')) + "/" + command, params);
////    process->start(path + QDir::separator() + command, params);
//    process->waitForFinished();
//    cout << "Outputs::\n" << process->readAllStandardOutput().toStdString() << endl;
//    cout << "Errors::\n" << process->readAllStandardError().toStdString() << endl;
//    int exitCode = process->exitCode() == 0;
//    process->close();
//    return exitCode;
}


QStringList To3DRProject::get_list_of_ply_files()
{
    QString dir_path = combine_path(project_url, "features", "pmvs");
    QDir ply_directory(dir_path);
    QStringList images = ply_directory.entryList(QStringList() << "*.ply", QDir::Files);
    QStringList full_path = QStringList();

    foreach(QString img, images)
    {
        full_path.append(combine_path(dir_path, img));
        cout << "ply file: " << img.toStdString() << endl;
    }
    return full_path;
}

#include "to3drproject.h"
#include <qdir.h>
#include <iostream>

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
    result += "/" + path2;
    if (path3 != "")
        result += "/" + path3;
    if (path4 != "")
        result += "/" + path4;
    if (path5 != "")
        result += "/" + path5;
    return result;
}

void To3DRProject::initialize_folders()
{
    cout << "here" << endl;
    un_initialize_all();

    {
        cout << "a" << endl;
        QDir dir(project_url);
        if (!dir.exists())
            dir.mkpath(".");
    }
    {
        cout << "b" << endl;
        QDir dir(combine_path(project_url, "images"));
        if (!dir.exists())
            dir.mkpath(".");
    }
    {
        cout << "c" << endl;
        QDir dir(combine_path(project_url, "features"));
        if (!dir.exists())
            dir.mkpath(".");
    }
    {
        cout << "d" << endl;
        QDir dir(combine_path(project_url, "model"));
        if (!dir.exists())
            dir.mkpath(".");
    }
cout << "e" << endl;

    top_node = new QStandardItem(QString("Project (") + project_name + ")");

    image_node = new QStandardItem("Images");
    model_node = new QStandardItem("Model");
    top_node->appendRow(image_node);
    top_node->appendRow(model_node);
    top_node->appendRow(new QStandardItem("DEM"));
cout << "f" << endl;
    tree_model->appendRow(top_node);
cout << "g" << endl;
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

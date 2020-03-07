#ifndef TO3DRPROJECT_H
#define TO3DRPROJECT_H

#include <qstring.h>
#include <QStandardItemModel>


class To3DRProject
{
public:
    To3DRProject(const QString& project_name, const QString& project_url, void* tree_model);
    ~To3DRProject();

    void add_images(const QStringList& image_list);
    void add_image_by_folder(const QString& path);
    QStringList get_list_of_ply_files();

//private:
    QStandardItemModel* tree_model;
    QStandardItem* top_node;
    QStandardItem* image_node;
    QStandardItem* model_node;


    QString project_name;
    QString project_url;

    bool run_feature_extractor();
    bool run_3d_recunstruct();
    int run_process(QStringList params);
    void un_initialize_all();
    void initialize_folders();
    QString combine_path(const QString& path, const QString& path2, const QString& path3="", const QString& path4="", const QString& path5="");
};

#endif // TO3DRPROJECT_H

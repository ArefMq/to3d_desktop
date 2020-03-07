#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qthread.h>
#include <QStandardItemModel>
#include "src/viewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent (QResizeEvent *event);

protected:
  bool eventFilter(QObject *obj, QEvent *event);

private slots:
  void on_actionExit_triggered();
  void on_actionNew_Project_triggered();
  void on_actionAdd_Images_triggered();
  void on_treeView_clicked(const QModelIndex &index);

  void on_actionExtract_Features_triggered();

  void on_actionRecunstruct_triggered();

  void on_actionReload_3D_Model_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* tree_view_item_model;
    Viewer* viewer;

    void check_button_access();
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/projecthelper.h"
#include <iostream>
#include <QTreeWidgetItem>
#include <qglobal.h>
#include <QFileDialog>
#include <QMessageBox>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tree_view_item_model(new QStandardItemModel())
    , viewer(0)
{
    ui->setupUi(this);
    ui->treeView->setModel(tree_view_item_model);

    this->setWindowTitle("To3D");

    ui->dockWidget_treeview->installEventFilter(this);
    ui->dockWidget_log->installEventFilter(this);
    ui->dockWidget_viewer->installEventFilter(this);


    // FIXME : make these lines work
    ui->dockWidget_treeview->setGeometry(0, 0, 390, 438);
    ui->dockWidget_log->setGeometry(0, 444, 965, 221);
    ui->dockWidget_viewer->setGeometry(403, 0, 562, 438);

    check_button_access();
    srand(time(nullptr));

    viewer = new Viewer(ui->tab_3d);//, "/home/parallels/Workspace/nab/ply/option-0001.ply");
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::Resize && obj == ui->dockWidget_treeview) {
      QResizeEvent *resizeEvent = static_cast<QResizeEvent*>(event);
      ui->treeView->setGeometry(1, 1, resizeEvent->size().width()-5, resizeEvent->size().height()-25);
  }

  if (event->type() == QEvent::Resize && obj == ui->dockWidget_log) {
      QResizeEvent *resizeEvent = static_cast<QResizeEvent*>(event);
      ui->textbox_log->setGeometry(1, 1, resizeEvent->size().width()-5, resizeEvent->size().height()-25);
  }

  if (event->type() == QEvent::Resize && obj == ui->dockWidget_viewer) {
      QResizeEvent *resizeEvent = static_cast<QResizeEvent*>(event);
      ui->tabview_viewer->setGeometry(1, 1, resizeEvent->size().width()-5, resizeEvent->size().height()-25);
      if (viewer)
          viewer->resize(ui->tabview_viewer->x(), ui->tabview_viewer->y(), ui->tabview_viewer->width(), ui->tabview_viewer->height());
  }

//  cout << "main" << this->width() << ", " << this->height() << endl;
//  cout << "tree" << ui->dockWidget_treeview->x() << ", "<< ui->dockWidget_treeview->y() << " - " << ui->dockWidget_treeview->width() << ", " << ui->dockWidget_treeview->height() << endl;
//  cout << "log" << ui->dockWidget_log->x() << ", "<< ui->dockWidget_log->y() << " - " << ui->dockWidget_log->width() << ", " << ui->dockWidget_log->height() << endl;
//  cout << "3d" << ui->dockWidget_viewer->x() << ", "<< ui->dockWidget_viewer->y() << " - " << ui->dockWidget_viewer->width() << ", " << ui->dockWidget_viewer->height() << endl;
//  cout << "\n\n" << endl;

  return QWidget::eventFilter(obj, event);
}


void MainWindow::resizeEvent (QResizeEvent *event)
{
    //ui->treeView->setGeometry(10, 10, this->width()a-20, this->height()-20);
}


void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionNew_Project_triggered()
{
    ProjectHelper::create_new(tree_view_item_model);
    if (ProjectHelper::the_project && ProjectHelper::the_project->project_name != "")
        this->setWindowTitle("To3D :: " + ProjectHelper::the_project->project_name);

    cout << ProjectHelper::the_project->project_url.toStdString() << endl;
    check_button_access();
}

void MainWindow::check_button_access()
{
    bool project_enabled = ProjectHelper::the_project != NULL;

    ui->actionSave->setEnabled(project_enabled);
    ui->actionSave_As->setEnabled(project_enabled);
    ui->actionAdd_Images->setEnabled(project_enabled);
    ui->actionAdd_Video->setEnabled(project_enabled);
    ui->actionExtract_Features->setEnabled(project_enabled);
    ui->actionRecunstruct->setEnabled(project_enabled);
    ui->actionReload_3D_Model->setEnabled(project_enabled);
}

void MainWindow::on_actionAdd_Images_triggered()
{
    if (ProjectHelper::the_project)
    {
        QStringList fileNames = QFileDialog::getOpenFileNames(this, "Select Images", "", "JPEG (*.jpg *.jpeg);;TIFF (*.tif);;PNG (*.png);;All files (*.*)");
        ProjectHelper::the_project->add_images(fileNames);
        cout << fileNames.size() << " files selected." << endl;
    }
    else
        QMessageBox::critical(this, "Error", "No active project!");
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{

}

void MainWindow::on_actionExtract_Features_triggered()
{
    if (ProjectHelper::the_project && ProjectHelper::the_project->run_feature_extractor())
    {
        // TODO: do enableing stuff here
    }
}

void MainWindow::on_actionRecunstruct_triggered()
{
    if (ProjectHelper::the_project && ProjectHelper::the_project->run_3d_recunstruct())
    {
       on_actionReload_3D_Model_triggered();
    }
}

void MainWindow::on_actionReload_3D_Model_triggered()
{
    if (ProjectHelper::the_project)
    {
        viewer->clear_model();
        viewer->load_model(ProjectHelper::the_project->get_list_of_ply_files());
    }
}

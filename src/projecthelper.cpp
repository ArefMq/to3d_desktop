#include "projecthelper.h"
#include "new_project_form.h"
#include <iostream>
#include <qmessagebox.h>

using namespace std;

To3DRProject* ProjectHelper::the_project = 0;


ProjectHelper::ProjectHelper()
{
}

void ProjectHelper::create_new(void* tree_model)
{
    new_project_form npf;
    npf.exec();

    if (npf.result())
    {
        // TODO : check if project already exists
        if (npf.get_project_name() == "" || npf.get_project_url() == "")
            QMessageBox::critical(0, "Error", "\"Project Name\" and \"Project Path\" Can not be empty.");
        else
            the_project = new To3DRProject(npf.get_project_name(), npf.get_project_url(), tree_model);
    }
}

void ProjectHelper::open_existing()
{

}

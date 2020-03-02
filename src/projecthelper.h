#ifndef PROJECTHELPER_H
#define PROJECTHELPER_H

#include "src/to3drproject.h"

class ProjectHelper
{
public:
    ProjectHelper();
    static To3DRProject* the_project;

    static void create_new(void* tree_model);
    static void open_existing();
};

#endif // PROJECTHELPER_H

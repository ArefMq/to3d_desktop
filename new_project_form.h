#ifndef NEW_PROJECT_FORM_H
#define NEW_PROJECT_FORM_H

#include <QDialog>

namespace Ui {
class new_project_form;
}

class new_project_form : public QDialog
{
    Q_OBJECT

public:
    explicit new_project_form(QWidget *parent = nullptr);
    ~new_project_form();
    QString get_project_name() const;
    QString get_project_url() const;

private slots:
    void on_push_rename_clicked();

    void on_push_browse_clicked();

private:
    Ui::new_project_form *ui;
};

#endif // NEW_PROJECT_FORM_H

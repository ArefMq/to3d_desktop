#include "new_project_form.h"
#include "ui_new_project_form.h"
#include <QFileDialog>
#include <qglobal.h>
#include <iostream>

using namespace std;

new_project_form::new_project_form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_project_form)
{
    ui->setupUi(this);
    on_push_rename_clicked();
}

new_project_form::~new_project_form()
{
    delete ui;
}

QString new_project_form::get_project_name() const
{
    return ui->lineEdit_name->text();
}

QString new_project_form::get_project_url() const
{
    return ui->lineEdit_path->text();
}

void new_project_form::on_push_browse_clicked()
{
    QString project_url = QFileDialog::getSaveFileName(this, "Project URL", ui->lineEdit_name->text());
    if (project_url != "")
        ui->lineEdit_path->setText(project_url);
}

void new_project_form::on_push_rename_clicked()
{
    // TODO: add color to these names
    QString animal_list[142] = {
        "Albatross",
        "Alligator",
        "Angelfish",
        "Ant",
        "Anteater",
        "Antelope",
        "Armadillo",
        "Baboon",
        "Bat",
        "Bear",
        "Blue Whale",
        "Bonobo",
        "Brown Bear",
        "Budger",
        "Buffalo",
        "Bumble Bee",
        "Butterfly",
        "Camel",
        "Cat",
        "Caterpillar",
        "Chameleon",
        "Cheetah",
        "Cougar",
        "Cow",
        "Coyote",
        "Crane",
        "Crocodile",
        "Cuttlefish",
        "Deer",
        "Dodo",
        "Dog",
        "Dolphin",
        "Donkey",
        "Duck",
        "Eagle",
        "Elephant",
        "Falcon",
        "Flamingo",
        "Fox",
        "Frog",
        "Giraffe",
        "Glass Lizard",
        "Glow Worm",
        "Goat",
        "Goose",
        "Gopher",
        "Gorilla",
        "Grey Seal",
        "Greyhound",
        "Grizzly Bear",
        "Guppy",
        "Hamster",
        "Hedgehog",
        "Hippopotamus",
        "Honey Bee",
        "Horse",
        "Humboldt Penguin",
        "Hummingbird",
        "Hyena",
        "Iguana",
        "Impala",
        "Jaguar",
        "Jellyfish",
        "Kakapo",
        "Kangaroo",
        "Kiwi",
        "Koala",
        "Lady Bug",
        "Lemur",
        "Leopard",
        "Lion",
        "Lionfish",
        "Little Penguin",
        "Lizard",
        "Llama",
        "Lobster",
        "Manatee",
        "Molly",
        "Monkey",
        "Moose",
        "Mountain Gorilla",
        "Mountain Lion",
        "Mouse",
        "Mule",
        "Nightingale",
        "Octopus",
        "Olm",
        "Ostrich",
        "Otter",
        "Panther",
        "Parrot",
        "Peacock",
        "Pekingese",
        "Pelican",
        "Penguin",
        "Pig",
        "Piranha",
        "Platypus",
        "Polar Bear",
        "Pug",
        "Puma",
        "Quail",
        "Quetzal",
        "Quokka",
        "Quoll",
        "Rabbit",
        "Raccoon",
        "Rat",
        "Red Panda",
        "Reindeer",
        "Rhino",
        "Scorpion",
        "Seahorse",
        "Sheep",
        "Shrimp",
        "Snail",
        "Snake",
        "Squid",
        "Squirrel",
        "Starfish",
        "Swan",
        "Tang",
        "Tiffany",
        "Tiger",
        "Tortoise",
        "Toucan",
        "Tree Frog",
        "Uakari",
        "Uguisu",
        "Vulture",
        "Wallaby",
        "Walrus",
        "Weasel",
        "Whale",
        "Whippet",
        "White Rhinoceros",
        "White Tiger",
        "Wolf",
        "Wolverine",
        "Woodlouse",
        "Woodpecker",
        "Zebra"
    };

    int id = rand() % 142;
    ui->lineEdit_name->setText(animal_list[id]);
}

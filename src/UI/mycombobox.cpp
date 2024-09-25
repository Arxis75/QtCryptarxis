#include "mycombobox.h"

MyComboBox::MyComboBox(QWidget *parent)
    : QComboBox(parent)
{
    // Connecter le signal currentIndexChanged au slot handleCurrentIndexChanged
    connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MyComboBox::handleCurrentIndexChanged);
}

void MyComboBox::handleCurrentIndexChanged(int index)
{
    // Émettre notre signal personnalisé avec le texte de l'élément sélectionné
    emit itemSelected(this->itemText(index));
}

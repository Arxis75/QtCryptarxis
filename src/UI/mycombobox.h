#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QComboBox>

class MyComboBox : public QComboBox
{
    Q_OBJECT  // Nécessaire pour le mécanisme de signaux/slots

public:
    explicit MyComboBox(QWidget *parent = nullptr);

signals:
    void itemSelected(const QString &itemText);  // Signal personnalisé avec le texte de l'élément sélectionné

private slots:
    void handleCurrentIndexChanged(int index);  // Slot interne pour gérer le changement d'index
};

#endif // MYCOMBOBOX_H

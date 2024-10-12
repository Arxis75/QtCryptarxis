#include "myLineEditValueInput.h"

#include <QHBoxLayout>

MyLineEditValueInput::MyLineEditValueInput(QWidget *parent)
    : QWidget(parent)
{
    //Create a horizontal layout of widgets
    QHBoxLayout *hbox = new QHBoxLayout;

    m_rb_hex = new QRadioButton(tr("hex"));
    m_rb_dec = new QRadioButton(tr("dec"));
    m_le_input = new QLineEdit(tr(""));

    connect(m_rb_hex, &QRadioButton::clicked, this, &MyLineEditValueInput::handleHexClicked);
    connect(m_rb_dec, &QRadioButton::clicked, this, &MyLineEditValueInput::handleDecClicked);
    //Propagates a textChanged signal coming from QLineEdit to MyLineEditValueInput
    connect(m_le_input, SIGNAL(textChanged(QString)), this, SIGNAL(textChanged(QString)));

    m_rb_hex->setChecked(true);

    hbox->addWidget(m_rb_hex);
    hbox->addWidget(m_rb_dec);
    hbox->addWidget(m_le_input);
    hbox->addStretch();

    setLayout(hbox);
}

void MyLineEditValueInput::handleHexClicked() {
    int a=1;
}

void MyLineEditValueInput::handleDecClicked() {
    int a=1;
}

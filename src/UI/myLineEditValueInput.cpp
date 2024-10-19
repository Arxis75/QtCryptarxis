#include "myLineEditValueInput.h"

#include <QHBoxLayout>
#include <QValidator>

MyLineEditValueInput::MyLineEditValueInput(QWidget *parent)
    : QWidget(parent)
{
    QRegularExpression hex("0[x][0-9a-fA-F]+");
    m_hex_validator = new QRegularExpressionValidator(hex, this);
    
    QRegularExpression dec("0|[1-9][0-9]+");
    m_dec_validator = new QRegularExpressionValidator(dec, this);

    //Create a horizontal layout of widgets
    QHBoxLayout *hbox = new QHBoxLayout;

    m_label = new QLabel(tr("Nonce:"));
    m_rb_hex = new QRadioButton(tr("hex"));
    m_rb_dec = new QRadioButton(tr("dec"));
    m_le_input = new QLineEdit(tr(""));

    connect(m_rb_hex, &QRadioButton::clicked, this, &MyLineEditValueInput::handleHexClicked);
    connect(m_rb_dec, &QRadioButton::clicked, this, &MyLineEditValueInput::handleDecClicked);
    //Propagates a textChanged signal coming from QLineEdit to MyLineEditValueInput
    connect(m_le_input, SIGNAL(textChanged(QString)), this, SIGNAL(textChanged(QString)));

    m_rb_hex->click();

    hbox->addWidget(m_label);
    hbox->addStretch();
    hbox->addWidget(m_rb_hex);
    hbox->addWidget(m_rb_dec);
    hbox->addWidget(m_le_input);

    setLayout(hbox);
}

MyLineEditValueInput::~MyLineEditValueInput() {
    delete m_label;
    delete m_rb_hex;
    delete m_rb_dec;
    delete m_le_input;
    delete m_hex_validator;
    delete m_dec_validator;
}

void MyLineEditValueInput::handleHexClicked() {
    m_le_input->setValidator(m_hex_validator);
    //m_le_input->setText(QString::fromStdString(changeBase(m_le_input->text().toStdString(), 16)));
}

void MyLineEditValueInput::handleDecClicked() {
    m_le_input->setValidator(m_dec_validator);
   //m_le_input->setText(QString::fromStdString(changeBase(m_le_input->text().toStdString(), 10)));
}

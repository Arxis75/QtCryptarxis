#include "myLineEditValueInput.h"

#include <QHBoxLayout>

MyLineEditValueInput::MyLineEditValueInput(QWidget *parent)
    : QWidget(parent)
    , m_ptr_value(nullptr)
    , m_validator(nullptr)
{
    //Create a horizontal layout of widgets
    QHBoxLayout *hbox = new QHBoxLayout;

    m_label = new QLabel(tr("Nonce:"));

    m_rb_hex = new QRadioButton(tr("Hex"));
    m_rb_dec = new QRadioButton(tr("Dec"));
    m_rb_gwei = new QRadioButton(tr("GWei"));
    m_rb_bin = new QRadioButton(tr("Bin"));

    m_le_input = new QLineEdit(tr(""));

    connect(m_rb_hex,   &QRadioButton::clicked, this, &MyLineEditValueInput::handleRadioClicked);
    connect(m_rb_dec,   &QRadioButton::clicked, this, &MyLineEditValueInput::handleRadioClicked);
    connect(m_rb_gwei,  &QRadioButton::clicked, this, &MyLineEditValueInput::handleRadioClicked);
    connect(m_rb_bin,   &QRadioButton::clicked, this, &MyLineEditValueInput::handleRadioClicked);

    //Propagates a textChanged signal coming from QLineEdit to MyLineEditValueInput
    connect(m_le_input, SIGNAL(textChanged(QString)), this, SIGNAL(textChanged(QString)));

    hbox->addWidget(m_label);
    hbox->addStretch();
    hbox->addWidget(m_rb_hex);
    hbox->addWidget(m_rb_dec);
    hbox->addWidget(m_rb_gwei);
    hbox->addWidget(m_rb_bin);
    hbox->addWidget(m_le_input);

    setLayout(hbox);
    
    handleRadioClicked();
}

MyLineEditValueInput::~MyLineEditValueInput() {
    delete m_label;
    delete m_rb_hex;
    delete m_rb_dec;
    delete m_rb_gwei;
    delete m_rb_bin;
    delete m_validator;
    delete m_le_input;
    delete m_ptr_value;
}

void MyLineEditValueInput::handleRadioClicked()
{
    ByteSet<bool>* p_value = dynamic_cast<ByteSet<bool>*>(m_ptr_value);

    if(m_ptr_value)
        delete m_ptr_value; 

    //const StrByteSetFormat format;
    QRegularExpression _regex;
    string str_value;
    if( m_rb_dec->isChecked() ) {
        m_ptr_value = new StrByteSet<Dec, bool>(p_value ? *p_value : ByteSet<bool>());
        str_value = dynamic_cast<StrByteSet<Dec, bool>*>(m_ptr_value)->toFormat(Dec);
        _regex = QRegularExpression(Dec.Regex.c_str());
    }

    else if( m_rb_gwei->isChecked() ) {
        m_ptr_value = new StrByteSet<GWei, bool>(p_value ? *p_value : ByteSet<bool>());
        str_value = dynamic_cast<StrByteSet<GWei, bool>*>(m_ptr_value)->toFormat(GWei);
        _regex = QRegularExpression(GWei.Regex.c_str());
    }

    else if( m_rb_bin->isChecked() ) {
        m_ptr_value = new StrByteSet<Bin, bool>(p_value ? *p_value : ByteSet<bool>());
        str_value = dynamic_cast<StrByteSet<Bin, bool>*>(m_ptr_value)->toFormat(Bin);
        _regex = QRegularExpression(Bin.Regex.c_str());
    }

    else {
        m_ptr_value = new StrByteSet<Hex, bool>(p_value ? *p_value : ByteSet<bool>());
        str_value = dynamic_cast<StrByteSet<Hex, bool>*>(m_ptr_value)->toFormat(Hex);
        _regex = QRegularExpression(Hex.Regex.c_str());
    }

    if(m_validator)
        delete m_validator;
    m_validator = new QRegularExpressionValidator(_regex, this);
    m_le_input->setValidator(m_validator);

    m_le_input->setText(QString::fromStdString(str_value));
}

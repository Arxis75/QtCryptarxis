#include "myLineEditValueInput.h"

#include <QHBoxLayout>

MyLineEditValueInput::MyLineEditValueInput(QWidget *parent, const StrByteSetFormat &default_format, uint64_t aligned_size)
    : QWidget(parent)
    , m_ptr_value(nullptr)
    , m_default_format(default_format)
    , m_aligned_size(aligned_size)
{
    //Create a horizontal layout of widgets
    QHBoxLayout *hbox = new QHBoxLayout;

    m_label = new QLabel(tr("Nonce:"));
    m_rb_hex = new QRadioButton(tr(Hex.getUIName().c_str()));
    m_rb_dec = new QRadioButton(tr(Dec.getUIName().c_str()));
    m_rb_gwei = new QRadioButton(tr(Gwei.getUIName().c_str()));
    m_rb_wei = new QRadioButton(tr(Wei.getUIName().c_str()));
    m_rb_eth = new QRadioButton(tr(Eth.getUIName().c_str()));
    m_rb_bin = new QRadioButton(tr(Bin.getUIName().c_str()));
    m_le_input = new QLineEdit(tr(""));     

    connect(m_rb_hex,  &QRadioButton::clicked, this, &MyLineEditValueInput::handleRadioClicked);
    connect(m_rb_dec,  &QRadioButton::clicked, this, &MyLineEditValueInput::handleRadioClicked);
    connect(m_rb_gwei, &QRadioButton::clicked, this, &MyLineEditValueInput::handleRadioClicked);
    connect(m_rb_wei,  &QRadioButton::clicked, this, &MyLineEditValueInput::handleRadioClicked);
    connect(m_rb_eth,  &QRadioButton::clicked, this, &MyLineEditValueInput::handleRadioClicked);
    connect(m_rb_bin,  &QRadioButton::clicked, this, &MyLineEditValueInput::handleRadioClicked);

    //Propagates a textChanged signal coming from QLineEdit to MyLineEditValueInput
    connect(m_le_input, SIGNAL(textChanged(QString)), this, SIGNAL(textChanged(QString)));

    // Connecter le signal textChanged au slot handleTextChanged
    connect(this, QOverload<const QString&>::of(&MyLineEditValueInput::textChanged), this, &MyLineEditValueInput::handleTextChanged);

    hbox->addWidget(m_label);
    hbox->addStretch();
    if(showFormat(Hex)) hbox->addWidget(m_rb_hex);
    if(showFormat(Dec)) hbox->addWidget(m_rb_dec);
    if(showFormat(Gwei)) hbox->addWidget(m_rb_gwei);
    if(showFormat(Wei)) hbox->addWidget(m_rb_wei);
    if(showFormat(Eth)) hbox->addWidget(m_rb_eth);
    if(showFormat(Bin)) hbox->addWidget(m_rb_bin);
    hbox->addWidget(m_le_input);

    setLayout(hbox);
    
    if( m_default_format == Dec)
        m_rb_dec->click();
    else if( m_default_format == Gwei)
        m_rb_gwei->click();
    else if( m_default_format == Wei)
        m_rb_wei->click();
    else if( m_default_format == Eth)
        m_rb_eth->click();
    else if( m_default_format == Bin)
        m_rb_bin->click();
    else
        m_rb_hex->click();

    if(m_default_format == Hex)
        //RadioButton Bugfix: prevent unclicking if single
        m_rb_hex->setEnabled(false);
}

MyLineEditValueInput::~MyLineEditValueInput() {
    delete m_label;
    delete m_rb_hex;
    delete m_rb_dec;
    delete m_rb_gwei;
    delete m_rb_wei;
    delete m_rb_eth;
    delete m_rb_bin;
    delete m_le_input;

    delete m_ptr_value;
}

void MyLineEditValueInput::handleTextChanged(const QString &value)
{
    if( m_rb_dec->isChecked() )
        updateValue(Dec, value.toStdString());
    else if( m_rb_gwei->isChecked() )
        updateValue(Gwei, value.toStdString());
    else if( m_rb_wei->isChecked() )
        updateValue(Wei, value.toStdString());
    else if( m_rb_eth->isChecked() )
        updateValue(Eth, value.toStdString());
    else if( m_rb_bin->isChecked() )
        updateValue(Bin, value.toStdString());
    else
        updateValue(Hex, value.toStdString());
}

void MyLineEditValueInput::handleRadioClicked()
{
    //Make a local copy of the value
    ByteSet<bool> value = getByteSet();

    //const StrByteSetFormat format;
    QRegularExpression _regex;
    string str_value;
    if( m_rb_dec->isChecked() ) {
        updateValue(Dec, value);
        str_value = dynamic_cast<StrByteSet<Dec, bool>*>(m_ptr_value)->toUserString(Dec);
        _regex = QRegularExpression(Dec.getRegex().c_str());
    }
    else if( m_rb_gwei->isChecked() ) {
        updateValue(Gwei, value);
        str_value = dynamic_cast<StrByteSet<Gwei, bool>*>(m_ptr_value)->toUserString(Gwei);
        _regex = QRegularExpression(Gwei.getRegex().c_str());
    }
    else if( m_rb_wei->isChecked() ) {
        updateValue(Wei, value);
        str_value = dynamic_cast<StrByteSet<Wei, bool>*>(m_ptr_value)->toUserString(Wei);
        _regex = QRegularExpression(Wei.getRegex().c_str());
    }
    else if( m_rb_eth->isChecked() ) {
        updateValue(Eth, value);
        str_value = dynamic_cast<StrByteSet<Eth, bool>*>(m_ptr_value)->toUserString(Eth);
        _regex = QRegularExpression(Eth.getRegex().c_str());
    }
    else if( m_rb_bin->isChecked() ) {
        updateValue(Bin, value);
        str_value = dynamic_cast<StrByteSet<Bin, bool>*>(m_ptr_value)->toUserString(Bin);
        _regex = QRegularExpression(Bin.getRegex().c_str());
    }
    else {
        updateValue(Hex, value);
        str_value = dynamic_cast<StrByteSet<Hex, bool>*>(m_ptr_value)->toUserString(Hex);
        _regex = QRegularExpression(Hex.getRegex().c_str());
    }

    if(const QValidator *validator = m_le_input->validator())
        delete validator;
    m_le_input->setValidator(new QRegularExpressionValidator(_regex, this));

    m_le_input->setText(QString::fromStdString(str_value));
}

void MyLineEditValueInput::updateValue(const StrByteSetFormat &dest_format, const string &str)
{
    if(m_ptr_value)
        delete m_ptr_value;
    if(dest_format == Dec)
        m_ptr_value = new StrByteSet<Dec, bool>(str, m_aligned_size);
    else if(dest_format == Gwei)
        m_ptr_value = new StrByteSet<Gwei, bool>(str, m_aligned_size);
    else if(dest_format == Wei)
        m_ptr_value = new StrByteSet<Wei, bool>(str, m_aligned_size);
    else if(dest_format == Eth)
        m_ptr_value = new StrByteSet<Eth, bool>(str, m_aligned_size); 
    else if(dest_format == Bin)
        m_ptr_value = new StrByteSet<Bin, bool>(str, m_aligned_size);
    else
        m_ptr_value = new StrByteSet<Hex, bool>(str, m_aligned_size);
}

void MyLineEditValueInput::updateValue(const StrByteSetFormat &dest_format, const ByteSet<bool> &val)
{
    if(m_ptr_value)
        delete m_ptr_value;
    if(dest_format == Dec)
        m_ptr_value = new StrByteSet<Dec, bool>(val);
    else if(dest_format == Gwei)
        m_ptr_value = new StrByteSet<Gwei, bool>(val);
    else if(dest_format == Wei)
        m_ptr_value = new StrByteSet<Wei, bool>(val);
    else if(dest_format == Eth)
        m_ptr_value = new StrByteSet<Eth, bool>(val); 
    else if(dest_format == Bin)
        m_ptr_value = new StrByteSet<Bin, bool>(val);
    else
        m_ptr_value = new StrByteSet<Hex, bool>(val);
}

ByteSet<bool> MyLineEditValueInput::getByteSet() const
{
    ByteSet<bool> ret_val;
    if( ByteSet<bool>* pvalue = dynamic_cast<ByteSet<bool>*>(m_ptr_value) )
        ret_val = *pvalue;
    return ret_val;
}

bool MyLineEditValueInput::showFormat(StrByteSetFormat const & dest_format) const
{
    return   m_default_format == dest_format
          || dest_format == Hex 
          || (m_default_format == Bin && dest_format != Eth && dest_format != Wei)
          || (m_default_format == Gwei && dest_format == Wei);
}


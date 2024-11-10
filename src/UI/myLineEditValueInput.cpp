#include "myLineEditValueInput.h"

#include <QHBoxLayout>
#include <QValidator>

MyLineEditValueInput::MyLineEditValueInput(QWidget *parent, const StrByteSetFormat &default_format)
    : QWidget(parent)
    , m_default_format(default_format)
    , m_ptr_value(nullptr)
{
    //Create a horizontal layout of widgets
    QHBoxLayout *hbox = new QHBoxLayout;

    //Create the widgets
    m_label = new QLabel(tr("Nonce:"));
    newRadioButtons(default_format);
    m_le_input = new QLineEdit(tr(""));     

    //Connect the radioButtons to the MyLineEditValueInput::handleRadioClicked() Slot
    auto it1 = m_rb.begin();
    while(it1 != m_rb.end()) {
        connect(it1->second.rb, &QRadioButton::clicked, this, &MyLineEditValueInput::handleRadioClicked);
        it1++;
    }

    //Propagates a textChanged signal coming from QLineEdit to MyLineEditValueInput
    connect(m_le_input, SIGNAL(textChanged(QString)), this, SIGNAL(textChanged(QString)));

    // Connect the textChanged Signal to the handleTextChanged Slot
    connect(this, QOverload<const QString&>::of(&MyLineEditValueInput::textChanged), this, &MyLineEditValueInput::handleTextChanged);

    //Adds the widgets to a horizontal layout.
    hbox->addWidget(m_label);
    hbox->addStretch();
    auto it2 = m_rb.begin();
    while(it2 != m_rb.end()) {
        hbox->addWidget(it2->second.rb);
        it2++;
    }
    hbox->addWidget(m_le_input);

    setLayout(hbox);

    //Click the most "detailed" (a.k.a last added) format
    m_rb.rbegin()->second.rb->click();

    if(m_rb.size() == 1)
        //RadioButton state bug fix => cannot unclick if single
        m_rb.begin()->second.rb->setEnabled(false);
}

void MyLineEditValueInput::newRadioButtons(const StrByteSetFormat &default_format)
{
    QRadioButton *rb16, *rb10, *rb2;
    FUpdateValueFromString f16_val_str, f10_val_str, f2_val_str;
    FUpdateValueFromByteSet f16_val_bs, f10_val_bs, f2_val_bs;
    FUpdateString f16_str, f10_str, f2_str;
    FUpdateRegex f16_regex, f10_regex, f2_regex;
    RadioButtonFunctions f16, f10, f2;

    if(true)
    {
        if(default_format == Hex20) {    
            f16_val_str = std::bind(&MyLineEditValueInput::updateValueFromString<Hex20>, this, std::placeholders::_1);
            f16_val_bs = std::bind(&MyLineEditValueInput::updateValueFromByteSet<Hex20>, this, std::placeholders::_1);
            f16_str = std::bind(&MyLineEditValueInput::updateString<Hex20>, this);
            f16_regex = std::bind(&MyLineEditValueInput::updateRegex<Hex20>, this);
        }
        else if(default_format == Hex32) {
            f16_val_str = std::bind(&MyLineEditValueInput::updateValueFromString<Hex32>, this, std::placeholders::_1);
            f16_val_bs = std::bind(&MyLineEditValueInput::updateValueFromByteSet<Hex32>, this, std::placeholders::_1);
            f16_str = std::bind(&MyLineEditValueInput::updateString<Hex32>, this);
            f16_regex = std::bind(&MyLineEditValueInput::updateRegex<Hex32>, this);        
        }
        else if(default_format == Hex33) {
            f16_val_str = std::bind(&MyLineEditValueInput::updateValueFromString<Hex33>, this, std::placeholders::_1);
            f16_val_bs = std::bind(&MyLineEditValueInput::updateValueFromByteSet<Hex33>, this, std::placeholders::_1);
            f16_str = std::bind(&MyLineEditValueInput::updateString<Hex33>, this);
            f16_regex = std::bind(&MyLineEditValueInput::updateRegex<Hex33>, this);    
        }
        else if(default_format == Hex64) {
            f16_val_str = std::bind(&MyLineEditValueInput::updateValueFromString<Hex64>, this, std::placeholders::_1);
            f16_val_bs = std::bind(&MyLineEditValueInput::updateValueFromByteSet<Hex64>, this, std::placeholders::_1);
            f16_str = std::bind(&MyLineEditValueInput::updateString<Hex64>, this);
            f16_regex = std::bind(&MyLineEditValueInput::updateRegex<Hex64>, this);     
        }
        else {
            f16_val_str = std::bind(&MyLineEditValueInput::updateValueFromString<Hex>, this, std::placeholders::_1);
            f16_val_bs = std::bind(&MyLineEditValueInput::updateValueFromByteSet<Hex>, this, std::placeholders::_1);
            f16_str = std::bind(&MyLineEditValueInput::updateString<Hex>, this);
            f16_regex = std::bind(&MyLineEditValueInput::updateRegex<Hex>, this);    
        }
        rb16 = new QRadioButton(tr("Hex"));
        f16 = {rb16, f16_val_str, f16_val_bs, f16_str, f16_regex};
        m_rb.insert(std::make_pair(0, f16));
    }

    if(default_format == Dec || default_format == Eth || default_format == Gwei || default_format == Bin)
    {
        if(default_format == Dec || default_format == Bin) {    
            f10_val_str = std::bind(&MyLineEditValueInput::updateValueFromString<Dec>, this, std::placeholders::_1);
            f10_val_bs = std::bind(&MyLineEditValueInput::updateValueFromByteSet<Dec>, this, std::placeholders::_1);
            f10_str = std::bind(&MyLineEditValueInput::updateString<Dec>, this);
            f10_regex = std::bind(&MyLineEditValueInput::updateRegex<Dec>, this);
            rb10 = new QRadioButton(tr("Dec"));
        }
        else if(default_format == Eth) {    
            f10_val_str = std::bind(&MyLineEditValueInput::updateValueFromString<Eth>, this, std::placeholders::_1);
            f10_val_bs = std::bind(&MyLineEditValueInput::updateValueFromByteSet<Eth>, this, std::placeholders::_1);
            f10_str = std::bind(&MyLineEditValueInput::updateString<Eth>, this);
            f10_regex = std::bind(&MyLineEditValueInput::updateRegex<Eth>, this);
            rb10 = new QRadioButton(tr("Eth"));
        }
        else if(default_format == Gwei) {    
            f10_val_str = std::bind(&MyLineEditValueInput::updateValueFromString<Gwei>, this, std::placeholders::_1);
            f10_val_bs = std::bind(&MyLineEditValueInput::updateValueFromByteSet<Gwei>, this, std::placeholders::_1);
            f10_str = std::bind(&MyLineEditValueInput::updateString<Gwei>, this);
            f10_regex = std::bind(&MyLineEditValueInput::updateRegex<Gwei>, this);
            rb10 = new QRadioButton(tr("Gwei"));
        }
        f10 = {rb10, f10_val_str, f10_val_bs, f10_str, f10_regex};
        m_rb.insert(std::make_pair(1, f10));
    }

    if(default_format == Bin) {    
        f2_val_str = std::bind(&MyLineEditValueInput::updateValueFromString<Bin>, this, std::placeholders::_1);
        f2_val_bs = std::bind(&MyLineEditValueInput::updateValueFromByteSet<Bin>, this, std::placeholders::_1);
        f2_str = std::bind(&MyLineEditValueInput::updateString<Bin>, this);
        f2_regex = std::bind(&MyLineEditValueInput::updateRegex<Bin>, this);

        rb2 = new QRadioButton(tr("Bin"));
        f2 = {rb2, f2_val_str, f2_val_bs, f2_str, f2_regex};
        m_rb.insert(std::make_pair(2, f2));
    }
}

MyLineEditValueInput::~MyLineEditValueInput() {
    delete m_label;
    while(m_rb.size()) {
        delete m_rb.begin()->second.rb;
        m_rb.erase(m_rb.begin());
    }
    delete m_le_input;
    delete m_ptr_value;
}

void MyLineEditValueInput::handleTextChanged(const QString &value)
{
    auto it = m_rb.begin();
    while(it!=m_rb.end() && !it->second.rb->isChecked())
        it++;

    if(it != m_rb.end() )
        it->second.f_update_val_from_str(value.toStdString());
}

void MyLineEditValueInput::handleRadioClicked()
{
    //Make a local copy of the value
    ByteSet<bool> value = getValue();

    auto it = m_rb.begin();
    while(it!=m_rb.end() && !it->second.rb->isChecked())
        it++;

    if(it != m_rb.end() ) {
        it->second.f_update_val_from_bs(value);
        it->second.f_update_str();
        it->second.f_update_regex();
    }
}

ByteSet<bool> MyLineEditValueInput::getValue() const
{
    ByteSet<bool> ret_val;
    if( ByteSet<bool>* pvalue = dynamic_cast<ByteSet<bool>*>(m_ptr_value); pvalue)
        ret_val = *pvalue;
    return ret_val;
}

template<StrByteSetFormat const & f>
    void MyLineEditValueInput::updateValueFromString(const string &str)
{
    if(m_ptr_value)
        delete m_ptr_value;
    m_ptr_value = new StrByteSet<f, bool>(str, f.getByteSize()<<3);
}

template<StrByteSetFormat const & f>
    void MyLineEditValueInput::updateValueFromByteSet(const ByteSet<bool> &val)
{
    if(m_ptr_value)
        delete m_ptr_value;
    m_ptr_value = new StrByteSet<f, bool>(val);
}

template<StrByteSetFormat const & f>
    void MyLineEditValueInput::updateString()
{
    m_le_input->setText(QString::fromStdString(dynamic_cast<StrByteSet<f, bool>*>(m_ptr_value)->toUserString(f)));
}

template<StrByteSetFormat const & f>
    void MyLineEditValueInput::updateRegex()
{
    QRegularExpression _regex(f.getRegex().c_str());   
    if(const QValidator *validator = m_le_input->validator(); validator)
        delete validator;
    m_le_input->setValidator(new QRegularExpressionValidator(_regex, this));
}

const vector<QRadioButton const*> MyLineEditValueInput::getRadioButtons() const
{
    vector<QRadioButton const*> v;

    auto it = m_rb.begin();
    while(it!=m_rb.end()) {
        v.push_back(it->second.rb);
        it++;
    }
    return v;
}
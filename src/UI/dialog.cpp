#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , m_pmnc(nullptr)
{
    ui->setupUi(this);

    updateWallet();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::updateWallet() {
    if( ui->radioButton_12_words->isChecked() )
        m_pmnc = new BIP39::Mnemonic(128);
    else
        m_pmnc = new BIP39::Mnemonic(256);

    m_pmnc->setPassword(ui->lineEdit_bip39_pwd->text().toStdString());

    m_pmnc->set_full_word_list(ui->plainTextEdit_mnc->toPlainText().toStdString());

    Privkey k = Privkey( *m_pmnc,
                         ui->lineEdit_derivation_path->text().toStdString().c_str(),
                         ui->lineEdit_derivation_path_index->text().toInt() );

    stringstream stream;

    stream.str(std::string());
    if( m_pmnc->is_valid() )
        stream << "0x" << std::hex << k.getSecret();
    else
        stream << "N/A";
    ui->lineEdit_k->setText( QString::fromStdString(stream.str())  );

    stream.str(std::string());
    if( m_pmnc->is_valid() )
        stream << "0x0" << std::hex << k.getPubKey().getKey(Pubkey::Format::PREFIXED_X);
    else
        stream << "N/A";
    ui->lineEdit_pub_c->setText( QString::fromStdString(stream.str()) );

    stream.str(std::string());
    if( m_pmnc->is_valid() )
        stream << "0x" << std::hex << k.getPubKey().getAddress();
    else
        stream << "N/A";
    ui->lineEdit_address->setText( QString::fromStdString(stream.str()) );

    delete m_pmnc;
}

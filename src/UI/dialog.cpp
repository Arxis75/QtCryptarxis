#include "dialog.h"
#include "./ui_dialog.h"

#include <eth/Transaction.h>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , m_pmnc(nullptr)
{
    ui->setupUi(this);

    updateWallet();
    updateReadTx();
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
    ui->lineEdit_k->setText( QString::fromStdString(stream.str()) );

    stream.str(std::string());
    if( m_pmnc->is_valid() )
        stream << "0x" << std::hex << k.getPubKey().getKey(Pubkey::Format::PREFIXED_X);
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

void Dialog::updateReadTx() {
    const string raw_tx(ui->plainTextEdit_raw_tx->toPlainText().toStdString());

    SignedTransaction* pstx = SignedTransaction::parse(raw_tx);
    if(pstx) {
        stringstream stream;

        ui->radioButton_invalid_tx->setChecked(false);
        ui->radioButton_pre_eip155->setChecked(pstx->getPayload().getFormat() == TransactionPayload::Format::PRE_EIP_155);
        ui->radioButton_eip155->setChecked(pstx->getPayload().getFormat() == TransactionPayload::Format::EIP_155);
        ui->radioButton_eip2930->setChecked(pstx->getPayload().getFormat() == TransactionPayload::Format::EIP_2930);
        ui->radioButton_eip1559->setChecked(pstx->getPayload().getFormat() == TransactionPayload::Format::EIP_1559);

        stream.str(std::string());
        //stream << "0x" << std::hex << pstx->serialize();
        stream << "0x" << std::hex << pstx->serialize().keccak256();
        ui->lineEdit_tx_hash->setText(QString::fromStdString(stream.str()));

        stream.str(std::string());
        stream << std::dec << pstx->getPayload().getChainId();
        ui->lineEdit_chainId->setText(QString::fromStdString(stream.str()));

        stream.str(std::string());
        stream << std::dec << pstx->getPayload().getNonce();
        ui->lineEdit_nonce->setText(QString::fromStdString(stream.str()));

        stream.str(std::string());
        stream << std::dec << pstx->getPayload().getGasPrice();
        ui->lineEdit_gasprice->setText(QString::fromStdString(stream.str()));

        stream.str(std::string());
        stream << std::dec << pstx->getPayload().getMaxPriorityFeePerGas();
        ui->lineEdit_max_priority_fee_per_gas->setText(QString::fromStdString(stream.str()));

        stream.str(std::string());
        stream << std::dec << pstx->getPayload().getMaxFeePerGas();
        ui->lineEdit_max_fee_per_gas->setText(QString::fromStdString(stream.str()));

        stream.str(std::string());
        stream << std::dec << pstx->getPayload().getGasLimit();
        ui->lineEdit_gaslimit->setText(QString::fromStdString(stream.str()));

        stream.str(std::string());
        stream << "0x" << std::hex << pstx->getPayload().getTo();
        ui->lineEdit_to->setText(QString::fromStdString(stream.str()));

        stream.str(std::string());
        stream << std::dec << pstx->getPayload().getValue();
        ui->lineEdit_eth->setText(QString::fromStdString(stream.str()));

        stream.str(std::string());
        stream << "0x";
        if(pstx->getPayload().getData().byteSize() > 0) stream << std::hex << pstx->getPayload().getData();
        ui->lineEdit_data->setText(QString::fromStdString(stream.str()));

        stream.str(std::string());
        stream  << std::dec << pstx->getSignature().get_imparity();
        ui->lineEdit_v->setText(QString::fromStdString(stream.str()));

        stream.str(std::string());
        stream << "0x" << std::hex << pstx->getSignature().get_r();
        ui->lineEdit_r->setText(QString::fromStdString(stream.str()));

        stream.str(std::string());
        stream << "0x" << std::hex << pstx->getSignature().get_s();
        ui->lineEdit_s->setText(QString::fromStdString(stream.str()));

        Pubkey pubkey;
        if( pstx->getSignature().ecrecover(pubkey, pstx->getPayload().serializeAsSigningPayload().keccak256()) )
        {
            stream.str(std::string());
            stream << "0x" << std::hex << pubkey.getKey(Pubkey::Format::PREFIXED_X);
            ui->lineEdit_from_pubkey->setText(QString::fromStdString(stream.str()));

            stream.str(std::string());
            stream << "0x" << std::hex << pubkey.getAddress();
            ui->lineEdit_from_address->setText(QString::fromStdString(stream.str()));
        }
        else
        {
            stream.str(std::string());
            stream << "N/A";
            ui->lineEdit_from_pubkey->setText(QString::fromStdString(stream.str()));
            ui->lineEdit_from_address->setText(QString::fromStdString(stream.str()));
        }
    }
    else
    {
        stringstream stream;

        stream.str(std::string());
        stream << "N/A";

        ui->radioButton_invalid_tx->setChecked(true);
        ui->radioButton_pre_eip155->setChecked(false);
        ui->radioButton_eip155->setChecked(false);
        ui->radioButton_eip2930->setChecked(false);
        ui->radioButton_eip1559->setChecked(false);

        ui->lineEdit_tx_hash->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_chainId->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_nonce->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_max_priority_fee_per_gas->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_max_fee_per_gas->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_gasprice->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_gaslimit->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_to->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_eth->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_data->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_access_list->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_v->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_r->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_s->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_from_pubkey->setText(QString::fromStdString(stream.str()));
        ui->lineEdit_from_address->setText(QString::fromStdString(stream.str()));
    }
}


#include "dialog.h"
#include "./ui_dialog.h"

#include <eth/Transaction.h>

#include <QGridLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    updateWallet();
    updateReadTx();
    updateForgeTx();

    QVBoxLayout *layout = new QVBoxLayout(ui->tab_4);

    MyLineEditValueInput *m_forge_chain_id = new MyLineEditValueInput(ui->tab_4, Dec);
    MyLineEditValueInput *m_forge_nonce = new MyLineEditValueInput(ui->tab_4, Dec);
    MyLineEditValueInput *m_forge_max_priority_fee = new MyLineEditValueInput(ui->tab_4, Gwei);
    MyLineEditValueInput *m_forge_max_fee = new MyLineEditValueInput(ui->tab_4, Gwei);
    MyLineEditValueInput *m_forge_gas_price = new MyLineEditValueInput(ui->tab_4, Gwei);
    MyLineEditValueInput *m_forge_gas_limit = new MyLineEditValueInput(ui->tab_4, Gwei);
    MyLineEditValueInput *m_forge_to = new MyLineEditValueInput(ui->tab_4, Hex, 160);
    MyLineEditValueInput *m_forge_eth = new MyLineEditValueInput(ui->tab_4, Eth);
    MyLineEditValueInput *m_forge_data = new MyLineEditValueInput(ui->tab_4);
    MyLineEditValueInput *m_forge_access_list = new MyLineEditValueInput(ui->tab_4);
    MyLineEditValueInput *m_forge_v = new MyLineEditValueInput(ui->tab_4, Dec);
    MyLineEditValueInput *m_forge_r = new MyLineEditValueInput(ui->tab_4, Hex, 256);
    MyLineEditValueInput *m_forge_s = new MyLineEditValueInput(ui->tab_4, Hex, 256);

    m_forge_chain_id->setTitle(tr("Chain Id:"));
    m_forge_nonce->setTitle(tr("Nonce:"));
    m_forge_max_priority_fee->setTitle(tr("Max Priority Fee Per Gas:"));
    m_forge_max_fee->setTitle(tr("Max Fee Per Gas:"));
    m_forge_gas_price->setTitle(tr("Gas Price:"));
    m_forge_gas_limit->setTitle(tr("Gas Limit:"));
    m_forge_to->setTitle(tr("To:"));
    m_forge_eth->setTitle(tr("Eth:"));
    m_forge_data->setTitle(tr("Data:"));
    m_forge_access_list->setTitle(tr("Access List:"));
    m_forge_v->setTitle(tr("v:"));
    m_forge_r->setTitle(tr("r:"));
    m_forge_s->setTitle(tr("s:"));

    layout->addWidget(m_forge_chain_id);
    layout->addWidget(m_forge_nonce);
    layout->addWidget(m_forge_max_priority_fee);
    layout->addWidget(m_forge_max_fee);
    layout->addWidget(m_forge_gas_price);
    layout->addWidget(m_forge_gas_limit);
    layout->addWidget(m_forge_to);
    layout->addWidget(m_forge_eth);
    layout->addWidget(m_forge_data);
    layout->addWidget(m_forge_access_list);
    layout->addWidget(m_forge_v);
    layout->addWidget(m_forge_r);
    layout->addWidget(m_forge_s);

    connect(m_forge_chain_id, SIGNAL(textChanged(QString)), this, SLOT(updateForgeTx()));
    connect(m_forge_nonce, SIGNAL(textChanged(QString)), this, SLOT(updateForgeTx()));
    connect(m_forge_max_priority_fee, SIGNAL(textChanged(QString)), this, SLOT(updateForgeTx()));
    connect(m_forge_max_fee, SIGNAL(textChanged(QString)), this, SLOT(updateForgeTx()));
    connect(m_forge_gas_price, SIGNAL(textChanged(QString)), this, SLOT(updateForgeTx()));
    connect(m_forge_gas_limit, SIGNAL(textChanged(QString)), this, SLOT(updateForgeTx()));
    connect(m_forge_to, SIGNAL(textChanged(QString)), this, SLOT(updateForgeTx()));
    connect(m_forge_eth, SIGNAL(textChanged(QString)), this, SLOT(updateForgeTx()));
    connect(m_forge_data, SIGNAL(textChanged(QString)), this, SLOT(updateForgeTx()));
    connect(m_forge_access_list, SIGNAL(textChanged(QString)), this, SLOT(updateForgeTx()));
    connect(m_forge_v, SIGNAL(textChanged(QString)), this, SLOT(updateForgeTx()));
    connect(m_forge_r, SIGNAL(textChanged(QString)), this, SLOT(updateForgeTx()));
    connect(m_forge_s, SIGNAL(textChanged(QString)), this, SLOT(updateForgeTx()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::updateWallet() {
/*    BIP39::Mnemonic* pmnc = nullptr;

    if( ui->radioButton_12_words->isChecked() )
        pmnc = new BIP39::Mnemonic(128);
    else
        pmnc = new BIP39::Mnemonic(256);

    if(pmnc) {
        pmnc->setPassword(ui->lineEdit_bip39_pwd->text().toStdString());

        pmnc->set_full_word_list(ui->plainTextEdit_mnc->toPlainText().toStdString());

        Privkey k = Privkey( *pmnc,
                             ui->lineEdit_derivation_path->text().toStdString().c_str(),
                             ui->lineEdit_derivation_path_index->text().toInt() );

        stringstream stream;

        stream.str(std::string());
        if( pmnc->is_valid() )
            stream << "0x" << std::hex << k.getSecret();
        else
            stream << "N/A";
        ui->lineEdit_k->setText( QString::fromStdString(stream.str()) );

        stream.str(std::string());
        if( pmnc->is_valid() )
            stream << "0x" << std::hex << k.getPubKey().getKey(Pubkey::Format::PREFIXED_X);
        else
            stream << "N/A";
        ui->lineEdit_pub_c->setText( QString::fromStdString(stream.str()) );

        stream.str(std::string());
        if( pmnc->is_valid() )
            stream << "0x" << std::hex << k.getPubKey().getAddress();
        else
            stream << "N/A";
        ui->lineEdit_address->setText( QString::fromStdString(stream.str()) );

        delete pmnc;
    }*/
}

void Dialog::updateReadTx() {/*
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
        stream << "0x" << std::hex << ByteSet(raw_tx,raw_tx.length(),16).keccak256();
        //stream << "0x" << std::hex << pstx->serialize().keccak256();
        ui->lineEdit_tx_hash->setText(QString::fromStdString(stream.str()));

        stream.str(std::string());
        if(pstx->getPayload().getChainId().as_uint64() > 0) stream << std::dec << pstx->getPayload().getChainId();
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
    }*/
}

void Dialog::updateForgeTx() {

    TransactionPayload::Format tx_type;
    if( ui->radioButton_pre_eip155_tab3->isChecked() )
        tx_type = TransactionPayload::Format::PRE_EIP_155;
    else if( ui->radioButton_eip155_tab3->isChecked() )
        tx_type = TransactionPayload::Format::EIP_155;
    else if( ui->radioButton_eip2930_tab3->isChecked() )
        tx_type = TransactionPayload::Format::EIP_2930;
    else
        tx_type = TransactionPayload::Format::EIP_1559;
/*
    const Integer chainId(ui->lineEdit_chainId_tab3->text().toStdString());
    const Integer nonce(ui->lineEdit_nonce_tab3->text().toStdString());
    const Integer max_priority_fee_per_gas(ui->lineEdit_max_priority_fee_per_gas_tab3->text().toStdString());
    const Integer max_fee_per_gas(ui->lineEdit_max_fee_per_gas_tab3->text().toStdString());
    const Integer gasprice(ui->lineEdit_gasprice_tab3->text().toStdString());
    const Integer gaslimit(ui->lineEdit_gaslimit_tab3->text().toStdString());
    const ByteSet to(ui->lineEdit_to_tab3->text().toStdString(), ui->lineEdit_to_tab3->text().length()-2, 16);
    const Integer eth(ui->lineEdit_eth_tab3->text().toStdString());
    const ByteSet data(ui->lineEdit_data_tab3->text().toStdString(), ui->lineEdit_data_tab3->text().length()-2,  16);
    const ByteSet access_list(ui->lineEdit_access_list_tab3->text().toStdString(), ui->lineEdit_access_list_tab3->text().length()-2, 16);
    const bool v(ui->lineEdit_v_tab3->text() == "1" ? true : false);
    const ByteSet r(ui->lineEdit_r_tab3->text().toStdString(), ui->lineEdit_r_tab3->text().length()-2, 16);
    const ByteSet s(ui->lineEdit_s_tab3->text().toStdString(), ui->lineEdit_s_tab3->text().length()-2, 16);
*/
    Integer nonce;
    std::stringstream ss;
    ss << std::hex << ui->lineEdit_nonce_tab3->text().toStdString().c_str();
    ss >> nonce;
/*
    TransactionPayload* ptxp = nullptr;
    switch( tx_type )
    {
        case TransactionPayload::Format::PRE_EIP_155:
            ptxp = new TransactionPayload( ByteSet(nonce, nonce.length(), 16),
                                           ByteSet(gasprice, gasprice.length(), 16),
                                           ByteSet(gaslimit, gaslimit.length(), 16),
                                           to,
                                           ByteSet(eth, eth.length(), 16),
                                           data );
            break;
        case TransactionPayload::Format::EIP_155:
            break;
        case TransactionPayload::Format::EIP_2930:
            break;
        default:
            break;
    }

    if(ptxp) {
        Signature sig = Signature(ByteSet(r, r.length(), 16), ByteSet(s, s.length(), 16), ByteSet(v, v.length(), 16).as_bool());

        SignedTransaction* pstx = new SignedTransaction(*ptxp, sig);
        if(pstx) {
            stringstream stream;

            stream.str(std::string());
            stream << "0x" << std::hex << pstx->serialize();
            ui->plainTextEdit_raw_tx_tab3->setPlainText(QString::fromStdString(stream.str()));

            stream.str(std::string());
            stream << "0x" << std::hex << pstx->serialize().keccak256();
            ui->lineEdit_tx_hash_tab3->setText(QString::fromStdString(stream.str()));

            Pubkey pubkey;
            if( pstx->getSignature().ecrecover(pubkey, pstx->getPayload().serializeAsSigningPayload().keccak256()) )
            {
                stream.str(std::string());
                stream << "0x" << std::hex << pubkey.getKey(Pubkey::Format::PREFIXED_X);
                ui->lineEdit_from_pubkey_tab3->setText(QString::fromStdString(stream.str()));

                stream.str(std::string());
                stream << "0x" << std::hex << pubkey.getAddress();
                ui->lineEdit_from_address_tab3->setText(QString::fromStdString(stream.str()));
            }
            delete pstx;
        }
        else {
            stringstream stream;
            stream.str(std::string());
            stream << "N/A";

            ui->plainTextEdit_raw_tx_tab3->setPlainText(QString::fromStdString(stream.str()));
            ui->lineEdit_tx_hash_tab3->setText(QString::fromStdString(stream.str()));
            ui->lineEdit_from_pubkey_tab3->setText(QString::fromStdString(stream.str()));
            ui->lineEdit_from_address_tab3->setText(QString::fromStdString(stream.str()));
        }
        delete ptxp;
    }
*/
}


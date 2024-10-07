#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <crypto/bips.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
    void updateWallet();
    void updateReadTx();

private slots:
    void on_plainTextEdit_mnc_textChanged() { updateWallet(); }
    void on_radioButton_12_words_clicked() { updateWallet(); }
    void on_radioButton_24_words_clicked() { updateWallet(); }
    void on_lineEdit_derivation_path_textChanged(const QString &arg1) { updateWallet(); }
    void on_lineEdit_derivation_path_index_textChanged(const QString &arg1) { updateWallet(); }
    void on_lineEdit_bip39_pwd_textChanged(const QString &arg1) { updateWallet(); }

    void on_plainTextEdit_raw_tx_textChanged() { updateReadTx(); }

private:
    Ui::Dialog *ui;
    BIP39::Mnemonic* m_pmnc;
};
#endif // DIALOG_H

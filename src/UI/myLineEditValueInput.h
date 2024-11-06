#pragma once

#include <QWidget>
#include <QLabel>
#include <QRadioButton>
#include <QLineEdit>
#include <QValidator>

#include <data/ByteSet.h>

//https://doc.qt.io/qt-5/qtwidgets-widgets-groupbox-example.html
class MyLineEditValueInput : public QWidget
{
    Q_OBJECT

public:
    explicit MyLineEditValueInput(QWidget *parent = nullptr);
    ~MyLineEditValueInput();

    void setTitle(const QString &title) const { m_label->setText(title); }

    //Value accessors
    //inline ByteSet toByteSet(uint64_t size = 0) const { return ByteSet(m_le_input->text().toStdString(), size, m_rb_dec->isChecked() ? 10 : 16); }
    //inline const string toStdString() const { return m_le_input->text().toStdString(); }

signals:
    void textChanged(const QString &value);

protected slots:
    void handleRadioClicked();
    void handleTextChanged(const QString &value);  // Slot interne pour gérer le changement d'index

private:    
    QLabel *m_label;
    QRadioButton *m_rb_hex;
    QRadioButton *m_rb_dec;
    QRadioButton *m_rb_gwei;
    QRadioButton *m_rb_bin;
    QLineEdit *m_le_input;
    QRegularExpressionValidator *m_validator;

    IStrByteSet<bool> *m_ptr_value;  //non-aligned bitset allowed
};

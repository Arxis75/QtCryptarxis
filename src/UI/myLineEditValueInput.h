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
    explicit MyLineEditValueInput(QWidget *parent = nullptr, const StrByteSetFormat &default_format = Hex, uint64_t bit_size = 0);
    ~MyLineEditValueInput();

    void setTitle(const QString &title) const { m_label->setText(title); }

signals:
    void textChanged(const QString &value);

protected slots:
    void handleRadioClicked();
    void handleTextChanged(const QString &value);  // Slot interne pour gérer le changement d'index

protected:
    void updateValue(const StrByteSetFormat &dest_format, const string &str);
    void updateValue(const StrByteSetFormat &dest_format, const ByteSet<bool> &val);
    ByteSet<bool> getByteSet() const;
    bool showFormat(StrByteSetFormat const & dest_format) const;

private:    
    QLabel *m_label;
    QRadioButton *m_rb_hex;
    QRadioButton *m_rb_dec;
    QRadioButton *m_rb_gwei;
    QRadioButton *m_rb_wei;
    QRadioButton *m_rb_eth;
    QRadioButton *m_rb_bin;
    QLineEdit *m_le_input;

    ByteSet<bool> *m_ptr_value;  //non-aligned bitset allowed

    const StrByteSetFormat m_default_format;
    const uint64_t m_aligned_size;
};

#pragma once

#include <QWidget>
#include <QLabel>
#include <QRadioButton>
#include <QLineEdit>

#include <data/RLPByteSet.h>

//https://doc.qt.io/qt-5/qtwidgets-widgets-groupbox-example.html
class MyLineEditValueInput : public QWidget
{
    Q_OBJECT

public:
    explicit MyLineEditValueInput(QWidget *parent = nullptr);
    ~MyLineEditValueInput();

    void setTitle(const QString &title) const { m_label->setText(title); }

    //Value accessors
    inline ByteSet toByteSet(uint64_t size = 0) const { return ByteSet(m_le_input->text().toStdString(), size, m_rb_dec->isChecked() ? 10 : 16); }
    inline const string toStdString() const { return m_le_input->text().toStdString(); }

signals:
    void textChanged(const QString &value);

protected slots:
    void handleHexClicked();
    void handleDecClicked();

private:
    QValidator *m_hex_validator;
    QValidator *m_dec_validator;
    QLabel *m_label;
    QRadioButton *m_rb_hex;
    QRadioButton *m_rb_dec;
    QLineEdit *m_le_input;
};

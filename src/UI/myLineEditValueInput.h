#pragma once

#include <QWidget>
#include <QRadioButton>
#include <QLineEdit>

#include <data/RLPByteSet.h>

//https://doc.qt.io/qt-5/qtwidgets-widgets-groupbox-example.html
class MyLineEditValueInput : public QWidget
{
    Q_OBJECT

public:
    explicit MyLineEditValueInput(QWidget *parent = nullptr);

    //Value accessors
    inline ByteSet toByteSet(uint64_t size = 0) const { return ByteSet(m_le_input->text().toStdString(), size, m_rb_dec->isChecked() ? 10 : 16); }
    inline const string toStdString() const { return m_le_input->text().toStdString(); }

signals:
    void textChanged(const QString &value);

protected slots:
    void handleHexClicked();
    void handleDecClicked();

private:
    QRadioButton *m_rb_hex;
    QRadioButton *m_rb_dec;
    QLineEdit *m_le_input;
};

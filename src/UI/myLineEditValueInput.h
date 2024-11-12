#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QLineEdit>
#include <QButtonGroup>

#include <data/ByteSet.h>

//https://doc.qt.io/qt-5/qtwidgets-widgets-groupbox-example.html
class MyLineEditValueInput : public QWidget
{
    Q_OBJECT

    typedef std::function<void(const string &)>        FUpdateValueFromString;
    typedef std::function<void(const ByteSet<bool> &)> FUpdateValueFromByteSet;
    typedef std::function<void()>                      FUpdateString;
    typedef std::function<void()>                      FUpdateRegex;

    typedef struct {
        QRadioButton* rb;
        FUpdateValueFromString f_update_val_from_str;
        FUpdateValueFromByteSet f_update_val_from_bs;
        FUpdateString f_update_str;
        FUpdateRegex f_update_regex;
    } RadioButtonFunctions;

public:
    explicit MyLineEditValueInput(QWidget *parent = nullptr, const StrByteSetFormat &default_format = Hex);
    ~MyLineEditValueInput();

    void setTitle(const QString &title) const { m_label->setText(title); }
    
    inline QWidget* getLabel() const { return m_label; }
    const vector<QRadioButton*> getRadioButtons() const;
    inline QWidget* getLineEdit() const { return m_le_input; }

    //inline QHBoxLayout* getLayout() const { return m_hbox; }
    inline QHBoxLayout* getLabelLayout() const { return m_hbox_lbl; }
    inline QHBoxLayout* getRadioButtonsLayout() const { return m_hbox_rb; }
    inline QHBoxLayout* getLineEditLayout() const { return m_hbox_le; }

    ByteSet<bool> getValue() const;

signals:
    void textChanged(const QString &value);

protected slots:
    void handleRadioClicked();
    void handleTextChanged(const QString &value);  // Slot interne pour gérer le changement d'index

protected:
    void newRadioButtons(QWidget *parent, const StrByteSetFormat &default_format);

    template<StrByteSetFormat const & f>
        void updateValueFromString(const string &str);
    template<StrByteSetFormat const & f>
        void updateValueFromByteSet(const ByteSet<bool> &val);
    template<StrByteSetFormat const & f>
        void updateString();
    template<StrByteSetFormat const & f>
        void updateRegex();

private:
    const StrByteSetFormat m_default_format;
    QButtonGroup *m_buttonGroup;
    //QHBoxLayout *m_hbox;
    QHBoxLayout *m_hbox_lbl;
    QHBoxLayout *m_hbox_rb;
    QHBoxLayout *m_hbox_le;
    QLabel *m_label;
    QLineEdit *m_le_input;
    /// Map containing the radioButtons and their specialized template methods for updating the widget
    /// This is done because MyLineEditValueInput cannot be made template, due to the QWidget inheritance limitation
    /// The first int represents the order of appearance (0 = first on the left) of each radio button
    map<int, RadioButtonFunctions> m_rb;
    ByteSet<bool> *m_ptr_value;             //non-aligned bitset allowed
};
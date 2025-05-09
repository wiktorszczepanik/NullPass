#ifndef NULLPASS_H
#define NULLPASS_H

#include <QMainWindow>
#include <string>
#include <array>

QT_BEGIN_NAMESPACE
namespace Ui {
class NullPass;
}
QT_END_NAMESPACE

class NullPass : public QMainWindow {
    Q_OBJECT

public:

    NullPass(QWidget *parent = nullptr);
    ~NullPass();

private slots:
    void on_pushButtonGenerate_clicked();

    void on_pushButtonCopy_clicked();

    void on_pushButtonShow_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButtonSiteCopy_clicked();

    void on_pushButtonLoginCopy_clicked();

    void on_lineEditSecret_textChanged(const QString &arg1);

private:
    Ui::NullPass *ui;
    auto get_passphrase() -> std::string;
    auto get_pass_length() -> int;
    auto get_pass_counter() -> int;
};
#endif // NULLPASS_H

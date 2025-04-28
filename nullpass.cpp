#include "nullpass.h"
#include "ui_nullpass.h"
#include "crypto.h"

#include <string>
#include <array>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <QString>
#include <QMessageBox>
#include <QApplication>
#include <QClipboard>
#include <QTimer>
#include <QDebug>
#include <thread>
#include <chrono>

NullPass::NullPass(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::NullPass) {
    ui->setupUi(this);
    emoji = {"🕶️", "🐧", "🍎", "⚽", "🙂", "🎸", "👣", "🚩", "☢️", "🎁", "💣", "🤡", "🥤", "🌵"};
}

NullPass::~NullPass() {
    delete ui;
}

auto NullPass::create_charset(bool lower, bool upper, bool digits, bool special) -> std::string {
    auto char_set = std::string();
    if (lower) char_set += "abcdefghijklmnopqrstuvwxyz";
    if (upper) char_set += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (digits) char_set += "0123456789";
    if (special) char_set += "!@#$%^&*()-_=+[{]};:'\"|,<.>/?";
    if (char_set.empty())
        throw std::runtime_error("One set of the characters must be selected.");
    return char_set;
}

auto NullPass::get_passphrase() -> std::string {
    auto passphrase = std::string();
    auto site_text = ui -> lineEditSite -> text().toStdString();
    auto login_text = ui -> lineEditLogin -> text().toStdString();
    auto secret_text = ui -> lineEditSecret -> text().toStdString();
    if (secret_text.empty())
        throw std::runtime_error("The secret text field cannot be empty.");
    return passphrase
        .append(site_text)
        .append(login_text)
        .append(secret_text);
}

auto NullPass::get_pass_length() -> int {
    return ui -> spinBoxLength -> value();
}

auto NullPass::get_pass_counter() -> int {
    auto iterations = ui -> spinBoxCounter -> value();
    auto counter = (ui -> spinBoxIterations -> value()) * 10000;
    return iterations + counter;
}

void NullPass::on_pushButtonGenerate_clicked() {
    try {
        auto passphrase = get_passphrase();
        auto char_set = create_charset(
            ui -> checkBoxLowercase -> isChecked(),
            ui -> checkBoxUppercase -> isChecked(),
            ui -> checkBoxDigets -> isChecked(),
            ui -> checkBoxSpecialCharacters -> isChecked()
        );
        auto pass_length = get_pass_length();
        auto pass_counter = get_pass_counter();

        unsigned char key[pass_length];

        crypto::PBKDF2_key(passphrase, pass_counter, pass_length, key);

        auto key_text = std::string();
        for (auto i = 0; i < pass_length; i++)
            key_text += char_set[key[i] % char_set.size()];

        auto qt_key_text = QString::fromStdString(key_text);
        ui -> lineEditOutput -> setText(qt_key_text);
    } catch (const std::exception &exception) {
        QMessageBox::critical(nullptr, "Exception", exception.what());
    }
}

void NullPass::on_pushButtonCopy_clicked() {
    auto password = ui -> lineEditOutput -> text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard -> setText(password);
    auto status = ui -> statusbar;
    status -> showMessage("Password copied for 10s...");
    QTimer::singleShot(10000, [clipboard, status]() {
        clipboard -> setText("");
        status -> showMessage("");
    });
}

void NullPass::on_pushButtonShow_clicked() {
    if (ui -> lineEditOutput -> echoMode() == QLineEdit::Password
        && !(ui -> lineEditOutput -> text().toStdString().empty())) {
        ui -> lineEditOutput -> setEchoMode(QLineEdit::Normal);
        ui -> pushButtonShow -> setText("Hide");
    } else {
        ui -> lineEditOutput -> setEchoMode(QLineEdit::Password);
        ui -> pushButtonShow -> setText("Show");
    }
}

void NullPass::on_pushButtonClear_clicked() {
    ui -> lineEditOutput -> setText("");
}

void NullPass::on_pushButtonSiteCopy_clicked() {
    auto site_text = ui -> lineEditSite -> text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard -> setText(site_text);
    auto status = ui -> statusbar;
    status -> showMessage("Site copied for 10s...");
    QTimer::singleShot(10000, [clipboard, status]() {
        clipboard -> setText("");
        status -> showMessage("");
    });
}

void NullPass::on_pushButtonLoginCopy_clicked() {
    auto login_text = ui -> lineEditLogin -> text();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard -> setText(login_text);
    auto status = ui -> statusbar;
    status -> showMessage("Login copied for 10s...");
    QTimer::singleShot(10000, [clipboard, status]() {
        clipboard -> setText("");
        status -> showMessage("");
    });
}

void NullPass::on_lineEditSecret_textChanged(const QString &arg1) {
    if (!arg1.toStdString().empty()) {
        auto hash = std::hash<std::string>{}(arg1.toStdString());
        auto emoji_len = emoji.size();
        auto emoji_text = QString();
        for (int i = 0; i < 3; i++) {
            auto index = (hash) % emoji_len;
            emoji_text += emoji[index];
            hash = std::hash<std::string>{}(std::to_string(hash));
        }
        ui -> lineEditEmoji -> setText(emoji_text);
    } else ui -> lineEditEmoji -> setText("");
}


/*  Copyright (C) 2014-2018 FastoGT. All right reserved.

    This file is part of FastoNoSQL.

    FastoNoSQL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FastoNoSQL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FastoNoSQL.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "gui/widgets/user_password_widget.h"

#include <QEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <common/macros.h>

#include "translations/global.h"

namespace fastonosql {
namespace gui {

UserPasswordWidget::UserPasswordWidget(const QString& user_title, const QString& password_title, QWidget* parent)
    : QWidget(parent), user_title_(user_title), password_title_(password_title) {
  QVBoxLayout* userPasswordLayout = new QVBoxLayout;
  QHBoxLayout* userLayout = new QHBoxLayout;
  user_name_label_ = new QLabel;
  user_name_textbox_ = new QLineEdit;
  userLayout->addWidget(user_name_label_);
  userLayout->addWidget(user_name_textbox_);
  userPasswordLayout->addLayout(userLayout);

  QHBoxLayout* passwordLayout = new QHBoxLayout;
  password_label_ = new QLabel;
  password_textbox_ = new QLineEdit;
  password_textbox_->setEchoMode(QLineEdit::Password);
  password_echomode_button_ = new QPushButton(translations::trShow);
  VERIFY(connect(password_echomode_button_, &QPushButton::clicked, this, &UserPasswordWidget::togglePasswordEchoMode));
  passwordLayout->addWidget(password_label_);
  passwordLayout->addWidget(password_textbox_);
  passwordLayout->addWidget(password_echomode_button_);
  userPasswordLayout->addLayout(passwordLayout);
  setLayout(userPasswordLayout);

  retranslateUi();
}

QString UserPasswordWidget::userName() const {
  return user_name_textbox_->text();
}

void UserPasswordWidget::setUserName(const QString& user) const {
  user_name_textbox_->setText(user);
}

QString UserPasswordWidget::password() const {
  return password_textbox_->text();
}

void UserPasswordWidget::setPassword(const QString& pass) {
  password_textbox_->setText(pass);
}

bool UserPasswordWidget::isValidCredential() const {
  QString uname = user_name_textbox_->text();
  QString pass = password_textbox_->text();
  return !uname.isEmpty() && !pass.isEmpty();
}

void UserPasswordWidget::togglePasswordEchoMode() {
  bool is_password = password_textbox_->echoMode() == QLineEdit::Password;
  password_textbox_->setEchoMode(is_password ? QLineEdit::Normal : QLineEdit::Password);
  password_echomode_button_->setText(is_password ? translations::trHide : translations::trShow);
}

void UserPasswordWidget::retranslateUi() {
  user_name_label_->setText(user_title_);
  password_label_->setText(password_title_);
}

void UserPasswordWidget::changeEvent(QEvent* ev) {
  if (ev->type() == QEvent::LanguageChange) {
    retranslateUi();
  }

  QWidget::changeEvent(ev);
}

}  // namespace gui
}  // namespace fastonosql

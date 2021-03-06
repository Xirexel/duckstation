#pragma once
#include "core/types.h"
#include <QtWidgets/QPushButton>

class QTimer;

class QtHostInterface;

class InputBindingWidget : public QPushButton
{
  Q_OBJECT

public:
  InputBindingWidget(QtHostInterface* host_interface, QString setting_name, QWidget* parent);
  ~InputBindingWidget();

protected:
  virtual bool eventFilter(QObject* watched, QEvent* event) override;

protected Q_SLOTS:
  void onPressed();
  void onInputListenTimerTimeout();

protected:
  virtual void startListeningForInput();
  virtual void stopListeningForInput();

  bool isListeningForInput() const { return m_input_listen_timer != nullptr; }
  void setNewBinding();

  QtHostInterface* m_host_interface;
  QString m_setting_name;
  QString m_current_binding_value;
  QString m_new_binding_value;
  QTimer* m_input_listen_timer = nullptr;
  u32 m_input_listen_remaining_seconds = 0;
};

class InputButtonBindingWidget : public InputBindingWidget
{
  Q_OBJECT

public:
  InputButtonBindingWidget(QtHostInterface* host_interface, QString setting_name, QWidget* parent);
  ~InputButtonBindingWidget();

protected:
  bool eventFilter(QObject* watched, QEvent* event) override;

private Q_SLOTS:
  void bindToControllerAxis(int controller_index, int axis_index, bool positive);
  void bindToControllerButton(int controller_index, int button_index);

protected:
  void startListeningForInput() override;
  void stopListeningForInput() override;
  void hookControllerInput();
  void unhookControllerInput();
};

class InputAxisBindingWidget : public InputBindingWidget
{
  Q_OBJECT

public:
  InputAxisBindingWidget(QtHostInterface* host_interface, QString setting_name, QWidget* parent);
  ~InputAxisBindingWidget();

private Q_SLOTS:
  void bindToControllerAxis(int controller_index, int axis_index);

protected:
  void startListeningForInput() override;
  void stopListeningForInput() override;
  void hookControllerInput();
  void unhookControllerInput();
};

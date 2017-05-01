#include "messyConsole.hpp"
#include "messyCode2D.hpp"
#include "messyCommandReceiver.hpp"

namespace MessyCode2D_Engine {
    MessyConsole::MessyConsole()
    {
        console = new QWidget();
        console->resize(300, 200);
        lineEdit = new QLineEdit(console);
        lineEdit->installEventFilter(this);
        QObject::connect(lineEdit, SIGNAL(textEdited(QString)),this, SLOT(CommandEdited(QString)));
    }

    MessyConsole::~MessyConsole()
    {
        delete console;
        console = NULL;
    }

    void MessyConsole::Boot()
    {
        console->setWindowTitle(QString("Messy Console"));
        console->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    }

    void MessyConsole::Start()
    {
        console->show();
    }

    void MessyConsole::Update(float elapseTime) { }

    void MessyConsole::AddReceiver(MessyCommandReceiver* receiver)
    {
        receivers.push_back(receiver);
    }

    void MessyConsole::RemoveReceiver(MessyCommandReceiver* receiver)
    {
        this->receivers.erase(std::remove(this->receivers.begin(), this->receivers.end(), receiver), this->receivers.end());
    }

    void MessyConsole::NotifyReceivers()
    {
        for (MessyCommandReceiver* receiver : receivers)
            receiver->ReceiveCommand(lastCommand.toStdString());
    }

    bool MessyConsole::eventFilter(QObject *obj, QEvent *event)
    {
        if (event->type() == QEvent::KeyPress) {
               QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
               if (!keyEvent->text().isEmpty() &&
                  (keyEvent->text() == "\r" || keyEvent->text() == "\n"))
               {
                   NotifyReceivers();
                   return true;
               }
        }
        return false;
    }

    void MessyConsole::CommandEdited(const QString &text)
    {
        lastCommand = text;
    }
}

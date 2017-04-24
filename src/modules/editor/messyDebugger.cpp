#include "messyDebugger.hpp"
#include "messyCode2D.hpp"
#include "messyCommandReceiver.hpp"

namespace MessyCode2D_Engine {
    MessyDebugger::MessyDebugger()
    {
        debugger = new QWidget();
        debugger->resize(300, 200);
        lineEdit = new QLineEdit(debugger);
        lineEdit->installEventFilter(this);
        QObject::connect(lineEdit, SIGNAL(textEdited(QString)),this, SLOT(CommandEdited(QString)));
    }

    MessyDebugger::~MessyDebugger()
    {
        delete debugger;
        delete lineEdit;

        debugger = NULL;
        lineEdit = NULL;
    }

    void MessyDebugger::Boot()
    {
        debugger->setWindowTitle(QString("Debugger"));
        debugger->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    }

    void MessyDebugger::Start()
    {
        debugger->show();
    }

    void MessyDebugger::Update(float elapseTime) { }

    void MessyDebugger::AddReceiver(MessyCommandReceiver* receiver)
    {
        receivers.push_back(receiver);
    }

    void MessyDebugger::RemoveReceiver(MessyCommandReceiver* receiver)
    {
        this->receivers.erase(std::remove(this->receivers.begin(), this->receivers.end(), receiver), this->receivers.end());
    }

    void MessyDebugger::NotifyReceivers()
    {
        for (MessyCommandReceiver* receiver : receivers)
            receiver->ReceiveCommand(lastCommand.toStdString());
    }

    bool MessyDebugger::eventFilter(QObject *obj, QEvent *event)
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

    void MessyDebugger::CommandEdited(const QString &text)
    {
        lastCommand = text;
    }
}

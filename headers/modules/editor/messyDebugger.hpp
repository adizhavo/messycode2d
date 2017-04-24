#ifndef MESSYDEBUGGER_H
#define MESSYDEBUGGER_H

#include "messyModule.hpp"
#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <string>
#include <vector>

namespace MessyCode2D_Engine {
    // Debugger GUI, input handler and logs

    class MessyCommandReceiver;

    class MessyDebugger : public QObject, public MessyModule
    {
        Q_OBJECT

    public:
        MessyDebugger();
        ~MessyDebugger();

        void Boot();
        void Start();
        void Update(float elapseTime);
        void AddReceiver(MessyCommandReceiver* receiver);
        void RemoveReceiver(MessyCommandReceiver* receiver);

    private:
        QWidget* debugger;
        std::vector<MessyCommandReceiver*> receivers;
        QLineEdit* lineEdit;
        QString lastCommand;

        void NotifyReceivers();

    protected:
        bool eventFilter(QObject *obj, QEvent *event);

    public slots:
        void CommandEdited(const QString & text);
    };
}

#endif // MESSYDEBUGGER_H

#ifndef MESSYDEBUGGER_H
#define MESSYDEBUGGER_H

#include "messyModule.hpp"
#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <string>
#include <vector>

namespace MessyCode2D_Engine {
    // Console GUI, input handler and logs

    class MessyCommandReceiver;

    class MessyConsole : public QObject, public MessyModule
    {
        Q_OBJECT

    public:
        MessyConsole();
        ~MessyConsole();

        void Boot();
        void Start();
        void Update(float elapseTime);
        void AddReceiver(MessyCommandReceiver* receiver);
        void RemoveReceiver(MessyCommandReceiver* receiver);

    private:
        QWidget* console;
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

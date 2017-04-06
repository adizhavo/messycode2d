#include "headers/messyCode2D.hpp"
#include "headers/scene.hpp"
#include "headers/messyCode2DEditor.hpp"
#include "headers/messyCode2DConfig.hpp"
#include <QApplication>
#include <QTreeWidget>

using namespace MessyCode2D_Engine;

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);

    MessyCodeConfig config;
    
    Scene scene;
    scene.Build();
    
    MessyCode2DEditor editor;
    
    MessyCode2D* engine = new MessyCode2D(&config, &scene, &editor);
    
    engine->Start();
    engine->Loop();
    
    // Create sample tree, will be used to render the hierarchy
    QTreeWidget *treeWidget = new QTreeWidget();
        treeWidget->setColumnCount(1);
        QList<QTreeWidgetItem *> items;
        for (int i = 0; i < 10; ++i)
        {
            items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
            items.at(i)->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
        }
        treeWidget->insertTopLevelItems(0, items);
        treeWidget->show();

        return a.exec();
}

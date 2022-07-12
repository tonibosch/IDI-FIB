#include <QLineEdit>

class MyQLineEdit: public QLineEdit
{
    Q_OBJECT
    
public:
    
    MyQLineEdit(QWidget *parent);
    
public slots:
    void tractaReturn();
    
signals:
    void returnPressed(const QString &);
    
};

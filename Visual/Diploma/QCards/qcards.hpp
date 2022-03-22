#ifndef QCARDS_H
#define QCARDS_H

#include <QWidget>
#include <QPushButton>

//
#include <stdio.h>
//

enum { //obosnovano dlja igroka tolko
    QCARDS_CTRL_ADD,
    QCARDS_CTRL_REM,
    QCARDS_CTRL_SADD,
    QCARDS_CTRL_OPEN,
    QCARDS_CTRL_POS,
    QCARDS_CTRL_VERTICAL,
    QCARDS_CTRL_CONTROL,
    QCARDS_CTRL_ENABLED
};

struct CardsItem {
    int cardid;
    QPushButton *button;
    CardsItem *next;
};

struct CardsProblem {
    int cmd;
    int size;
    int *cards;
    CardsProblem *next;
};

class QCards : public QWidget
{
    Q_OBJECT
public:
    explicit QCards(QWidget *parent = 0);
    ~QCards(void);
    void setX(int X);
    void setY(int Y);
    void clearCards(void);
    void repaintCards(void);
    void addCards(int *cards, int number);
    void addSecretCards(int number);
    void delCards(int *cards, int number);
    void delSecretCards(int number);
    void openCards(int *cards, int number);
    void whichHidden(int *cards, int &number);
    void setVertical(bool mode);
    int countCards(void);
    void getCards(int *cards);
    int countSelectCards();
    void getSelectCards(int *cards);
    void setControl(bool mode);
    void LaterRun(int cmd, int size, int *cards);
    void ReleaseProblems(void);
    void Change(void);
    bool isChange(void);
    static void initCollectObj(QWidget *block);
    static void releaseCollectObj(void);

private:
    CardsItem *root;
    CardsProblem *problems, *prevprob;
    bool ischange;
    int x, y;
    static int w, h;
    int step, count;
    bool isvertical, iscontrol;
    void clearCards(CardsItem *p);
    void sortArray(int *cards, int number);
    static QPushButton **collectObj;
    
signals:
    
public slots:
    void checkCards();
};

#endif // QCARDS_H

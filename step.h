#ifndef ACTION_H
#define ACTION_H

#include <QString>
#include "ingredients.h"
class Step
{
public:
    Step();
    void setInstruction(QString inst);
    void setItem(Ingredients::Ingredients itm);
    void setAmount(double amt);
    QString getInstruction();
    Ingredients::Ingredients getItem();
    double getAmount();
private:
    QString instruction;
    Ingredients::Ingredients item;
    double amount;
};

#endif // ACTION_H

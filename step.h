#ifndef ACTION_H
#define ACTION_H

#include <QString>
#include "ingredients.h"
class Step
{
public:
    Step();
    Step(QString inst, Ingredients::Ingredients ingred, double amt);
    void setInstruction(QString inst) ;
    void setItem(Ingredients::Ingredients itm) ;
    void setAmount(double amt);
    QString getInstruction() const;
    Ingredients::Ingredients getItem() const;
    double getAmount() const;
private:
    QString instruction;
    Ingredients::Ingredients item;
    double amount;
};

#endif // ACTION_H

#include "step.h"

Step::Step()
{

}

Step::Step(QString inst, Ingredients::Ingredients ingred, double amt){
    instruction=inst;
    item=ingred;
    amount=amt;
}

void Step::setInstruction(QString inst){
    instruction=inst;
}

void Step::setItem(Ingredients::Ingredients itm){
    item=itm;
}

void Step::setAmount(double amt){
    amount=amt;
}

QString Step::getInstruction() const{
    return instruction;
}

Ingredients::Ingredients Step::getItem() const{
    return item;
}

double Step::getAmount() const{
    return amount;
}

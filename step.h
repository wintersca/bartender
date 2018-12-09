#include <QString>
#include "ingredients.h"

#ifndef ACTION_H
#define ACTION_H

/**
 * @brief The Step class
 * Encapsulates instruction details for a drink.
 */
class Step
{

public:
    /**
     * @brief Step
     */
    Step();

    /**
     * @brief Step: constructs a step that holds an instruction, ingredient, and amount.
     * @param inst: instruction to hold
     * @param ingred: ingredient to hold
     * @param amt: amount to hold
     */
    Step(QString inst, Ingredients::Ingredients ingred, double amt);

    /**
     * @brief setInstruction: sets the instruction string
     * @param inst: string for instruction
     */
    void setInstruction(QString inst) ;

    /**
     * @brief setItem: sets the ingredient
     * @param itm: ingredient to set
     */
    void setItem(Ingredients::Ingredients itm) ;

    /**
     * @brief setAmount: sets the amount
     * @param amt: amount to set
     */
    void setAmount(double amt);

    /**
     * @brief getInstruction: returns the instruction
     * @return
     */
    QString getInstruction() const;

    /**
     * @brief getItem: returns the item
     * @return
     */
    Ingredients::Ingredients getItem() const;

    /**
     * @brief getAmount: returns the amount
     * @return
     */
    double getAmount() const;

private:
    QString instruction;
    Ingredients::Ingredients item;
    double amount;
};

#endif // ACTION_H

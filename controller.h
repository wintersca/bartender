#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include <QtMath>
#include <QDebug>
#include "drink.h"
#include "ingredients.h"
#include "ingredientsprite.h"
#include "qsfmlcanvas.h"
#include "xmldrinkparser.h"
#include "recordtracker.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(XMLDrinkParser *parser, QObject *parent = nullptr);
public slots:

    /* timerUpdate()
     *
     * updates the in-game timer and mood sprite every second
     * If the time has exceed the time alloted to make the drink, decreases the
     * customers current mood every starting mood seconds. If the customers mood
     * drops to 0 the mood is no longer decreased, but the timer continues to run
     * until the user ends the roudn by serving the drink.
     */
    void timerUpdate();

    /* startRound()
     *
     * Calls newCustomer and sets up values for the round:
     * drinkComplexity: the number of steps in the selected recipe, it is used to
     * calculate the time allowed to complete the drink as well as the tip earned
     * at the end of a round
     * Sends the selected drink and mood to the game and allows the user to serve a drink.
     * If the user has selected the easy difficulty, they are given unlimited time.
     */
    void startRound();

    /* updateRecipes(Drink*)
     *
     * Receives a drink object created by the user and calls the xml parser to add
     * the drink to the database. Also, appends the new drink to the main and user
     * specified menus
     */
    void updateRecipes(Drink* newRecipe);

    /*checkIngredient(Ingredients::Ingredients)
     *
     * Checks the user added ingredient and amount against the recipe for the currently
     * selected drink and assigns points/penalties. Actions (eg stir) are handled separately
     * as they have no amount value. Points are assigned according to the following rules:
     * If the ingredient has not been added to the drink:
     *  correct ingredient, step, and amount = 3 points
     *  correct ingredient and step, but wrong amount = 2 points
     *  correct ingredient, but wrong step and amount = 1 point
     *  ingredient that the drink does not contain = -3 points
     * If the added ingredient has already been added to the drink:
     *  ingredient in the recipe and this addition corrects the amount = 1 point
     *  otherwise adding a previously added ingredient = -3 points
     */
    void checkIngredient(Ingredients::Ingredients ingredient);

    /* menuRequestByGameArea()
     *
     * send the entire menu (not only userspecified) to gameArea
     */
    void menuRequestByGameArea();

    /* menuRequestedByMainWindow()
     *
     * send the entire menu (not only userspecified) to mainWindow in the
     * receiveMenu slot
     */
    void menuRequestedByMainWindow();

    /* menuInfoRequestedByMainWindow()
     *
     * send the entire menu (not only userspecified) to mainWindow in the
     * receiveMenuInfo slot
     */
    void menuInfoRequestedByMainWindow();

    /* receiveUserSpecifiedMenu(QVector<Drink*> newMenu)
     *
     * After the user has selected/deselected drinks in the UI, receive the
     * vector containing all drinks and remove/add drinks to the user specified
     * menu for use in selecting drinks in future rounds
     */
    void receiveUserSpecifiedMenu(QVector<Drink*> newMenu);

    /* startGame(unsigned int difficultyInit)
     *
     * intializes the difficutly variable, clears any ingredients added to the
     * glass before the game started, and calls the startRound function
     */
    void startGame(unsigned int difficulty);

    /* receiveAmountToAdd(double amount)
     *
     * intializes the ingredient amount variable with the user specifed amount
     */
    void receiveAmountToAdd(double amount);

    /* drinkServed()
     *
     * calls the endRound() for the current round, clears the contents of the
     * current drink from the glass and starts a new round after 1 second
     */
    void drinkServed();

    /* recordsRequestedByMainWindow()
     *
     * sends the historical score data to mainWindow as a QMap<QString, int>
     */
    void recordsRequestedByMainWindow();

signals:

    /* moodToGameArea(int happinessLevel)
     *
     * sends the currentHappiness variable to the receiveMood slot in gameArea
     * for sprite selection
     */
    void moodToGameArea(int happinessLevel);

    /* clearDrink()
     *
     * informs gameArea to remove ingredients from the glass via the drinkServed slot
     */
    void clearDrink();

    /* menuToMainWindow(QVector<Drink*> menu)
     *
     * sends the menu to the receiveMenu slot in mainWindow
     */
    void menuToMainWindow(QVector<Drink*> menu);

    /*  menuInfoToMainWindow(QVector<Drink*> menu)
     *
     * sends the menu to the receiveMenuInfo slot in mainWindow
     */
    void menuInfoToMainWindow(QVector<Drink*> menu);

    /* recordsToMainWindow(QMap<QString, int>)
     *
     * sends historical score data to the receiveRecords slot in MainWindow
     */
    void recordsToMainWindow(QMap<QString, int>);

    /* sendDrink(Drink* drink)
     *
     * sends a reference to the round selected drink object to the receiveDrink
     * slot in mainWindow
     */
    void sendDrink(Drink* drink);

    /* sendTime(int currentTime)
     *
     * sends the updated timer to the receiveTime slot in mainWindow
     */
    void sendTime(int currentTime);

    /* tipAmountToGame(int tipDollars, int tipCents)
     *
     * sends total dollars and cents for this game session as ints to the
     * receiveTips slot in mainWindow
     */
    void tipAmountToGame(int tipDollars, int tipCents);

    /* requestAmountToAdd()
     *
     * sends a request for the amount of an ingredient that has been added to the
     * drink glass in gameArea to the requestAmountToAdd slot in mainWindow
     */
    void requestAmountToAdd();

    /* enableServe()
     *
     * sends a request to the enableServe slot of mainWindow to set the status of the
     * serve drink button to enabled(true)
     */
    void enableServe();

private:

    /* calculateTip(int &dollars, int &cents)
     *
     * Receives references to the totalTip dollars and cents variables that are appropriate
     * to the user selected difficulty as parameters. The tip for the round is calcualted by
     * the following equation (drinkPoints * 10 * moodValueModifier) where drink points are the
     * points earned by adding correct ingredients and the moodValueModifier is
     * currentHappiness/5 where 5 is the maximum displayed customer mood.
     *
     * currentHappines can exceed 5 due to excellent service time and drink correctness or drop below
     * zero due to served drink incorrectness
     * Tips are not calculated for customers whose currentHappiness is <= 0
     */
    void calculateTip(int dollars, int cents); //when drink is served

    /* endRound()
     *
     * stops the round timer and calls endOfRoundHappinessBonus() to determine the
     * currentHappiness score for the customer based on quality and timeliness of drink
     * service. The calculates the tip and stores the following information in the historical
     * score document:
     *  total tip dollars and cents
     *  number of satisfied customers
     *  number of dissatisfied customers
     *  numer of drinks served
     * After the score information has been stored, standardizes the happiness of the customer
     * to be between 0 and 5 so that mood can be displayed by the UI
     */
    void endRound();

    /* getAllRecipes()
     *
     * calls the XML database parser for a vector of Drink pointers to be used as the
     * menu for the game
     */
    QVector<Drink*> getAllRecipes();

    /* newCustomer(unsigned int difficulty)
     *
     * Randomizes the starting currentHappiness value based on difficulty level as per below:
     * easy: 3, 4, 5
     * medium: 2, 3, 4
     * hard: 2, 3
     * calls selectRandomDrink() to get a recipe from the user specified menu
     * generates the moodValuModifier as currentHappiness/5 where 5 is the maximum starting
     * happiness
     * sets up the added ingredients vector and step count for a new round
     */
    void newCustomer(unsigned int difficulty);

    /* selectNewRandomDrink()
     *
     * Randomly selects a recipe from the user specified menu and returns a pointer to
     * the drink object.
     */
    Drink* selectNewRandomDrink();

    /* handleActionIngredients(QVector<Step> steps, Step current, Ingredients::Ingredients ingredient)
     *
     * because action ingredients do not have an amount, they are handled by this helper method
     * instead of in checkAddedIngredients()
     * Actions are granted points based on the following rules:
     *  action taken on the correct step = 3 points
     *  action in recipe, but wrong order = 1 point
     *  action not in recipe or action has already been taken = -3 points
     */
    void handleActionIngredients(QVector<Step> steps, Step current, Ingredients::Ingredients ingredient);

    /* endOfRoundHappinessBonus()
     *
     * Allows the user to gain extra tips through timely and accurate drink service according
     * to the following rules:
     *
     * when drinkPoints <= 0: happiness = 0
     * otherwise happiness =  (5 * drinkPoints) / (drinkComplexity * 3)) - 2
     * This equation is derived from the following
     * max drinkPoints = 3 times drinkComplexity (3 for each step in the recipe)
     * percent correct = 100 x drinkPoints / max drink points
     * divide by 20 to get a number from 0 to 5 (100 becomes 5)
     * subtract 2 so that tips dont get higher than the price of a drink
     *
     * apply the new mood to moodValueModifier
     */
    void endOfRoundHappinessBonus();

    /* standardizeHappiness()
     *
     * The moods that can be displayed by the UI canonly be in the range of 0 to 5 while
     * the moods of customers in the controller can be higher or lower for score calculation
     * after score has been tabluated, return currentHappiness to the displayable range
     */
    void standardizeHappiness();

    /* containsIngredient(Ingredients::Ingredients ingredient, QVector<Step> steps)
     *
     * Helper method for checkIngredient() which scans a recipe to determine if an
     * ingredient is contained therin.
     */
    bool containsIngredient(Ingredients::Ingredients ingredient, QVector<Step> steps);

    /* outOfOrderAmount(Ingredients::Ingredients ingredient, QVector<Step> steps, double amount)
     *
     * Helper method for checkIngredient() which checks if the amount of ingredient added to the
     * glass when the ingredients are not added in order, matches the amount of the ingredient that
     * is supposed to be added according to the recipe
     */
    bool outOfOrderAmount(Ingredients::Ingredients ingredient, QVector<Step> steps, double amount);

    // class variables
    Drink* currentDrink;
    int currentHappiness;
    int standardizedHappiness;
    int stepCount;
    int easyTotalTipDollars;
    int medTotalTipDollars;
    int hardTotalTipDollars;
    int easyTotalTipCents;
    int medTotalTipCents;
    int hardTotalTipCents;
    int easyTotalCustomersSatisfied;
    int medTotalCustomersSatisfied;
    int hardTotalCustomersSatisfied;
    int easyTotalCustomersDissatisfied;
    int medTotalCustomersDissatisfied;
    int hardTotalCustomersDissatisfied;
    int easyTotalDrinksServed;
    int medTotalDrinksServed;
    int hardTotalDrinksServed;
    int timeToCompleteDrink;
    int drinkComplexity;
    int drinkPoints;
    unsigned int difficulty;
    double moodValueModifier;
    double ingredientAmount;
    QVector<Drink*> menu;
    QVector<Drink*> userSpecifiedMenu;
    QMap<Ingredients::Ingredients,double> addedIngredients;
    XMLDrinkParser *parser;
    QTimer *timer;
};

#endif // CONTROLLER_H

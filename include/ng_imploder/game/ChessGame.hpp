#ifndef _CHESSGAME_HPP
#define _CHESSGAME_HPP

#include <iostream>
#include <extras/interfaces.hpp>

/**
 * @brief ChessGameInterface
 *
 */
interface ChessGameInterface
{

    /**
     * @brief moves()
     * @return all the chess moves of the given chess game
     */
    virtual void moves() const pure;

};

/**
 * @brief ChessGame
 *
 */
concrete class ChessGame implements ChessGameInterface
{

    /**
     * @brief moves()
     * @return all the chess moves of the given chess game
     */
    virtual void moves() const override;

};

/**
 * @brief EndOfGameReachedException
 *
 */

concrete class EndOfGameReachedException
extends extras::AbstractCustomException {
public:
    EndOfGameReachedException(
        const std::string& msg,
        const extras::WhereAmI& whereAmI)
        : AbstractCustomException(msg.c_str(),
            whereAmI._file.c_str(),
            whereAmI._func.c_str(), whereAmI._line) {}
    static void assertion(
        int sizePGN, int sizeFEN,
        const std::string& msg,
        const extras::WhereAmI& ref);
};


#endif // _CHESSGAME_HPP

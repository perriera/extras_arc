
#include <iostream>
#include "cpp_starter/game/ChessGame.hpp"

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ChessGameInterface: toOctal", "[CHES-9]") {

    Mock<ChessGameInterface> mock;
    When(Method(mock, moves)).Return();

    ChessGameInterface& i = mock.get();
    i.moves();
    Verify(Method(mock, moves));
}
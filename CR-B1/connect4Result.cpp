#include <optional>
#include <iostream>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

using Line = vector<char>;
using Board = vector<Line>;
using Lines = vector<Line>;

using Coordinate = pair<int, int>;

// CODE
template<typename DestinationType>
auto transformAll = [](const auto& source, auto fn){
    DestinationType result;
    result.reserve(source.size());
    transform(source.begin(), source.end(), back_inserter(result), fn);
    return result;
};

auto toRange = [](const auto& collection){
    vector<int> range(collection.size());
    iota(begin(range), end(range), 0);
    return range;
};

auto accessAtCoordinates = [](const auto& board, const Coordinate& coordinate){
    return board[coordinate.first][coordinate.second];
};

auto projectCoordinates = [](const auto& board, const auto& coordinates){
    const auto boardElementFromCoordinates = bind(accessAtCoordinates, board, _1);
    return transformAll<Line>(coordinates, boardElementFromCoordinates);
};

#pragma region LINES
auto lineCoordinates = [](const auto& board, const auto& lineIndex){
    const auto range = toRange(board[0]); 
    return transformAll<vector<Coordinate>>(range, [lineIndex](const auto& columnIndex){
        return make_pair(lineIndex, columnIndex); 
    });
};

auto line = [](const auto& board, const int lineIndex){
    return projectCoordinates(board, lineCoordinates(board, lineIndex));
};
#pragma endregion

#pragma region COLUMNS
auto columnCoordinates = [](const auto& board, const auto& columnIndex){
    const auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [columnIndex](const auto& index){return make_pair(index, columnIndex);});
};

auto column = [](const auto& board, const auto& columnIndex){
    return projectCoordinates(board, columnCoordinates(board, columnIndex));
};
#pragma endregion

#pragma region DIAGONALS
auto fwdDiagonalCoordinates = [](const auto& board, const Coordinate& startCoordinates){
    vector<Coordinate> diagonalCoordinates;
    int x = startCoordinates.first;
    int y = startCoordinates.second;

    while (x < board.size() && y < board[0].size()) 
    {
        diagonalCoordinates.emplace_back(x, y);

        x++;
        y++;
    }

    return diagonalCoordinates;
};

auto backDiagonalCoordinates = [](const auto& board, const Coordinate& startCoordinates){
    vector<Coordinate> diagonalCoordinates;
    int x = startCoordinates.first;
    int y = startCoordinates.second;

    while (x < board.size() && y >= 0) 
    {
        diagonalCoordinates.emplace_back(x, y);
        x++;
        y--;
    }

    return diagonalCoordinates;
};

auto fwdDiagonal = [](const auto& board, const Coordinate& startCoordinates){
    return projectCoordinates(board, fwdDiagonalCoordinates(board, startCoordinates));
};

auto backDiagonal = [](const auto& board, const Coordinate& startCoordinates){
    return projectCoordinates(board, backDiagonalCoordinates(board, startCoordinates));
};
#pragma endregion

#pragma region LINES AND COLUMNS
auto concatenate = [](const auto& first, const auto& second){
    auto result{first};
    result.insert(result.end(), make_move_iterator(second.begin()), make_move_iterator(second.end()));
    return result;
};

// auto concatenate3 = [](const auto& first, const auto& second, const auto& third){
//     return concatenate(concatenate(first, second), third);
// };

auto allLines = [](const auto& board) {
    const auto range = toRange(board);
    return transformAll<Lines>(range, [board](auto index) { return line(board, index);});
};

auto allColumns = [](const auto& board) {
    const auto range = toRange(board);
    return transformAll<Lines>(range, [board](auto index) { return column(board, index);});
};

// auto allDiagonals = [](const auto& board) -> Lines {
//     return {fwdDiagonal(board), backDiagonal(board)};
// };

auto allLinesAndColumns = [](const auto& board) {
    return concatenate(allLines(board), allColumns(board));
};
#pragma endregion

#pragma region LINE TO STRING CONVERSION
auto accumulateAll = [](const auto source, auto fn){
    return accumulate(source.begin(), source.end(), typename decltype(source)::value_type(), fn);
};

auto lineToString = [](const auto& line){
    return transformAll<string>(line, [](auto const token) -> char { return token;});
};

auto boardToLinesString = [](const auto& board){
    return transformAll<vector<string>>(board, lineToString);
};

auto boardToString = [](const auto& board){
    const auto linesAsString = boardToLinesString(board);
    return accumulateAll(linesAsString, 
            [](string current, string lineAsString) { return current + lineAsString + "\n"; }
            );
};
#pragma endregion

#pragma region FOUR IN A ROW
auto fourInARow = [](const auto& line, const auto& tokenToCheck) -> bool {
    string l = lineToString(line);
    string target(4, tokenToCheck);

    return l.find(target) != string::npos;
};

auto fourXInARow = bind(fourInARow, _1, 'X'); 
auto fourOInARow = bind(fourInARow, _1, 'O');
#pragma endregion

#pragma region GAME
auto all_of_collection = [](const auto& collection, auto fn){
    return all_of(collection.begin(), collection.end(), fn);
};

auto any_of_collection = [](const auto& collection, auto fn){
    return any_of(collection.begin(), collection.end(), fn);
};

template <typename CollectionBooleanOperation, typename CollectionProvider, typename Predicate>
auto booleanOperationOnProvidedCollection(CollectionBooleanOperation collectionBooleanOperation, CollectionProvider collectionProvider, Predicate predicate){
  return [=](auto collectionProviderSeed, auto predicateFirstParameter){
      return collectionBooleanOperation(collectionProvider(collectionProviderSeed), 
              bind(predicate, _1, predicateFirstParameter));
  };
}

auto tokenWins = booleanOperationOnProvidedCollection(any_of_collection, allLinesAndColumns, fourInARow);
auto xWins = bind(tokenWins, _1, 'X');
auto oWins = bind(tokenWins, _1, 'O');

auto isNotEmpty= [](const auto& token){return token != ' ';};

auto fullLine = bind(all_of_collection, _1, isNotEmpty);

auto full = [](const auto& board){
    return all_of_collection(board, fullLine);
};

auto draw = [](const auto& board){
    return full(board) && !xWins(board) && !oWins(board); 
};
#pragma endregion

auto CheckValidTokenDiff = [](auto const board, const char redToken, const char yellowToken)
{
    int redCount = std::accumulate(board.begin(), board.end(), 0, 
        [redToken](int count, const Line& row) {
            return count + std::count(row.begin(), row.end(), redToken);
        });
    
    int yellowCount = std::accumulate(board.begin(), board.end(), 0, 
        [yellowToken](int count, const Line& row) {
            return count + std::count(row.begin(), row.end(), yellowToken);
        });

    return (redCount - yellowCount <= 1 && yellowCount - redCount <= 1);
};

auto CheckValidTokens = [](auto const board, const vector<char>& validTokens)
{
    return all_of(board.begin(), board.end(), [&validTokens](const Line& line) {
        return all_of(line.begin(), line.end(), [&validTokens](char token) {
            return find(validTokens.begin(), validTokens.end(), token) != validTokens.end();
        });
    });
};

auto CheckBoardDimensions = [](auto const board, int expectedRow, int expectedCol)
{
    return (board[0].size() == expectedRow && board.size() == expectedCol) ? true : false;
};

// TESTS
#pragma region REF TESTS
TEST_CASE("lines")
{
    Board board {
        {'X', ' ', ' ', 'X', ' ', ' ', 'X'},
        {' ', 'X', ' ', ' ', 'X', ' ', ' '},
        {' ', ' ', 'X', ' ', ' ', 'X', ' '},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', 'O', ' ', ' ', ' ', ' '},
    };

    Line expectedLine0{'X', ' ', ' ', 'X', ' ', ' ', 'X'};
    CHECK_EQ(expectedLine0, line(board, 0));

    Line expectedLine1{' ', 'X', ' ', ' ', 'X', ' ', ' '};
    CHECK_EQ(expectedLine1, line(board, 1));

    Line expectedLine2{' ', ' ', 'X', ' ', ' ', 'X', ' '};
    CHECK_EQ(expectedLine2, line(board, 2));

    Line expectedLine3{'O', 'O', 'O', 'O', 'O', 'O', 'O'};
    CHECK_EQ(expectedLine3, line(board, 3));

    Line expectedLine4{'O', 'O', ' ', ' ', ' ', ' ', ' '};
    CHECK_EQ(expectedLine4, line(board, 4));

    Line expectedLine5{' ', ' ', 'O', ' ', ' ', ' ', ' '};
    CHECK_EQ(expectedLine5, line(board, 5));

}

TEST_CASE("all columns")
{
    Board board {
        {'X', ' ', ' ', 'X', ' ', ' ', 'X'},
        {' ', 'X', ' ', ' ', 'X', ' ', ' '},
        {' ', ' ', 'X', ' ', ' ', 'X', ' '},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };

    Line expectedColumn0{'X', ' ', ' ', 'O', 'O', ' '};
    CHECK_EQ(expectedColumn0, column(board, 0));
    Line expectedColumn1{' ', 'X', ' ', 'O', 'O', ' '};
    CHECK_EQ(expectedColumn1, column(board, 1));
    Line expectedColumn2{' ', ' ', 'X', 'O', ' ', ' '};
    CHECK_EQ(expectedColumn2, column(board, 2));
    Line expectedColumn3{'X', ' ', ' ', 'O', ' ', ' '};
    CHECK_EQ(expectedColumn3, column(board, 3));
    Line expectedColumn4{' ', 'X', ' ', 'O', ' ', ' '};
    CHECK_EQ(expectedColumn4, column(board, 4));
    Line expectedColumn5{' ', ' ', 'X', 'O', ' ', ' '};
    CHECK_EQ(expectedColumn5, column(board, 5));
    Line expectedColumn6{'X', ' ', ' ', 'O', ' ', ' '};
    CHECK_EQ(expectedColumn6, column(board, 6));
}

TEST_CASE("fwd diagonal")
{
    Board board {
        {'X', ' ', ' ', 'X', ' ', ' ', 'X'},
        {' ', 'X', ' ', ' ', 'X', ' ', ' '},
        {' ', ' ', 'X', ' ', ' ', 'X', ' '},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };

    Line expectedDiagonal00{'X', 'X', 'X', 'O', ' ', ' '};
    CHECK_EQ(expectedDiagonal00, fwdDiagonal(board, {0, 0}));

    Line expectedDiagonal01{' ', ' ', ' ', 'O', ' ', ' '};
    CHECK_EQ(expectedDiagonal01, fwdDiagonal(board, {0, 1}));
}

TEST_CASE("back diagonal")
{
    Board board {
        {'X', ' ', ' ', 'X', ' ', ' ', 'X'},
        {' ', 'X', ' ', ' ', 'X', ' ', ' '},
        {' ', ' ', 'X', ' ', ' ', 'X', ' '},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };

    Line expectedDiagonal06{'X', ' ', ' ', 'O', ' ', ' '};
    CHECK_EQ(expectedDiagonal06, backDiagonal(board, {0, 6}));

    Line expectedDiagonal05{' ', 'X', ' ', 'O', 'O', ' '};
    CHECK_EQ(expectedDiagonal05, backDiagonal(board, {0, 5}));
}

TEST_CASE("all lines and columns")
{
    Board board {
        {'X', ' ', ' ', 'X', ' ', ' ', 'X'},
        {' ', 'X', ' ', ' ', 'X', ' ', ' '},
        {' ', ' ', 'X', ' ', ' ', 'X', ' '},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };

    Lines expected{
        {'X', ' ', ' ', 'X', ' ', ' ', 'X'},
        {' ', 'X', ' ', ' ', 'X', ' ', ' '},
        {' ', ' ', 'X', ' ', ' ', 'X', ' '},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'X', ' ', ' ', 'O', 'O', ' '},
        {' ', 'X', ' ', 'O', 'O', ' '},
        {' ', ' ', 'X', 'O', ' ', ' '},
        {'X', ' ', ' ', 'O', ' ', ' '},
        {' ', 'X', ' ', 'O', ' ', ' '},
        {' ', ' ', 'X', 'O', ' ', ' '},
    };

    auto all = allLinesAndColumns(board);

    CHECK_EQ(expected, all);
}

TEST_CASE("line to string")
{
    Line line{
        ' ', 'X', 'O', ' ', 'X', 'O', ' '
    };

    CHECK_EQ(" XO XO ", lineToString(line));
}

TEST_CASE("board to lines string")
{
    Board board{
        {'X', 'X', 'X', 'X', 'X', 'X', 'O'},
        {' ', 'O', ' ', ' ', 'O', ' ', 'O'},
        {' ', ' ', 'O', ' ', 'O', ' ', 'O'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'O'},
        {' ', 'O', ' ', ' ', 'O', ' ', 'O'},
        {' ', ' ', 'O', ' ', 'O', ' ', 'X'},
    };
    vector<string> expected{
        "XXXXXXO",
        " O  O O",
        "  O O O",
        "XXXXXXO",
        " O  O O",
        "  O O X",
    };

    CHECK_EQ(expected, boardToLinesString(board));
}

TEST_CASE("board to string"){
    Board board {
        {'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
    };

    string expected{"XXXXXXX\nXXXXXXX\nXXXXXXX\nOOOOOOO\nOOOOOOO\nOOOOOOO\n"};

    CHECK_EQ(expected, boardToString(board));
}

TEST_CASE("Four X in a row"){
    Line line{'O', ' ', 'X', 'X', 'X', 'X', 'O'};

    CHECK(fourXInARow(line));
}

TEST_CASE("Line not filled with X"){
    CHECK(!fourXInARow(Line({'X', 'O', 'X', 'X', 'O', 'X', 'O'})));
    CHECK(!fourXInARow(Line({'X', ' ', 'X', 'X', 'X', ' ', ' '})));
}

TEST_CASE("Four O in a row"){
    Line line{'O', 'O', 'O', 'O', 'X', 'X', 'O'};

    CHECK(fourOInARow(line));
}

TEST_CASE("Line not filled with O"){
    CHECK(!fourOInARow(Line({'X', 'O', 'X', 'X', 'O', 'X', 'O'})));
    CHECK(!fourOInARow(Line({'X', ' ', 'X', 'X', 'X', ' ', ' '})));
}

TEST_CASE("X wins"){
    Board board{
        {' ', 'X', 'X', 'X', 'X', ' ', ' '},
        {' ', ' ', 'O', 'O', 'O', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    CHECK(xWins(board));
}

TEST_CASE("O wins"){
    Board board{
        {' ', 'X', 'X', 'X', ' ', ' ', ' '},
        {' ', ' ', 'O', 'O', 'O', 'O', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

    CHECK(oWins(board));
}

TEST_CASE("draw"){
    Board board{
        {'X', 'O', 'O', 'X', 'O', 'O', 'X'},
        {'O', 'X', 'O', 'O', 'O', 'X', 'O'},
        {'X', 'X', 'O', 'X', 'O', 'X', 'X'},
        {'O', 'X', 'X', 'O', 'X', 'X', 'O'},
        {'X', 'O', 'X', 'X', 'X', 'O', 'X'},
        {'O', 'X', 'O', 'O', 'O', 'X', 'O'}
    };

    CHECK(draw(board));
}
#pragma endregion

TEST_CASE("Difference in number of tokens > 1")
{
    Board board {
        {'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };

    CHECK_FALSE(CheckValidTokenDiff(board, 'X', 'O'));
}

TEST_CASE("Difference in number of tokens < 1")
{
    Board board {
        {'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };

    CHECK(CheckValidTokenDiff(board, 'X', 'O'));
}

TEST_CASE("Correct tokens")
{
    Board board {
        {'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };

    CHECK(CheckValidTokens(board, {'X', 'O', ' '}));
}

TEST_CASE("Wrong tokens")
{
    Board board {
        {'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'-', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };

    CHECK_FALSE(CheckValidTokens(board, {'X', 'O', ' '}));
}

TEST_CASE("Board dimension wrong")
{
    Board board {
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };

    CHECK_FALSE(CheckBoardDimensions(board, 7, 6));
}

TEST_CASE("Board dimension correct")
{
    Board board {
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    };

    CHECK(CheckBoardDimensions(board, 7, 6));
}
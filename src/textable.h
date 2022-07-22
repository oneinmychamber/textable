/**********************************************************************************
*  MIT License                                                                    *
*                                                                                 *
*  Copyright (c) 2018 Vahan Aghajanyan <vahancho@gmail.com>                       *
*                                                                                 *
*  Permission is hereby granted, free of charge, to any person obtaining a copy   *
*  of this software and associated documentation files (the "Software"), to deal  *
*  in the Software without restriction, including without limitation the rights   *
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
*  copies of the Software, and to permit persons to whom the Software is          *
*  furnished to do so, subject to the following conditions:                       *
*                                                                                 *
*  The above copyright notice and this permission notice shall be included in all *
*  copies or substantial portions of the Software.                                *
*                                                                                 *
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  *
*  SOFTWARE.                                                                      *
***********************************************************************************/

#ifndef __TEXTABLE_H__
#define __TEXTABLE_H__

#include <iostream>
#include <vector>

//! Implements a textual table abstraction.
/*!
    A text table represents a table-like structure that can be streamed out as
    a plain text. A table has cells that hold string values, each of which can be referred by
    a row and column numbers.

    The process of the text table generation is simple and intuitive.
    You create an instance of the `Textable` class and populate it with your data.
    You may add data in any order you want - `Textable` will handle it.
    By default all cell content is center aligned. A table can be output to a
    character stream.

    No special requirements except C++11 compliant compiler.
    In order to properly handle Unicode content all input strings must be UTF-8
    encoded. The client should set a proper locale too. For example:
    'std::setlocale(LC_ALL, "en_US.utf8");'.
*/
class Textable
{
public:
    using Row          = std::vector<std::string>;
    using Table        = std::vector<Row>;
    using RowNumber    = Row::size_type;
    using ColumnNumber = Table::size_type;

    template<typename T>
    void setCell(RowNumber row, ColumnNumber column, T && value);

    template<typename T, typename U = typename std::decay<decltype(*begin(std::declval<T>()))>::type>
    void setRow(RowNumber row, T && rowData);

    template<typename Value, typename... Ts>
    void setRow(RowNumber row, Value && value, Ts &&... restValues);

    template<typename T, typename U = typename std::decay<decltype(*begin(std::declval<T>()))>::type>
    void setColumn(ColumnNumber column, T && columnData);

    template<typename Value, typename... Ts>
    void setColumn(ColumnNumber column, Value && value, Ts &&... restValues);

    //! Returns the number of rows of the table.
    RowNumber rowCount() const;

    //! Returns the number of columns of the table.
    ColumnNumber columnCount() const;

    std::string cellValue(RowNumber row, ColumnNumber column) const;

    friend std::ostream &operator<<(std::ostream &os, const Textable &table);

private:
    /// Implements the base case for setRow() variadic function template recursion.
    template <typename T>
    void setRow(T);

    /// Implements the base case for setColumn() variadic function template recursion.
    template <typename T>
    void setColumn(T);

    Table m_table;
};

#endif // !__TEXTABLE_H__


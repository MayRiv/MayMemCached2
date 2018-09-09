#ifndef LEXEME_PARSER_TEST
#define LEXEME_PARSER_TEST
#include "gtest/gtest.h"
#include "../../src/SimpleProto/ILexemeParser.hpp"
#include "../../src/SimpleProto/LexemeParser.hpp"
#include <optional>

TEST(LexemeParserTest, SimpleLexems)
{
    auto parser  = std::make_unique<maycached::engine::lexeme_parser::LexemeParser>();
    auto result = parser->parse("first second third");
    EXPECT_EQ(result.has_value(), true);
    if (result.has_value())
    {
        EXPECT_EQ(3, result.value().size());
    }
}

TEST(LexemeParserTest, QuotationLexems)
{
    auto parser  = std::make_unique<maycached::engine::lexeme_parser::LexemeParser>();
    auto result = parser->parse("firstLexem second \" third also third and this is third\" fourth \"fifth\" sixth");
    EXPECT_EQ(result.has_value(), true);
    if (result.has_value())
    {
        EXPECT_EQ(6, result.value().size());
    }
}

TEST(LexemeParserTest, EscapeLexems)
{
    auto parser  = std::make_unique<maycached::engine::lexeme_parser::LexemeParser>();
    auto result = parser->parse("firstLexem \\second \\\" fourth \\5");
    EXPECT_EQ(result.has_value(), true);
    if (result.has_value())
    {
        EXPECT_EQ(5, result.value().size());
    }
}
TEST(LexemeParserTest, EmptyFail)
{
    auto parser  = std::make_unique<maycached::engine::lexeme_parser::LexemeParser>();
    auto result = parser->parse("");
    EXPECT_EQ(result.has_value(), true);
    if (result.has_value())
    {
        EXPECT_EQ(1, result.value().size());
        EXPECT_EQ(result.value()[0], "");
    }
}
TEST(LexemeParserTest, ComplexLexems)
{
    auto parser  = std::make_unique<maycached::engine::lexeme_parser::LexemeParser>();
    auto result = parser->parse("firstLexem second \" third\\\"Test\" \\a");
    EXPECT_EQ(result.has_value(), true);
    if (result.has_value())
    {
        EXPECT_EQ(4, result.value().size());
    }
}

#endif

#ifndef RULE_SET_HPP
#define RULE_SET_HPP
#include <logic/Commands/ICommand.hpp>
#include <memory>
#include <functional>
#include <list>
#include <iostream>
#include <algorithm>
#include <ctype.h>
namespace maycached {
namespace engine {
namespace rules {

class RuleSet
{
public:

    typedef  const std::vector<std::string>& Lexemes;
    typedef  std::function<bool(Lexemes)> Predicate;
    typedef  std::function<std::unique_ptr<logic::ICommand>(Lexemes)> Builder;

    RuleSet& addRule(Predicate&& rule){
        rules.push_back(std::move(rule));
        return *this;
    }
    void setBuilder(Builder&& f){
        this->builder = std::move(f);
    }
    bool check(Lexemes lexemes){
        return std::all_of(rules.begin(), rules.end(), [&lexemes](auto p){
            return p(lexemes);
        });
    }
    auto build(Lexemes l)
    {
        return builder(l);
    }
private:
    std::list<Predicate> rules{};
    Builder builder = [](Lexemes l){
        return nullptr;
    };

};
constexpr auto IS_DIGIT_N = [](RuleSet::Lexemes l, const short n){
    const auto& s = l[n - 1];
    auto nonDigit = std::find_if(s.begin(), s.end(), [](const char c){
            return !isdigit(c);
        });
    bool foundNonDigit = nonDigit != s.end();
    return !foundNonDigit;
};
}

}
}
#endif

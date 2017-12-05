//
// Created by ahmed on 12/5/17.
//

#include "Table_Generator.h"

Table_Generator::Table_Generator(mss first, mss follow) {
    this->first = std::move(first);
    this->follow = std::move(follow);
}

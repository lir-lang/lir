#pragma once


#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)


#include <util/util.hpp>
#include <structures/structures.hpp>
#include <preprocessor/preprocessor.hpp>
#include <lexer/lexer.hpp>
#include <parser/parser.hpp>


#undef likely
#undef unlikely

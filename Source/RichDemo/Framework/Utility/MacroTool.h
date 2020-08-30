/****************************************************************************************
*
* (C) Copyright 2019
*
****************************************************************************************/

#pragma once


//--------------------------------------------------------------------------------
// @see http://stackoverflow.com/questions/32438252/efficient-way-to-apply-mirror-effect-on-quaternion-rotation
#define MIRROR_QUAT_X(Q)\
    do\
    {\
        Q.Y *= -1.0f;\
        Q.Z *= -1.0f;\
    } while(0)

#define MIRROR_QUAT_Y(Q)\
    do\
    {\
        Q.X *= -1.0f;\
        Q.Z *= -1.0f;\
    } while(0)

#define MIRROR_QUAT_Z(Q)\
    do\
    {\
        Q.X *= -1.0f;\
        Q.Y *= -1.0f;\
    } while(0)


//--------------------------------------------------------------------------------
#if defined(_MSC_VER) && !defined(__clang__) // Microsoft compilers

#   define GET_ARG_COUNT(...)  INTERNAL_EXPAND_ARGS_PRIVATE(INTERNAL_ARGS_AUGMENTER(__VA_ARGS__))

#   define INTERNAL_ARGS_AUGMENTER(...) unused, __VA_ARGS__
#   define INTERNAL_EXPAND(x) x
#   define INTERNAL_EXPAND_ARGS_PRIVATE(...) INTERNAL_EXPAND(INTERNAL_GET_ARG_COUNT_PRIVATE(__VA_ARGS__, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#   define INTERNAL_GET_ARG_COUNT_PRIVATE(_1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, count, ...) count

#else // Non-Microsoft compilers

#   define GET_ARG_COUNT(...) INTERNAL_GET_ARG_COUNT_PRIVATE(0, ## __VA_ARGS__, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#   define INTERNAL_GET_ARG_COUNT_PRIVATE(_0, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, count, ...) count

#endif

#define VORTEX_EXPAND_VAR(...) (__VA_ARGS__)

#define VORTEX_EXPAND_1(A) (A)
#define VORTEX_EXPAND_2(A, B) (A, B)
#define VORTEX_EXPAND_3(A, B, C) (A, B, C)
#define VORTEX_FEA0( W, O, X)
#define VORTEX_FEA1( W, O, X)      O(W, X, 0)

#if defined(_MSC_VER) && !defined(__clang__) // Microsoft compilers

#define VORTEX_FEA2( W, O, X, ...) O(W, X, 1); VORTEX_FEA1 VORTEX_EXPAND_3(W, O, __VA_ARGS__)
#define VORTEX_FEA3( W, O, X, ...) O(W, X, 2); VORTEX_FEA2 VORTEX_EXPAND_3(W, O, __VA_ARGS__)
#define VORTEX_FEA4( W, O, X, ...) O(W, X, 3); VORTEX_FEA3 VORTEX_EXPAND_3(W, O, __VA_ARGS__)
#define VORTEX_FEA5( W, O, X, ...) O(W, X, 4); VORTEX_FEA4 VORTEX_EXPAND_3(W, O, __VA_ARGS__)
#define VORTEX_FEA6( W, O, X, ...) O(W, X, 5); VORTEX_FEA5 VORTEX_EXPAND_3(W, O, __VA_ARGS__)
#define VORTEX_FEA7( W, O, X, ...) O(W, X, 6); VORTEX_FEA6 VORTEX_EXPAND_3(W, O, __VA_ARGS__)
#define VORTEX_FEA8( W, O, X, ...) O(W, X, 7); VORTEX_FEA7 VORTEX_EXPAND_3(W, O, __VA_ARGS__)
#define VORTEX_FEA9( W, O, X, ...) O(W, X, 8); VORTEX_FEA8 VORTEX_EXPAND_3(W, O, __VA_ARGS__)
#define VORTEX_FEA10(W, O, X, ...) O(W, X, 9); VORTEX_FEA9 VORTEX_EXPAND_3(W, O, __VA_ARGS__)

#else

#define VORTEX_FEA2( W, O, X, ...) O(W, X, 1); VORTEX_FEA1(W, O, __VA_ARGS__)
#define VORTEX_FEA3( W, O, X, ...) O(W, X, 2); VORTEX_FEA2(W, O, __VA_ARGS__)
#define VORTEX_FEA4( W, O, X, ...) O(W, X, 3); VORTEX_FEA3(W, O, __VA_ARGS__)
#define VORTEX_FEA5( W, O, X, ...) O(W, X, 4); VORTEX_FEA4(W, O, __VA_ARGS__)
#define VORTEX_FEA6( W, O, X, ...) O(W, X, 5); VORTEX_FEA5(W, O, __VA_ARGS__)
#define VORTEX_FEA7( W, O, X, ...) O(W, X, 6); VORTEX_FEA6(W, O, __VA_ARGS__)
#define VORTEX_FEA8( W, O, X, ...) O(W, X, 7); VORTEX_FEA7(W, O, __VA_ARGS__)
#define VORTEX_FEA9( W, O, X, ...) O(W, X, 8); VORTEX_FEA8(W, O, __VA_ARGS__)
#define VORTEX_FEA10(W, O, X, ...) O(W, X, 9); VORTEX_FEA9(W, O, __VA_ARGS__)
#endif

#define VORTEX_CONCAT_(A, B) A##B
#define VORTEX_CONCAT(A, B) VORTEX_CONCAT_(A, B)
#define FOREACH_DO_SERIAILIZE(A, B, SUFFIX) A << B
#define FOREACH_DO_SERIAILIZE_VAR(A, B, SUFFIX) auto _x##SUFFIX = B; A << _x##SUFFIX
#define FOREACH_DO_DESERIAILIZE(A, B, SUFFIX) A >> B

#if defined(_MSC_VER) && !defined(__clang__) // Microsoft compilers

#define VORTEX_FOREACH_ASSIGN(W, O, ...) VORTEX_CONCAT(VORTEX_FEA, GET_ARG_COUNT(__VA_ARGS__)) VORTEX_EXPAND_3(W, O, __VA_ARGS__)

#else

#define VORTEX_FOREACH_ASSIGN(W, O, ...) VORTEX_CONCAT(VORTEX_FEA, GET_ARG_COUNT(__VA_ARGS__)) (W, O, __VA_ARGS__)

#endif

#define EXTRAC_1_0()
#define EXTRAC_1_1(A) A
#define EXTRAC_1_2(A, B) A
#define EXTRAC_1_3(A, B, C) A
#define EXTRAC_2_0()
#define EXTRAC_2_1(A)
#define EXTRAC_2_2(A, B) B
#define EXTRAC_2_3(A, B, C) B
#define EXTRAC_3_0()
#define EXTRAC_3_1(A)
#define EXTRAC_3_2(A, B)
#define EXTRAC_3_3(A, B, C) C

#if defined(_MSC_VER) && !defined(__clang__) // Microsoft compilers

#define EXTRAC_1st_PARAM(...) VORTEX_CONCAT(EXTRAC_1_, GET_ARG_COUNT(__VA_ARGS__))VORTEX_EXPAND_VAR(__VA_ARGS__)
#define EXTRAC_2nd_PARAM(...) VORTEX_CONCAT(EXTRAC_2_, GET_ARG_COUNT(__VA_ARGS__))VORTEX_EXPAND_VAR(__VA_ARGS__)
#define EXTRAC_3rd_PARAM(...) VORTEX_CONCAT(EXTRAC_3_, GET_ARG_COUNT(__VA_ARGS__))VORTEX_EXPAND_VAR(__VA_ARGS__)

#else

#define EXTRAC_1st_PARAM(...) VORTEX_CONCAT(EXTRAC_1_, GET_ARG_COUNT( __VA_ARGS__))( __VA_ARGS__)
#define EXTRAC_2nd_PARAM(...) VORTEX_CONCAT(EXTRAC_2_, GET_ARG_COUNT( __VA_ARGS__))( __VA_ARGS__)
#define EXTRAC_3rd_PARAM(...) VORTEX_CONCAT(EXTRAC_3_, GET_ARG_COUNT( __VA_ARGS__))( __VA_ARGS__)

#endif
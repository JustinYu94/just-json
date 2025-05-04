#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdint.h>

#define JUST_JSON_ERROR_NULL_PARAM      1
#define JUST_JSON_ERROR_NULL_POINTER    2
#define JUST_JSON_ERROR_INVALID_TOKEN   3

/**
 * The JSON token types.
 */
enum JustJsonTokenType
{
    JUST_JSON_TOKEN_NONE, /** An undefined token */
    JUST_JSON_TOKEN_BEGIN_OBJECT, /** An object begin token */
    JUST_JSON_TOKEN_END_OBJECT, /** An object end token */
    JUST_JSON_TOKEN_BEGIN_ARRAY, /** An array begin token */
    JUST_JSON_TOKEN_END_ARRAY, /** An array end token */
    JUST_JSON_TOKEN_PROPERTY_NAME, /** A property name */
    JUST_JSON_TOKEN_STRING, /** A string */
    JUST_JSON_TOKEN_INTEGER, /** An integer */
    JUST_JSON_TOKEN_FLOAT, /** A float */
    JUST_JSON_TOKEN_BOOLEAN, /** A boolean */
    JUST_JSON_TOKEN_NULL /** A null token */
};

/**
 * The JSON reader.
 */
struct JustJsonReader
{
    const char* buffer; /** The read-only buffer contains the JSON string. */
    const char* bufferEnd; /** The position after the JSON string. */
    const char* current; /** The current reached position */
    const char* token; /** The pointer to the first character of the token. */
    const char* tokenEnd; /** The position after the token. */
    enum JustJsonTokenType tokenType; /** The token type currently readed. */
    int currentDepth; /** The current depth that the reader reached. */
};

/**
 * Initialize the reader to its initial state.
 *
 * @param [in,out] reader The pointer that point to the reader be initialized.
 *
 * @retval 0 on success.
 * @retval `JUST_JSON_ERROR_NULL_PARAM` on `reader` is NULL.
 */
int JustJsonReader_Init(struct JustJsonReader* reader);

int JustJsonReader_Read(struct JustJsonReader* reader);

#ifdef __cplusplus
}
#endif // __cplusplus

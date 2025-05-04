#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "JustJson.h"

static bool _JustJson_IsWhiteSpace(char c)
{
    switch(c)
    {
        case '\x20': // space
        case '\x09': // tab
        case '\x0A': // line feed
        case '\x0D': // carriage return
            return true;
        default:
            return false;
    }
}

static const char* _JustJson_SkipWhiteSpaces(const char* s)
{
    assert(s);
    while (1)
    {
        if (_JustJson_IsWhiteSpace(*s))
            s++;
        else
            return s;
    }
}

static const char* _JustJson_ReadToNextQuote(const char* current)
{
    assert(*current == '\"');
    const char* pCurrent = current;
    while (1)
    {
        pCurrent++;
        if (*pCurrent == '\"')
            break;
    };
    return pCurrent;
}

int JustJsonReader_Init(struct JustJsonReader* reader)
{
    if (reader == NULL)
        return JUST_JSON_ERROR_NULL_PARAM;
    reader->buffer = NULL;
    reader->bufferEnd = NULL;
    reader->current = NULL;
    reader->tokenType = JUST_JSON_TOKEN_NONE;
    reader->token = NULL;
    reader->tokenEnd = NULL;
    reader->currentDepth = 0;
    return 0;
}

int JustJsonReader_Read(struct JustJsonReader* reader)
{
    if (!reader)
        return JUST_JSON_ERROR_NULL_PARAM;
    if (!reader->buffer)
        return JUST_JSON_ERROR_NULL_POINTER;
    if (!reader->token && reader->tokenType != JUST_JSON_TOKEN_NONE)
        return JUST_JSON_ERROR_NULL_POINTER;

    enum JustJsonTokenType prevTokenType = reader->tokenType;
    const char* current = _JustJson_SkipWhiteSpaces(reader->current);

    if (prevTokenType == JUST_JSON_TOKEN_NONE)
    {
        // The first token should be a begin of object.
        if (*current != '{')
        {
            return JUST_JSON_ERROR_INVALID_TOKEN;
        }
        reader->tokenType = JUST_JSON_TOKEN_BEGIN_OBJECT;
        reader->current = current;
        reader->token = current;
        reader->tokenEnd = current + 1;
        reader->currentDepth++;
        return 0;
    }
    else if (prevTokenType == JUST_JSON_TOKEN_BEGIN_OBJECT)
    {
        // The token should be a property after the begin of object.
        if (*(++current) != '\"')
        {
            return JUST_JSON_ERROR_INVALID_TOKEN;
        }
        const char* nextQuote = _JustJson_ReadToNextQuote(current);
        reader->tokenType = JUST_JSON_TOKEN_PROPERTY_NAME;
        reader->current = nextQuote;
        reader->token = current + 1; // skip the begin quote
        reader->tokenEnd = nextQuote;
        return 0;
    }
    else
    {
        assert((0, "Not implement."));
        return 0;
    }
}
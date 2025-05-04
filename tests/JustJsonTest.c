#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/JustJson.h"

static void Test_Init()
{
    struct JustJsonReader reader = {0};

    int ret = JustJsonReader_Init(&reader);
    if (ret != 0)
    {
        printf("Failed to call 'JustJsonReader_Init': %ld\n", ret);
        return;
    }

    assert(reader.buffer == NULL);
    assert(reader.bufferEnd == NULL);
    assert(reader.token == NULL);
    assert(reader.tokenEnd == NULL);
    assert(reader.tokenType == JUST_JSON_TOKEN_NONE);
    assert(reader.current == NULL);
    assert(reader.currentDepth == 0);
}

static void Test_ReadPropertyName()
{
    int ret = 0;
    struct JustJsonReader reader = {0};
    const char* json = "{\"name\":\"justin\"}";
    char buffer[32] = "";

    reader.buffer = json;
    reader.bufferEnd = json + strlen(json);
    reader.current = json;

    while (1)
    {
        ret = JustJsonReader_Read(&reader);
        if (ret != 0)
        {
            printf("Failed to call 'JustJsonReader_Read': %ld\n", ret);
            return;
        }

        if (reader.tokenType == JUST_JSON_TOKEN_PROPERTY_NAME)
        {
            size_t len = reader.tokenEnd - reader.token;
            if (len > sizeof(buffer) - 1)
            {
                printf("Not enough buffer for property name.\n");
                return;
            }
            memcpy(buffer, reader.token, len);
            break;
        }
    }
}

int main(void)
{
    Test_Init();
    Test_ReadPropertyName();

    return 0;
}
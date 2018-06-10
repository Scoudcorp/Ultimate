#include "iw_string.h"
#include "dvar.h"
#include "level.h"
#include "script.h"
#include "server.h"

int String::CustomLocalizedStringIndex(const char* string)
{
    const auto warnings = Dvar::FindDvar("loc_warnings");
    const auto errors = Dvar::FindDvar("loc_warningsAsErrors");

    auto result = 0;

    const auto targetString = string;
    if (!*string) {
        return 0;
    }

    auto* v3 = reinterpret_cast<char*>(0x6F944C); // WRONG IN PATCH

    auto isInitializing = g_level->initializing;

    if (!isInitializing) {
        if (warnings->current.enabled) {
            if (!errors->current.enabled) {
                v3 = nullptr;
            }
        } else {
            isInitializing = 1;
        }
    }

    const auto targetStringRef = FindString(targetString);

    auto i = 1;
    for (; i < 600; ++i) {
        const auto configStringRef = Server::GetConfigStringConst(i + 511);

        if (configStringRef == Script::g_scriptStringConstants->_) {
            std::printf("CustomLocalizedStringIndex -> found empty slot %d (%d)\n", i, i + 511);
            break;
        }
        if (configStringRef == targetStringRef) {
            std::printf("CustomLocalizedStringIndex -> Found match at %i (%d): %d == %d\n", i, i + 511, configStringRef, targetStringRef);
            goto LABEL_19;
        }
    }

    if (!isInitializing) {
        if (v3) {
            std::printf("CustomLocalizedStringIndex -> ERROR: !isInitializing and v3\n");
            return result;
        }

        result = 0;
        goto LABEL_21;
    }

    if (i == 600) {
        const auto error = Format(reinterpret_cast<char*>(0x69BEE8), 511, targetString);
        std::printf("CustomLocalizedStringIndex -> Overflow: %s\n", error);
    }

    std::printf("CustomLocalizedStringIndex -> Setting %d (%d) to %s\n", i + 511, i, targetString);
    Server::SetConfigString(i + 511, targetString);

LABEL_19:
    result = i;

    if (i || isInitializing) {
        std::printf("CustomLocalizedStringIndex -> Wants early return (%d || %d)\n", i, isInitializing);

        std::printf("Dumping 40 neighbouring config strings\n");
        for (auto j = 0; j < i + 40; ++j) {
            const auto index = Server::GetConfigStringConst(j + 511);
            const auto stringAtIndex = ConvertToString(index);
            const auto localizedIndex = LocalizedStringIndex(stringAtIndex);

            std::printf("%i: %s -> %i\n", j, stringAtIndex, index);
        }

        return result;
    }

LABEL_21:
    if (!warnings->current.enabled || errors->current.enabled) {
        return result;
    }

    if (*targetString) {
        const auto v8 = FindString(targetString);
        auto currentIndex2 = 1;

        do {
            const auto currentStringRef = Server::GetConfigStringConst(currentIndex2 + 511);
            if (currentStringRef == Script::g_scriptStringConstants->_) {
                std::printf("CustomLocalizedStringIndex -> found empty slot search2 %d\n", i);
                break;
            }
            if (currentStringRef == v8) {
                std::printf("CustomLocalizedStringIndex -> Found match2 %d == %d\n", currentStringRef, v8);
                goto LABEL_31;
            }
            ++currentIndex2;
        } while (currentIndex2 < 600);

        if (currentIndex2 == 600) {
            const auto error = Format(reinterpret_cast<char*>(0x69BEE8), 511, targetString);
            std::printf("CustomLocalizedStringIndex -> ERROR: %s\n", error);
        }

        std::printf("CustomLocalizedStringIndex -> Setting %d (%d) to %s\n", currentIndex2 + 511, currentIndex2, targetString);
        Server::SetConfigString(currentIndex2 + 511, targetString);

    LABEL_31:
        result = currentIndex2;
    } else {
        result = 0;
    }

    std::printf("CustomLocalizedStringIndex -> returning %d\n", result);

    return result;
}

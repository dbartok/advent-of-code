#include "Day25-ComboBreaker.h"

#include <AdventOfCodeCommon/DisableLibraryWarningsMacros.h>

__BEGIN_LIBRARIES_DISABLE_WARNINGS
#include <stdexcept>
__END_LIBRARIES_DISABLE_WARNINGS

namespace
{

int64_t TRANSFORMATION_START_VALUE = 1;
int64_t TRANSFORMATION_MODULUS = 20201227;

int64_t SUBJECT_NUMBER_TO_DETERMINE_PUBLIC_KEY = 7;

}

namespace AdventOfCode
{
namespace Year2020
{
namespace Day25
{

int64_t applyTransformationStep(int64_t subjectNumber, int64_t value)
{
    return (value * subjectNumber) % TRANSFORMATION_MODULUS;
}

int64_t transform(int64_t subjectNumber, unsigned loopSize)
{
    int64_t value = subjectNumber;
    for (unsigned i = 0; i < loopSize; ++i)
    {
        value = applyTransformationStep(subjectNumber, value);
    }

    return value;
}

unsigned determineLoopSize(int64_t subjectNumber, int64_t targetNumber)
{
    int64_t value = subjectNumber;
    for (unsigned loopSize = 1; ;++loopSize)
    {
        value = applyTransformationStep(subjectNumber, value);
        if (value == targetNumber)
        {
            return loopSize;
        }
    }
}

int64_t encryptionKeyForHandshake(int64_t cardPublicKey, int64_t doorPublicKey)
{
    const unsigned cardLoopSize = determineLoopSize(SUBJECT_NUMBER_TO_DETERMINE_PUBLIC_KEY, cardPublicKey);
    const int64_t encryptionKey = transform(doorPublicKey, cardLoopSize);
    return encryptionKey;
}

}
}
}

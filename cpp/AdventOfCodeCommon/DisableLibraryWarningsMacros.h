#pragma once

#include <codeanalysis/warnings.h>

// Surround a block of code with these macros to suppress one or more warnings for that block
// e.g.,
// __BEGIN_DISABLE_WARNINGS(26440 26446)
// int f(const std::vector<int>& v) { return v[0]; }
// __END_DISABLE_WARNINGS

#define __BEGIN_DISABLE_WARNINGS(WARNINGS) \
__pragma(warning(push)) \
__pragma(warning(disable: WARNINGS)) \

#define __END_DISABLE_WARNINGS \
__pragma(warning(pop))

// Unfixable warnings encountered in libraries
//
// Each of these warnings occurs at least once in the external dependencies (e.g., the standard library) intrinsically (meaning they are unfixable externally).
// Ignoring all of these is not a perfect solution, because even though at least once their cause is intrinsic,
// at other times they might also occur inside the library as a result of misusing the library.
// However, apart from one level 3 warning (4996), every single warning in this list is level 4.
// There is much higher value in a cleaner warning list rather than having literally thousands of extra warnings, with the overwhelming majority being unfixable.
//
// 4061 - enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
// 4365 - 'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch
// 4464 - relative include path contains '..'
// 4514 - 'function' : unreferenced inline function has been removed
// 4571 - Informational: catch(...) semantics changed since Visual C++ 7.1; structured exceptions (SEH) are no longer caught
// 4619 - #pragma warning: there is no warning number 'number'
// 4623 - 'derived class': default constructor was implicitly defined as deleted
// 4625 - 'derived class': copy constructor was implicitly defined as deleted
// 4626 - 'derived class': assignment operator was implicitly defined as deleted
// 4643 - Forward declaring 'type' in namespace std is not permitted by the C++ Standard
// 4668 - 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
// 4710 - 'function': function not inlined
// 4774 - 'function' : format string expected in argument 'position' is not a string literal
// 4820 - 'bytes' bytes padding added after construct 'member_name'
// 4996 - The compiler encountered a deprecated declaration.
// 5026 - 'type': move constructor was implicitly defined as deleted
// 5027 - 'type': move assignment operator was implicitly defined as deleted
// 5031 - #pragma warning(pop): likely mismatch, popping warning state pushed in different file
// 5039 - pointer or reference to potentially throwing function passed to extern C function under -EHc.
// 26812 - Prefer 'enum class' over 'enum'
// 26814 - Use constexpr for constants whose value is known at compile time.
#define UNFIXABLE_WARNINGS_ENCOUNTERED_IN_LIBRARIES 4061 4365 4464 4514 4571 4619 4623 4625 4626 4643 4668 4710 4774 4820 4996 5026 5027 5031 5039 26812 26814


#define __BEGIN_LIBRARIES_DISABLE_WARNINGS \
__BEGIN_DISABLE_WARNINGS(\
ALL_CPPCORECHECK_WARNINGS \
ALL_CODE_ANALYSIS_WARNINGS \
UNFIXABLE_WARNINGS_ENCOUNTERED_IN_LIBRARIES)

#define __END_LIBRARIES_DISABLE_WARNINGS \
__END_DISABLE_WARNINGS
#pragma once

#ifdef _WIN32
#pragma warning(disable: 4061) // enumerator in switch of enum is not explicitly handled by a case label
#pragma warning(disable: 4514) // 'Function' unreferenced inline function has been removed
#pragma warning(disable: 4619) // #pragma warning: there is no warning number '5267'
#pragma warning(disable: 4623) // '__std_type_info_data': default constructor was implicitly defined as deleted
#pragma warning(disable: 4625) // copy constructor was implicitly defined as deleted
#pragma warning(disable: 4626) // assignment operator was implicitly defined as deleted
#pragma warning(disable: 4668) // 'BETA' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
#pragma warning(disable: 4710) // function not inlined
#pragma warning(disable: 4711) // function 'FunctionSignature' selected for automatic inline expansion
#pragma warning(disable: 4820) // 'TypeName': 'N' bytes padding added after data member 'dataMember'
#pragma warning(disable: 5026) // move constructor was implicitly defined as deleted
#pragma warning(disable: 5027) // move assignment operator was implicitly defined as deleted
#pragma warning(disable: 5039) // pointer or reference to potentially throwing function passed to extern C function under -EHc. Undefined behavior may occur if this function throws an exception.
#pragma warning(disable: 5045) // Compiler will insert Spectre mitigation for memory load if / Qspectre switch specified
#pragma warning(disable: 5262) // implicit fall-through occurs here
#pragma warning(disable: 5264) // variable is not used
#pragma warning(disable: 5267) // definition of implicit copy constructor is deprecated because it has a user-provided destructor
#endif

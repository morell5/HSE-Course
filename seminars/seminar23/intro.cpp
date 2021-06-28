//  The C+20 concept library is not supported by all compilers (01.04.2021)
//  LLVM:
//  std::totally_ordered was added 02.04.2021 (https://github.com/llvm/llvm-project/commit/7959d59028dd126416cdf10dbbd22162922e1336)
//  thus clang 13.0.0 HEAD(fcdf7f6224610a51dc2ff47f2f1e3377329b64a7)
//  does not support std::totally_ordered https://github.com/llvm/llvm-project/commit/fcdf7f6224610a51dc2ff47f2f1e3377329b64a7
//
//  GCC:
//  std::totally_ordered was add may in 2020:
//  https://github.com/gcc-mirror/gcc/commit/c9313582d82e0768a3a68250dc97d82a9ad3c116#diff-d31b758993c80e8ffbae4f72d59f9b40674080760ff2d7092a9bb2107d5c9786
//
//
//  C++20 contracts (expects, ensures, assert) is not supported by any compiler (01.04.2021)
//  Standard: https://doc.bccnsoft.com/docs/cppreference2018/en/cpp/language/attributes/contract.html
//  There is a custom implementation for clang and proposal to clang:
//  Proposal: https://llvm.org/devmtg/2019-04/slides/Poster-Lopez-Gomez-Adding_support_for_C++_contracts_to_Clang.pdf
//  Implementation: https://github.com/arcosuc3m/clang-contracts/
int main() {
    return 0;
}
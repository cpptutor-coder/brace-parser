#ifndef OKC_ASSIGN_FINITE_STATE_H
#define OKC_ASSIGN_FINITE_STATE_H

// enum for various Finite State Automate states
enum class EState {
    start,
    alpha,
    open_brace,
    close_brace,
    comma,
    invalid
};

#endif 
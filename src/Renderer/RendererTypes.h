#pragma once
// Declares types for interfacing with the underlying renderer architecture

#define KEY_PRESSES                                                                                \
    X(A)                                                                                           \
    X(B)                                                                                           \
    X(C) X(D) X(E) X(F) X(G) X(H) X(I) X(J) X(K) X(L) X(M) X(N) X(O) X(P) X(Q) X(R) X(S) X(T) X(U) \
        X(V) X(W) X(X) X(Y) X(Z) X(ESCAPE) X(LEFT_CONTROL) X(LEFT_SHIFT) X(SPACE) X(UNKNOWN)

class GL {
  public:
    enum class MagFilter {
        Nearest,
        Linear,
    };
    enum class CursorMode {
        Disabled,
        Normal,
    };
#define X(a) a,
    enum class KeyCode { KEY_PRESSES };
#undef X

    using Sampler2D = unsigned int;

    static unsigned int getMagFilter(const MagFilter &m);
    static unsigned int getCursorMode(const CursorMode &m);
    static unsigned int getKeyCode(const KeyCode &k);
    static KeyCode getKeyCodeFromInt(int k);
}; // namespace GL

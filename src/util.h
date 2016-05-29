// Note: UNUSED is also defined in basictypes.h
// from libjingle, bsd 3-clause
#ifndef UNUSED
#define UNUSED(x) Unused(static_cast<const void*>(&x))
#define UNUSED2(x, y) Unused(static_cast<const void*>(&x)); \
    Unused(static_cast<const void*>(&y))
#define UNUSED3(x, y, z) Unused(static_cast<const void*>(&x)); \
    Unused(static_cast<const void*>(&y)); \
    Unused(static_cast<const void*>(&z))
#define UNUSED4(x, y, z, a) Unused(static_cast<const void*>(&x)); \
    Unused(static_cast<const void*>(&y)); \
    Unused(static_cast<const void*>(&z)); \
    Unused(static_cast<const void*>(&a))
#define UNUSED5(x, y, z, a, b) Unused(static_cast<const void*>(&x)); \
    Unused(static_cast<const void*>(&y)); \
    Unused(static_cast<const void*>(&z)); \
    Unused(static_cast<const void*>(&a)); \
    Unused(static_cast<const void*>(&b))
inline void Unused(const void*) {}
#endif  // UNUSED

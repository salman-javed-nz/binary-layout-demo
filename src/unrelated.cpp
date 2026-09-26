// These functions are never called by the benchmark. They model unrelated
// code added to the same executable and add space between the hot stages.

// Defines one block of unrelated code. ID identifies the hot stage before this
// block. The NOPs make the block large enough to move later stages.
#define DEFINE_UNUSED(ID)                           \
    [[gnu::used, gnu::noinline, gnu::aligned(64),   \
      gnu::section(".text.layout." #ID ".unused")]] \
    void unrelated_##ID()                           \
    {                                               \
        asm volatile(".rept 1000\n\tnop\n\t.endr"); \
    }

extern "C" {
DEFINE_UNUSED(00)
DEFINE_UNUSED(01)
DEFINE_UNUSED(02)
DEFINE_UNUSED(03)
DEFINE_UNUSED(04)
DEFINE_UNUSED(05)
DEFINE_UNUSED(06)
DEFINE_UNUSED(07)
DEFINE_UNUSED(08)
DEFINE_UNUSED(09)
DEFINE_UNUSED(10)
DEFINE_UNUSED(11)
DEFINE_UNUSED(12)
DEFINE_UNUSED(13)
DEFINE_UNUSED(14)
DEFINE_UNUSED(15)
DEFINE_UNUSED(16)
DEFINE_UNUSED(17)
DEFINE_UNUSED(18)
DEFINE_UNUSED(19)
DEFINE_UNUSED(20)
DEFINE_UNUSED(21)
DEFINE_UNUSED(22)
DEFINE_UNUSED(23)
DEFINE_UNUSED(24)
DEFINE_UNUSED(25)
DEFINE_UNUSED(26)
DEFINE_UNUSED(27)
DEFINE_UNUSED(28)
DEFINE_UNUSED(29)
DEFINE_UNUSED(30)
}

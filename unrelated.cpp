#define UNUSED_CODE(ID)                             \
    [[gnu::used, gnu::noinline, gnu::aligned(64),   \
      gnu::section(".text.layout." #ID ".unused")]] \
    void unrelated_##ID()                           \
    {                                               \
        asm volatile(".rept 1000\n\tnop\n\t.endr"); \
    }

extern "C" {
UNUSED_CODE(00)
UNUSED_CODE(01)
UNUSED_CODE(02)
UNUSED_CODE(03)
UNUSED_CODE(04)
UNUSED_CODE(05)
UNUSED_CODE(06)
UNUSED_CODE(07)
UNUSED_CODE(08)
UNUSED_CODE(09)
UNUSED_CODE(10)
UNUSED_CODE(11)
UNUSED_CODE(12)
UNUSED_CODE(13)
UNUSED_CODE(14)
UNUSED_CODE(15)
UNUSED_CODE(16)
UNUSED_CODE(17)
UNUSED_CODE(18)
UNUSED_CODE(19)
UNUSED_CODE(20)
UNUSED_CODE(21)
UNUSED_CODE(22)
UNUSED_CODE(23)
UNUSED_CODE(24)
UNUSED_CODE(25)
UNUSED_CODE(26)
UNUSED_CODE(27)
UNUSED_CODE(28)
UNUSED_CODE(29)
UNUSED_CODE(30)
}

#undef UNUSED_CODE

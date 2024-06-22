ENTRY(_start)
SECTIONS
{
  . = 0x1000;
  .text : {
    *(.text.entry)
    *(.text.kernel)
    *(.text)
  }
  .data : {
    *(.data)
  }
  .bss : {
    *(.bss)
  }
}

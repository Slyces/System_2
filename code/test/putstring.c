#include "syscall.h"

int main() {
  PutString("Bonjour ! Test 1 !\n");
  PutString("Incroyable ! Une fin de stri\0g au milieu d'un string ? oO");
  PutString("\n");
  PutString("abcdefghijklmnopqrstuvwxyz0123456789\n");
  PutString("\n...\n\n");
  PutString("012345678901234567890123456789ab");
  PutString("\nLorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus id scelerisque leo. Integer vestibulum mattis orci, ut eleifend diam. Nullam quis viverra purus. Nunc feugiat nibh non massa semper, in vehicula leo hendrerit. Quisque scelerisque, nisl nec laoreet commodo, mauris erat viverra nisi, vitae blandit justo augue at ante. Nulla varius, velit at pretium volutpat, quam elit feugiat urna, sit amet tempor nunc nunc at sem. Fusce in consequat odio. In pretium mauris dolor, ac finibus urna accumsan at. Duis volutpat, quam ut luctus lobortis, nisl lectus sodales eros, vel dictum dui mauris ac enim. Fusce pellentesque eget mi sollicitudin tempor.\nAliquam ultricies, sem id aliquam mollis, sem nibh volutpat turpis, sit amet interdum risus urna a nunc.\n");
  Halt();

  }

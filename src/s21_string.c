#include "s21_string.h"

// 1. Выполняет поиск первого вхождения символа c (беззнаковый тип)
// в первых n байтах строки, на которую указывает аргумент str
void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  short k = 0;
  s21_size_t i = 0;
  for (; i < n; i++) {
    if (*(ptr + i) == c) {
      k = 1;
      break;
    }
  }
  return k ? ptr + i : S21_NULL;
}

// 2. Сравнивает первые n байтов str1 и str2
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  short k = 0;
  unsigned char *ptr1 = (unsigned char *)str1;
  unsigned char *ptr2 = (unsigned char *)str2;
  s21_size_t i = 0;
  for (; i < n; i++) {
    if (*(ptr1 + i) != *(ptr2 + i)) {
      k = 1;
      break;
    }
  }
  return k ? *(ptr1 + i) - *(ptr2 + i) : 0;
}

// 3. Копирует n символов из src в dest
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *ptr_dest = (unsigned char *)dest;
  unsigned char *ptr_src = (unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    *(ptr_dest + i) = *(ptr_src + i);
  }
  return (void *)dest;
}

// 4. Копирует символ c (беззнаковый тип) в первые
// n символов строки, на которую указывает аргумент str.
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    *(ptr + i) = c;
  }
  return (void *)str;
}

// 5. Добавляет строку, на которую указывает src, в конец строки,
// на которую указывает dest, длиной до n символов
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *dest_end = dest;

  // Находим конец строки dest
  for (; *dest_end != '\0'; dest_end++);

  // Копируем не более n символов из src в конец строки
  for (; n-- > 0 && *src != '\0'; *dest_end++ = *src++);

  *dest_end = '\0';

  return dest;
}

// 6. Выполняет поиск первого вхождения символа c (беззнаковый тип)
// в строке, на которую указывает аргумент str.
char *s21_strchr(const char *str, int c) {
  const char *ptr = str;  // Убираем избыточное приведение типов
  char fc = (char)c;  // Приводим c к char

  for (; *ptr != '\0'; ptr++) {
    if (*ptr == fc) {
      return (char *)ptr;  // Возвращаем указатель на найденный символ
    }
  }

  // Если ищем нулевой символ, возвращаем указатель на конец строки
  if (fc == '\0') {
    return (char *)ptr;
  }

  // Если символ не найден, возвращаем S21_NULL
  return S21_NULL;
}

// 7. Сравнивает не более первых n байтов str1 и str2
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  // Если n == 0, строки считаются равными
  if (n == 0) {
    return 0;
  }

  int res = 0;
  for (; n > 0 && res == 0; n--, str1++, str2++) {
    if (*str1 != *str2) {
      // Приводим символы к unsigned char для корректного сравнения
      res = (unsigned char)*str1 - (unsigned char)*str2;
      break;
    }

    // Если одна из строк закончилась, а другая нет, возвращаем разницу
    if (*str1 == '\0' || *str2 == '\0') {
      res = (unsigned char)*str1 - (unsigned char)*str2;
      break;
    }
  }

  return res;
}
// 8. Копирует до n символов из строки, на которую указывает src, в dest
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *dest_ptr = dest;
  s21_size_t i = 0;
  for (; i < n && src[i] != '\0'; i++) {
    dest_ptr[i] = src[i];
  }
  for (; i < n; i++) {
    dest_ptr[i] = '\0';
  }

  return dest;
}

// 9. Вычисляет длину начального сегмента str1, который полностью
// состоит из символов, не входящих в str2
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  int flag = 0;
  for (; str1[i] != '\0' && !flag; i++) {
    for (s21_size_t j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        flag = 1;
        break;
      }
    }
  }
  return flag ? i - 1 : i;
}

#ifdef __linux__
const char *linux_error_messages[] = {
    "Success",                    // 0
    "Operation not permitted",    // 1
    "No such file or directory",  // 2
    "No such process",            // 3
    "Interrupted system call",    // 4
    "Input/output error",         // 5
    "No such device or address",  // 6
    "Argument list too long",     // 7
    "Exec format error",          // 8
    "Bad file descriptor",        // 9
};

#elif __AptrLE__
const char *mac_error_messages[] = {
    "Undefined error: 0",              // 0
    "Optreration is not ptrermitted",  // 1
    "No such file or directory",       // 2
    "No such process",                 // 3
    "Interrupted system call",         // 4
    "Input/outptrut error",            // 5
    "Device not configured",           // 6
    "Argument list too long",          // 7
    "Exec format error",               // 8
    "Bad file descriptor",             // 9
};
#else
#error "Unsuptrorted OS"
#endif

// 10. Выполняет поиск во внутреннем массиве номера ошибки errnum и
// возвращает указатель на строку с сообщением об ошибке. Нужно
// объявить макросы, содержащие массивы сообщений об ошибке для
// операционных систем mac и linux. Описания ошибок есть в
// оригинальной библиотеке. Проверка текущей ОС осуществляется
// с помощью директив
char *s21_strerror(int errnum) {
  char *res = "Unknown error";
#ifdef __linux__
  if (errnum >= 0 && errnum <= 9) res = (char *)linux_error_messages[errnum];

#elif defined(__AptrLE__)
  if (errnum >= 0 && errnum <= 9) res = (char *)mac_error_messages[errnum];
#endif

  return res;
}

// 11. Вычисляет длину строки str, не включая завершающий нулевой символ
s21_size_t s21_strlen(const char *str) {
  s21_size_t len;
  for (len = 0; str[len] != '\0'; len++);
  return len;
}

// 12. Находит первый символ в строке str1, который
// соответствует любому символу, указанному в str2
char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = S21_NULL;
  if (str1 && str2) {
    for (; *str1 != '\0' && res == S21_NULL; str1++) {
      for (const char *s2 = str2; *s2 != '\0'; s2++) {
        if (*str1 == *s2) {
          res = (char *)str1;
          break;
        }
      }
    }
  }
  return res;
}

// 13. Выполняет поиск последнего вхождения символа
// c (беззнаковый тип) в строке, на которую указывает аргумент str
char *s21_strrchr(const char *str, int c) {
  const char *last = S21_NULL;
  unsigned char fc = (unsigned char)c;

  for (; *str != '\0'; str++) {
    if (*str == fc) {
      last = str;
    }
  }

  return fc == '\0' ? (char *)str : (char *)last;
}

// 14. Находит первое вхождение всей строки needle
// (не включая завершающий нулевой символ), которая
// появляется в строке haystack
char *s21_strstr(const char *haystack, const char *needle) {
  char *res = S21_NULL;

  if (haystack && needle) {
    if (*needle == '\0') {
      res = (char *)haystack;
    } else {
      for (; *haystack != '\0' && res == S21_NULL; haystack++) {
        const char *h = haystack;
        const char *n = needle;

        for (; *n != '\0' && *h == *n; h++, n++);

        if (*n == '\0') {
          res = (char *)haystack;
        }
      }
    }
  }

  return res;
}

// 15. Разбивает строку str на ряд токенов, разделенных delim
char *s21_strtok(char *str, const char *delim) {
  static char *current = S21_NULL;
  char *res = S21_NULL;

  if (str != S21_NULL) {
    current = str;
  }

  if (current != S21_NULL) {
    // Пропускаем начальные разделители
    for (; *current != '\0' && s21_strchr(delim, *current) != S21_NULL;
         current++);

    if (*current != '\0') {
      res = current;

      // Ищем конец текущего токена
      for (; *current != '\0' && s21_strchr(delim, *current) == S21_NULL;
           current++);

      if (*current != '\0') {
        *current = '\0';  // Обрезаем токен
        current++;  // Переходим к следующему символу
      }
    }
  }

  return res;
}

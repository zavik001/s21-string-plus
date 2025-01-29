#include "s21_string.h"

// Функция для разбора строки ввода по заданному формату
int s21_sscanf(const char *input_string, const char *format_string, ...) {
  int matched_count = 0;
  int parsing_error = 0;
  if (format_string) {
    va_list arguments;
    va_start(arguments, format_string);
    int current_index = 0;
    for (s21_size_t i = 0; format_string[i] && !parsing_error; i++) {
      if (format_string[i] == '%') {
        format_flags flags = {-1, 0, 0, 0};
        read_format(format_string, &flags, &i);
        current_index += is_space(input_string + current_index, flags);
        switch (flags.spec) {
          case 'c':
            current_index += write_char(arguments, input_string + current_index,
                                        flags, &matched_count);
            break;
          case 's':
            current_index += write_string(
                arguments, input_string + current_index, flags, &matched_count);
            break;
          case 'i':
          case 'd':
            current_index += write_signed_int(
                arguments, input_string + current_index, flags, &matched_count);
            break;
          case 'o':
          case 'u':
          case 'x':
          case 'X':
          case 'p':
            current_index += write_unsigned_int(
                arguments, input_string + current_index, flags, &matched_count);
            break;
          case 'e':
          case 'E':
          case 'g':
          case 'G':
          case 'f':
            current_index += write_float(
                arguments, input_string + current_index, flags, &matched_count);
            break;
          case 'n':
            *va_arg(arguments, int *) = current_index;
            break;
          default:
            parsing_error = 1;
        }
      } else if (isspace(format_string[i])) {
        while (input_string[current_index] &&
               isspace(input_string[current_index]))
          current_index++;
      } else {
        if (format_string[i] == input_string[current_index]) {
          current_index++;
        } else {
          parsing_error = 1;
        }
      }
    }
    va_end(arguments);
  }
  return matched_count;
}

// Функция для чтения формата
void read_format(const char *format_string, format_flags *flags,
                 s21_size_t *index) {
  int i = *index + 1;
  if (format_string[i] == '*') {
    flags->supress_writing = 1;
    i++;
  } else if (isdigit(format_string[i])) {
    char buffer[256];
    int j = 0;
    while (isdigit(format_string[i])) {
      buffer[j++] = format_string[i++];
    }
    buffer[j] = '\0';
    flags->width = to_integer(buffer, 10);
  }
  if (s21_strchr("lLh", format_string[i])) {
    flags->length = format_string[i++];
  }
  if (s21_strchr("cdieEfgGosuxXpn%", format_string[i])) {
    flags->spec = format_string[i];
  }
  *index = i;
}

// Функция для проверки пробелов
int is_space(const char *input_string, format_flags flags) {
  int n = 0;
  if (flags.spec != 'c') {
    while (input_string[n] && s21_strchr(" \n\t\r\f", input_string[n])) n++;
  }
  return n;
}

// Функция для записи символа
int write_char(va_list arguments, const char *input_string, format_flags flags,
               int *matched_count) {
  if (!flags.supress_writing && input_string[0]) {
    *va_arg(arguments, char *) = input_string[0];
    (*matched_count)++;
  }
  return input_string[0] ? 1 : 0;
}

// Функция для записи строки
int write_string(va_list arguments, const char *input_string,
                 format_flags flags, int *matched_count) {
  int n = 0;
  char *buffer = va_arg(arguments, char *);
  if (!flags.supress_writing && buffer) {
    while (input_string[n] && !isspace(input_string[n]) &&
           (flags.width == -1 || n < flags.width)) {
      buffer[n] = input_string[n];
      n++;
    }
    buffer[n] = '\0';
    *matched_count += input_string[0] ? 1 : 0;
  }
  return n;
}

// Функция для записи знакового целого числа
int write_signed_int(va_list arg, const char *input_string, format_flags flags,
                     int *matched_count) {
  int n = 0;
  char *buffer = calloc(s21_strlen(input_string) + 1, sizeof(char));
  int i = 0;
  if (input_string[n] == '+' || input_string[n] == '-') {
    buffer[i++] = input_string[n++];
  }
  int base = (input_string[n] == '0' && flags.spec == 'i') ? 8 : 10;
  if (base == 8 && (input_string[n] == 'x' || input_string[n] == 'X')) {
    base = 16;
    n++;
  }
  char *base_alphabet = (base == 8)    ? "01234567"
                        : (base == 10) ? "0123456789"
                                       : "0123456789abcdefxABCDEFX";
  while (input_string[n] && s21_strchr(base_alphabet, input_string[n]) &&
         (flags.width == -1 || n < flags.width)) {
    buffer[i++] = input_string[n++];
  }
  buffer[i] = '\0';
  if (!flags.supress_writing) {
    if (flags.length == 'h') {
      CONVERT_TO_AND_SAVE_AS(to_integer(buffer, base), short int);
    } else if (flags.length == 'l') {
      CONVERT_TO_AND_SAVE_AS(to_integer(buffer, base), long int);
    } else {
      CONVERT_TO_AND_SAVE_AS(to_integer(buffer, base), int);
    }
    *matched_count += input_string[0] ? 1 : 0;
  }
  free(buffer);
  return n;
}

// Функция для записи беззнакового целого числа
int write_unsigned_int(va_list arg, const char *input_string,
                       format_flags flags, int *matched_count) {
  int n = 0;
  char *buffer = calloc(s21_strlen(input_string) + 1, sizeof(char));
  int base = (flags.spec == 'o') ? 8
             : (flags.spec == 'x' || flags.spec == 'X' || flags.spec == 'p')
                 ? 16
                 : 10;

  while (input_string[n] &&
         s21_strchr("0123456789abcdefxABCDEFX", input_string[n]) &&
         (flags.width == -1 || n < flags.width)) {
    buffer[n] = input_string[n];
    n++;
  }
  buffer[n] = '\0';

  if (!flags.supress_writing) {
    if (flags.spec == 'p') {
      unsigned long int *pointer_void = va_arg(arg, void *);
      *pointer_void = to_integer(buffer, base);
    } else if (flags.length == 'h') {
      CONVERT_TO_AND_SAVE_AS(to_integer(buffer, base), unsigned short int);
    } else if (flags.length == 'l') {
      CONVERT_TO_AND_SAVE_AS(to_integer(buffer, base), unsigned long int);
    } else {
      CONVERT_TO_AND_SAVE_AS(to_integer(buffer, base), unsigned int);
    }
    *matched_count += input_string[0] ? 1 : 0;
  }
  free(buffer);
  return n;
}

// Функция для записи числа с плавающей точкой
int write_float(va_list arg, const char *input_string, format_flags flags,
                int *matched_count) {
  int n = 0;
  char *buffer = calloc(s21_strlen(input_string) + 1, sizeof(char));

  if (input_string[n] == '-' || input_string[n] == '+') {
    buffer[n] = input_string[n];
    n++;
  }
  int has_decimal_point = 0;

  while (input_string[n] &&
         (isdigit(input_string[n]) || input_string[n] == '.') &&
         has_decimal_point <= 1 && (flags.width == -1 || n < flags.width)) {
    if (input_string[n] == '.') has_decimal_point++;
    buffer[n] = input_string[n];
    n++;
  }

  if (input_string[n] == 'e' || input_string[n] == 'E') {
    buffer[n] = input_string[n];
    n++;
    if (input_string[n] == '-' || input_string[n] == '+') {
      buffer[n] = input_string[n];
      n++;
    }
    while (input_string[n] && isdigit(input_string[n])) {
      buffer[n] = input_string[n];
      n++;
    }
  }
  buffer[n] = '\0';

  if (!flags.supress_writing) {
    if (flags.length == 'l') {
      CONVERT_TO_AND_SAVE_AS(to_float(buffer), double);
    } else if (flags.length == 'L') {
      CONVERT_TO_AND_SAVE_AS(to_float(buffer), long double);
    } else {
      CONVERT_TO_AND_SAVE_AS(to_float(buffer), float);
    }
  }
  *matched_count += input_string[0] ? 1 : 0;
  free(buffer);
  return n;
}

// Функция для преобразования строки в целое число
long int to_integer(char *buffer, int base) {
  long int result = 0;
  int sign = 1;
  s21_size_t i = 0;

  if (buffer[i] == '-' || buffer[i] == '+') {
    sign = (buffer[i] == '-') ? -1 : 1;
    i++;
  }

  for (; buffer[i]; i++) {
    int digit = 0;

    if (isdigit(buffer[i])) {
      digit = buffer[i] - '0';
    } else if (buffer[i] >= 'a' && buffer[i] <= 'f') {
      digit = buffer[i] - 'a' + 10;
    } else if (buffer[i] >= 'A' && buffer[i] <= 'F') {
      digit = buffer[i] - 'A' + 10;
    } else {
      break;
    }
    result = result * base + digit;
  }
  return result * sign;
}

// Функция для преобразования строки в число с плавающей запятой
long double to_float(char *buffer) {
  long double result = 0;
  int exponent = 0;
  int sign = 1, exponent_sign = 1;
  s21_size_t i = 0;
  long double divide_after_point = 1.0;

  if (buffer[i] == '-' || buffer[i] == '+') {
    sign = (buffer[i] == '-') ? -1 : 1;
    i++;
  }
  int has_decimal_point = 0;
  while (buffer[i] && (isdigit(buffer[i]) || buffer[i] == '.')) {
    if (buffer[i] == '.')
      has_decimal_point = 1;
    else {
      if (!has_decimal_point)
        result = result * 10 + (buffer[i] - '0');
      else {
        divide_after_point /= 10;
        result += (buffer[i] - '0') * divide_after_point;
      }
    }
    i++;
  }
  if (buffer[i] == 'e' || buffer[i] == 'E') {
    i++;
    if (buffer[i] == '-' || buffer[i] == '+') {
      exponent_sign = (buffer[i] == '-') ? -1 : 1;
      i++;
    }
    while (isdigit(buffer[i])) {
      exponent = exponent * 10 + buffer[i] - '0';
      i++;
    }
  }
  result *= pow(10, exponent_sign * exponent);
  return result * sign;
}

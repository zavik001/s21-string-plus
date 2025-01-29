#include "s21_string.h"

// Функция для разбора флагов формата
void parse_flags(const char *format, int *index, int *flag_array) {
  const char *valid_flags = " -+.hl";
  while (s21_strchr(valid_flags, format[*index])) {
    switch (format[*index]) {
      case '-':
        flag_array[0] = 1;
        break;
      case ' ':
        flag_array[1] = 1;
        break;
      case '+':
        flag_array[2] = 1;
        break;
      case 'h':
        flag_array[3] = 1;
        break;
      case 'l':
        flag_array[4] = 1;
        break;
      case '.':
        flag_array[5] = 1;
        break;
    }
    (*index)++;
  }
}

// Функция для разбора ширины формата
void parse_width(const char *format, int *index, int *width_value) {
  while (format[*index] >= '0' && format[*index] <= '9') {
    *width_value = *width_value * 10 + (format[*index] - '0');
    (*index)++;
  }
}

// Функция для обработки спецификаторов формата
void handle_specifier(const char *format, int *index, va_list args,
                      char *output_str, int *length, int flag_array[],
                      int width_value) {
  switch (format[*index]) {
    case 'c':
      handle_char(args, output_str, length, flag_array[0], width_value);
      break;
    case 'd':
      handle_int(args, output_str, length, flag_array[0], flag_array[1],
                 flag_array[2], flag_array[3], flag_array[4], width_value);
      break;
    case 's':
      handle_string(args, output_str, length, flag_array[0], width_value);
      break;
    case 'u':
      handle_unsigned(args, output_str, length, flag_array[0], flag_array[3],
                      flag_array[4], width_value);
      break;
    case '%':
      output_str[(*length)++] = '%';
      break;
    case 'f':
      handle_float(args, output_str, length, flag_array[0], flag_array[1],
                   flag_array[2], flag_array[5], width_value);
      break;
  }
  (*index)++;
}

// Функция для обработки символа
void handle_char(va_list args, char *output_str, int *length, int flag_minus,
                 int width_value) {
  char character = (char)va_arg(args, int);
  int padding = width_value > 1 ? width_value - 1 : 0;

  if (flag_minus) {
    s21_memset(output_str + (*length), ' ', padding);
    (*length) += padding;
  }
  output_str[(*length)++] = character;
  if (!flag_minus) {
    s21_memset(output_str + (*length), ' ', padding);
    (*length) += padding;
  }
}

// Функция для обработки целого числа
void handle_int(va_list args, char *output_str, int *length, int flag_minus,
                int flag_space, int flag_plus, int short_flag, int long_flag,
                int width_value) {
  int negative_flag = 0;
  size_t new_value = 0;
  int array_size = 0;

  if (short_flag) {
    short digit = (short)va_arg(args, int);
    negative_flag = (digit < 0);
    new_value = negative_flag ? -digit : digit;
    array_size = short_counter(new_value);
  } else if (long_flag) {
    long digit = va_arg(args, long);
    negative_flag = (digit < 0);
    new_value = negative_flag ? -digit : digit;
    array_size = long_counter(new_value);
  } else {
    int digit = va_arg(args, int);
    negative_flag = (digit < 0);
    new_value = negative_flag ? -digit : digit;
    array_size = int_counter(new_value);
  }

  char digit_array[array_size];
  int_to_char(new_value, digit_array);
  int padding =
      (width_value > array_size) ? width_value - array_size - negative_flag : 0;

  if (!flag_minus) {
    s21_memset(output_str + (*length), ' ', padding);
    (*length) += padding;
  }
  if (negative_flag)
    output_str[(*length)++] = '-';
  else if (flag_plus)
    output_str[(*length)++] = '+';
  else if (flag_space)
    output_str[(*length)++] = ' ';

  s21_memcpy(output_str + (*length), digit_array, array_size);
  (*length) += array_size;

  if (flag_minus) {
    s21_memset(output_str + (*length), ' ', padding);
    (*length) += padding;
  }
}

// Функция для обработки строки
void handle_string(va_list args, char *output_str, int *length, int flag_minus,
                   int width_value) {
  char *string_value = va_arg(args, char *);
  int string_length = s21_strlen(string_value);
  int padding = width_value > string_length ? width_value - string_length : 0;

  if (!flag_minus) {
    s21_memset(output_str + (*length), ' ', padding);
    (*length) += padding;
  }
  s21_memcpy(output_str + (*length), string_value, string_length);
  (*length) += string_length;
  if (flag_minus) {
    s21_memset(output_str + (*length), ' ', padding);
    (*length) += padding;
  }
}

// Функция для обработки беззнакового числа
void handle_unsigned(va_list args, char *output_str, int *length,
                     int flag_minus, int short_flag, int long_flag,
                     int width_value) {
  int array_size = 0;
  size_t new_value = 0;

  if (short_flag) {
    short digit = (short)va_arg(args, int);
    new_value = (digit < 0) ? short_neg_processing(digit) : (size_t)digit;
  } else if (long_flag) {
    long digit = va_arg(args, long);
    new_value = (digit < 0) ? long_neg_processing(digit) : (size_t)digit;
  } else {
    int digit = va_arg(args, int);
    new_value = (digit < 0) ? int_neg_processing(digit) : (size_t)digit;
  }

  array_size = long_counter(new_value);
  char digit_array[array_size];
  int_to_char(new_value, digit_array);

  if (!flag_minus && width_value > array_size) {
    s21_memset(output_str + (*length), ' ', width_value - array_size);
    (*length) += (width_value - array_size);
  }

  s21_memcpy(output_str + (*length), digit_array, array_size);
  (*length) += array_size;

  if (flag_minus && width_value > array_size) {
    s21_memset(output_str + (*length), ' ', width_value - array_size);
    (*length) += (width_value - array_size);
  }
}

// Функция для обработки числа с плавающей точкой
void handle_float(va_list args, char *output_str, int *length, int flag_minus,
                  int flag_space, int flag_plus, int point_flag,
                  int width_value) {
  double float_value = va_arg(args, double);
  int negative_flag = (float_value < 0);
  if (negative_flag) float_value *= -1;

  int array_size = 0;
  if (point_flag) {
    array_size =
        int_counter((int)float_value) + (width_value ? width_value + 1 : 1);
  } else {
    array_size = int_counter((int)float_value) + 7;
  }

  char float_array[array_size];
  if (point_flag) {
    float_to_char_round(float_array, array_size, float_value, width_value);
  } else {
    float_to_char(float_array, array_size, float_value);
  }

  int padding =
      (width_value > array_size) ? width_value - array_size - negative_flag : 0;

  if (!flag_minus) {
    s21_memset(output_str + (*length), ' ', padding);
    (*length) += padding;
  }
  if (negative_flag)
    output_str[(*length)++] = '-';
  else if (flag_space)
    output_str[(*length)++] = ' ';
  else if (flag_plus)
    output_str[(*length)++] = '+';

  s21_memcpy(output_str + (*length), float_array, array_size);
  (*length) += array_size;

  if (flag_minus) {
    s21_memset(output_str + (*length), ' ', padding);
    (*length) += padding;
  }
}

// Основная функция для форматирования строки
int s21_sprintf(char *output_str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int index = 0, length = 0, flag_array[6] = {0}, width_value = 0;

  while (format[index] != '\0') {
    if (format[index] != '%') {
      output_str[length++] = format[index++];
      continue;
    }
    index++;
    parse_flags(format, &index, flag_array);
    parse_width(format, &index, &width_value);
    handle_specifier(format, &index, args, output_str, &length, flag_array,
                     width_value);
    s21_memset(flag_array, 0, sizeof(flag_array));
    width_value = 0;
  }

  output_str[length] = '\0';
  va_end(args);
  return length;
}

// Функция для подсчета количества цифр в целом числе
int int_counter(int number) {
  int count = (number == 0) ? 1 : 0;
  while (number != 0) {
    number /= 10;
    count++;
  }
  return count;
}

// Функция для подсчета количества цифр в коротком числе
int short_counter(short number) {
  short n = number;
  int count = (number == 0) ? 1 : 0;

  while (n != 0) {
    n /= 10;
    count++;
  }

  return count;
}

// Функция для подсчета количества цифр в длинном числе
int long_counter(long number) {
  long n = number;
  int count = (number == 0) ? 1 : 0;

  while (n != 0) {
    n /= 10;
    count++;
  }

  return count;
}

// Функция для преобразования целого числа в строку
void int_to_char(size_t number, char *array) {
  int size = long_counter(number);
  int index = size - 1;

  while (number > 0) {
    array[index] = (number % 10) + '0';
    number /= 10;
    index--;
  }
}

// Функция для обработки отрицательных целых чисел
size_t int_neg_processing(int number) {
  size_t num = 1;
  for (int i = 0; i < 32; i++) num = num * 2;
  return num + number;
}

// Функция для обработки отрицательных коротких чисел
size_t short_neg_processing(short number) {
  size_t num = 1;
  for (int i = 0; i < 32; i++) num = num * 2;
  return num + number;
}

// Функция для обработки отрицательных длинных чисел
size_t long_neg_processing(long number) {
  size_t num = 1;
  for (int i = 0; i < 32; i++) num = num * 2;
  return num + number;
}

// Функция для преобразования числа с плавающей запятой в строку
void float_to_char(char *array, int array_size, double number) {
  int whole_part = (int)number;
  double fractional_part = number - whole_part;
  int index = int_counter(whole_part) - 1, k = 0;

  int result = fractional_part * 10000000;
  if (result % 10 > 5 && int_counter(result) >= 3) {
    fractional_part += 0.000001;
  }

  for (; index >= 0; index--) {
    array[index] = (whole_part % 10) + '0';
    whole_part /= 10;
    k++;
  }
  array[k] = '.';

  for (int l = k + 1; l < array_size; l++) {
    fractional_part *= 10;
    int num = (int)fractional_part;
    array[l] = (num % 10) + '0';
    fractional_part -= num;
  }
}

// Функция для преобразования числа с плавающей запятой в строку с округлением
void float_to_char_round(char *array, int array_size, double number,
                         int width_value) {
  int whole_part = (int)number;
  double fractional_part = number - whole_part;
  int index = int_counter(whole_part) - 1, k = 0,
      result = fractional_part * s21_pow(10, width_value + 1);

  if (result % 10 >= 5) {
    fractional_part += (1.0 / s21_pow(10, width_value));
  }

  for (; index >= 0; index--) {
    array[index] = (whole_part % 10) + '0';
    whole_part /= 10;
    k++;
  }

  array[k] = '.';

  for (int l = k + 1; l < array_size; l++) {
    fractional_part *= 10;
    int num = (int)fractional_part;
    array[l] = (num % 10) + '0';
    fractional_part -= num;
  }
}

// Функция для вычисления степени числа
long s21_pow(int base, int exponent) {
  long result = 1;
  for (int i = 0; i < exponent; i++) {
    result *= base;
  }
  return result;
}

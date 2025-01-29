#include "s21_string.h"

// Функция копирует строку из src в dest
void s21_strcpy(char *dest, const char *src) {
  while ((*dest++ = *src++)) {
  }
}

// Функция преобразует строку input_str в верхний регистр
void *s21_to_upper(const char *input_str) {
  char *upper_str = NULL;
  if (input_str) {
    s21_size_t length = s21_strlen(input_str) + 1;
    upper_str = malloc(length);
    for (char *current_char = upper_str; *input_str;
         current_char++, input_str++) {
      *current_char = (*input_str >= 'a' && *input_str <= 'z')
                          ? (*input_str - 32)
                          : *input_str;
    }
    upper_str[length - 1] = '\0';
  }
  return upper_str;
}

// Функция преобразует строку input_str в нижний регистр
void *s21_to_lower(const char *input_str) {
  char *lower_str = NULL;
  if (input_str) {
    s21_size_t length = s21_strlen(input_str) + 1;
    lower_str = malloc(length);
    for (char *current_char = lower_str; *input_str;
         current_char++, input_str++) {
      *current_char = (*input_str >= 'A' && *input_str <= 'Z')
                          ? (*input_str + 32)
                          : *input_str;
    }
    lower_str[length - 1] = '\0';
  }
  return lower_str;
}

// Функция вставляет строку insert_str в source_str начиная с индекса
// start_index
void *s21_insert(const char *source_str, const char *insert_str,
                 size_t start_index) {
  char *result_str = NULL;
  s21_size_t source_length = s21_strlen(source_str);
  s21_size_t insert_length = s21_strlen(insert_str);
  s21_size_t result_length = source_length + insert_length + 1;
  if (insert_str && source_str && start_index < source_length) {
    result_str = malloc(result_length * sizeof(char));
    s21_strncpy(result_str, source_str, start_index);
    s21_strcpy(result_str + start_index, insert_str);
    s21_strcpy(result_str + start_index + insert_length,
               source_str + start_index);
  }
  return result_str;
}

// Функция обрезает символы trim_chars из начала и конца строки source_str
void *s21_trim(const char *source_str, const char *trim_chars) {
  char *trimmed_str = S21_NULL;
  int should_continue = 0;

  if (source_str && trim_chars) {
    s21_size_t source_length = s21_strlen(source_str);
    trimmed_str = malloc(source_length + 1);
    while (*source_str && s21_strchr(trim_chars, *source_str)) source_str++;
    s21_strcpy(trimmed_str, source_str);
    s21_size_t trimmed_length = s21_strlen(source_str);

    for (s21_size_t i = 0; i < trimmed_length && !should_continue; i++) {
      char last_character = source_str[trimmed_length - i];
      if (s21_strchr(trim_chars, last_character))
        trimmed_str[s21_strlen(source_str) - i] = '\0';
      else
        should_continue = 1;
    }
    trimmed_str = realloc(trimmed_str, trimmed_length + 1);
  }

  return trimmed_str;
}

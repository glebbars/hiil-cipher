#include <stdio.h>
#include <string.h>

#define MATRIX_SIZE 3        // розмірність матриці
#define ALPHABET_SIZE 26     // розмірність англійського алфавіту
#define PADDING_CHARACTER 23 // номер додатковго символу для заповнення
#define A_NUMERIC_EQ 65      // номер літери A в таблиці ASCII

// функція шифрування
void encrypt(unsigned int a[MATRIX_SIZE][MATRIX_SIZE], unsigned int pt[], int pt_length, unsigned int d[])
{
  int i, j, t = 0;

  for (i = 0; i < pt_length; i += MATRIX_SIZE)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
    {
      t = 0;
      for (int k = 0; k < MATRIX_SIZE; k++)
      {
        t += a[j][k] * pt[i + k];
      }
      d[i + j] = t % ALPHABET_SIZE;
    }
  }
}

// функція розшифрування
void decrypt(unsigned int b[MATRIX_SIZE][MATRIX_SIZE], unsigned int d[], int d_length, unsigned int pt[])
{
  int i, j, t = 0;

  for (i = 0; i < d_length; i += MATRIX_SIZE)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
    {
      t = 0;
      for (int k = 0; k < MATRIX_SIZE; k++)
      {
        t += b[j][k] * d[i + k];
      }
      pt[i + j] = t % ALPHABET_SIZE;
    }
  }
}

// функція додавання додаткових символів для кратності на розмірність матриці (3)
int add_padding(unsigned int pt[], int pt_length, int matrix_size, int padding_character)
{
  int padding = matrix_size - pt_length % matrix_size;
  for (int i = 0; i < padding; i++)
  {
    pt[pt_length + i] = padding_character;
  }
  return pt_length + padding;
}

int main()
{
  unsigned int a[MATRIX_SIZE][MATRIX_SIZE] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}}; // матриця для шифрування
  unsigned int b[MATRIX_SIZE][MATRIX_SIZE] = {{8, 5, 10}, {21, 8, 21}, {21, 12, 8}};   // матриця для дешифрування

  int i, decrypted_length = 0;
  unsigned int pt[20], d[20];

  char msg[20];
  FILE *input_file;

  // Відкриття файлу та перевірка на помилку
  input_file = fopen("input.txt", "r");
  if (input_file == NULL)
  {
    printf("Error: Could not open input file.\n");
    return 1;
  }

  // Читання повідмолення з файлу
  fgets(msg, sizeof(msg), input_file);

  // Закриття файлу
  fclose(input_file);

  printf("Plain text: %s", msg);
  for (i = 0; i < strlen(msg); i++)
  {
    // Перевірка на правильність повідомлення
    if (msg[i] < 'A' || msg[i] > 'Z')
    {
      printf("Помилка: текст повинен містити тільки великі літери.\n");
      return 1;
    }
    // Конвертація тексту у число згідно з таблицею ASCII
    pt[i] = msg[i] - A_NUMERIC_EQ;
  }

  // Розрахунок довжини повідомлення
  int pt_length = strlen(msg);

  // Додавання додаткових символів для кратності на 3
  pt_length = add_padding(pt, pt_length, MATRIX_SIZE, PADDING_CHARACTER);

  // шифрування повідомлення
  encrypt(a, pt, pt_length, d);

  // друкування зашифрованого повідомлення
  printf("\nЗашифрований текст: ");
  for (i = 0; i < pt_length; i += MATRIX_SIZE)
  {
    printf("%c", d[i] + A_NUMERIC_EQ);
    printf("%c", d[i + 1] + A_NUMERIC_EQ);
    printf("%c", d[i + 2] + A_NUMERIC_EQ);
  }

  // розшифрування повідомлення
  decrypt(b, d, pt_length, pt);

  // друкування розшифрованого повідомлення
  printf("\nРозшифрований текст: ");
  for (i = 0; i < pt_length; i++)
  {
    if (pt[i] != PADDING_CHARACTER)
    {
      printf("%c", pt[i] + A_NUMERIC_EQ);
    }
  }

  printf("\n");

  return 0;
}
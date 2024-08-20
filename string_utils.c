#include "shell.h"

/**
 * _strlen - find the length of a string
 * @string: string to find the length
 * Return: the length of the string
 */
int _strlen(char *string)
{
	int count = 0;

	while (string[count] != '\0')
		count++;
	return (count);
}

/**
 * _strcat - concatenate two strings
 * @dest: destination
 * @src: source
 * Return: dest
 */
char *_strcat(char *dest, char *src)
{
	int i, j;

	i = _strlen(dest);

	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';

	return (dest);
}
/**
 * _strcpy - Copies a string
 * @dest: First operand destination
 * @src: Second operand source
 * Return: Return the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;
	int len = _strlen(src);

	for (i = 0; i < len; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
/**
 * _strdup - Duplicates a string
 * @string: A pointer to char
 * Return: A pointer or NULL
 */
char *_strdup(char *string)
{
	int i = 0;
	char *copy;
	int length;

	if (string == NULL)
		return (NULL);
	length = _strlen(string);
	copy = malloc((length + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	while ((copy[i] = string[i]) != '\0')
		i++;
	return (copy);
}
/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: 1 -1 or 0
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

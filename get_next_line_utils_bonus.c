/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:00:50 by cjackows          #+#    #+#             */
/*   Updated: 2022/09/25 22:35:43 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * @brief   function searches for the FIRST occurrence of 
 * character 'c' in string 's'.If 's' doesnt end with 
 * NULL program might cras!
 * @param s This is the string to be scanned.
 * @param c This is the character to be searched in 's'.
 * @return char* Returns a pointer to the first 
 * occurrence of c that is converted to a character in string.
 * The function returns NULL if the specified character is not found.
 */
char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if ((char)c == str[i])
				return ((char *)&str[i]);
			i++;
		}
		if ((char)c == str[i])
			return ((char *)&str[i]);
	}
	return (NULL);
}

/**
 * @brief Allocates (with malloc) and returns a substring from the string 's'.
 * The substring begins at index ’start’ and is of maximum size ’len’.
 * @param s	The string from which to create the substring. 
 * @param start	The start index of the substring in the string ’s’.
 * @param len	The maximum length of the substring.
 * @return char* to allocated with subtring memory. 
**/
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (s[0] == 0 || ft_strlen(s) <= start)
		return (ft_strdup(""));
	sub = NULL;
	if (len > ft_strlen(s))
		sub = malloc(ft_strlen(s) + 1);
	else
		sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	while (i < len && s[start])
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = 0;
	return (sub);
}

/**
 * @brief Function duplicates a string and returns a pointer 
 * pointing to the first byte of copied string. || 
 * It tries to allocate (with malloc) enough memory to hold the old string 
 * (plus a '\0' character to mark the end of the string).
 * @param s1 pointer to string that gets duplicated.
 * @return char*  Return the new address (which the caller is responsible for 
 * freeing at some point).
 * If the allocation failed returns NULL.
 */
char	*ft_strdup(char *s1)
{
	char	*output_str;
	int		i;

	output_str = (char *)malloc(sizeof (char) * ft_strlen(s1) + 1);
	i = 0;
	if (!output_str)
		return (NULL);
	while (s1[i])
	{
		output_str[i] = s1[i];
		i++;
	}
	output_str[i] = '\0';
	return (output_str);
}

/**
 * @brief 	Function appends the NUL-terminated string 'src' to the end of 'dst'.
 * Takes whole size of destination buffer not only the size
 * It garantees null termination (as long size > 0 && dest 
 * has at least onefree space)
 * Function does not check if 'dts' or 'src' is NULL!
 * @param dst String where 'src' gets appended to.
 * @param src String that gets appended to the end of 'dst' 
 * @param dstsize How many characters of 'dst' gets appended.
 * @return 	Returns size_t of src + dst (without NUL) OR NULL if fails.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ldst;
	size_t	lsrc;
	size_t	i;
	size_t	j;

	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	i = 0;
	j = ldst;
	if (ldst < dstsize - 1 && dstsize > 0)
	{
		while (src[i] && (ldst + i < dstsize - 1))
		{
			dst[j] = src[i];
			j++;
			i++;
		}
		dst[j] = 0;
	}
	if (ldst >= dstsize)
		ldst = dstsize;
	return (ldst + lsrc);
}

/**
 * @brief Allocates (with malloc(3)) and returns a new
 * string, which is the result of the concatenation of ’s1’ and ’s2’.
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return Char pointer to the new string.
 * 	NULL if the allocation fails.
 */
char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	size_s1;
	size_t	size_s2;
	size_t	i;

	if (s1 == NULL)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = 0;
	}
	i = 0;
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	new = malloc(size_s1 + size_s2 + 1);
	if (!new)
		return (NULL);
	while (i < size_s1 + 1)
	{
		((char *)new)[i] = ((char *)s1)[i];
		i++;
	}
	ft_strlcat(new, s2, size_s1 + size_s2 + 1);
	free(s1);
	return (new);
}

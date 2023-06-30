#include "thm.h"

static int	count_words(const char *str, char c)
{
	int i;
	int trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char		**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	if (!s || !(split = malloc((count_words(s, c) + 1) * sizeof(char *))))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= (size_t)strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == (size_t)strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

int	rdm_nb(int i)
{
	struct timeval	t;
	int nb = 0;

	gettimeofday(&t, NULL);
	nb = (int)(t.tv_sec * 1000) + (int)(t.tv_usec / 1000);
	
	if (nb < 0)
		nb *= -1;
	return (nb % i);
}

void	vis(wl *wrong, char *line, int f)
{
	wl *t;

	t = wrong;
	printf(" Wrong letters: ");
	while (t)
	{
		if (t->wg)
			printf("%c ", t->wg);
		t = t->next;
	}
	printf("\n\n");

	printf("%s\n", rep[f]);
	for (int i = 0; line[i]; i++)
		printf(" %c", line[i]);
	
}

void	check(wl *wrong, char *line, char *word, char guess, int *f)
{
	wl *t;
	long unsigned int len = strlen(word);
	int i = 0;

	while (line[i])
	{
		if (line[i] == '_')
			break ;
		i++;
	}

	if (!line[i])
	{
		printf("\n YOU WIN!\n");
		exit(0);
	}

	i = -1;
	while (word[++i])
	{
		if (word[i] != line[i] && word[i] == guess)
			line[i] = guess;
		else if (word[i] != guess)
			len--;
	}
	if (!len)
	{
		t = wrong;
		while (t->next != NULL && t->wg != '\0')
		{
			if (t->wg == guess)
				break ;
			t = t->next;
		}
		t->wg = guess;
	}
	*f = -1;
	t = wrong;
	while (t->wg != '\0')
	{
		if (++(*f) >= 7)
		{

			printf("\n You lose...\n The word was: [%s]\n", word);
			exit(0);
		}
		t = t->next;
	}
}
char	*convert(char *word)
{
	char	*line;
	int i = 0, len = strlen(word);
	
	line = malloc(sizeof(char) * (len + 1));
	
	while (i < len)
		line[i++] = '_';
	line[i] = '\0';
	return (line);
}

void	wl_gen(wl **wrong)
{
	wl *t, *a;
	int i = -1;

	while (++i < 10)
	{
		a = malloc(sizeof(wl));
		a->wg = '\0';
		if (i == 0)
			*wrong = t = a;
		else
		{
			t->next = a;
			t = a;
		}
	}
	t->next = NULL;
}

int	main(void)
{
	wl	*wrong;
	char	**tab = NULL, word[20], *line = 0, word_list[2000], loading[26] = "//////////////////////////", guess;
	int opt = 3, f = 0, nb = rdm_nb(200), fd = 3, i = 0, j = 0;

	system("clear");

	while (opt != 1 && opt != 2)
	{
		printf("\n Choose game mode:\n [1] - manual\n [2] - random\n [3] - rules\n\n type: ");
		scanf("%i", &opt);
		if (opt == 3)
		{
			system("clear");
			printf("\n------------------------------------[RULES]------------------------------------\n\n");
			printf(" [Manual] - input your personalized word (every printsble char is accepted)\n\n");
			printf(" [Random] - a word shall be picked randomly from the \"word_list.txt\" file (feel free to change the file, as long you keep it under 200 words)\n");
			printf("\n\n - Player starts with 7 tries, losing after inputing a wrong char when the body is completed;\n - This game accepts chars and strings as input; \n - Inputed strings will be counted as individual chars, so if you get the word right away you win, otherwise the chars that don't fit shall be added to the wrong char list.\n");
			printf("\n-------------------------------------------------------------------------------\n");
		}
		else if (opt < 1 || opt > 3)
			printf("\ndude can you even read? that wasn't an option...\n");
	}

	system("clear");

	if (opt == 1)
	{
		printf("\n type a word: ");
		scanf("%s", word);
		printf("\n");
		system("clear");
		for (j = 0; loading[j]; j++)
		{
			usleep(100000);
			system("clear");
			printf("\n Loading [");
			for (int k = 0; k < j - 2; k++)
				printf("%c", loading[k]);
			printf("]\n");
		}
		system("clear");
		printf("\n Get Ready!\n");
		for (int k = 3; k > 0; k--)
		{
			usleep(1000000);
			system("clear");
			printf("\n[%i]\n", k);
		}
		usleep(1000000);
	}

	else if (opt == 2)
	{
		open("word_list.txt", O_RDONLY);
		read(fd, word_list, 2000);
		tab = ft_split(word_list, 10);
		for (i = 0; tab[nb][i] >= 32 && tab[nb][i] <= 126; i++)
			word[i] = tab[nb][i];
		word[i] = '\0';
		system("clear");
		for (j = 0; loading[j]; j++)
		{
			usleep(100000);
			system("clear");
			printf("\n Loading [");
			for (int k = 0; k < j - 2; k++)
				printf("%c", loading[k]);
			printf("]\n");
		}
		system("clear");
		printf("\n Get Ready!\n");
		for (int k = 3; k > 0; k--)
		{
			usleep(1000000);
			system("clear");
			printf("\n[%i]\n", k);
		}
		usleep(1000000);
	}


	line = convert(word);
	wl_gen(&wrong);

	while (1)
	{
		system("clear");
		vis(wrong, line, f);
		printf("\n\n type a letter: ");
		scanf("%c", &guess);
		printf("\n");
		check(wrong, line, word, guess, &f);
	}
	return (0);
}
#include <stdio.h>
#include <ctype.h>
int main(void)
{
	int n = 0, c = 0, max = 0, a = 0;
	char* build = NULL;
	while ((c = getchar()) != EOF) {
		build = realloc(build, ++n);
		build[n-1] = c;

	}
	for (size_t i = 0, c = 0; i < n ; i++) {
		if (isalpha(build[i])) {
			c++;
		} else {
			if (c > max) {
				max = c;
				a = i - c;
			}
			c = 0;
		}
	}
	build[a + max] = '\0';
	printf("%d characters in longest word: %s\n", max, &build[a]);
	free(build);
	return 0;
}

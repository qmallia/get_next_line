*This project has been created as part of the 42 curriculum by qmallia.*

# 📄 Get Next Line

## 📝 Summary

### [Description](#-description)
A section that clearly **presents the project**, including its goal and a brief overview.

### [Instructions](#-instructions)
A section containing any relevant information about **compilation**, **installation**, and/or **execution**.

### [Resources](#-resources)
A section listing classic **references** related to the topic (documentation, articles, tutorials, etc.), as well as a description of how **AI** was used - specifying for which tasks and which parts of the project.

### [Detailing](#-detailing)
A **detailed explanation and justification** of the algorithm selected for this project.

---

## 📖 Description
**get_next_line** is a project that aims at returning a single line of the file corresponding to the file descriptor passed as argument, using **static variables**.

When you use the function, it returns a unique line, and then the next line of the file if you call it again, including the ``\n``, or NULL if there is nothing left to read.

Bonus has been achieved and gives you the opportunity to change the file descriptor between each call of the function without losing the track of each file.

You can decide the size of the buffer used to read the file, using ``-D BUFFER_SIZE=42`` in the compilation command, and replacing ``42`` with the size you want. By default, the buffer is set to a size of 1000.

## ⚙️ Instructions

**1. Clone the project**
```
git clone https://github.com/qmallia/get_next_line
```

**2. Using it in your own projects**

To use ``get_next_line`` in your own project, you'll need to copy all the files in your folder and include the ``get_next_line.h`` in your C files that use the function.

An example to understand :

*Considering that all the files of the project and a ``test.txt`` are at the root of your project, you could use the function in your main.c like this :*

```C
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		printf("Line %d : %s\n", i++, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

*``get_next_line`` returns a unique line each time it's called, until it returns NULL.*

Then, you can compile the program with the following command :

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o program_name
```

Or with the bonus files :

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o program_name
```

## 💻 Resources

Different man pages of the allowed functions of the project (read, open, etc), as well as some wikis found on the internet, especially about static variable and file descriptors limits.

AI was used especially to suggest on debugging some functions and to suggest some changes. All the other aspects, including the logic of the functions, were done manually.

## 🏷️ Detailing

### How it works
Each call of ``get_next_line`` goes through 3 steps, using a unique **static variable** ``stock`` that keeps what was read after the last ``\n`` between calls of the function.


1. ``read_file`` returns ``stock`` directly if it contains a ``\n``, without calling ``read``. Otherwise, it reads a size defined by ``BUFFER_SIZE`` into a buffer and appends them to ``stock`` with ``ft_strjoin`` until a ``\n`` is found or ``read`` returns 0 (end of the file). If ``read`` fails (returns -1), everything is freed and it returns ``NULL``.
2. ``find_line`` allocates and copies everything in a variable, from ``stock`` up to the first ``\n`` encountered (if there is one), including it in the destination string. It will be the string containing the line that will be returned to the user.
3. ``create_new_stock`` allocates a new string containing only what remains after the ``\n`` encountered, frees the older ``stock`` and reassign what was just allocated to the new ``stock``. If nothing remains, ``stock`` is freed and it returns ``NULL``.

### Bonus
The bonus uses an array of the static ``stock`` variable with a fixed size of 4096, which covers the usual pre-processor limit of open file descriptors possible in one function call. So, there is one ``stock`` per file descriptor passed as argument for each call, indexed directly by the ``fd``.
This makes it possible to alternate between several files, each keeping its leftovers.

### Files
* ``get_next_line(_bonus).c`` → ``get_next_line`` and its 3 static helpers (``read_file``, ``find_line`` and ``create_new_stock``).
* ``get_next_line_utils(_bonus).c`` → ``ft_strlen``, ``ft_strchr``, ``ft_strjoin`` and ``free_errors``.
* ``get_next_line(_bonus).h`` → All the needed prototypes.

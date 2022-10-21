
<h1 align="center">
💻 Minishell
</h1>

### 🗝️ Original in [**Russian**](https://github.com/AYglazk0v/minishell/blob/main/README.md)

## 💡 About the project:

> _This project is about creating a simple shell. Yes, we will create a little bash.
You will learn a lot about processes and file descriptors._

	This project consists in writing your own command interpreter.
	This interpreter must:
	- Display a prompt when waiting for a new command
	- Have a running history.
	- Find and run executable files based on the `PATH` variable in env as well as
	If an absolute path is specified.
	- Maintain no more than one global variable.
	- Handle single and double quotes correctly.
	- Redirect input and output ('<' and '>') correctly.
	- Perform file overwrite and reproduce heredoc behavior ('>>' and '<<').
	- Execute pipelined commands ('|') [Command1 output goes to command2 input].
	- Handle environment variables with '$' (example: echo $PATH).
	- Repeat the shell behavior of the `$ $?` command [expand to the output state of
	of the last pipeline].
	- Handle 'Ctrl-C', 'Ctrl-D', 'Ctrl-\' signals
	- Must not reproduce shell behavior with '\' and ';'.

	It is also necessary to implement the following built-in functions:
	- `echo` with option `-n`.
	- `cd` -- only with relative and absolute path.
	- `pwd` with no options
	- `export` with no options
    - `unset` without options
    - `env` with no options or arguments
    - `exit` without options
    
    Bonus part:
    - `&&` and `||` with brackets for priorities.
	- The wildcards `*` must work for the current working directory.

More details about the project and the nuances can be found at  [**subject**](https://github.com/MKKurbandibirov/Minishell/blob/main/Subject.pdf).

## 🛠 Testing and Usage:

	# Clone the project and access the folder
	git clone git@github.com:AYglazk0v/minishell.git && cd minishell/
	# Perform make to build the project
	make
	# To run the program, run the command
	./minishell
	# To exit the program, type exit, or press 'Ctrl-D'.
	# Clean up the output files with
	make fclean

To verify the correctness of the project implementation, you can go through the [checklist](https://github.com/AYglazk0v/minishell/blob/main/additionally/checklist(old).pdf).

## 🎬 Demonstration(example):
![exec](https://github.com/AYglazk0v/minishell/blob/main/additionally/exec.gif)

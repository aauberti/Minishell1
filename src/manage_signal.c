#include "minishell.h"

void process_sigint_for_execution(int signal_number)
{
    shell_signal = signal_number;
    write(1, "\n", 1);
}

void setup_execution_signals_handler(void)
{
    signal(SIGINT, process_sigint_for_execution);
    signal(SIGQUIT, SIG_IGN);
}

void process_sigint_for_input(int signal_number)
{
    shell_signal = signal_number;
    ioctl(0, TIOCSTI, "\n");
    rl_replace_line("", 0);
    rl_on_new_line();
}

void setup_input_signals_handler(void)
{
    signal(SIGINT, process_sigint_for_input);
    signal(SIGQUIT, SIG_IGN);
}
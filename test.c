#include "cub3d.h"

int main()
{
    t_main main;

    ft_bzero(&main, sizeof(t_main));
    main.file_name = ft_strdup("map.cub");
    // signal(SIGCHLD, SIG_IGN);
    play_sound(&main);
    printf("Playing sound... %s\n", main.file_name);
    exit_and_print("Game started successfully!", &main, CLOSE_FD);
    return 0;
}

void	play_sound(t_main *main)
{

	pid_t	pid;
	int		devnull;
    bool is_open = true;
    
	if (is_open) 
    {
        pid = fork();
        if (pid == 0)
        {
            devnull = open("/dev/null", O_WRONLY);
            if (devnull == -1)
            	exit_and_print("open /dev/null failed", main, DONT_CLOSE_FD);
            dup2(devnull, STDOUT_FILENO);
            dup2(devnull, STDERR_FILENO);
            close(devnull);
            execlp("ffplay", "ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet",
                "assets/sound/shot.mp3 ", (char *) NULL);
        }
        else if (pid > 0)
            ;
        else
            exit_and_print("fork failed", main, DONT_CLOSE_FD);
    }  
}
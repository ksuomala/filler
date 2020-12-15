/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:59:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/12 21:24:47 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

// Read the stdout/in, take the size of the board. Board width and height. Divide the screen. Most of it should be the board and that should scale
// according to the size so it always takes the same area of the screen. I want to make bars on the right side with the player colors, names and
// scores. Maybe buttons where I could change the players.


void ft_error(int msg)
{
    ft_printf("error %d", msg);
    exit(0);
}



void    ft_score(t_filler *filler, char *line)
{
    char **scoreline;

    scoreline = ft_strsplit(line, ' ');
    filler->score_1 = ft_strdup(scoreline[3]);
    ft_strdel(&line);
    ft_free2d((void**)scoreline);
    get_next_line(0, &line);
    scoreline = ft_strsplit(line, ' ');
    filler->score_2 = ft_strdup(scoreline[3]);
    ft_printf("score %s, score %s\n", filler->score_1, filler->score_2);
    text_to_window(filler);
}

int game_over(t_filler *filler)
{
    char *line;

    line = NULL;
    while (!ft_strstr(line, "Plateau") && !ft_strstr(line, "=="))
    {
        ft_strdel(&line);
        if (!get_next_line(0, &line))
            break;
    }
    if (ft_strstr(line, "Plateau"))
    {
        ft_strdel(&line);
        return (0);
    }
    else
    {
        ft_score(filler, line);
        ft_strdel(&line);
        return (1);
    }
}

void    events(t_filler filler)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            exit(0);
    }
}

void    start(void)
{
    t_filler        data;
    
    ft_bzero(&data, sizeof(t_filler));
    data = get_data(data.win);
    if (SDL_Init(SDL_INIT_VIDEO))
        ft_printf("Error initializing SDL : %s", SDL_GetError());
    ft_printf("SDL initialized\n");
    data.win = SDL_CreateWindow("Filler", SDL_WINDOWPOS_UNDEFINED,\
    SDL_WINDOWPOS_CENTERED, (float)data.w / data.h * WIN_HT + 420, WIN_HT, 0);
    if (!data.win)
        ft_printf("error creating window");
    data.renderer = background(&data);
    while (1)
    {
        events(data);
        data.board = get_board(data.h, data.w);
        if (game_over(&data))
            break;
        game_to_window(data);
    }
    SDL_Delay(5000);
    SDL_DestroyWindow(data.win);
}

int main(void)
{
    start();
    SDL_Quit();
    return (0);
}       
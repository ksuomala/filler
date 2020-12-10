/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:59:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/10 18:53:36 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>
#include <SDL2/SDL.h>

// Read the stdout/in, take the size of the board. Board width and height. Divide the screen. Most of it should be the board and that should scale
// according to the size so it always takes the same area of the screen. I want to make bars on the right side with the player colors, names and
// scores. Maybe buttons where I could change the players.

typedef struct s_filler {
    SDL_Window      *win;
    SDL_Renderer    *renderer;
    int             h;
    int             w;
    char            *p1;
    char            *p2;
}               t_filler;

void ft_error(int msg)
{
    ft_printf("error");
    exit(0);
}

t_filler parse_data(SDL_Window *w)
{
    t_filler    new;
    char        *line;
    char        **size;
    
    new.win = w;
    while(get_next_line(0, &line))
    {
        if (ft_strstr(line, "exec p1"))
            if (!(new.p1 = ft_strdup(ft_strstr(line, "./") + 2)))
                ft_error(0);
        if (ft_strstr(line, "exec p2"))
            if (!(new.p2 = ft_strdup(ft_strstr(line, "./") + 2)))
                ft_error(0);
        if (ft_strstr(line, "Plateau"))
        {
            if (!(size = ft_strsplit(line, ' ')))
                ft_error(0);
            new.h = ft_atoi(size[1]);
            new.w = ft_atoi(size[2]);
            ft_free2d((void**)size);
        }
        free(line);
    }
    return (new);
}

int read_game(SDL_Window *win, SDL_Renderer *renderer)
{
   return (0);
}

SDL_Renderer *background(t_filler data)
{
    SDL_Renderer    *renderer;
    SDL_Rect        board;

    renderer = SDL_CreateRenderer(data.win, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
    SDL_RenderClear(renderer);
    board.h = WIN_HT * 0.9;
    board.w = WIN_WT * 0.6;
    board.x = WIN_HT * 0.05;
    board.y = WIN_HT * 0.05;
    SDL_SetRenderDrawColor(renderer, 69, 69, 69, 255);
    SDL_RenderFillRect(renderer, &board);
    SDL_RenderPresent(renderer);
    return (renderer);
}

void    start(void)
{
    t_filler        data;
    
    ft_bzero(&data, sizeof(t_filler));
    if (SDL_Init(SDL_INIT_VIDEO))
        ft_printf("Error initializing SDL : %s", SDL_GetError());
    ft_printf("SDL initialized\n");
    data.win = SDL_CreateWindow("Filler", SDL_WINDOWPOS_CENTERED,\
    SDL_WINDOWPOS_CENTERED, WIN_WT, WIN_HT, 0);
    if (!data.win)
        ft_printf("error creating window");
    data = parse_data(data.win);
    data.renderer = background(data);

    SDL_Delay(5000);
    SDL_DestroyWindow(data.win);
}

int main(void)
{
    start();
    SDL_Quit();
    return (0);
}       
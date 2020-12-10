/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:59:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/10 18:18:03 by ksuomala         ###   ########.fr       */
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

t_filler board_size(SDL_Window *w, SDL_Renderer *r)
{
    t_filler    new;
    char        *line;
    char        **size;
    
    new.win = w;
    new.renderer = r;
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
    t_filler game;

    game = board_size(win, renderer);
}

SDL_Renderer *render(SDL_Window *window)
{
    SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 69, 69, 69, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    return (renderer);
}

int main(void)
{
    SDL_Window      *win;
    SDL_Renderer    *renderer;
    SDL_Rect sq;
    
    if (SDL_Init(SDL_INIT_VIDEO))
        ft_printf("Error initializing SDL : %s", SDL_GetError());
    ft_printf("SDL initialized\n");
    win = SDL_CreateWindow("Filler", SDL_WINDOWPOS_CENTERED,\
    SDL_WINDOWPOS_CENTERED, WIN_WT, WIN_HT, 0);
    if (!win)
        ft_printf("error creating window");

    renderer = render(win);
    read_game(win, renderer);
    SDL_Delay(3000);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return (0);
}       
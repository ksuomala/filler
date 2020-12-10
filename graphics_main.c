/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:59:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/10 14:20:58 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>
#include <SDL2/SDL.h>

// Read the stdout/in, take the size of the board. Board width and height. Divide the screen. Most of it should be the board and that should scale
// according to the size so it always takes the same area of the screen. I want to make bars on the right side with the player colors, names and
// scores. Maybe buttons where I could change the players.

typedef struct s_window {
    SDL_Window *win;
    SDL_Surface *surf;
    SDL_Renderer *render;
}               t_win;

int read_output(t_win *win)
{

}

int main(void)
{
    t_win   win;
    SDL_Rect sq;
    
    if (SDL_Init(SDL_INIT_VIDEO))
        ft_printf("Error initializing SDL : %s", SDL_GetError());
    ft_printf("SDL initialized\n");
    win.win = SDL_CreateWindow("Filler", SDL_WINDOWPOS_CENTERED,\
    SDL_WINDOWPOS_CENTERED, WIN_WT, WIN_HT, 0);
    if (!win.win)
        ft_printf("error creating window");
    win.surf = SDL_GetWindowSurface(win.win);
    win.render = SDL_CreateRenderer(win.win, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(win.render, 69, 69, 69, 255);
    SDL_RenderClear(win.render);

    sq.h = 12;
    sq.w = 10;
    sq.y = WIN_HT / 2 - sq.h / 2;
    sq.x = WIN_WT / 2 - sq.w / 2;

    SDL_SetRenderDrawColor(win.render, 200, 200, 200, 255);
    SDL_RenderFillRect(win.render, &sq);
    SDL_RenderPresent(win.render);
    SDL_Delay(3000);
    SDL_DestroyWindow(win.win);
    SDL_Quit();
    return (0);
}       
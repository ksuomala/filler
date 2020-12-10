/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:59:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/10 04:18:37 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>
#include <SDL2/SDL.h>

int main(void)
{
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Renderer *renderer;
    SDL_Rect sq;
    
    if (SDL_Init(SDL_INIT_VIDEO))
        ft_printf("Error initializing SDL : %s", SDL_GetError());
    ft_printf("SDL initialized\n");
    window = SDL_CreateWindow("Filler", SDL_WINDOWPOS_CENTERED,\
    SDL_WINDOWPOS_CENTERED, WIN_WT, WIN_HT, 0);
    if (!window)
        ft_printf("error creating window");
    surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 69, 69, 69, 255);
    SDL_RenderClear(renderer);

    sq.h = 12;
    sq.w = 10;
    sq.y = WIN_HT / 2 - sq.h / 2;
    sq.x = WIN_WT / 2 - sq.w / 2;

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &sq);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return (0);
}       
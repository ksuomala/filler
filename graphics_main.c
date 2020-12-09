/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:59:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/10 00:53:37 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>
#include <SDL2/SDL.h>

int main(void)
{
    SDL_Window *window;
    if (SDL_Init(SDL_INIT_VIDEO))
        ft_printf("Error initializing SDL : %s", SDL_GetError());
    ft_printf("SDL initialized\n");
    window = SDL_CreateWindow("Filler", SDL_WINDOWPOS_CENTERED,\
    SDL_WINDOWPOS_CENTERED, WIN_WT, WIN_HT, 0);
    if (!window)
        ft_printf("error creating window");
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return (0);
}       
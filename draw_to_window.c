/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_to_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:11:16 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/15 17:20:20 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void    square_to_window(t_filler filler, int y, int x)
{
    SDL_Rect    square;

    if (filler.board[y][x] == 'O')
        SDL_SetRenderDrawColor(filler.renderer, 0, 0, 255, 255);
    else if (filler.board[y][x] == 'o')
        SDL_SetRenderDrawColor(filler.renderer, 50, 50, 255, 230);
    else if (filler.board[y][x] == 'X')
        SDL_SetRenderDrawColor(filler.renderer, 255, 0, 0, 255);
    else if (filler.board[y][x] == 'x')
        SDL_SetRenderDrawColor(filler.renderer, 255, 50, 50, 230);
    square.h = filler.square_size;
    square.w = square.h;
    square.x = WIN_HT * 0.05 + square.h * x;
    square.y = WIN_HT * 0.05 + square.h * y;
    SDL_RenderFillRect(filler.renderer, &square);
}

int game_to_window(t_filler filler)
{
    int x;
    int y;
    static char **current;

    x = -1;
    y = -1;
    while(++y < filler.h)
    {
        while(++x < filler.w)
        {
 //           ft_putchar(filler.board[y][x]);
            if (filler.board[y][x] != '.' && (!current || filler.board[y][x] != current[y][x]))
                square_to_window(filler, y, x);
        }
        x = -1;
//        ft_n(1);
    }
    if (!(current = cpy_board(filler.board, filler.h + 1)))
        ft_error(5);
    SDL_Delay(100);
    SDL_RenderPresent(filler.renderer);
   return (0);
}

void        players_to_window(SDL_Renderer *renderer)
{

TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

ft_printf("This is just for test purposes\n");
SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

SDL_Rect Message_rect; //create a rect
Message_rect.x = 100;  //controls the rect's x coordinate 
Message_rect.y = 100; // controls the rect's y coordinte
Message_rect.w = 100; // controls the width of the rect
Message_rect.h = 100; // controls the height of the rect


//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

SDL_RenderPresent(renderer);
SDL_Delay(4000);
//Don't forget to free your surface and texture
SDL_FreeSurface(surfaceMessage);
SDL_DestroyTexture(Message);
}

SDL_Renderer *background(t_filler *data)
{
    SDL_Renderer    *renderer;
    SDL_Rect        board;

    renderer = SDL_CreateRenderer(data->win, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
    SDL_RenderClear(renderer);
    board.h = WIN_HT * 0.9;
    data->square_size = board.h / data->h;
    board.w = data->square_size * data->w;
    board.x = WIN_HT * 0.05;
    board.y = WIN_HT * 0.05;
    SDL_SetRenderDrawColor(renderer, 69, 69, 69, 255);
    SDL_RenderFillRect(renderer, &board);
    players_to_window(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    return (renderer);
}

void    text_to_window(t_filler *filler)
{
    return ;
}
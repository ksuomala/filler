/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuomala <ksuomala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 17:59:31 by ksuomala          #+#    #+#             */
/*   Updated: 2020/12/12 19:58:23 by ksuomala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "filler.h"
#include <fcntl.h>
#include <SDL2/SDL.h>

// Read the stdout/in, take the size of the board. Board width and height. Divide the screen. Most of it should be the board and that should scale
// according to the size so it always takes the same area of the screen. I want to make bars on the right side with the player colors, names and
// scores. Maybe buttons where I could change the players.


typedef struct s_filler 
{
    SDL_Window      *win;
    SDL_Renderer    *renderer;
    char            **board;
    int             h;
    int             w;
    int             square_size;
    char            *p1;
    char            *p2;
    char            *score_1;
    char            *score_2;
}               t_filler;

void ft_error(int msg)
{
    ft_printf("error %d", msg);
    exit(0);
}

char    **get_board(size_t height, size_t width)
{
    int y;
    char    *line;
    char    **board;

    y = -1;
    if (!(board = ft_memalloc(sizeof(char**) * (height + 1))))
        ft_error(0);
    get_next_line(0, &line);
    ft_strdel(&line);
    while (++y < height)
    {
        get_next_line(0, &line);
        if (!(board[y] = ft_strsub(line, 4, width)))
            ft_error(1);
        ft_strdel(&line);
    }
    return (board);
}

t_filler get_data(SDL_Window *w)
{
    t_filler    new;
    char        *line;
    char        **size;
    
 //   new.win = w;
    while(get_next_line(0, &line))
    {
        if (ft_strstr(line, "exec p1"))
            if (!(new.p1 = ft_strdup(ft_strstr(line, "./") + 2)))
                ft_error(3);
        if (ft_strstr(line, "exec p2"))
            if (!(new.p2 = ft_strdup(ft_strstr(line, "./") + 2)))
                ft_error(4);
        if (ft_strstr(line, "Plateau"))
        {
            if (!(size = ft_strsplit(line, ' ')))
                ft_error(2);
            new.h = ft_atoi(size[1]);
            new.w = ft_atoi(size[2]);
            ft_free2d((void**)size);
            free(line);
            break;
        }
        free(line);
    }
    return (new);
}

char **cpy_board(char **board, size_t n)
{
    int     i;
    char    **cpy;

    cpy = ft_memalloc(sizeof(char**) * n);
    if (!cpy)
        return (NULL);
    i = -1;
    while (++i < n - 1)
        if (!(cpy[i] = ft_strdup(board[i])))
            return (NULL);
    return (cpy);
}

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
 //   SDL_RenderPresent(renderer);
    return (renderer);
}

void    text_to_window(t_filler *filler)
{
    return ;
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
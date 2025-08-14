/**
 * @file
 * @brief Заголовочный файл основных функций тетриса.
 */

#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../components/specification.h"
#include "defines.h"
#include "fsm.h"
#include "types.h"

void userInput(UserAction_t action, bool hold);

Params_t *create_prms();
void reset_prms(Params_t *prms);
Figureinfo_t *create_figure_info();
void reset_figure_info(Figureinfo_t *current_figure);
GameInfo_t *get_field_info(Figureinfo_t *figureinfo);
GameInfo_t *create_field_info(Figureinfo_t *figure_info);
void reset_field_info(GameInfo_t *field_info, Figureinfo_t *figure_info);

void clear_or_draw_position(Params_t *prms, bool param);
void hi_score(GameInfo_t *gameinfo);
int get_block_coord(int figure_type, int figure_state, int block_number,
                    int coord);
void chech_timer(Params_t *prms);

GameInfo_t updateCurrentState();

#endif  // BACKEND_H

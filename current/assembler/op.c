/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/09/05 22:45:14 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

const t_op    g_op_tab[17] =
{
/*
**	text		#args		arg types									op code		#cycles			real name		see note;
*/
	{"live", 	1,	{T_DIR}, 												1, 		10, 	"alive", 				0, 0},//5
	{"ld", 		2,	{T_DIR | T_IND, T_REG}, 								2, 		5, 		"load", 				1, 0},//5
	{"st", 		2,	{T_REG, T_IND | T_REG}, 								3, 		5, 		"store", 				1, 0},//5
	{"add", 	3,	{T_REG, T_REG, T_REG}, 									4, 		10, 	"addition", 			1, 0},//5
	{"sub", 	3,	{T_REG, T_REG, T_REG}, 									5, 		10, 	"subtraction",			1, 0},//5
	{"and", 	3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	6, 		6, 		"and  r1 & r2 -> r3",	1, 0},//5
	{"or", 		3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	7, 		6, 		"or   r1 | r2 -> r3",	1, 0},//5
	{"xor", 	3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	8, 		6, 		"xor  r1 ^ r2 -> r3",	1, 0},//5
	{"zjmp", 	1,	{T_DIR}, 												9, 		20, 	"jump if zero", 		0, 1},//3
	{"ldi", 	3,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			10, 	25,	 	"load index", 			1, 1},//5
	{"sti", 	3,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 			11, 	25,	 	"store index", 			1, 1},//5
	{"fork", 	1,	{T_DIR}, 												12, 	800, 	"fork", 				0, 1},//3
	{"lld", 	2,	{T_DIR | T_IND, T_REG}, 								13, 	10, 	"long load", 			1, 0},//
	{"lldi", 	3,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			14, 	50,	 	"long load index", 		1, 1},//
	{"lfork", 	1,	{T_DIR}, 												15, 	1000,	"long fork", 			0, 1},//3
	{"aff", 	1,	{T_REG}, 												16, 	2, 		"ascii to stdout",		1, 0},//3
	{0, 		0,	{0}, 													0, 		0, 		0,						0, 0}
};
/*
** 'r'		 '%'	  'num' | ':'
** reg = 01; dir = 10; ind = 11;
** EDIT: FIRST NUM == 1 ? ACB : NO ACB;
**{1, 1} is only for index commands, always 3 args;
**{1, 0} are simple codes, load store math and aff, 2 or 3 args;
**{0, 1} is forks and jump, only takes 1 direct arg;
**{0, 0} is live only, 1 direct arg but 4 bytes after op code;
**
**if first num == 0, whole command will be 3 bytes. 1 byte opcode, no ACB byte, 2 byte direct.
**if second num == 1, last arg will be 1 byte REG, except sti where IND or REG is interpreted as 2 byte IND.
*/
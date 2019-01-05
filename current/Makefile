# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jochang <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/10 15:16:58 by jochang           #+#    #+#              #
#    Updated: 2019/01/05 01:44:26 by smonroe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASSEMBLER = asm

COREWAR = corewar

UTIL = util/pc_app.c \
	util/pc_free.c \
	util/pc_new.c \
	util/pc_rem_head.c \
	util/pc_rem.c \
	util/pc_scan_rem.c \
	util/pc_scan_op.c \

OP = op/op_add.c \
	op/op_aff.c \
	op/op_and.c \
	op/op_fork.c \
	op/op_ld.c \
	op/op_ldi.c \
	op/op_lfork.c \
	op/op_live.c \
	op/op_lld.c \
	op/op_lldi.c \
	op/op_or.c \
	op/op_st.c \
	op/op_sti.c \
	op/op_sub.c \
	op/op_xor.c \
	op/op_zjmp.c \

ASRC = assembler/asm.c \
	assembler/op.c \
	assembler/get_bytecode.c \
	assembler/get_header.c \
	assembler/make_cor.c \
	assembler/t_byte_fun.c \
	assembler/label_fun.c \
	assembler/arg_fun.c \

CSRC = core_war/corewar.c \
	core_war/ft_setopt.c \
	core_war/parse_file.c \
	core_war/init_vm.c \
	core_war/op_fn.c \
	core_war/init_env.c \
	core_war/ft_memrcpy.c \
	core_war/ft_memfree.c \
	core_war/acb_len.c \
	core_war/display.c \
	core_war/mem_func.c

AINC = -I inc/asm.h \
	-I inc/op.h \
	-I inc/err.h \

CINC = -I inc/corewar.h \
	-I inc/op.h \
	-I inc/err.h \
	-lncurses

ERR = err/err_invarg.c \
	err/err_invfile.c \
	err/err_invflag.c \
	err/err_invheader.c \
	err/err_invop.c \
	err/err_malloc.c \
	err/err_nofile.c \

GUI = gui/init_gui.c \
	gui/update_memblock.c \
	gui/init_infoblock.c \

GCC = gcc
CFLAGS = -Wall -Wextra -Werror
LFT = libft/libft.a
NCR = -lncurses

.PHONY: all clean fclean re lldb fsan
all: $(COREWAR)

$(COREWAR):
	@make -C libft
	@echo "\033[32mmaking assembler...\033[0m"
	@$(GCC) $(CFLAGS) -o $(ASSEMBLER) $(ASRC) $(ERR) \
	$(AINC) $(LFT)
	@echo "\033[32mmaking corewar...\033[0m"
	@$(GCC) $(CFLAGS) -o $(COREWAR) $(CSRC) $(ERR) $(UTIL) $(OP) $(GUI)\
	$(CINC) $(LFT) $(NCR)

clean:
	@make -C libft clean
	@echo "\033[33mcleaning repository...\033[0m"
	@rm -f inc/*.gch

fclean: clean
	@make -C libft fclean
	@echo "\033[33mremoving executables...\033[0m"
	@rm -f $(ASSEMBLER)
	@rm -f $(COREWAR)

re: fclean all

lldb:
	@make -C libft
	@echo "\033[32mmaking lldb executable...\033[0m"
	@$(GCC) $(CFLAGS) -o $(ASSEMBLER) $(ASRC) $(ERR) $(INC) $(LFT) -g
	@$(GCC) $(CFLAGS) -o $(COREWAR) $(CSRC) $(ERR) $(UTIL) $(OP) $(CINC) $(LFT) -g

fsan:
	make -C libft
	echo "\033[32mmaking fsan executable...\033[0m"
	@$(GCC) $(CFLAGS) -o $(ASSEMBLER) $(ASRC) $(ERR) $(INC) $(LFT) -g -fsanitize=address
	@$(GCC) $(CFLAGS) -o $(COREWAR) $(CSRC) $(ERR) $(UTIL) $(OP) $(CINC) $(LFT) -g -fsanitize=address

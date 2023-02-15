/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:17:52 by marius            #+#    #+#             */
/*   Updated: 2022/04/26 10:24:26 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include <stdio.h>

# define ALLOC_SIZE 60
# define ULL unsigned long long

typedef struct s_print
{
	char	flags[5];
	size_t	width;
	int		prec;
	char	length[3];
	char	type;
	size_t	index;
	size_t	printed;
	size_t	ret;
	va_list	args;
	char	*buff;
	int		var;
}				t_print;

int		ft_printf(const char *format, ...);
void	handle_proc(t_print *tab);
void	handle_c(t_print *tab);
void	handle_s(t_print *tab);
void	handle_p(t_print *tab);
void	handle_d_i(t_print *tab);
void	handle_o(t_print *tab);
void	handle_u(t_print *tab);
void	handle_x(int var, t_print *tab);
void	handle_f(t_print *tab);
char	*abs_itoa_long(unsigned long long n);
void	add_flags(const	char *format, t_print *tab);
void	add_width(const	char *format, t_print *tab);
void	add_prec(const char *format, t_print *tab);
void	add_length(const char *format, t_print *tab);
void	in_double(char **num, long double f, t_print *tab);
void	ulong_init(unsigned long long *a, t_print *tab);
void	in_octave(char **dec, unsigned long long o);
void	x_minflag(ULL x, int len, char *num, t_print *tab);
void	x_zeroflag(ULL x, int len, char *num, t_print *tab);
void	x_noflag(ULL x, int len, char *num, t_print *tab);
void	add_to_buff(char c, t_print *tab);
void	add_str_to_buff(char *str, t_print *tab);
int		is_inf(long double d);
int		is_nan(long double d);

#endif
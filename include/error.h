/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:06:36 by echatela          #+#    #+#             */
/*   Updated: 2025/12/15 15:13:56 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

int	err_per(int code, const char *ctx);

int	fill1(char *buf, const char *s);
int	fill2(char *buf, const char *a, const char *b);
int	fill3(char *buf, const char *a, const char *b, const char *c);

#endif
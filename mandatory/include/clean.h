/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:07:14 by afatimi           #+#    #+#             */
/*   Updated: 2024/02/13 21:07:29 by afatimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>
#include <stdlib.h>
#include <structs.h>

void	free_textures(mlx_texture_t **textures);
void	free_lst_map(t_map_data *ptr);
void	destroy_map(t_map *map);
void	free_texture_names(char **texture_names);

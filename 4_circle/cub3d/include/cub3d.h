#ifndef CUB#D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_data t_data;

struct s_data
{
	void	*mlx;
	void	*win;
};

void	data_mlx_init(t_data *data);

#endif
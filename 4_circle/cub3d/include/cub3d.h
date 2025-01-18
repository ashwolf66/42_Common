#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define WIDTH 854
# define HEIGHT 480

typedef struct s_data t_data;

struct s_data
{
	void	*mlx;
	void	*win;
};

void	data_mlx_init(t_data *data);
void	event_init(t_data *data);
int		close_handler(t_data *data);
int		key_handler(int keysym, t_data *data);

#endif
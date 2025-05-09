#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error: Incorrect number of arguments.\n");
		return (1);
	}
	if (!check_extension(argv[1]))
	{
		printf("Error: Expected [map_name].cub\n");
		return (1);
	}

	init_settings(&game.settings);
	parse_file(argv[1], &game.settings);
	init_game(&game); // crea la ventana

	game.started = 0;
	game.intro_img = mlx_xpm_file_to_image(
		game.img.mlx, "assets/intro.xpm", &game.intro_w, &game.intro_h);
	if (!game.intro_img)
	{
		printf("Error: no se pudo cargar la imagen intro.xpm\n");
		return (1);
	}

	mlx_loop_hook(game.img.mlx, render_frame, &game);
	mlx_key_hook(game.img.win, key_handler, &game);
	mlx_hook(game.img.win, 17, 0, close_window, &game);

	mlx_loop(game.img.mlx);
	return (0);
}

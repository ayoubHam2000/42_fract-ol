# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <SDL2/SDL.h>
# include <cuda_runtime.h>
# include <sys/time.h>

# define ZOOM 0.9
# define TRAN 0.2
# define TITLE "Fract"

void	set_colors(int *map)
{
	map[0] = 0x0009012f;
	map[1] = 0x00040449;
	map[2] = 0x00000764;
	map[3] = 0x000c2c8a;
	map[4] = 0x001852b1;
	map[5] = 0x00397dd1;
	map[6] = 0x0086b5e5;
	map[7] = 0x00d3ecf8;
	map[8] = 0x00f1e9bf;
	map[9] = 0x00f8c95f;
	map[10] = 0x00ffaa00;
	map[11] = 0x00cc8000;
	map[12] = 0x00995700;
	map[13] = 0x006a3403;
	map[14] = 0x00421e0f;
	map[15] = 0x0019071a;
}

typedef double t_double;

struct t_complex
{
	double	a;
	double	b;
};

struct GPU_Surface
{
	int 	w;
	int 	h;
	int 	pitch;
	void	*pixels;
	Uint8 BytesPerPixel;
	size_t pixel_size;
};


struct t_global
{
	int						w_size;
  int         	depth;
  t_complex 		x_bound;
	t_complex 		y_bound;
	t_double  		step_x;
	t_double  		step_y;

	int						color_map[16];
	int 					*d_color_map;
  GPU_Surface 	gpu_surface;
	SDL_Window		*win;
	SDL_Surface   *win_surface;
	void					*f;
	t_double  		zoom;
	int						m_wheel;
	int						m_x;
	int						m_y;
	int						quit;
};

struct GPUData {
	int						w_size;
  int         	depth;
  t_complex 		x_bound;
	t_complex 		y_bound;
	t_double  		step_x;
	t_double  		step_y;
};

void cpu_ft_put_pixel(SDL_Surface* surface, unsigned int x, unsigned int y, unsigned int color)
{
	if (y >= (unsigned int)surface->h || x >= (unsigned int)surface->w)
			return ;
	*((Uint32*)((Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel)) = color;
}

__device__ void ft_put_pixel(GPU_Surface surface, unsigned int x, unsigned int y, unsigned int color)
{
	if (y >= (unsigned int)surface.h || x >= (unsigned int)surface.w)
			return ;
	*((Uint32*)((Uint8*)surface.pixels + y * surface.pitch + x * surface.BytesPerPixel)) = color;
}


__device__ void	trans_iter(double a, double b, int *iter)
{
	t_double	log_zn;
	t_double	nu;

	log_zn = log(a * a + b * b) / 2;
	nu = log(log_zn / __logf(2)) / __logf(2);
	*iter = *iter + 1 - nu;
}

__device__ int	mandelbrot_set(int depth, t_double X, t_double Y)
{
	int				iter;
	double		xtemp;
  double 		a = 0.0;
  double 		b = 0.0;

  iter = 0;
  while (a * a + b * b <= 4 && iter < depth)
  {
    xtemp = a * a - b * b + X;
    b = 2 * a * b + Y;
    a = xtemp;
    iter++;
  }
  if (iter < depth)
	{
    trans_iter(a, b, &iter);
		return (iter % 16);
	}
	return 0;
}


__global__ void	graph_loop(unsigned int *ptr, GPUData data, int start_x, int start_y, int *map)
{
	int x = blockDim.x * blockIdx.x	+ threadIdx.x + start_x;
	int y = blockDim.y * blockIdx.y	+ threadIdx.y + start_y;
	


	if (x >= data.w_size || y >= data.w_size)
		return;

	t_double X = data.step_x * x + data.x_bound.a;
	t_double Y = data.step_y * y + data.y_bound.a;
	int color = mandelbrot_set(data.depth, X, Y);
	ptr[x + y * data.w_size] = map[color];
}


// unsigned int *d_pixels;
// int size = 4 * 1000 * 1000;
// cudaMalloc(&d_pixels, size);

void	fractol_frame(t_global *global)
{
	unsigned int *d_pixels = (unsigned int*)(global->gpu_surface.pixels);
	
	// cudaStream_t streams[4];
	// cudaStreamCreate(&streams[0]);
	// cudaStreamCreate(&streams[1]);
	// cudaStreamCreate(&streams[2]);
	// cudaStreamCreate(&streams[3]);

	GPUData gpu_data = *((GPUData *)global);
	// graph_loop<<<dim3(16, 16), dim3(32, 32), 0, streams[0]>>>(d_pixels, gpu_data, 0, 0, global->d_color_map);
	// graph_loop<<<dim3(16, 16), dim3(32, 32), 0, streams[1]>>>(d_pixels, gpu_data, 512, 0, global->d_color_map);
	// graph_loop<<<dim3(16, 16), dim3(32, 32), 0, streams[2]>>>(d_pixels, gpu_data, 0, 512, global->d_color_map);
	// graph_loop<<<dim3(16, 16), dim3(32, 32), 0, streams[3]>>>(d_pixels, gpu_data, 512, 512, global->d_color_map);
	graph_loop<<<dim3(32, 32), dim3(32, 32)>>>(d_pixels, gpu_data, 0, 0, global->d_color_map);
	cudaDeviceSynchronize();


	//update
	cudaError_t err = cudaSuccess;
	err = cudaMemcpy(global->win_surface->pixels, d_pixels, 4 * global->w_size * global->w_size, cudaMemcpyDeviceToHost);
	if (err != cudaSuccess) {
    printf("Failed (error code %s)!\n", cudaGetErrorString(err));
    exit(EXIT_FAILURE);
	}
	
	SDL_UpdateWindowSurface(global->win);
}

inline void on_mouse_wheel(int y, t_global *global)
{
	global->m_wheel = y;
}

inline void on_mouse_move(int x, int y, t_global *global)
{
	global->m_x = x;
	global->m_y = y;
}

void perform_events(t_global *global)
{
	if (global->m_wheel)
	{
		global->zoom += ZOOM * global->m_wheel * global->zoom;

		// double dir_x = TRAN * (1.0 * global->m_x / global->w_size - 0.5); 
		// double dir_y = TRAN * (1.0 * global->m_y / global->w_size - 0.5);
		// printf("%d %d %lf %lf\n", global->m_x, global->m_y, dir_x, dir_y);


		double x_a = global->x_bound.a;
		double x_b = global->x_bound.b;
		double y_a = global->y_bound.a;
		double y_b = global->y_bound.b;

		double dir_x = (1.0 * global->m_x / global->w_size);
		double dir_y = (1.0 * global->m_y / global->w_size);
		double p_x = x_a + (x_b - x_a) * dir_x;
		double p_y = y_a + (y_b - y_a) * dir_y;
	
		printf("%d %d %lf %lf\n", global->m_x, global->m_y, dir_x, dir_y);

		float zoom = 1.2;
		if (global->m_wheel > 0) {
			zoom = 0.9;
		} else {
			zoom = 1.2;
		}

		global->x_bound.a = (x_b + x_a - zoom * (x_b - x_a)) / 2.0;
		global->x_bound.b = (x_b + x_a + zoom * (x_b - x_a)) / 2.0;
		global->y_bound.a = (y_b + y_a - zoom * (y_b - y_a)) / 2.0;
		global->y_bound.b = (y_b + y_a + zoom * (y_b - y_a)) / 2.0;

		x_a = global->x_bound.a;
		x_b = global->x_bound.b;
		y_a = global->y_bound.a;
		y_b = global->y_bound.b;


		global->x_bound.a = p_x - (x_b - x_a) * (dir_x);
		global->x_bound.b = p_x + (x_b - x_a) * (1.0 - dir_x);
		global->y_bound.a = p_y - (y_b - y_a) * (dir_y);
		global->y_bound.b = p_y + (y_b - y_a) * (1.0 - dir_y);


		// global->x_bound.a += dir_x;
		// global->x_bound.b += dir_x;
		// global->y_bound.a += dir_y;
		// global->y_bound.b += dir_y;

		// global->x_bound.a = -2 / global->zoom;
		// global->x_bound.b = 2 / global->zoom;
		// global->y_bound.a = -2 / global->zoom;
		// global->y_bound.b = 2 / global->zoom;
		global->step_x = (global->x_bound.b - global->x_bound.a) / global->w_size;
		global->step_y = (global->y_bound.b - global->y_bound.a) / global->w_size;
	}
}

void	fractol_loop(t_global *global)
{
	SDL_Event e;
	struct timeval t1;
	struct timeval t2;

	while (!global->quit)
	{
		gettimeofday(&t1, NULL);
		fractol_frame(global);
		gettimeofday(&t2, NULL);
		printf("---> time %ld\n", (t2.tv_sec * 1000000 + t2.tv_usec) - (t1.tv_sec * 1000000 + t1.tv_usec));
		global->m_wheel = 0;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				global->quit = 1;
			else if (e.type == SDL_MOUSEWHEEL)
				on_mouse_wheel(e.wheel.y, global);
			else if (e.type == SDL_MOUSEMOTION)
				on_mouse_move(e.motion.x, e.motion.y, global);
		}
		perform_events(global);
	}
}


t_global	*init_prog(void)
{
	t_global	*global;

	global = (t_global *)malloc(sizeof(t_global));
	if (!global)
		return (NULL);
	global->quit = 0;

	global->zoom = 1;
	global->x_bound.a = -2;
	global->x_bound.b = 2;
	global->y_bound.a = -2;
	global->y_bound.b = 2;


	set_colors(global->color_map);
	
	cudaMalloc(&(global->d_color_map), 16 * 4);
	
	cudaMemcpy(global->d_color_map, ((global->color_map)), 16 * 4, cudaMemcpyHostToDevice);
	global->f = NULL;
	return (global);
}

void    *init_sdl(t_global *global)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return NULL;
  SDL_Window* window = SDL_CreateWindow(
    TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    global->w_size, global->w_size, SDL_WINDOW_SHOWN);
  if (window == NULL)
    return NULL;
  global->win = window;
  global->win_surface = SDL_GetWindowSurface(global->win);
	global->gpu_surface.w = global->win_surface->w;
	global->gpu_surface.h = global->win_surface->h;
	global->gpu_surface.pitch = global->win_surface->pitch;
	global->gpu_surface.BytesPerPixel = global->win_surface->format->BytesPerPixel;
	global->gpu_surface.pixels = NULL;
	global->gpu_surface.pixel_size = global->gpu_surface.pitch * global->gpu_surface.h;

	cudaMalloc(&(global->gpu_surface.pixels), global->w_size * global->w_size * 4);

  return global;
}

int	main(int ac, char **av)
{
	t_global		*global;

	if (ac < 3)
	{
		printf("check args\n");
		exit(1);
	}
	global = init_prog();
	if (!global)
		return (1);
	global->w_size = atoi(av[1]);
	global->depth = atoi(av[2]);
	global->step_x = (global->x_bound.b - global->x_bound.a) / global->w_size;
	global->step_y = (global->y_bound.b - global->y_bound.a) / global->w_size;
	if (!init_sdl(global))
		return (1);
	fractol_loop(global);
	return (0);
}